/*
 * myusb.c
 *
 *  Created on: Feb 13, 2023
 *      Author: andrew
 */
#include "myusb.h"
#include "myprint.h"
#include "USB_Definitions.h"

/*-----------------------------------*/
/* --------------MACROS--------------*/
/*-----------------------------------*/



/*-----------------------------------*/
/* -----------DECLARATIONS-----------*/
/*-----------------------------------*/

USB_TypeDef * USBz;		/* USB Address Handle */

typedef struct //__attribute__((packed))
{
	__IO uint16_t ADDR_TX;
	__IO uint16_t COUNT_TX;
	__IO uint16_t ADDR_RX;
	__IO uint16_t COUNT_RX;
} BTableLayout;
volatile BTableLayout *my_btable;

volatile uint16_t buffer[32];
volatile uint8_t big_buffer[256];

uint8_t address = 0;

union Device{
	DeviceDescriptor descriptor;
	uint8_t data[18];
} device;

union Configuration{
	ConfigurationDescriptor descriptor;
	uint8_t data[9];
} configuration;

union Interface{
	InterfaceDescriptor descriptor;
	uint8_t data[9];
} interface;

union Endpoint{
	EndpointDescriptor descriptor;
	uint8_t data[7];
} endpoint;

union HID{
	HIDDescriptor descriptor;
	uint8_t data[9];
} hid;

Report report;


uint8_t const gamepad_report[63] = {
	0x05, 0x01,	//Generic Desktop
	0x09, 0x05, //Game Pad
	0xA1, 0x01,	//Collection(App)
	0xA1, 0x00,		//Collection (Physical)
	0x05, 0x09,			//Usage Page (Button)
	0x19, 0x01,			//Usage Min (Button 1)
	0x29, 0x06,			//Usage Max (Button 6)
	0x15, 0x00,			//Logical Min (0)
	0x25, 0x01,			//Logical Max (1)
	0x95, 0x06,			//Report Count (6)
	0x75, 0x01,			//Report Size (1)
	0x81, 0x02,			//Input (Variable)
	0x95, 0x01,			//Report Count (1)
	0x75, 0x02,			//Report Size (2)
	0x81, 0x01,			//Input (Cnst)
	0x05, 0x01,			//Usage Page (Generic)
	0x09, 0x32,			//Usage (z)
	0x09, 0x31,			//Usage (y)
	0x15, 0x00,			//Logical Min (0)
	0x26, 0xFF, 0x00,	//Logical Max (255)
	0x75, 0x08,			//Report Size (8)
	0x95, 0x02,			//Report Count (2)
	0x81, 0x82,			//Input (Variable)
	0x09, 0x30,			//Usage (X)
	0x16, 0xF8, 0xF8,	//Logical Min (-1800)
	0x26, 0x08, 0x07,	//Logical Max (1800)
	0x75, 0x10,			//Report Size (16)
	0x95, 0x01,			//Report Count (1)
	0x81, 0x82,			//Input (Variable)
	0xC0,			//End Collection
	0xC0		//End Collection
};

static void DescriptorInitialization(void);

static void EndpointCallback(void);
static void SetupCallback(void);

static void ReadEndpoint(uint8_t endpoint, uint8_t num_bytes);
static void WriteEndpoint(uint8_t endpoint, uint16_t* data_buffer, uint8_t num_bytes);

/*-----------------------------------*/
/* ----------INITIALIZATION----------*/
/*-----------------------------------*/

/*
 * Memory locations found in stm32f303xe.h
 */

void myusb_Initialize(void)
{
	//Initialize Descriptors
	DescriptorInitialization();

	//Initialize data in report
	report.members.brake = 0;
	report.members.throttle = 0;
	report.members.buttons = 0x00;
	report.members.steering = 0;

	//Map USBz to registers
	USBz = USB;
	my_btable = (BTableLayout*)0x40006000;

	//Enable clocks
	__HAL_RCC_USB_CLK_ENABLE();

	//Initialize interrupts + remapping
    __HAL_REMAPINTERRUPT_USB_ENABLE();
    HAL_NVIC_SetPriority(USB_HP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_HP_IRQn);
    HAL_NVIC_SetPriority(USB_LP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_IRQn);
    HAL_NVIC_SetPriority(USBWakeUp_RMP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USBWakeUp_RMP_IRQn);

	//Configure USB GPIO
    __HAL_RCC_GPIOG_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF14_USB;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);

	//Start USB peripheral
	USBz->CNTR = 1;	//Start transceiver

	for (int i = 0; i < 1000; i++)	//Delay according to datasheet
	{
		__asm volatile("nop");
	}

	//De-assert reset
	USBz->CNTR = 0;

	//Clear pending interrupts
	USBz->ISTR = 0U;

	//Enable these USB Interrupts
	USBz->CNTR |= USB_CNTR_RESETM | USB_CNTR_CTRM | USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_ESOFM;

	//Enable pull up to start enumeration
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);

}

