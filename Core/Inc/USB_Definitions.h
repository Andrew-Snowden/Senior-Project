/*
 * USB_Definitions.h
 *
 * Created: 3/20/2022 12:50:38 PM
 *  Author: andre
 */ 


#ifndef USB_DEFINITIONS_H_
#define USB_DEFINITIONS_H_

#include <stdint.h>

typedef struct 
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
} DeviceDescriptor;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumInterfaces;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	uint8_t bmAttributes;
	uint8_t MaxPower;
} ConfigurationDescriptor;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
} InterfaceDescriptor;

typedef struct
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
} EndpointDescriptor;

typedef struct __attribute__((__packed__))
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdHID;
	uint8_t bCountryCode;
	uint8_t bNumDescriptors;
	uint8_t bDescriptorTypeReport;
	uint16_t wDescriptorLength;
} HIDDescriptor;

typedef struct 
{
	DeviceDescriptor device_descriptor;
	ConfigurationDescriptor config_descriptor;
	InterfaceDescriptor interface_descriptor;
	EndpointDescriptor endpoint_descriptors[2];
	HIDDescriptor hid_descriptors[2];
	uint8_t hid_report[255];
	uint16_t report_length;
} USBDescriptor;

typedef enum
{
	GET_STATUS = 0x0,
	CLEAR_FEATURE = 0x1,
	SET_FEATURE = 0x3,
	SET_ADDRESS = 0x5,
	GET_DESCRIPTOR = 0x6,
	SET_DESCRIPTOR = 0x7,
	GET_CONFIGURATION = 0x8,
	SET_CONFIGURATION = 0x9,
	GET_INTERFACE = 0x0A,
	SET_INTERFACE = 0x11,
	SYNCH_FRAME = 0x12
} USBRequest;

typedef enum
{
	REQUEST_H2D = 0,
	REQUEST_D2H = 1
} USBRequestDirection;

typedef enum
{
	REQUEST_STANDARD = 0,
	REQUEST_CLASS = 1,
	REQUEST_VENDOR = 2,
	REQUEST_RESERVED = 3
} USBRequestType;

typedef enum
{
	REQUEST_DEVICE = 0,
	REQUEST_INTERFACE = 1,
	REQUEST_ENDPOINT = 2,
	REQUEST_OTHER = 3
} USBRequestRecipient;

typedef struct  
{
	
} EffectBlock;

typedef struct  
{
	
} EnvelopeBlock;

typedef struct  
{
	
} ConditionBlock;

typedef struct
{
	
} PeriodicBlock;

typedef struct
{
	
} ConstantForceBlock;

typedef struct
{
	
} RampForceBlock;

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
	0x16, 0xC0, 0xC7,	//Logical Min (-14400)
	0x26, 0x40, 0x38,	//Logical Max (14400)
	0x75, 0x10,			//Report Size (16)
	0x95, 0x01,			//Report Count (1)
	0x81, 0x82,			//Input (Variable)
	0xC0,			//End Collection
	0xC0		//End Collection
};

uint8_t const ReportDescriptor[67] = {
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x04,                    // USAGE (Joystick)
	0xa1, 0x01,                    // COLLECTION (Application)
	0xa1, 0x00,                    //   COLLECTION (Physical)
	0x05, 0x09,                    //     USAGE_PAGE (Button)
	0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
	0x29, 0x16,                    //     USAGE_MAXIMUM (Button 22)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	0x75, 0x01,                    //     REPORT_SIZE (1)
	0x95, 0x16,                    //     REPORT_COUNT (22)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	0x75, 0x02,                    //     REPORT_SIZE (2)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)
	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x31,                    //     USAGE (Y)
	0x09, 0x32,                    //     USAGE (Z)
	0x09, 0x33,                    //     USAGE (Rx)
	0x09, 0x34,                    //     USAGE (Ry)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x04,                    //     REPORT_COUNT (4)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	0x09, 0x30,                    //     USAGE (X)
	0x16, 0xc0, 0xc7,              //     LOGICAL_MINIMUM (-14400)
	0x26, 0x40, 0x38,              //     LOGICAL_MAXIMUM (14400)
	0x75, 0x10,                    //     REPORT_SIZE (16)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	0xc0,                          //     END_COLLECTION
	0xc0                           // END_COLLECTION
};

typedef struct
{
	__IO uint16_t ADDR_TX;
	__IO uint16_t COUNT_TX;
	__IO uint16_t ADDR_RX;
	__IO uint16_t COUNT_RX;
} BTableLayout;

#endif /* USB_DEFINITIONS_H_ */