void DescriptorInitialization(void)
{
	//Just device descriptor until I reach further requests
	device.descriptor.bLength = 18;
	device.descriptor.bDescriptorType = 0x01;
	device.descriptor.bcdUSB = 0x0110;
	device.descriptor.bDeviceClass = 0x00;
	device.descriptor.bDeviceSubClass = 0x00;
	device.descriptor.bDeviceProtocol = 0x00;
	device.descriptor.bMaxPacketSize0 = 64;
	device.descriptor.idVendor = 0x03ED;
	device.descriptor.idProduct = 0x2FF4;
	device.descriptor.bcdDevice = 0x0100;
	device.descriptor.iManufacturer = 0x00;
	device.descriptor.iProduct = 0x00;
	device.descriptor.iSerialNumber = 0x00;
	device.descriptor.bNumConfigurations = 1;

	configuration.descriptor.bLength = 0x09;
	configuration.descriptor.bDescriptorType = 0x02;
	configuration.descriptor.wTotalLength = 0x22;
	configuration.descriptor.bNumInterfaces = 0x01;
	configuration.descriptor.bConfigurationValue = 0x01;
	configuration.descriptor.iConfiguration = 0x00;
	configuration.descriptor.bmAttributes = 0xC0;
	configuration.descriptor.MaxPower = 0x00;

	interface.descriptor.bLength = 0x09;
	interface.descriptor.bDescriptorType = 0x04;
	interface.descriptor.bInterfaceNumber = 0x00;
	interface.descriptor.bAlternateSetting = 0x00;
	interface.descriptor.bNumEndpoints = 0x01;
	interface.descriptor.bInterfaceClass = 0x03;
	interface.descriptor.bInterfaceSubClass = 0x00;
	interface.descriptor.bInterfaceProtocol = 0x00;
	interface.descriptor.iInterface = 0x00;

	endpoint.descriptor.bLength = 0x07;
	endpoint.descriptor.bDescriptorType = 0x05;
	endpoint.descriptor.bEndpointAddress = 0x81;
	endpoint.descriptor.bmAttributes = 0x03;
	endpoint.descriptor.wMaxPacketSize = 0x40; //64 bytes
	endpoint.descriptor.bInterval = 0xA;

	hid.descriptor.bLength = 0x09;
	hid.descriptor.bDescriptorType = 0x21;
	hid.descriptor.bcdHID = 0x111;
	hid.descriptor.bCountryCode = 0x00;
	hid.descriptor.bNumDescriptors = 0x01;
	hid.descriptor.bDescriptorTypeReport = 0x22;
	hid.descriptor.wDescriptorLength = 0x3F; //63 bytes
}

/*-----------------------------------*/
/* -----------FUNCTIONS--------------*/
/*-----------------------------------*/

//Reads single byte past buffer if num_bytes is odd. Shouldn't result in any issues...
void ReadEndpoint(uint8_t endpoint, uint8_t num_bytes)
{
	if (num_bytes != 0)
	{
		if ((num_bytes % 2) != 0)
		{
			num_bytes += 1;
		}
		//Get offset to endpoint n RX buffer
		uint16_t offset = *(volatile uint16_t*)((endpoint*8 + 4) + 0x40006000);

		//Point to RX buffer
		volatile uint16_t* location = ((uint16_t*)(0x40006000 + offset));

		for (int i = 0; i < (num_bytes/2); i++)
		{
			buffer[i] = ((uint16_t*)location)[i];
		}
	}
}

//Reads single byte past data_buffer if num_bytes is odd. Shouldn't result in any issues...
void WriteEndpoint(uint8_t endpoint, uint16_t* data_buffer, uint8_t num_bytes)
{
	//Get offset to endpoint n TX buffer
	uint16_t offset = *(volatile uint16_t*)((endpoint*8) + 0x40006000);

	//Point to TX buffer
	volatile uint16_t* location = ((uint16_t*)(0x40006000 + offset));

	my_btable[endpoint].COUNT_TX = num_bytes;

	if ((num_bytes%2) != 0)
		num_bytes = (num_bytes/2) + 1;
	else
		num_bytes = num_bytes/2;

	for (int i = 0; i < num_bytes; i++)
	{
		location[i] = data_buffer[i];
	}


	//Set STAT_TX to VALID. Mask to avoid toggling the toggle bits.
	switch(endpoint)
	{
	case 0:
		USBz->EP0R = (1 << 4) | (USBz->EP0R & 0x8F9F);
		break;
	case 1:
		USBz->EP1R = (1 << 4) | (USBz->EP1R & 0x8F9F);
		break;
	case 2:
		USBz->EP2R = (1 << 4) | (USBz->EP2R & 0x8F9F);
		break;
	}
}

/*-----------------------------------*/
/* -----------INTERRUPTS-------------*/
/*-----------------------------------*/

//Isochronous and Bulk stuff
void USB_HP_IRQHandler(void)
{

}

//Everything
void USB_LP_IRQHandler(void)
{
	if (USBz->ISTR & USB_ISTR_CTR)
	{
		EndpointCallback();
	}
	if (USBz->ISTR & USB_ISTR_PMAOVR)
	{
		USBz->ISTR = ~USB_ISTR_PMAOVR;
		myprint("PMAOVR Interrupt\r\n");
	}
	if (USBz->ISTR & USB_ISTR_ERR)
	{
		USBz->ISTR = ~USB_ISTR_ERR;
		//myprint("ERR Interrupt\r\n");
	}
	if (USBz->ISTR & USB_ISTR_SUSP)
	{
		USBz->CNTR |= USB_CNTR_FSUSP;
		USBz->ISTR = ~USB_ISTR_SUSP;
		USBz->CNTR |= USB_CNTR_LPMODE;

		myprint("SUSP Interrupt\r\n");
	}
	if (USBz->ISTR & USB_ISTR_WKUP)
	{
		USBz->CNTR &= (uint16_t) ~(USB_CNTR_LPMODE);
		USBz->CNTR &= (uint16_t) ~(USB_CNTR_FSUSP);
		USBz->ISTR = ~USB_ISTR_WKUP;

		USBz->CNTR |= USB_CNTR_RESETM | USB_CNTR_CTRM | USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_ESOFM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM | USB_CNTR_SOFM;	//Enable these USB Interrupts
		//myprint("WKUP Interrupt\r\n");
	}
	if (USBz->ISTR & USB_ISTR_RESET)
	{
		USBz->ISTR = ~USB_ISTR_RESET;

		USBz->BTABLE = 0;

		//Configure endpoint0 as control, TX NAK, RX VALID
		USBz->EP0R = USB_EP_CONTROL | (2 << 4) | (3 << 12);

		//Configure endpoint1
		USBz->EP1R = USB_EP_INTERRUPT | (3 << 4) | (3 << 12) | USB_EP_DTOG_RX | USB_EP_DTOG_TX | 0x1;

		//Configure BTable for endpoint 0
		my_btable[0].ADDR_TX = (uint16_t)0x20;
		my_btable[0].COUNT_TX = (uint16_t)0;
		my_btable[0].ADDR_RX = (uint16_t)0x60;
		my_btable[0].COUNT_RX = (uint16_t)0x8400;

		//Configure BTable for endpoint 1
		my_btable[1].ADDR_TX = (uint16_t)0xA0;
		my_btable[1].COUNT_TX = (uint16_t)0;
		my_btable[1].ADDR_RX = (uint16_t)0xE0;
		my_btable[1].COUNT_RX = (uint16_t)0x8400;

		//Enable USB interrupts and peripheral
		USBz->CNTR |= USB_CNTR_RESETM | USB_CNTR_CTRM | USB_CNTR_WKUPM | USB_CNTR_SUSPM | USB_CNTR_ESOFM;
		USBz->DADDR = USB_DADDR_EF;

		myprint("Reset Interrupt\r\n");
	}
	if (USBz->ISTR & USB_ISTR_SOF)
	{
		USBz->ISTR = ~USB_ISTR_SOF;
	}
	if (USBz->ISTR & USB_ISTR_ESOF)
	{
		USBz->ISTR = ~USB_ISTR_ESOF;
	}
}

void EndpointCallback(void)
{
	//Loop to take care of all endpoint interrupts
	while (USBz->ISTR & USB_ISTR_CTR)
	{
		uint16_t ep = USBz->ISTR & USB_ISTR_EP_ID;
		uint16_t dir = USBz->ISTR & USB_ISTR_DIR;

		switch(ep)
		{
		case 0:	//Control
			if (dir) //OUT/SETUP
			{
				//See if SETUP has been received
				if (USBz->EP0R & USB_EP_SETUP)	//SETUP
				{
					uint8_t num_bytes = my_btable[0].COUNT_RX;
					if (num_bytes > 0)
					{
						ReadEndpoint(0, num_bytes);
					}

					USBz->EP0R = ((~USB_EP_CTR_RX) & USBz->EP0R) & 0x8F8F;

					SetupCallback();

					//Set RX to Valid
					USBz->EP0R = (1 << 12) | (USBz->EP0R & 0x9F8F);
				}
				else if (USBz->EP0R & USB_EP_CTR_RX) //OUT
				{
					USBz->EP0R = ((~USB_EP_CTR_RX) & USBz->EP0R) & 0x8F8F;

					uint8_t num_bytes = my_btable[0].COUNT_RX;

					//Set RX to Valid
					USBz->EP0R = (1 << 12) | (USBz->EP0R & 0x9F8F);
				}
			}
			else //IN
			{
				if ((address > 0))
				{
					USBz->DADDR = address | (1 << 7);	//Set address and enable
					address = 0;
				}
				USBz->EP0R = ((~USB_EP_CTR_TX) & USBz->EP0R) & 0x8F8F;
			}
		break;
		case 1: //Endpoint
			if (dir) //OUT/SETUP
			{

			}
			else //IN
			{
				WriteEndpoint(1, report.data, 5);

				USBz->EP1R = ((~USB_EP_CTR_TX) & USBz->EP1R) & 0x8F8F;
			}

		break;
		}
	}
}

void SetupCallback(void)
{
	//myprint("\tSETUP RECEIVED\r\n");
	uint8_t descriptor_type;

	//Determine Request
	uint8_t bmRequestType = ((uint8_t*)buffer)[0];
	uint8_t bRequest = ((uint8_t*)buffer)[1];
	uint16_t wValue = buffer[1];
	uint16_t wIndex = buffer[2];
	uint16_t wLength = buffer[3];

	USBRequestDirection direction 	= (bmRequestType & 0x80) ? REQUEST_D2H : REQUEST_H2D;
	USBRequestType type 			= (bmRequestType & 0x60) >> 5;
	USBRequestRecipient recipient 	= bmRequestType & 0x1F;

	//Handle Request
	switch(bRequest)
	{
	case GET_STATUS:
		myprint("\t\tGET_STATUS\r\n");
		break;
	case CLEAR_FEATURE:
		myprint("\t\tCLEAR_FEATURE\r\n");
		break;
	case SET_FEATURE:
		myprint("\t\tSET_FEATURE\r\n");
		break;
	case SET_ADDRESS:
		address = wValue & 0x7F;
		my_btable[0].COUNT_TX = 0;
		USBz->EP0R = (1 << 4) | (USBz->EP0R & 0x8F9F);

		myprint("\t\tSET_ADDRESS\r\n");

		break;
	case GET_DESCRIPTOR:
		myprint("\t\tGET_DESCRIPTOR\r\n");
		descriptor_type = (wValue >> 8) & 0xFF;

		switch(descriptor_type)
		{
		case 1:
			myprint("\t\t\tDevice\r\n");
			//myprint_hex(wLength);

			//Write data to PMA (sets endpoint transfer as valid)
			WriteEndpoint(0, device.data, device.descriptor.bLength);
			break;
		case 2:
			myprint("\t\t\tConfiguration\r\n");

			if (wLength == 9)
			{
				WriteEndpoint(0, configuration.data, configuration.descriptor.bLength);
			}
			else
			{
				int big_buffer_index = 0;
				for (int i = 0; i < configuration.descriptor.bLength; i++, big_buffer_index++)
				{
					big_buffer[big_buffer_index] = configuration.data[i];
				}
				for (int i = 0; i < interface.descriptor.bLength; i++, big_buffer_index++)
				{
					big_buffer[big_buffer_index] = interface.data[i];
				}
				for (int i = 0; i < endpoint.descriptor.bLength; i++, big_buffer_index++)
				{
					big_buffer[big_buffer_index] = endpoint.data[i];
				}
				for (int i = 0; i < hid.descriptor.bLength; i++, big_buffer_index++)
				{
					big_buffer[big_buffer_index] = hid.data[i];
				}

				WriteEndpoint(0, big_buffer, big_buffer_index);
			}

			break;
		case 34: //HID Report
			myprint("\t\t\tHID Report\r\n");

			WriteEndpoint(0, gamepad_report, 63);
			break;
		default:
			myprint("\t\t\tDefault: ");
			myprint_hex(descriptor_type);
			myprint("\r\n");
			break;
		}

		break;
	case SET_DESCRIPTOR:
		myprint("\t\tSET_DESCRIPTOR\r\n");
		break;
	case GET_CONFIGURATION:
		myprint("\t\tGET_CONFIGURATION\r\n");
		break;
	case SET_CONFIGURATION:
		myprint("\t\tSET_CONFIGURATION\r\n");
		break;
	case GET_INTERFACE:
		myprint("\t\tGET_INTERFACE\r\n");
		break;
	case SET_INTERFACE:
		myprint("\t\tSET_INTERFACE\r\n");
		break;
	case SYNCH_FRAME:
		myprint("\t\tSYNCH_FRAME\r\n");
		break;
	default:
		myprint("\t\tWE SHOULDN'T BE HERE IN THE SETUP\r\n");
		break;
	}
}
