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
	GET_STATUS 			= 0x0,
	CLEAR_FEATURE 		= 0x1,
	SET_FEATURE 		= 0x3,
	SET_ADDRESS 		= 0x5,
	GET_DESCRIPTOR 		= 0x6,
	SET_DESCRIPTOR 		= 0x7,
	GET_CONFIGURATION 	= 0x8,
	SET_CONFIGURATION 	= 0x9,
	GET_INTERFACE 		= 0xA,
	SET_INTERFACE 		= 0x11,
	SYNCH_FRAME 		= 0x12
} USBRequest;


typedef enum
{
	GET_REPORT 		= 0x01,
	GET_IDLE		= 0x02,
	GET_PROTOCOL 	= 0x03,
	SET_REPORT		= 0x09,
	SET_IDLE		= 0x0A,
	SET_PROTOCOL	= 0x0B
} USBClassRequest;


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

typedef struct __attribute__((__packed__))
{
	uint8_t 	effect_block_index;
	uint8_t 	effect_type;
	uint16_t 	duration;
	uint16_t 	trigger_repeat_interval;
	uint16_t 	sample_period;
	uint8_t 	gain;
	uint8_t 	trigger_button;
	uint8_t 	axes_enable;
	uint8_t 	type_specific_block_offset_1;
	uint8_t 	type_specific_block_offset_2;
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

typedef struct __attribute__((__packed__))
{
	int16_t 	magnitude;
	uint8_t 	parameter_block_offset;
} ConstantForceBlock;

typedef struct
{
	
} RampForceBlock;

typedef struct __attribute__((__packed__))
{
	uint8_t report_id;
	uint8_t effect_block_index;
	uint8_t block_load_status;
	uint32_t ram_pool_available;
} PIDBlockLoad_t;

union PIDBlockLoadReport
{
	PIDBlockLoad_t report;
	uint8_t data[7];
};

typedef struct __attribute__((__packed__))
{
	uint8_t report_id;
	uint16_t ram_pool_size;
	uint8_t simultaneous_effects_max;
	uint8_t device_manage_pool_shared_parameter_blocks;
} PIDPoolReport_t;

union PIDPoolReport
{
	PIDPoolReport_t report;
	uint8_t data[5];
};

typedef struct __attribute__((__packed__))
{
	uint8_t report_id;
	uint8_t effect_type;
	uint8_t byte_count;	//Used for custom force
} CreateNewEffect;

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


enum EndpointReponse
{
	ER_DISABLED = 0,
	ER_STALL = 1,
	ER_NAK = 2,
	ER_VALID = 3
};

/*
uint8_t const ReportDescriptor[63] = {
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
};*/

uint8_t const ReportDescriptor[117] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x01,                    //     REPORT_ID (1)
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
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x0F,              //     LOGICAL_MAXIMUM (4095)				//39

	0x05, 0x02,					   //	  USAGE_PAGE(Simulation Controls)
    0x09, 0xBB,                    //     USAGE (Y)	//31
    0x75, 0x0C,                    //     REPORT_SIZE (12)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x75, 0x04,                    //     REPORT_SIZE (4)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)				//16

    0x09, 0xC5,                    //     USAGE (Z)	//32
    0x75, 0x0C,                    //     REPORT_SIZE (12)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x75, 0x04,                    //     REPORT_SIZE (4)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)				//14

    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x32,                    //     USAGE (Rx) //33
    0x75, 0x0C,                    //     REPORT_SIZE (12)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x75, 0x04,                    //     REPORT_SIZE (4)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)				//14


    0x09, 0x34,                    //     USAGE (Ry)
    0x75, 0x0C,                    //     REPORT_SIZE (12)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x75, 0x04,                    //     REPORT_SIZE (4)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)				//14

	0x05, 0x02,					   //	  USAGE_PAGE(Simulation Controls)//Delete
    0x09, 0xC8,                    //     USAGE (X)					//09 30
    0x16, 0xc0, 0xc7,              //     LOGICAL_MINIMUM (-14400)
    0x26, 0x40, 0x38,              //     LOGICAL_MAXIMUM (14400)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //     END_COLLECTION
    0xc0                           // END_COLLECTION						//16
};

/*
uint8_t ReportDescriptor[336] = {
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x04,                    // USAGE (Joystick)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0x01,                    //   REPORT_ID (1)
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
	0xc0,                          //   END_COLLECTION
	0x05, 0x0f,                    //   USAGE_PAGE (Physical Interface)
	0x09, 0x21,                    //   USAGE (Set Effect Report)
	0xa1, 0x02,                    //   COLLECTION (Logical)
	0x09, 0x22,                    //     USAGE (Effect Block Index)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
	0x09, 0x25,                    //     USAGE (Effect Type)
	0xa1, 0x02,                    //     COLLECTION (Logical)
	0x09, 0x26,                    //       USAGE (ET Constant Force)
	0x09, 0x27,                    //       USAGE (ET Ramp)
	0x09, 0x30,                    //       USAGE (ET Square)
	0x09, 0x31,                    //       USAGE (ET Sine)
	0x09, 0x32,                    //       USAGE (ET Triangle)
	0x09, 0x33,                    //       USAGE (ET Sawtooth Up)
	0x09, 0x34,                    //       USAGE (ET Sawtooth Down)
	0x09, 0x40,                    //       USAGE (ET Spring)
	0x09, 0x41,                    //       USAGE (ET Damper)
	0x09, 0x42,                    //       USAGE (ET Inertia)
	0x15, 0x01,                    //       LOGICAL_MINIMUM (1)
	0x25, 0x0a,                    //       LOGICAL_MAXIMUM (10)
	0x75, 0x08,                    //       REPORT_SIZE (8)
	0x91, 0x00,                    //       OUTPUT (Data,Ary,Abs)
	0xc0,                          //     END_COLLECTION
	0x09, 0x50,                    //     USAGE (Duration)
	0x09, 0x54,                    //     USAGE (Trigger Repeat Interval)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x26, 0x10, 0x27,              //     LOGICAL_MAXIMUM (10000)
	0x46, 0x10, 0x27,              //     PHYSICAL_MAXIMUM (10000)
	0x75, 0x10,                    //     REPORT_SIZE (16)
	0x66, 0x03, 0x10,              //     UNIT (Eng Lin:Time)
	0x55, 0x0d,                    //     UNIT_EXPONENT (-3)
	0x95, 0x02,                    //     REPORT_COUNT (2)
	0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
	0x55, 0x0a,                    //     UNIT_EXPONENT (-6)
	0x09, 0x51,                    //     USAGE (Sample Period)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
	0x45, 0x00,                    //     PHYSICAL_MAXIMUM (0)
	0x55, 0x00,                    //     UNIT_EXPONENT (0)
	0x65, 0x00,                    //     UNIT (None)
	0x09, 0x52,                    //     USAGE (Gain)
	0x09, 0x53,                    //     USAGE (Trigger Button)
	0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x02,                    //     REPORT_COUNT (2)
	0x91, 0x02,                    //     OUTPUT (Data,Var,Abs)
	0x09, 0x55,                    //     USAGE (Axes Enable)
	0xa1, 0x02,                    //     COLLECTION (Logical)
	0x05, 0x01,                    //       USAGE_PAGE (Generic Desktop)
	0x09, 0x04,                    //       USAGE (Joystick)
	0xa1, 0x00,                    //       COLLECTION (Physical)
	0x09, 0x30,                    //         USAGE (X)
	0x25, 0x01,                    //         LOGICAL_MAXIMUM (1)
	0x75, 0x01,                    //         REPORT_SIZE (1)
	0x95, 0x01,                    //         REPORT_COUNT (1)
	0x91, 0x02,                    //         OUTPUT (Data,Var,Abs)
	0xc0,                          //       END_COLLECTION
	0xc0,                          //     END_COLLECTION
	0x95, 0x07,                    //     REPORT_COUNT (7)
	0x91, 0x03,                    //     OUTPUT (Cnst,Var,Abs)
	0x05, 0x0f,                    //     USAGE_PAGE (Physical Interface)
	0x09, 0x58,                    //     USAGE (Type Specific Block Offset)
	0xa1, 0x02,                    //     COLLECTION (Logical)
	0x0b, 0x01, 0x00, 0x0a, 0x00,  //       USAGE (Ordinals:Instance 1)
	0x0b, 0x02, 0x00, 0x0a, 0x00,  //       USAGE (Ordinals:Instance 2)
	0x26, 0xff, 0x00,              //       LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //       REPORT_SIZE (8)
	0x95, 0x02,                    //       REPORT_COUNT (2)
	0x91, 0x02,                    //       OUTPUT (Data,Var,Abs)
	0xc0,                          //   END_COLLECTION
	0xc0,                          //               END_COLLECTION
	0x09, 0xab,                    //   USAGE (Create New Effect Report)
	0xa1, 0x02,                    //   COLLECTION (Logical)
	0x85, 0x01,                    //     REPORT_ID (1)
	0x09, 0x25,                    //     USAGE (Effect Type)
	0xa1, 0x02,                    //     COLLECTION (Logical)
	0x09, 0x26,                    //       USAGE (ET Constant Force)
	0x09, 0x27,                    //       USAGE (ET Ramp)
	0x09, 0x30,                    //       USAGE (ET Square)
	0x09, 0x31,                    //       USAGE (ET Sine)
	0x09, 0x32,                    //       USAGE (ET Triangle)
	0x09, 0x33,                    //       USAGE (ET Sawtooth Up)
	0x09, 0x34,                    //       USAGE (ET Sawtooth Down)
	0x09, 0x40,                    //       USAGE (ET Spring)
	0x09, 0x41,                    //       USAGE (ET Damper)
	0x09, 0x42,                    //       USAGE (ET Inertia)
	0x15, 0x01,                    //       LOGICAL_MINIMUM (1)
	0x25, 0x0a,                    //       LOGICAL_MAXIMUM (10)
	0x75, 0x08,                    //       REPORT_SIZE (8)
	0x95, 0x01,                    //       REPORT_COUNT (1)
	0xb1, 0x00,                    //       FEATURE (Data,Ary,Abs)
	0xc0,                          //   END_COLLECTION
	0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	0x09, 0x3b,                    //     USAGE (Byte Count)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0xb1, 0x02,                    //     FEATURE (Data,Var,Abs)
	0xc0,                          //               END_COLLECTION
	0x05, 0x0f,                    //   USAGE_PAGE (Physical Interface)
	0x09, 0x89,                    //   USAGE (PID Block Load Report)
	0xa1, 0x02,                    //   COLLECTION (Logical)
	0x85, 0x02,                    //     REPORT_ID (2)
	0x09, 0x22,                    //     USAGE (Effect Block Index)
	0x25, 0x0a,                    //     LOGICAL_MAXIMUM (10)
	0x15, 0x01,                    //     LOGICAL_MINIMUM (1)
	0x75, 0x08,                    //     REPORT_SIZE (8)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0xb1, 0x02,                    //     FEATURE (Data,Var,Abs)
	0x09, 0x8b,                    //     USAGE (Block Load Status)
	0xa1, 0x02,                    //     COLLECTION (Logical)
	0x09, 0x8c,                    //       USAGE (Block Load Success)
	0x09, 0x8d,                    //       USAGE (Block Load Full)
	0x09, 0x8e,                    //       USAGE (Block Load Error)
	0x15, 0x01,                    //       LOGICAL_MINIMUM (1)
	0x25, 0x03,                    //       LOGICAL_MAXIMUM (3)
	0x75, 0x08,                    //       REPORT_SIZE (8)
	0x95, 0x01,                    //       REPORT_COUNT (1)
	0xb1, 0x00,                    //       FEATURE (Data,Ary,Abs)
	0xc0,                          //   END_COLLECTION
	0x09, 0xac,                    //     USAGE (RAM Pool Available)
	0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	0x27, 0xff, 0xff, 0x00, 0x00,  //     LOGICAL_MAXIMUM (65535)
	0x75, 0x10,                    //     REPORT_SIZE (16)
	0x95, 0x01,                    //     REPORT_COUNT (1)
	0xb1, 0x02,                    //     FEATURE (Data,Var,Abs)
	0xc0,                          //               END_COLLECTION
	0xc0                           //               END_COLLECTION
};*/

/*
uint8_t const ReportDescriptor[1252] =
{
		0x05,0x01,                //Usage_Page(Generic_Desktop_ID),
		0x15,0x00,                //Logical_Minimum(0),
		0x09,0x04,                //Usage(Joystick_ID),
		0xa1,0x01,                //Collection(Clc_Application),
		  0x85,0x01,                //    Report_ID(1), //FFBMK1 JoyStick Inputs interrupt in pipe->default 0
		  0x05,0x02,                //    Usage_Page(Simulation_ID),
		  0x09,0xbb,                //    Usage(Throttle_ID), //Throttle
		  0x15,0x00,                //    Logical_Minimum(0),
		  0x25,0x7f,                //    Logical_Maximum(127),
		  0x75,0x08,                //    Report_Size(8),
		  0x95,0x01,                //    Report_Count(1),
		  0x81,0x02,                //    Input(IOF_Variable),
		  0x05,0x01,                //    Usage_Page(Generic_Desktop_ID),
		  0x09,0x01,                //    Usage(Pointer_ID),
		  0xa1,0x00,                //    Collection(Clc_Physical), //X&Y
		  0x09,0x30,                //        Usage(X_ID),
		  0x09,0x31,                //        Usage(Y_ID),
		  0x16,0x00,0xf8,           //        Logical_Minimum(-2048),
		  0x26,0xff,0x07,           //        Logical_Maximum(2047),
		  0x75,0x10,                //        Report_Size(16),
		  0x95,0x02,                //        Report_Count(2),
		  0x81,0x02,                //        Input(IOF_Variable),
		  0xc0,                     //    End_Collection(),
		  0x05,0x09,                //    Usage_Page(Button_ID), //Buttons
		  0x19,0x01,                //    Usage_Minimum(Button1_ID),
		  0x29,0x04,                //    Usage_Maximum(Button4_ID),
		  0x25,0x01,                //    Logical_Maximum(1),
		  0x15,0x00,                //    Logical_Minimum(0),
		  0x95,0x04,                //    Report_Count(4),
		  0x75,0x01,                //    Report_Size(1),
		  0x35,0x00,                //    Physical_Minimum(0),
		  0x81,0x02,                //    Input(IOF_Variable),
		  0x81,0x03,                //    Input(IOF_Constant), //4-bit pad
		  0x05,0x0F,  // USAGE_PAGE (Physical Interface)
		  0x09,0x92,  // USAGE (PID State Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x02,  // REPORT_ID (02)
		    0x09,0x9F,  // USAGE (Device Paused)
		    0x09,0xA0,  // USAGE (Actuators Enabled)
		    0x09,0xA4,  // USAGE (Safety Switch)
		    0x09,0xA5,  // USAGE (Actuator Override Switch)
		    0x09,0xA6,  // USAGE (Actuator Power)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x25,0x01,  // LOGICAL_MINIMUM (01)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x45,0x01,  // PHYSICAL_MAXIMUM (01)
		    0x75,0x01,  // REPORT_SIZE (01)
		    0x95,0x05,  // REPORT_COUNT (05)
		    0x81,0x02,  // INPUT (Data,Var,Abs)
		    0x95,0x03,  // REPORT_COUNT (03)
		    0x81,0x03,  // INPUT (Constant,Var,Abs)
		    0x09,0x94,  // USAGE (Effect Playing)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x25,0x01,  // LOGICAL_MAXIMUM (01)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x45,0x01,  // PHYSICAL_MAXIMUM (01)
		    0x75,0x01,  // REPORT_SIZE (01)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x81,0x02,  // INPUT (Data,Var,Abs)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x07,  // REPORT_SIZE (07)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x81,0x02,  // INPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x09,0x21,  // USAGE (Set Effect Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x01,  // REPORT_ID (01)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x25,  // USAGE (25)
		    0xA1,0x02,  // COLLECTION (Logical)
		      0x09,0x26,  // USAGE (26)
		      0x09,0x27,  // USAGE (27)
		      0x09,0x30,  // USAGE (30)
		      0x09,0x31,  // USAGE (31)
		      0x09,0x32,  // USAGE (32)
		      0x09,0x33,  // USAGE (33)
		      0x09,0x34,  // USAGE (34)
		      0x09,0x40,  // USAGE (40)
		      0x09,0x41,  // USAGE (41)
		      0x09,0x42,  // USAGE (42)
		      0x09,0x43,  // USAGE (43)
		      0x09,0x28,  // USAGE (28)
		      0x25,0x0C,  // LOGICAL_MAXIMUM (0C)
		      0x15,0x01,  // LOGICAL_MINIMUM (01)
		      0x35,0x01,  // PHYSICAL_MINIMUM (01)
		      0x45,0x0C,  // PHYSICAL_MAXIMUM (0C)
		      0x75,0x08,  // REPORT_SIZE (08)
		      0x95,0x01,  // REPORT_COUNT (01)
		      0x91,0x00,  // OUTPUT (Data)
		    0xC0, // END COLLECTION ()
		    0x09,0x50,  // USAGE (Duration)
		    0x09,0x54,  // USAGE (Trigger Repeat Interval)
		    0x09,0x51,  // USAGE (Sample Period)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x7F, // LOGICAL_MAXIMUM (7F FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x7F, // PHYSICAL_MAXIMUM (7F FF)
		    0x66,0x03,0x10, // UNIT (Eng Lin:Time)
		    0x55,0x0D,  // UNIT_EXPONENT (-3)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x03,  // REPORT_COUNT (03)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x55,0x00,  // UNIT_EXPONENT (00)
		    0x65,0x00, // UNIT (None)
		    0x09,0x52,  // USAGE (Gain)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x53,  // USAGE (Trigger Button)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x08,  // LOGICAL_MAXIMUM (08)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x08,  // PHYSICAL_MAXIMUM (08)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x55,  // USAGE (Axes Enable)
		    0xA1,0x02,  // COLLECTION (Logical)
		      0x05,0x01,  // USAGE_PAGE (Generic Desktop)
		      0x09,0x30,  // USAGE (X)
		      0x09,0x31,  // USAGE (Y)
		      0x15,0x00,  // LOGICAL_MINIMUM (00)
		      0x25,0x01,  // LOGICAL_MAXIMUM (01)
		      0x75,0x01,  // REPORT_SIZE (01)
		      0x95,0x02,  // REPORT_COUNT (02)
		      0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0xC0, // END COLLECTION ()
		    0x05,0x0F,  // USAGE_PAGE (Physical Interface)
		    0x09,0x56,  // USAGE (Direction Enable)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x95,0x05,  // REPORT_COUNT (05)
		    0x91,0x03,  // OUTPUT (Constant,Var,Abs)
		    0x09,0x57,  // USAGE (Direction)
		    0xA1,0x02,  // COLLECTION (Logical)
		      0x0B,0x01,0x00,0x0A,0x00,
		      0x0B,0x02,0x00,0x0A,0x00,
		      0x65,0x14, // UNIT (Eng Rot:Angular Pos)
		      0x55,0x0E,  // UNIT_EXPONENT (FE)
		      0x15,0x00,  // LOGICAL_MINIMUM (00)
		      0x26,0xB4,0x00, // LOGICAL_MAXIMUM (00 B4)
		      0x35,0x00,  // PHYSICAL_MINIMUM (00)
		      0x47,0xA0,0x8C,0x00,0x00, // PHYSICAL_MAXIMUM (00 00 8C A0)
		      0x65,0x00, // UNIT (None)
		      0x75,0x08,  // REPORT_SIZE (08)
		      0x95,0x02,  // REPORT_COUNT (02)
		      0x91,0x02,  // OUTPUT (Data,Var,Abs)
		      0x55,0x00,  // UNIT_EXPONENT (00)
		      0x65,0x00, // UNIT (None)
		    0xC0, // END COLLECTION ()
		    0x05,0x0F,  // USAGE_PAGE (Physical Interface)
		//    0x09,0xA7,  // USAGE (Start Delay)
		    0x66,0x03,0x10, // UNIT (Eng Lin:Time)
		    0x55,0x0D,  // UNIT_EXPONENT (-3)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x7F, // LOGICAL_MAXIMUM (7F FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x7F, // PHYSICAL_MAXIMUM (7F FF)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x01,  // REPORT_COUNT (01)
		//    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x65,0x00, // UNIT (None)
		    0x55,0x00,  // UNIT_EXPONENT (00)
		  0xC0, // END COLLECTION ()

		  0x05,0x0F,  // USAGE_PAGE (Physical Interface)
		  0x09,0x5A,  // USAGE (Set Envelope Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x02,  // REPORT_ID (02)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x5B,  // USAGE (Attack Level)
		    0x09,0x5D,  // USAGE (Fade Level)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x95,0x02,  // REPORT_COUNT (02)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x5C,  // USAGE (5C)
		    0x09,0x5E,  // USAGE (5E)
		    0x66,0x03,0x10, // UNIT (Eng Lin:Time)
		    0x55,0x0D,  // UNIT_EXPONENT (-3)
		    0x26,0xFF,0x7F, // LOGICAL_MAXIMUM (7F FF)
		    0x46,0xFF,0x7F, // PHYSICAL_MAXIMUM (7F FF)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x45,0x00,  // PHYSICAL_MAXIMUM (00)
		    0x65,0x00,// UNIT (None)
		    0x55,0x00,  // UNIT_EXPONENT (00)
		  0xC0, // END COLLECTION ()

		  0x09,0x5F,  // USAGE (Set Condition Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x03,  // REPORT_ID (03)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x23,  // USAGE (Parameter Block Offset)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x25,0x01,  // LOGICAL_MAXIMUM (01)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x45,0x01,  // PHYSICAL_MAXIMUM (01)
		    0x75,0x04,  // REPORT_SIZE (04)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x58,  // USAGE (Type Specific Block Offset)
		    0xA1,0x02,  // COLLECTION (Logical)
		      0x0B,0x01,0x00,0x0A,0x00, // USAGE (Instance 1)
		      0x0B,0x02,0x00,0x0A,0x00, // USAGE (Instance 2)
		      0x75,0x02,  // REPORT_SIZE (02)
		      0x95,0x02,  // REPORT_COUNT (02)
		      0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0xC0, // END COLLECTION ()
		    0x15,0x80,  // LOGICAL_MINIMUM (80)
		    0x25,0x7F,  // LOGICAL_MAXIMUM (7F)
		    0x36,0xF0,0xD8, // PHYSICAL_MINIMUM (-10000)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x09,0x60,  // USAGE (CP Offset)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x36,0xF0,0xD8, // PHYSICAL_MINIMUM (-10000)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x09,0x61,  // USAGE (Positive Coefficient)
		//    0x09,0x62,  // USAGE (Negative Coefficient)
		    0x95,0x01,  // REPORT_COUNT (01)  // ???? WAS 2 with "negative coeff"
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x09,0x63,  // USAGE (Positive Saturation)
		    0x09,0x64,  // USAGE (Negative Saturation)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x02,  // REPORT_COUNT (02)
		//    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		//    0x09,0x65,  // USAGE (Dead Band )
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x95,0x01,  // REPORT_COUNT (01)
		//    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x09,0x6E,  // USAGE (Set Periodic Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x04,  // REPORT_ID (04)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x70,  // USAGE (Magnitude)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x6F,  // USAGE (Offset)
		    0x15,0x80,  // LOGICAL_MINIMUM (80)
		    0x25,0x7F,  // LOGICAL_MAXIMUM (7F)
		    0x36,0xF0,0xD8, // PHYSICAL_MINIMUM (-10000)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x71,  // USAGE (Phase)
		    0x65,0x14, // UNIT (Eng Rot:Angular Pos)
		    0x55,0x0E,  // UNIT_EXPONENT (FE)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x47,0xA0,0x8C,0x00,0x00, // PHYSICAL_MAXIMUM (00 00 8C A0)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x72,  // USAGE (Period)
		    0x26,0xFF,0x7F, // LOGICAL_MAXIMUM (7F FF)
		    0x46,0xFF,0x7F, // PHYSICAL_MAXIMUM (7F FF)
		    0x66,0x03,0x10, // UNIT (Eng Lin:Time)
		    0x55,0x0D,  // UNIT_EXPONENT (-3)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x65,0x00, // UNIT (None)
		    0x55,0x00,  // UNIT_EXPONENT (00)
		  0xC0, // END COLLECTION ()

		  0x09,0x73,  // USAGE (Set Constant Force Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x05,  // REPORT_ID (05)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x70,  // USAGE (Magnitude)
		    0x16,0x01,0xFF, // LOGICAL_MINIMUM (-255)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (255)
		    0x36,0xF0,0xD8, // PHYSICAL_MINIMUM (-10000)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x09,0x74,  // USAGE (Set Ramp Force Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x06,  // REPORT_ID (06)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x75,  // USAGE (Ramp Start)
		    0x09,0x76,  // USAGE (Ramp End)
		    0x15,0x80,  // LOGICAL_MINIMUM (-128)
		    0x25,0x7F,  // LOGICAL_MAXIMUM (127)
		    0x36,0xF0,0xD8, // PHYSICAL_MINIMUM (-10000)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x02,  // REPORT_COUNT (02)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x09,0x68,  // USAGE (Custom Force Data Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x07,  // REPORT_ID (07)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x6C,  // USAGE (Custom Force Data Offset)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0x10,0x27, // LOGICAL_MAXIMUM (10000)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x69,  // USAGE (Custom Force Data)
		    0x15,0x81,  // LOGICAL_MINIMUM (-127)
		    0x25,0x7F,  // LOGICAL_MAXIMUM (127)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x00, // PHYSICAL_MAXIMUM (255)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x0C,  // REPORT_COUNT (0C)
		    0x92,0x02,0x01, // OUTPUT ( Data,Var,Abs,Buf)
		  0xC0, // END COLLECTION ()

		  0x09,0x66,  // USAGE (Download Force Sample)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x08,  // REPORT_ID (08)
		    0x05,0x01,  // USAGE_PAGE (Generic Desktop)
		    0x09,0x30,  // USAGE (X)
		    0x09,0x31,  // USAGE (Y)
		    0x15,0x81,  // LOGICAL_MINIMUM (-127)
		    0x25,0x7F,  // LOGICAL_MAXIMUM (127)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x00, // PHYSICAL_MAXIMUM (255)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x02,  // REPORT_COUNT (02)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x05,0x0F,  // USAGE_PAGE (Physical Interface)
		  0x09,0x77,  // USAGE (Effect Operation Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x0A,  // REPORT_ID (0A)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x78,  // USAGE (78)
		    0xA1,0x02,  // COLLECTION (Logical)
		      0x09,0x79,  // USAGE (Op Effect Start)
		      0x09,0x7A,  // USAGE (Op Effect Start Solo)
		      0x09,0x7B,  // USAGE (Op Effect Stop)
		      0x15,0x01,  // LOGICAL_MINIMUM (01)
		      0x25,0x03,  // LOGICAL_MAXIMUM (03)
		      0x75,0x08,  // REPORT_SIZE (08)
		      0x95,0x01,  // REPORT_COUNT (01)
		      0x91,0x00,  // OUTPUT (Data,Ary,Abs)
		    0xC0, // END COLLECTION ()
		    0x09,0x7C,  // USAGE (Loop Count)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x00, // PHYSICAL_MAXIMUM (00 FF)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x09,0x90,  // USAGE (PID Block Free Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x0B,  // REPORT_ID (0B)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x09,0x96,  // USAGE (PID Device Control)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x0C,  // REPORT_ID (0C)
		    0x09,0x97,  // USAGE (DC Enable Actuators)
		    0x09,0x98,  // USAGE (DC Disable Actuators)
		    0x09,0x99,  // USAGE (DC Stop All Effects)
		    0x09,0x9A,  // USAGE (DC Device Reset)
		    0x09,0x9B,  // USAGE (DC Device Pause)
		    0x09,0x9C,  // USAGE (DC Device Continue)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x06,  // LOGICAL_MAXIMUM (06)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x00,  // OUTPUT (Data)
		  0xC0, // END COLLECTION ()

		  0x09,0x7D,  // USAGE (Device Gain Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x0D,  // REPORT_ID (0D)
		    0x09,0x7E,  // USAGE (Device Gain)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0x10,0x27, // PHYSICAL_MAXIMUM (10000)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		  0xC0, // END COLLECTION ()

		  0x09,0x6B,  // USAGE (Set Custom Force Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x0E,  // REPORT_ID (0E)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x6D,  // USAGE (Sample Count)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x00, // PHYSICAL_MAXIMUM (00 FF)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x09,0x51,  // USAGE (Sample Period)
		    0x66,0x03,0x10, // UNIT (Eng Lin:Time)
		    0x55,0x0D,  // UNIT_EXPONENT (-3)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x7F, // LOGICAL_MAXIMUM (32767)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x7F, // PHYSICAL_MAXIMUM (32767)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x91,0x02,  // OUTPUT (Data,Var,Abs)
		    0x55,0x00,  // UNIT_EXPONENT (00)
		    0x65,0x00, // UNIT (None)
		  0xC0, // END COLLECTION ()

		  0x09,0xAB,  // USAGE (Create New Effect Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x05,  // REPORT_ID (05)
		    0x09,0x25,  // USAGE (Effect Type)
		    0xA1,0x02,  // COLLECTION (Logical)
		      0x09,0x26,  // USAGE (26)
		      0x09,0x27,  // USAGE (27)
		      0x09,0x30,  // USAGE (30)
		      0x09,0x31,  // USAGE (31)
		      0x09,0x32,  // USAGE (32)
		      0x09,0x33,  // USAGE (33)
		      0x09,0x34,  // USAGE (34)
		      0x09,0x40,  // USAGE (40)
		      0x09,0x41,  // USAGE (41)
		      0x09,0x42,  // USAGE (42)
		      0x09,0x43,  // USAGE (43)
		      0x09,0x28,  // USAGE (28)
		      0x25,0x0C,  // LOGICAL_MAXIMUM (0C)
		      0x15,0x01,  // LOGICAL_MINIMUM (01)
		      0x35,0x01,  // PHYSICAL_MINIMUM (01)
		      0x45,0x0C,  // PHYSICAL_MAXIMUM (0C)
		      0x75,0x08,  // REPORT_SIZE (08)
		      0x95,0x01,  // REPORT_COUNT (01)
		      0xB1,0x00,  // FEATURE (Data)
		    0xC0, // END COLLECTION ()
		    0x05,0x01,  // USAGE_PAGE (Generic Desktop)
		    0x09,0x3B,  // USAGE (Byte Count)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x26,0xFF,0x01, // LOGICAL_MAXIMUM (511)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x46,0xFF,0x01, // PHYSICAL_MAXIMUM (511)
		    0x75,0x0A,  // REPORT_SIZE (0A)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0xB1,0x02,  // FEATURE (Data,Var,Abs)
		    0x75,0x06,  // REPORT_SIZE (06)
		    0xB1,0x01,  // FEATURE (Constant,Ary,Abs)
		  0xC0, // END COLLECTION ()

		  0x05,0x0F,  // USAGE_PAGE (Physical Interface)
		  0x09,0x89,  // USAGE (PID Block Load Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x06,  // REPORT_ID (06)
		    0x09,0x22,  // USAGE (Effect Block Index)
		    0x25,0x28,  // LOGICAL_MAXIMUM (28)
		    0x15,0x01,  // LOGICAL_MINIMUM (01)
		    0x35,0x01,  // PHYSICAL_MINIMUM (01)
		    0x45,0x28,  // PHYSICAL_MAXIMUM (28)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0xB1,0x02,  // FEATURE (Data,Var,Abs)
		    0x09,0x8B,  // USAGE (Block Load Status)
		    0xA1,0x02,  // COLLECTION (Logical)
		      0x09,0x8C,  // USAGE (Block Load Success)
		      0x09,0x8D,  // USAGE (Block Load Full)
		      0x09,0x8E,  // USAGE (Block Load Error)
		      0x25,0x03,  // LOGICAL_MAXIMUM (03)
		      0x15,0x01,  // LOGICAL_MINIMUM (01)
		      0x35,0x01,  // PHYSICAL_MINIMUM (01)
		      0x45,0x03,  // PHYSICAL_MAXIMUM (03)
		      0x75,0x08,  // REPORT_SIZE (08)
		      0x95,0x01,  // REPORT_COUNT (01)
		      0xB1,0x00,  // FEATURE (Data)
		    0xC0, // END COLLECTION ()
		    0x09,0xAC,  // USAGE (RAM Pool Available)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x27,0xFF,0xFF,0x00,0x00, // LOGICAL_MAXIMUM (00 00 FF FF)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x47,0xFF,0xFF,0x00,0x00, // PHYSICAL_MAXIMUM (00 00 FF FF)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0xB1,0x02,  // FEATURE (Data)
		  0xC0, // END COLLECTION ()

		  0x09,0x7F,  // USAGE (PID Pool Report)
		  0xA1,0x02,  // COLLECTION (Logical)
		    0x85,0x07,  // REPORT_ID (07)
		    0x09,0x80,  // USAGE (RAM Pool Size)
		    0x75,0x10,  // REPORT_SIZE (10)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x27,0xFF,0xFF,0x00,0x00, // LOGICAL_MAXIMUM (00 00 FF FF)
		    0x47,0xFF,0xFF,0x00,0x00, // PHYSICAL_MAXIMUM (00 00 FF FF)
		    0xB1,0x02,  // FEATURE (Data,Var,Abs)
		    0x09,0x83,  // USAGE (Simultaneous Effects Max)
		    0x26,0xFF,0x00, // LOGICAL_MAXIMUM (00 FF)
		    0x46,0xFF,0x00, // PHYSICAL_MAXIMUM (00 FF)
		    0x75,0x08,  // REPORT_SIZE (08)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0xB1,0x02,  // FEATURE (Data,Var,Abs)
		    0x09,0xA9,  // USAGE (Device Managed Pool)
		    0x09,0xAA,  // USAGE (Shared Parameter Blocks)
		    0x75,0x01,  // REPORT_SIZE (01)
		    0x95,0x02,  // REPORT_COUNT (02)
		    0x15,0x00,  // LOGICAL_MINIMUM (00)
		    0x25,0x01,  // LOGICAL_MAXIMUM (01)
		    0x35,0x00,  // PHYSICAL_MINIMUM (00)
		    0x45,0x01,  // PHYSICAL_MAXIMUM (01)
		    0xB1,0x02,  // FEATURE (Data,Var,Abs)
		    0x75,0x06,  // REPORT_SIZE (06)
		    0x95,0x01,  // REPORT_COUNT (01)
		    0x95, 0x01,
		    0xB1,0x03,  // FEATURE ( Cnst,Var,Abs)
		  0xC0, // END COLLECTION ()
		0xC0, // END COLLECTION ()
		//1250 bytes
};
*/
/*
uint8_t const ReportDescriptor[1274] = {

 0x05,0x01, // Usage Page Generic Desktop
 0x09,0x04, // Usage Joystick
 0xA1,0x01, // Collection Application
    0x85,0x01, // Report ID 1
0x05,0x09, // [0x03]USAGE PAGE (BUTTON)
0x19,0x01, // [0x04]USAGE_MINIMUM(BUTTON 1)
0x29,0x10, // [0x05]USAGE_MAXIMUM(BUTTON 16)
0x15,0x00, // [0x06]LOGICAL_MINIMUM
0x25,0x01, // [0x07]LOGICAL_MAXIMUM
0x35,0x00, // [0x08]PHYSICAL_MINIMUM
0x45,0x01, // [0x09]PHYSICAL_MAXIMUM
0x75,0x01, // [0x0A]REPORT_SIZE
0x95,0x10, // [0x0B]REPORT_COUNT
0x81,0x02, // [0x0C]INPUT
0x05,0x01, // [0x0D]USAGE PAGE (GENERIC DESKTOP CONTROLS)
0x09,0x39, // [0x0E]USAGE(HAT_SWITCH)
0x15,0x00, // [0x0F]LOGICAL_MINIMUM
0x25,0x07, // [0x10]LOGICAL_MAXIMUM
0x35,0x00, // [0x11]PHYSICAL_MINIMUM
0x46,0x3B,0x01, // [0x12]PHYSICAL_MAXIMUM
0x65,0x14, // [0x13]UNIT
0x75,0x04, // [0x14]REPORT_SIZE
0x95,0x01, // [0x15]REPORT_COUNT
0x81,0x42, // [0x16]INPUT
0x65,0x00, // [0x17]UNIT
0x95,0x01, // [0x18]REPORT_COUNT
0x81,0x01, // [0x19]INPUT
0x09,0x30, // [0x1A]USAGE(X)
0x09,0x31, // [0x1B]USAGE(Y)
0x09,0x32, // [0x1C]USAGE(Z)
0x09,0x33, // [0x1D]USAGE(Rx)
0x15,0x00, // [0x1E]LOGICAL_MINIMUM
0x26,0x00,0x04, // [0x1F]LOGICAL_MAXIMUM
0x35,0x00, // [0x20]PHYSICAL_MINIMUM
0x46,0x00,0x04, // [0x21]PHYSICAL_MAXIMUM
0x75,0x10, // [0x22]REPORT_SIZE
0x95,0x04, // [0x23]REPORT_COUNT
0x81,0x02, // [0x24]INPUT

    0x05,0x0F, // Usage Page Physical Interface
    0x09,0x92, // Usage PID State report
    0xA1,0x02, // Collection Datalink (logical)

       0x85,0x02, // Report ID 2
       0x09,0x9F, // Usage Device is Pause
       0x09,0xA0, // Usage Actuators Enabled
       0x09,0xA4, // Usage Safety Switch
       0x09,0xA5, // Usage Actuator Override Switch
       0x09,0xA6, // Usage Actuator Power
       0x15,0x00, // Logical Minimum 0
       0x25,0x01, // Logical Maximum 1
       0x35,0x00, // Physical Minimum 0
       0x45,0x01, // Physical Maximum 1
       0x75,0x01, // Report Size 1
       0x95,0x05, // Report Count 5
       0x81,0x02, // Input (Variable)
       0x95,0x03, // Report Count 3
       0x81,0x03, // Input (Constant, Variable)


       0x09,0x94, // Usage Effect Playing
       0x15,0x00, // Logical Minimum 0
       0x25,0x01, // Logical Maximum 1
       0x35,0x00, // Physical Minimum 0
       0x45,0x01, // Physical Maximum 1
       0x75,0x01, // Report Size 1
       0x95,0x01, // Report Count 1
       0x81,0x02, // Input (Variable)
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x07, // Report Size 7
       0x95,0x01, // Report Count 1
       0x81,0x02, // Input (Variable)
    0xC0 , // End Collection

    0x09,0x21, // Usage Set Effect Report
    0xA1,0x02, // Collection Datalink (Logical)
       0x85,0x01, // Report ID 1
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)

       0x09,0x25, // Usage Effect Type
       0xA1,0x02, // Collection Datalink
          0x09,0x26, // Usage ET Constant Force
          0x09,0x27, // Usage ET Ramp
          0x09,0x30, // Usage ET Square
          0x09,0x31, // Usage ET Sine
          0x09,0x32, // Usage ET Triangle
          0x09,0x33, // Usage ET Sawtooth Up
          0x09,0x34, // Usage ET Sawtooth Down
          0x09,0x40, // Usage ET Spring
          0x09,0x41, // Usage ET Damper
          0x09,0x42, // Usage ET Inertia
          0x09,0x43, // Usage ET Friction
          0x09,0x28, // Usage ET Custom Force Data
          0x25,0x0C, // Logical Maximum Ch (12d)
          0x15,0x01, // Logical Minimum 1
          0x35,0x01, // Physical Minimum 1
          0x45,0x0C, // Physical Maximum Ch (12d)
          0x75,0x08, // Report Size 8
          0x95,0x01, // Report Count 1
          0x91,0x00, // Output

       0xC0 , // End Collection

       0x09,0x50, // Usage Duration
       0x09,0x54, // Usage Trigger Repeat Interval
       0x09,0x51, // Usage Sample Period
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x7F, // Logical Maximum 7FFFh (32767d)
       0x35,0x00, // Physical Minimum 0
       0x46,0xFF,0x7F, // Physical Maximum 7FFFh (32767d)
       0x66,0x03,0x10, // Unit 1003h (4099d)
       0x55,0xFD, // Unit Exponent FDh (253d)
       0x75,0x10, // Report Size 10h (16d)
       0x95,0x03, // Report Count 3
       0x91,0x02, // Output (Variable)

       0x55,0x00, // Unit Exponent 0
       0x66,0x00,0x00, // Unit 0
       0x09,0x52, // Usage Gain
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)

       0x09,0x53, // Usage Trigger Button
       0x15,0x01, // Logical Minimum 1
       0x25,0x08, // Logical Maximum 8
       0x35,0x01, // Physical Minimum 1
       0x45,0x08, // Physical Maximum 8
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)

       0x09,0x55, // Usage Axes Enable
       0xA1,0x02, // Collection Datalink
          0x05,0x01, // Usage Page Generic Desktop
          0x09,0x30, // Usage X
          0x09,0x31, // Usage Y
          0x15,0x00, // Logical Minimum 0
          0x25,0x01, // Logical Maximum 1
          0x75,0x01, // Report Size 1
          0x95,0x02, // Report Count 2
          0x91,0x02, // Output (Variable)

       0xC0 , // End Collection

       0x05,0x0F, // Usage Page Physical Interface
       0x09,0x56, // Usage Direction Enable
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)

       0x95,0x05, // Report Count 5
       0x91,0x03, // Output (Constant, Variable)

       0x09,0x57, // Usage Direction
       0xA1,0x02, // Collection Datalink
          0x0B,0x01,0x00,0x0A,0x00, // Usage Ordinals: Instance 1
          0x0B,0x02,0x00,0x0A,0x00, // Usage Ordinals: Instance 2
          0x66,0x14,0x00, // Unit 14h (20d)
          0x55,0xFE, // Unit Exponent FEh (254d)
          0x15,0x00, // Logical Minimum 0
          0x26,0xFF,0x00, // Logical Maximum FFh (255d)
          0x35,0x00, // Physical Minimum 0
          0x47,0xA0,0x8C,0x00,0x00, // Physical Maximum 8CA0h (36000d)
          0x66,0x00,0x00, // Unit 0
          0x75,0x08, // Report Size 8
          0x95,0x02, // Report Count 2
          0x91,0x02, // Output (Variable)
          0x55,0x00, // Unit Exponent 0
          0x66,0x00,0x00, // Unit 0
       0xC0 , // End Collection

       0x05,0x0F, // Usage Page Physical Interface
       0x09,0xA7, // Usage Undefined
       0x66,0x03,0x10, // Unit 1003h (4099d)
       0x55,0xFD, // Unit Exponent FDh (253d)
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x7F, // Logical Maximum 7FFFh (32767d)
       0x35,0x00, // Physical Minimum 0
       0x46,0xFF,0x7F, // Physical Maximum 7FFFh (32767d)
       0x75,0x10, // Report Size 10h (16d)
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x66,0x00,0x00, // Unit 0
       0x55,0x00, // Unit Exponent 0
    0xC0 , // End Collection

    0x05,0x0F, // Usage Page Physical Interface
    0x09,0x5A, // Usage Set Envelope Report
    0xA1,0x02, // Collection Datalink
       0x85,0x02, // Report ID 2
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x5B, // Usage Attack Level
       0x09,0x5D, // Usage Fade Level
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x95,0x02, // Report Count 2
       0x91,0x02, // Output (Variable)
       0x09,0x5C, // Usage Attack Time
       0x09,0x5E, // Usage Fade Time
       0x66,0x03,0x10, // Unit 1003h (4099d)
       0x55,0xFD, // Unit Exponent FDh (253d)
       0x26,0xFF,0x7F, // Logical Maximum 7FFFh (32767d)
       0x46,0xFF,0x7F, // Physical Maximum 7FFFh (32767d)
       0x75,0x10, // Report Size 10h (16d)
       0x91,0x02, // Output (Variable)
       0x45,0x00, // Physical Maximum 0
       0x66,0x00,0x00, // Unit 0
       0x55,0x00, // Unit Exponent 0
    0xC0 , // End Collection

    0x09,0x5F, // Usage Set Condition Report
    0xA1,0x02, // Collection Datalink
       0x85,0x03, // Report ID 3
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x23, // Usage Parameter Block Offset
       0x15,0x00, // Logical Minimum 0
       0x25,0x01, // Logical Maximum 1
       0x35,0x00, // Physical Minimum 0
       0x45,0x01, // Physical Maximum 1
       0x75,0x04, // Report Size 4
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x58, // Usage Type Specific Block Off...
       0xA1,0x02, // Collection Datalink

          0x0B,0x01,0x00,0x0A,0x00, // Usage Ordinals: Instance 1
          0x0B,0x02,0x00,0x0A,0x00, // Usage Ordinals: Instance 2
          0x75,0x02, // Report Size 2
          0x95,0x02, // Report Count 2
          0x91,0x02, // Output (Variable)
       0xC0 , // End Collection

       0x15,0x80, // Logical Minimum 80h (-128d)
       0x25,0x7F, // Logical Maximum 7Fh (127d)
       0x36,0xF0,0xD8, // Physical Minimum D8F0h (-10000d)
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x09,0x60, // Usage CP Offset
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x36,0xF0,0xD8, // Physical Minimum D8F0h (-10000d)
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x09,0x61, // Usage Positive Coefficient
       0x09,0x62, // Usage Negative Coefficient
       0x95,0x02, // Report Count 2
       0x91,0x02, // Output (Variable)
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x09,0x63, // Usage Positive Saturation
       0x09,0x64, // Usage Negative Saturation
       0x75,0x08, // Report Size 8
       0x95,0x02, // Report Count 2
       0x91,0x02, // Output (Variable)
       0x09,0x65, // Usage Dead Band
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
    0xC0 , // End Collection
    0x09,0x6E, // Usage Set Periodic Report
    0xA1,0x02, // Collection Datalink
       0x85,0x04, // Report ID 4
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x70, // Usage Magnitude
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x6F, // Usage Offset
       0x15,0x80, // Logical Minimum 80h (-128d)
       0x25,0x7F, // Logical Maximum 7Fh (127d)
       0x36,0xF0,0xD8, // Physical Minimum D8F0h (-10000d)
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x71, // Usage Phase
       0x66,0x14,0x00, // Unit 14h (20d)
       0x55,0xFE, // Unit Exponent FEh (254d)
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x47,0xA0,0x8C,0x00,0x00, // Physical Maximum 8CA0h (36000d)
       0x91,0x02, // Output (Variable)
       0x09,0x72, // Usage Period
       0x26,0xFF,0x7F, // Logical Maximum 7FFFh (32767d)
       0x46,0xFF,0x7F, // Physical Maximum 7FFFh (32767d)
       0x66,0x03,0x10, // Unit 1003h (4099d)
       0x55,0xFD, // Unit Exponent FDh (253d)
       0x75,0x10, // Report Size 10h (16d)
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x66,0x00,0x00, // Unit 0
       0x55,0x00, // Unit Exponent 0
    0xC0 , // End Collection
    0x09,0x73, // Usage Set Constant Force Rep...
    0xA1,0x02, // Collection Datalink
       0x85,0x05, // Report ID 5
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x70, // Usage Magnitude
       0x16,0x01,0xFF, // Logical Minimum FF01h (-255d)
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x36,0xF0,0xD8, // Physical Minimum D8F0h (-10000d)
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x75,0x10, // Report Size 10h (16d)
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
    0xC0 , // End Collection
    0x09,0x74, // Usage Set Ramp Force Report
    0xA1,0x02, // Collection Datalink
       0x85,0x06, // Report ID 6
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x75, // Usage Ramp Start
       0x09,0x76, // Usage Ramp End
       0x15,0x80, // Logical Minimum 80h (-128d)
       0x25,0x7F, // Logical Maximum 7Fh (127d)
       0x36,0xF0,0xD8, // Physical Minimum D8F0h (-10000d)
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x75,0x08, // Report Size 8
       0x95,0x02, // Report Count 2
       0x91,0x02, // Output (Variable)
    0xC0 , // End Collection
    0x09,0x68, // Usage Custom Force Data Rep...
    0xA1,0x02, // Collection Datalink
       0x85,0x07, // Report ID 7
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x6C, // Usage Custom Force Data Offset
       0x15,0x00, // Logical Minimum 0
       0x26,0x10,0x27, // Logical Maximum 2710h (10000d)
       0x35,0x00, // Physical Minimum 0
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x75,0x10, // Report Size 10h (16d)
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x69, // Usage Custom Force Data
       0x15,0x81, // Logical Minimum 81h (-127d)
       0x25,0x7F, // Logical Maximum 7Fh (127d)
       0x35,0x00, // Physical Minimum 0
       0x46,0xFF,0x00, // Physical Maximum FFh (255d)
       0x75,0x08, // Report Size 8
       0x95,0x0C, // Report Count Ch (12d)
       0x92,0x02,0x01, // Output (Variable, Buffered)
    0xC0 , // End Collection
    0x09,0x66, // Usage Download Force Sample
    0xA1,0x02, // Collection Datalink
       0x85,0x08, // Report ID 8
       0x05,0x01, // Usage Page Generic Desktop
       0x09,0x30, // Usage X
       0x09,0x31, // Usage Y
       0x15,0x81, // Logical Minimum 81h (-127d)
       0x25,0x7F, // Logical Maximum 7Fh (127d)
       0x35,0x00, // Physical Minimum 0
       0x46,0xFF,0x00, // Physical Maximum FFh (255d)
       0x75,0x08, // Report Size 8
       0x95,0x02, // Report Count 2
       0x91,0x02, // Output (Variable)
    0xC0 , // End Collection
    0x05,0x0F, // Usage Page Physical Interface
    0x09,0x77, // Usage Effect Operation Report
    0xA1,0x02, // Collection Datalink
       0x85,0x0A, // Report ID Ah (10d)
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x78, // Usage Effect Operation
       0xA1,0x02, // Collection Datalink
          0x09,0x79, // Usage Op Effect Start
          0x09,0x7A, // Usage Op Effect Start Solo
          0x09,0x7B, // Usage Op Effect Stop
          0x15,0x01, // Logical Minimum 1
          0x25,0x03, // Logical Maximum 3
          0x75,0x08, // Report Size 8
          0x95,0x01, // Report Count 1
          0x91,0x00, // Output
       0xC0 , // End Collection
       0x09,0x7C, // Usage Loop Count
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x46,0xFF,0x00, // Physical Maximum FFh (255d)
       0x91,0x02, // Output (Variable)
    0xC0 , // End Collection
    0x09,0x90, // Usage PID Block Free Report
    0xA1,0x02, // Collection Datalink
       0x85,0x0B, // Report ID Bh (11d)
       0x09,0x22, // Usage Effect Block Index
       0x25,0x28, // Logical Maximum 28h (40d)
       0x15,0x01, // Logical Minimum 1
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
    0xC0 , // End Collection
    0x09,0x96, // Usage PID Device Control
    0xA1,0x02, // Collection Datalink
       0x85,0x0C, // Report ID Ch (12d)
       0x09,0x97, // Usage DC Enable Actuators
       0x09,0x98, // Usage DC Disable Actuators
       0x09,0x99, // Usage DC Stop All Effects
       0x09,0x9A, // Usage DC Device Reset
       0x09,0x9B, // Usage DC Device Pause
       0x09,0x9C, // Usage DC Device Continue
       0x15,0x01, // Logical Minimum 1
       0x25,0x06, // Logical Maximum 6
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x00, // Output
    0xC0 , // End Collection
    0x09,0x7D, // Usage Device Gain Report
    0xA1,0x02, // Collection Datalink
       0x85,0x0D, // Report ID Dh (13d)
       0x09,0x7E, // Usage Device Gain
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x46,0x10,0x27, // Physical Maximum 2710h (10000d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
    0xC0 , // End Collection
    0x09,0x6B, // Usage Set Custom Force Report
    0xA1,0x02, // Collection Datalink
       0x85,0x0E, // Report ID Eh (14d)
       0x09,0x22, // Usage Effect Block Index
       0x15,0x01, // Logical Minimum 1
       0x25,0x28, // Logical Maximum 28h (40d)
       0x35,0x01, // Physical Minimum 1
       0x45,0x28, // Physical Maximum 28h (40d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x6D, // Usage Sample Count
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x00, // Logical Maximum FFh (255d)
       0x35,0x00, // Physical Minimum 0
       0x46,0xFF,0x00, // Physical Maximum FFh (255d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x09,0x51, // Usage Sample Period
       0x66,0x03,0x10, // Unit 1003h (4099d)
       0x55,0xFD, // Unit Exponent FDh (253d)
       0x15,0x00, // Logical Minimum 0
       0x26,0xFF,0x7F, // Logical Maximum 7FFFh (32767d)
       0x35,0x00, // Physical Minimum 0
       0x46,0xFF,0x7F, // Physical Maximum 7FFFh (32767d)
       0x75,0x10, // Report Size 10h (16d)
       0x95,0x01, // Report Count 1
       0x91,0x02, // Output (Variable)
       0x55,0x00, // Unit Exponent 0
       0x66,0x00,0x00, // Unit 0
    0xC0 , // End Collection
    0x09,0xAB, // Usage Create New Effect Report
    0xA1,0x02, // Collection Datalink
       0x85,0x01, // Report ID 1
       0x09,0x25, // Usage Effect Type
       0xA1,0x02, // Collection Datalink
       0x09,0x26, // Usage ET Constant Force
       0x09,0x27, // Usage ET Ramp
       0x09,0x30, // Usage ET Square
       0x09,0x31, // Usage ET Sine
       0x09,0x32, // Usage ET Triangle
       0x09,0x33, // Usage ET Sawtooth Up
       0x09,0x34, // Usage ET Sawtooth Down
       0x09,0x40, // Usage ET Spring
       0x09,0x41, // Usage ET Damper
       0x09,0x42, // Usage ET Inertia
       0x09,0x43, // Usage ET Friction
       0x09,0x28, // Usage ET Custom Force Data
       0x25,0x0C, // Logical Maximum Ch (12d)
       0x15,0x01, // Logical Minimum 1
       0x35,0x01, // Physical Minimum 1
       0x45,0x0C, // Physical Maximum Ch (12d)
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0xB1,0x00, // Feature
    0xC0 , // End Collection
    0x05,0x01, // Usage Page Generic Desktop
    0x09,0x3B, // Usage Reserved
    0x15,0x00, // Logical Minimum 0
    0x26,0xFF,0x01, // Logical Maximum 1FFh (511d)
    0x35,0x00, // Physical Minimum 0
    0x46,0xFF,0x01, // Physical Maximum 1FFh (511d)
    0x75,0x0A, // Report Size Ah (10d)
    0x95,0x01, // Report Count 1
    0xB1,0x02, // Feature (Variable)
    0x75,0x06, // Report Size 6
    0xB1,0x01, // Feature (Constant)
 0xC0 , // End Collection
 0x05,0x0F, // Usage Page Physical Interface
 0x09,0x89, // Usage Block Load Status
 0xA1,0x02, // Collection Datalink
    0x85,0x02, // Report ID 2
    0x09,0x22, // Usage Effect Block Index
    0x25,0x28, // Logical Maximum 28h (40d)
    0x15,0x01, // Logical Minimum 1
    0x35,0x01, // Physical Minimum 1
    0x45,0x28, // Physical Maximum 28h (40d)
    0x75,0x08, // Report Size 8
    0x95,0x01, // Report Count 1
    0xB1,0x02, // Feature (Variable)
    0x09,0x8B, // Usage Block Load Status
    0xA1,0x02, // Collection Datalink
       0x09,0x8C, // Usage Block Load Success
       0x09,0x8D, // Usage Block Load Full
       0x09,0x8E, // Usage Block Load Error
       0x25,0x03, // Logical Maximum 3
       0x15,0x01, // Logical Minimum 1
       0x35,0x01, // Physical Minimum 1
       0x45,0x03, // Physical Maximum 3
       0x75,0x08, // Report Size 8
       0x95,0x01, // Report Count 1
       0xB1,0x00, // Feature
    0xC0 , // End Collection
    0x09,0xAC, // Usage Undefined
    0x15,0x00, // Logical Minimum 0
    0x27,0xFF,0xFF,0x00,0x00, // Logical Maximum FFFFh (65535d)
    0x35,0x00, // Physical Minimum 0
    0x47,0xFF,0xFF,0x00,0x00, // Physical Maximum FFFFh (65535d)
    0x75,0x10, // Report Size 10h (16d)
    0x95,0x01, // Report Count 1
    0xB1,0x00, // Feature
 0xC0 , // End Collection
 0x09,0x7F, // Usage PID Pool Report
 0xA1,0x02, // Collection Datalink
    0x85,0x03, // Report ID 3
    0x09,0x80, // Usage RAM Pool size
    0x75,0x10, // Report Size 10h (16d)
    0x95,0x01, // Report Count 1
    0x15,0x00, // Logical Minimum 0
    0x35,0x00, // Physical Minimum 0
    0x27,0xFF,0xFF,0x00,0x00, // Logical Maximum FFFFh (65535d)
    0x47,0xFF,0xFF,0x00,0x00, // Physical Maximum FFFFh (65535d)
    0xB1,0x02, // Feature (Variable)
    0x09,0x83, // Usage Simultaneous Effects Max
    0x26,0xFF,0x00, // Logical Maximum FFh (255d)
    0x46,0xFF,0x00, // Physical Maximum FFh (255d)
    0x75,0x08, // Report Size 8
    0x95,0x01, // Report Count 1
    0xB1,0x02, // Feature (Variable)
    0x09,0xA9, // Usage Device Managed Pool
    0x09,0xAA, // Usage Shared Parameter Blocks
    0x75,0x01, // Report Size 1
    0x95,0x02, // Report Count 2
    0x15,0x00, // Logical Minimum 0
    0x25,0x01, // Logical Maximum 1
    0x35,0x00, // Physical Minimum 0
    0x45,0x01, // Physical Maximum 1
    0xB1,0x02, // Feature (Variable)
    0x75,0x06, // Report Size 6
    0x95,0x01, // Report Count 1
    0xB1,0x03, // Feature (Constant, Variable)
    0xC0, // End Collection
 0xC0 // End Collection

};*/
/*
uint8_t ReportDescriptor[1298] =
{
		0x05,0x01,  //    Usage Page Generic Desktop
		 0x09,0x04,  //    Usage Joystick
		 0xA1,0x01,  //    Collection Application
		    0x85,0x01,        //    Report ID 1
		    0x85,0x01,
		    0x09,0x30,        //    Usage X
		    0x16,0x00,0xFE,   //    Logical Minimum FE00h (-512d)
		    0x26,0xFF,0x01,   //    Logical Maximum 1FFh (511d)
		    0x35,0x00,        //    Physical Minimum 0
		    0x46,0xFF,0x03,   //    Physical Maximum 3FFh (1023d)
		    0x75,0x0A,        //    Report Size Ah (10d)
		    0x95,0x01,        //    Report Count 1
		    0x81,0x02,        //    Input (Variable)
		    0x75,0x06,        //    Report Size 6
		    0x81,0x03,        //    Input (Constant, Variable)
		    0xA1,0x00,        //    Collection Linked
		       0x05,0x01,        //    Usage Page Generic Desktop
		       0x09,0x31,        //    Usage Y
		       0x15,0x00,        //    Logical Minimum 0
		       0x25,0x3F,        //    Logical Maximum 3Fh (63d)
		       0x35,0x00,        //    Physical Minimum 0
		       0x45,0x3F,        //    Physical Maximum 3Fh (63d)
		       0x75,0x06,        //    Report Size 6
		       0x95,0x01,        //    Report Count 1
		       0x81,0x02,        //    Input (Variable)
		       0x75,0x02,        //    Report Size 2
		       0x81,0x03,        //    Input (Constant, Variable)
		       0x09,0x35,        //    Usage Rz
		       0x75,0x06,        //    Report Size 6
		       0x81,0x02,        //    Input (Variable)
		       0x75,0x02,        //    Report Size 2
		       0x81,0x03,        //    Input (Constant, Variable)
		    0xC0    ,         //    End Collection
		    0x05,0x09,        //    Usage Page Button
		    0x15,0x00,        //    Logical Minimum 0
		    0x19,0x01,        //    Usage Minimum Button 1
		    0x29,0x08,        //    Usage Maximum Button 8
		    0x25,0x01,        //    Logical Maximum 1
		    0x35,0x00,        //    Physical Minimum 0
		    0x45,0x01,        //    Physical Maximum 1
		    0x75,0x01,        //    Report Size 1
		    0x95,0x08,        //    Report Count 8
		    0x81,0x02,        //    Input (Variable)
		    0x06,0x01,0xFF,   //    Usage Page Generic Desktop
		    0x09,0x49,        //    Usage Undefined
		    0x75,0x01,        //    Report Size 1
		    0x95,0x01,        //    Report Count 1
		    0x81,0x02,        //    Input (Variable)
		    0x75,0x07,        //    Report Size 7
		    0x81,0x03,        //    Input (Constant, Variable)
		    0x05,0x0F,        //    Usage Page Physical Interface
		    0x09,0x92,        //    Usage ES Playing
		    0xA1,0x02,        //    Collection Datalink
		       0x85,0x02,    //    Report ID 2
		       0x09,0x9F,    //    Usage DS Device is Reset
		       0x09,0xA0,    //    Usage DS Device is Pause
		       0x09,0xA4,    //    Usage Actuator Power
		       0x09,0xA5,    //    Usage Undefined
		       0x09,0xA6,    //    Usage Undefined
		       0x15,0x00,    //    Logical Minimum 0
		       0x25,0x01,    //    Logical Maximum 1
		       0x35,0x00,    //    Physical Minimum 0
		       0x45,0x01,    //    Physical Maximum 1
		       0x75,0x01,    //    Report Size 1
		       0x95,0x05,    //    Report Count 5
		       0x81,0x02,    //    Input (Variable)
		       0x95,0x03,    //    Report Count 3
		       0x81,0x03,    //    Input (Constant, Variable)
		       0x09,0x94,    //    Usage PID Device Control
		       0x15,0x00,    //    Logical Minimum 0
		       0x25,0x01,    //    Logical Maximum 1
		       0x35,0x00,    //    Physical Minimum 0
		       0x45,0x01,    //    Physical Maximum 1
		       0x75,0x01,    //    Report Size 1
		       0x95,0x01,    //    Report Count 1
		       0x81,0x02,    //    Input (Variable)
		       0x09,0x22,    //    Usage Effect Block Index
		       0x15,0x01,    //    Logical Minimum 1
		       0x25,0x28,    //    Logical Maximum 28h (40d)
		       0x35,0x01,    //    Physical Minimum 1
		       0x45,0x28,    //    Physical Maximum 28h (40d)
		       0x75,0x07,    //    Report Size 7
		       0x95,0x01,    //    Report Count 1
		       0x81,0x02,    //    Input (Variable)
		    0xC0    ,    // End Collection
		    0x09,0x21,    //    Usage Set Effect Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x01,    //    Report ID 1
		       0x09,0x22,    //    Usage Effect Block Index
		       0x15,0x01,    //    Logical Minimum 1
		       0x25,0x28,    //    Logical Maximum 28h (40d)
		       0x35,0x01,    //    Physical Minimum 1
		       0x45,0x28,    //    Physical Maximum 28h (40d)
		       0x75,0x08,    //    Report Size 8
		       0x95,0x01,    //    Report Count 1
		       0x91,0x02,    //    Output (Variable)
		       0x09,0x25,    //    Usage Effect Type
		       0xA1,0x02,    //    Collection Datalink
		          0x09,0x26,    //    Usage ET Constant Force
		          0x09,0x27,    //    Usage ET Ramp
		          0x09,0x30,    //    Usage ET Square
		          0x09,0x31,    //    Usage ET Sine
		          0x09,0x32,    //    Usage ET Triangle
		          0x09,0x33,    //    Usage ET Sawtooth Up
		          0x09,0x34,    //    Usage ET Sawtooth Down
		          0x09,0x40,    //    Usage ET Spring
		          0x09,0x41,    //    Usage ET Damper
		          0x09,0x42,    //    Usage ET Inertia
		          0x09,0x43,    //    Usage ET Friction
		          0x09,0x28,    //    Usage ET Custom Force Data
		          0x25,0x0C,    //    Logical Maximum Ch (12d)
		          0x15,0x01,    //    Logical Minimum 1
		          0x35,0x01,    //    Physical Minimum 1
		          0x45,0x0C,    //    Physical Maximum Ch (12d)
		          0x75,0x08,    //    Report Size 8
		          0x95,0x01,    //    Report Count 1
		          0x91,0x00,    //    Output
		       0xC0    ,          //    End Collection
		       0x09,0x50,         //    Usage Duration
		       0x09,0x54,         //    Usage Trigger Repeat Interval
		       0x09,0x51,         //    Usage Sample Period
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x7F,    //    Logical Maximum 7FFFh (32767d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0xFF,0x7F,    //    Physical Maximum 7FFFh (32767d)
		       0x66,0x03,0x10,    //    Unit 1003h (4099d)
		       0x55,0xFD,         //    Unit Exponent FDh (253d)
		       0x75,0x10,         //    Report Size 10h (16d)
		       0x95,0x03,         //    Report Count 3
		       0x91,0x02,         //    Output (Variable)
		       0x55,0x00,         //    Unit Exponent 0
		       0x66,0x00,0x00,    //    Unit 0
		       0x09,0x52,         //    Usage Gain
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x00,    //    Logical Maximum FFh (255d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x53,         //    Usage Trigger Button
		       0x15,0x01,         //    Logical Minimum 1
		       0x25,0x08,         //    Logical Maximum 8
		       0x35,0x01,         //    Physical Minimum 1
		       0x45,0x08,         //    Physical Maximum 8
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x55,         //    Usage Axes Enable
		       0xA1,0x02,         //    Collection Datalink
		          0x05,0x01,    //    Usage Page Generic Desktop
		          0x09,0x30,    //    Usage X
		          0x09,0x31,    //    Usage Y
		          0x15,0x00,    //    Logical Minimum 0
		          0x25,0x01,    //    Logical Maximum 1
		          0x75,0x01,    //    Report Size 1
		          0x95,0x02,    //    Report Count 2
		          0x91,0x02,    //    Output (Variable)
		       0xC0     ,    // End Collection
		       0x05,0x0F,    //    Usage Page Physical Interface
		       0x09,0x56,    //    Usage Direction Enable
		       0x95,0x01,    //    Report Count 1
		       0x91,0x02,    //    Output (Variable)
		       0x95,0x05,    //    Report Count 5
		       0x91,0x03,    //    Output (Constant, Variable)
		       0x09,0x57,    //    Usage Direction
		       0xA1,0x02,    //    Collection Datalink
		          0x0B,0x01,0x00,0x0A,0x00,    //    Usage Ordinals: Instance 1
		          0x0B,0x02,0x00,0x0A,0x00,    //    Usage Ordinals: Instance 2
		          0x66,0x14,0x00,              //    Unit 14h (20d)
		          0x55,0xFE,                   //    Unit Exponent FEh (254d)
		          0x15,0x00,                   //    Logical Minimum 0
		          0x26,0xFF,0x00,              //    Logical Maximum FFh (255d)
		          0x35,0x00,                   //    Physical Minimum 0
		          0x47,0xA0,0x8C,0x00,0x00,    //    Physical Maximum 8CA0h (36000d)
		          0x66,0x00,0x00,              //    Unit 0
		          0x75,0x08,                   //    Report Size 8
		          0x95,0x02,                   //    Report Count 2
		          0x91,0x02,                   //    Output (Variable)
		          0x55,0x00,                   //    Unit Exponent 0
		          0x66,0x00,0x00,              //    Unit 0
		       0xC0     ,         //    End Collection
		       0x05,0x0F,         //    Usage Page Physical Interface
		       0x09,0xA7,         //    Usage Undefined
		       0x66,0x03,0x10,    //    Unit 1003h (4099d)
		       0x55,0xFD,         //    Unit Exponent FDh (253d)
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x7F,    //    Logical Maximum 7FFFh (32767d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0xFF,0x7F,    //    Physical Maximum 7FFFh (32767d)
		       0x75,0x10,         //    Report Size 10h (16d)
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x66,0x00,0x00,    //    Unit 0
		       0x55,0x00,         //    Unit Exponent 0
		    0xC0     ,    //    End Collection
		    0x05,0x0F,    //    Usage Page Physical Interface
		    0x09,0x5A,    //    Usage Set Envelope Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x02,         //    Report ID 2
		       0x09,0x22,         //    Usage Effect Block Index
		       0x15,0x01,         //    Logical Minimum 1
		       0x25,0x28,         //    Logical Maximum 28h (40d)
		       0x35,0x01,         //    Physical Minimum 1
		       0x45,0x28,         //    Physical Maximum 28h (40d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x5B,         //    Usage Attack Level
		       0x09,0x5D,         //    Usage Fade Level
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x00,    //    Logical Maximum FFh (255d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x95,0x02,         //    Report Count 2
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x5C,         //    Usage Attack Time
		       0x09,0x5E,         //    Usage Fade Time
		       0x66,0x03,0x10,    //    Unit 1003h (4099d)
		       0x55,0xFD,         //    Unit Exponent FDh (253d)
		       0x26,0xFF,0x7F,    //    Logical Maximum 7FFFh (32767d)
		       0x46,0xFF,0x7F,    //    Physical Maximum 7FFFh (32767d)
		       0x75,0x10,         //    Report Size 10h (16d)
		       0x91,0x02,         //    Output (Variable)
		       0x45,0x00,         //    Physical Maximum 0
		       0x66,0x00,0x00,    //    Unit 0
		       0x55,0x00,         //    Unit Exponent 0
		    0xC0     ,            //    End Collection
		    0x09,0x5F,    //    Usage Set Condition Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x03,    //    Report ID 3
		       0x09,0x22,    //    Usage Effect Block Index
		       0x15,0x01,    //    Logical Minimum 1
		       0x25,0x28,    //    Logical Maximum 28h (40d)
		       0x35,0x01,    //    Physical Minimum 1
		       0x45,0x28,    //    Physical Maximum 28h (40d)
		       0x75,0x08,    //    Report Size 8
		       0x95,0x01,    //    Report Count 1
		       0x91,0x02,    //    Output (Variable)
		       0x09,0x23,    //    Usage Parameter Block Offset
		       0x15,0x00,    //    Logical Minimum 0
		       0x25,0x01,    //    Logical Maximum 1
		       0x35,0x00,    //    Physical Minimum 0
		       0x45,0x01,    //    Physical Maximum 1
		       0x75,0x04,    //    Report Size 4
		       0x95,0x01,    //    Report Count 1
		       0x91,0x02,    //    Output (Variable)
		       0x09,0x58,    //    Usage Type Specific Block Off...
		       0xA1,0x02,    //    Collection Datalink
		          0x0B,0x01,0x00,0x0A,0x00,    //    Usage Ordinals: Instance 1
		          0x0B,0x02,0x00,0x0A,0x00,    //    Usage Ordinals: Instance 2
		          0x75,0x02,                   //    Report Size 2
		          0x95,0x02,                   //    Report Count 2
		          0x91,0x02,                   //    Output (Variable)
		       0xC0     ,         //    End Collection
		       0x15,0x80,         //    Logical Minimum 80h (-128d)
		       0x25,0x7F,         //    Logical Maximum 7Fh (127d)
		       0x36,0xF0,0xD8,    //    Physical Minimum D8F0h (-10000d)
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x09,0x60,         //    Usage CP Offset
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x36,0xF0,0xD8,    //    Physical Minimum D8F0h (-10000d)
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x09,0x61,         //    Usage Positive Coefficient
		       0x09,0x62,         //    Usage Negative Coefficient
		       0x95,0x02,         //    Report Count 2
		       0x91,0x02,         //    Output (Variable)
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x00,    //    Logical Maximum FFh (255d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x09,0x63,         //    Usage Positive Saturation
		       0x09,0x64,         //    Usage Negative Saturation
		       0x75,0x08,         //    Report Size 8
		       0x95,0x02,         //    Report Count 2
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x65,         //    Usage Dead Band
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		    0xC0     ,    //    End Collection
		    0x09,0x6E,    //    Usage Set Periodic Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x04,                   //    Report ID 4
		       0x09,0x22,                   //    Usage Effect Block Index
		       0x15,0x01,                   //    Logical Minimum 1
		       0x25,0x28,                   //    Logical Maximum 28h (40d)
		       0x35,0x01,                   //    Physical Minimum 1
		       0x45,0x28,                   //    Physical Maximum 28h (40d)
		       0x75,0x08,                   //    Report Size 8
		       0x95,0x01,                   //    Report Count 1
		       0x91,0x02,                   //    Output (Variable)
		       0x09,0x70,                   //    Usage Magnitude
		       0x15,0x00,                   //    Logical Minimum 0
		       0x26,0xFF,0x00,              //    Logical Maximum FFh (255d)
		       0x35,0x00,                   //    Physical Minimum 0
		       0x46,0x10,0x27,              //    Physical Maximum 2710h (10000d)
		       0x75,0x08,                   //    Report Size 8
		       0x95,0x01,                   //    Report Count 1
		       0x91,0x02,                   //    Output (Variable)
		       0x09,0x6F,                   //    Usage Offset
		       0x15,0x80,                   //    Logical Minimum 80h (-128d)
		       0x25,0x7F,                   //    Logical Maximum 7Fh (127d)
		       0x36,0xF0,0xD8,              //    Physical Minimum D8F0h (-10000d)
		       0x46,0x10,0x27,              //    Physical Maximum 2710h (10000d)
		       0x95,0x01,                   //    Report Count 1
		       0x91,0x02,                   //    Output (Variable)
		       0x09,0x71,                   //    Usage Phase
		       0x66,0x14,0x00,              //    Unit 14h (20d)
		       0x55,0xFE,                   //    Unit Exponent FEh (254d)
		       0x15,0x00,                   //    Logical Minimum 0
		       0x26,0xFF,0x00,              //    Logical Maximum FFh (255d)
		       0x35,0x00,                   //    Physical Minimum 0
		       0x47,0xA0,0x8C,0x00,0x00,    //    Physical Maximum 8CA0h (36000d)
		       0x91,0x02,                   //    Output (Variable)
		       0x09,0x72,                   //    Usage Period
		       0x26,0xFF,0x7F,              //    Logical Maximum 7FFFh (32767d)
		       0x46,0xFF,0x7F,              //    Physical Maximum 7FFFh (32767d)
		       0x66,0x03,0x10,              //    Unit 1003h (4099d)
		       0x55,0xFD,                   //    Unit Exponent FDh (253d)
		       0x75,0x10,                   //    Report Size 10h (16d)
		       0x95,0x01,                   //    Report Count 1
		       0x91,0x02,                   //    Output (Variable)
		       0x66,0x00,0x00,              //    Unit 0
		       0x55,0x00,                   //    Unit Exponent 0
		    0xC0     ,    // End Collection
		    0x09,0x73,    //    Usage Set Constant Force Rep...
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x05,         //    Report ID 5
		       0x09,0x22,         //    Usage Effect Block Index
		       0x15,0x01,         //    Logical Minimum 1
		       0x25,0x28,         //    Logical Maximum 28h (40d)
		       0x35,0x01,         //    Physical Minimum 1
		       0x45,0x28,         //    Physical Maximum 28h (40d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x70,         //    Usage Magnitude
		       0x16,0x01,0xFF,    //    Logical Minimum FF01h (-255d)
		       0x26,0xFF,0x00,    //    Logical Maximum FFh (255d)
		       0x36,0xF0,0xD8,    //    Physical Minimum D8F0h (-10000d)
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x75,0x10,         //    Report Size 10h (16d)
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		    0xC0     ,    //    End Collection
		    0x09,0x74,    //    Usage Set Ramp Force Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x06,         //    Report ID 6
		       0x09,0x22,         //    Usage Effect Block Index
		       0x15,0x01,         //    Logical Minimum 1
		       0x25,0x28,         //    Logical Maximum 28h (40d)
		       0x35,0x01,         //    Physical Minimum 1
		       0x45,0x28,         //    Physical Maximum 28h (40d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x75,         //    Usage Ramp Start
		       0x09,0x76,         //    Usage Ramp End
		       0x15,0x80,         //    Logical Minimum 80h (-128d)
		       0x25,0x7F,         //    Logical Maximum 7Fh (127d)
		       0x36,0xF0,0xD8,    //    Physical Minimum D8F0h (-10000d)
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x02,         //    Report Count 2
		       0x91,0x02,         //    Output (Variable)
		    0xC0     ,    //    End Collection
		    0x09,0x68,    //    Usage Custom Force Data Rep...
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x07,         //    Report ID 7
		       0x09,0x22,         //    Usage Effect Block Index
		       0x15,0x01,         //    Logical Minimum 1
		       0x25,0x28,         //    Logical Maximum 28h (40d)
		       0x35,0x01,         //    Physical Minimum 1
		       0x45,0x28,         //    Physical Maximum 28h (40d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x6C,         //    Usage Custom Force Data Offset
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0x10,0x27,    //    Logical Maximum 2710h (10000d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x75,0x10,         //    Report Size 10h (16d)
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x69,         //    Usage Custom Force Data
		       0x15,0x81,         //    Logical Minimum 81h (-127d)
		       0x25,0x7F,         //    Logical Maximum 7Fh (127d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0xFF,0x00,    //    Physical Maximum FFh (255d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x0C,         //    Report Count Ch (12d)
		       0x92,0x02,0x01,    //       Output (Variable, Buffered)
		    0xC0     ,    //    End Collection
		    0x09,0x66,    //    Usage Download Force Sample
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x08,         //    Report ID 8
		       0x05,0x01,         //    Usage Page Generic Desktop
		       0x09,0x30,         //    Usage X
		       0x09,0x31,         //    Usage Y
		       0x15,0x81,         //    Logical Minimum 81h (-127d)
		       0x25,0x7F,         //    Logical Maximum 7Fh (127d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0xFF,0x00,    //    Physical Maximum FFh (255d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x02,         //    Report Count 2
		       0x91,0x02,         //    Output (Variable)
		    0xC0     ,   //    End Collection
		    0x05,0x0F,   //    Usage Page Physical Interface
		    0x09,0x77,   //    Usage Effect Operation Report
		    0xA1,0x02,   //    Collection Datalink
		       0x85,0x0A,    //    Report ID Ah (10d)
		       0x09,0x22,    //    Usage Effect Block Index
		       0x15,0x01,    //    Logical Minimum 1
		       0x25,0x28,    //    Logical Maximum 28h (40d)
		       0x35,0x01,    //    Physical Minimum 1
		       0x45,0x28,    //    Physical Maximum 28h (40d)
		       0x75,0x08,    //    Report Size 8
		       0x95,0x01,    //    Report Count 1
		       0x91,0x02,    //    Output (Variable)
		       0x09,0x78,    //    Usage Operation
		       0xA1,0x02,    //    Collection Datalink
		          0x09,0x79,    //    Usage Op Effect Start
		          0x09,0x7A,    //    Usage Op Effect Start Solo
		          0x09,0x7B,    //    Usage Op Effect Stop
		          0x15,0x01,    //    Logical Minimum 1
		          0x25,0x03,    //    Logical Maximum 3
		          0x75,0x08,    //    Report Size 8
		          0x95,0x01,    //    Report Count 1
		          0x91,0x00,    //    Output
		       0xC0     ,         //    End Collection
		       0x09,0x7C,         //    Usage Loop Count
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x00,    //    Logical Maximum FFh (255d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0xFF,0x00,    //    Physical Maximum FFh (255d)
		       0x91,0x02,         //    Output (Variable)
		    0xC0     ,    //    End Collection
		    0x09,0x90,    //    Usage PID State Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x0B,    //    Report ID Bh (11d)
		       0x09,0x22,    //    Usage Effect Block Index
		       0x25,0x28,    //    Logical Maximum 28h (40d)
		       0x15,0x01,    //    Logical Minimum 1
		       0x35,0x01,    //    Physical Minimum 1
		       0x45,0x28,    //    Physical Maximum 28h (40d)
		       0x75,0x08,    //    Report Size 8
		       0x95,0x01,    //    Report Count 1
		       0x91,0x02,    //    Output (Variable)
		    0xC0     ,    //    End Collection
		    0x09,0x96,    //    Usage DC Disable Actuators
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x0C,    //    Report ID Ch (12d)
		       0x09,0x97,    //    Usage DC Stop All Effects
		       0x09,0x98,    //    Usage DC Device Reset
		       0x09,0x99,    //    Usage DC Device Pause
		       0x09,0x9A,    //    Usage DC Device Continue
		       0x09,0x9B,    //    Usage PID Device State
		       0x09,0x9C,    //    Usage DS Actuators Enabled
		       0x15,0x01,    //    Logical Minimum 1
		       0x25,0x06,    //    Logical Maximum 6
		       0x75,0x08,    //    Report Size 8
		       0x95,0x01,    //    Report Count 1
		       0x91,0x00,    //    Output
		    0xC0     ,    //    End Collection
		    0x09,0x7D,    //    Usage PID Pool Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x0D,         //    Report ID Dh (13d)
		       0x09,0x7E,         //    Usage RAM Pool Size
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x00,    //    Logical Maximum FFh (255d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0x10,0x27,    //    Physical Maximum 2710h (10000d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		    0xC0     ,            //    End Collection
		    0x09,0x6B,    //    Usage Set Custom Force Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x0E,         //    Report ID Eh (14d)
		       0x09,0x22,         //    Usage Effect Block Index
		       0x15,0x01,         //    Logical Minimum 1
		       0x25,0x28,         //    Logical Maximum 28h (40d)
		       0x35,0x01,         //    Physical Minimum 1
		       0x45,0x28,         //    Physical Maximum 28h (40d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x6D,         //    Usage Sample Count
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x00,    //    Logical Maximum FFh (255d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0xFF,0x00,    //    Physical Maximum FFh (255d)
		       0x75,0x08,         //    Report Size 8
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x09,0x51,         //    Usage Sample Period
		       0x66,0x03,0x10,    //    Unit 1003h (4099d)
		       0x55,0xFD,         //    Unit Exponent FDh (253d)
		       0x15,0x00,         //    Logical Minimum 0
		       0x26,0xFF,0x7F,    //    Logical Maximum 7FFFh (32767d)
		       0x35,0x00,         //    Physical Minimum 0
		       0x46,0xFF,0x7F,    //    Physical Maximum 7FFFh (32767d)
		       0x75,0x10,         //    Report Size 10h (16d)
		       0x95,0x01,         //    Report Count 1
		       0x91,0x02,         //    Output (Variable)
		       0x55,0x00,         //    Unit Exponent 0
		       0x66,0x00,0x00,    //    Unit 0
		    0xC0     ,    //    End Collection
		    0x09,0xAB,    //    Usage Create New Effect Report
		    0xA1,0x02,    //    Collection Datalink
		       0x85,0x01,    //    Report ID 1
		       0x09,0x25,    //    Usage Effect Type
		       0xA1,0x02,    //    Collection Datalink
		       0x09,0x26,    //    Usage ET Constant Force
		       0x09,0x27,    //    Usage ET Ramp
		       0x09,0x30,    //    Usage ET Square
		       0x09,0x31,    //    Usage ET Sine
		       0x09,0x32,    //    Usage ET Triangle
		       0x09,0x33,    //    Usage ET Sawtooth Up
		       0x09,0x34,    //    Usage ET Sawtooth Down
		       0x09,0x40,    //    Usage ET Spring
		       0x09,0x41,    //    Usage ET Damper
		       0x09,0x42,    //    Usage ET Inertia
		       0x09,0x43,    //    Usage ET Friction
		       0x09,0x28,    //    Usage ET Custom Force Data
		       0x25,0x0C,    //    Logical Maximum Ch (12d)
		       0x15,0x01,    //    Logical Minimum 1
		       0x35,0x01,    //    Physical Minimum 1
		       0x45,0x0C,    //    Physical Maximum Ch (12d)
		       0x75,0x08,    //    Report Size 8
		       0x95,0x01,    //    Report Count 1
		       0xB1,0x00,    //    Feature
		    0xC0     ,    // End Collection
		    0x05,0x01,         //    Usage Page Generic Desktop
		    0x09,0x3B,         //    Usage Byte Count
		    0x15,0x00,         //    Logical Minimum 0
		    0x26,0xFF,0x01,    //    Logical Maximum 1FFh (511d)
		    0x35,0x00,         //    Physical Minimum 0
		    0x46,0xFF,0x01,    //    Physical Maximum 1FFh (511d)
		    0x75,0x0A,         //    Report Size Ah (10d)
		    0x95,0x01,         //    Report Count 1
		    0xB1,0x02,         //    Feature (Variable)
		    0x75,0x06,         //    Report Size 6
		    0xB1,0x01,         //    Feature (Constant)
		 0xC0     ,    //    End Collection
		 0x05,0x0F,    //    Usage Page Physical Interface
		 0x09,0x89,    //    Usage Block Load Status
		 0xA1,0x02,    //    Collection Datalink
		    0x85,0x02,    //    Report ID 2
		    0x09,0x22,    //    Usage Effect Block Index
		    0x25,0x28,    //    Logical Maximum 28h (40d)
		    0x15,0x01,    //    Logical Minimum 1
		    0x35,0x01,    //    Physical Minimum 1
		    0x45,0x28,    //    Physical Maximum 28h (40d)
		    0x75,0x08,    //    Report Size 8
		    0x95,0x01,    //    Report Count 1
		    0xB1,0x02,    //    Feature (Variable)
		    0x09,0x8B,    //    Usage Block Load Full
		    0xA1,0x02,    //    Collection Datalink
		       0x09,0x8C,    //    Usage Block Load Error
		       0x09,0x8D,    //    Usage Block Handle
		       0x09,0x8E,    //    Usage PID Block Free Report
		       0x25,0x03,    //    Logical Maximum 3
		       0x15,0x01,    //    Logical Minimum 1
		       0x35,0x01,    //    Physical Minimum 1
		       0x45,0x03,    //    Physical Maximum 3
		       0x75,0x08,    //    Report Size 8
		       0x95,0x01,    //    Report Count 1
		       0xB1,0x00,    //    Feature
		    0xC0     ,                   // End Collection
		    0x09,0xAC,                   //    Usage Undefined
		    0x15,0x00,                   //    Logical Minimum 0
		    0x27,0xFF,0xFF,0x00,0x00,    //    Logical Maximum FFFFh (65535d)
		    0x35,0x00,                   //    Physical Minimum 0
		    0x47,0xFF,0xFF,0x00,0x00,    //    Physical Maximum FFFFh (65535d)
		    0x75,0x10,                   //    Report Size 10h (16d)
		    0x95,0x01,                   //    Report Count 1
		    0xB1,0x00,                   //    Feature
		 0xC0     ,    //    End Collection
		 0x09,0x7F,    //    Usage ROM Pool Size
		 0xA1,0x02,    //    Collection Datalink
		    0x85,0x03,                   //    Report ID 3
		    0x09,0x80,                   //    Usage ROM Effect Block Count
		    0x75,0x10,                   //    Report Size 10h (16d)
		    0x95,0x01,                   //    Report Count 1
		    0x15,0x00,                   //    Logical Minimum 0
		    0x35,0x00,                   //    Physical Minimum 0
		    0x27,0xFF,0xFF,0x00,0x00,    //    Logical Maximum FFFFh (65535d)
		    0x47,0xFF,0xFF,0x00,0x00,    //    Physical Maximum FFFFh (65535d)
		    0xB1,0x02,                   //    Feature (Variable)
		    0x09,0x83,                   //    Usage PID Pool Move Report
		    0x26,0xFF,0x00,              //    Logical Maximum FFh (255d)
		    0x46,0xFF,0x00,              //    Physical Maximum FFh (255d)
		    0x75,0x08,                   //    Report Size 8
		    0x95,0x01,                   //    Report Count 1
		    0xB1,0x02,                   //    Feature (Variable)
		    0x09,0xA9,                   //    Usage Undefined
		    0x09,0xAA,                   //    Usage Undefined
		    0x75,0x01,                   //    Report Size 1
		    0x95,0x02,                   //    Report Count 2
		    0x15,0x00,                   //    Logical Minimum 0
		    0x25,0x01,                   //    Logical Maximum 1
		    0x35,0x00,                   //    Physical Minimum 0
		    0x45,0x01,                   //    Physical Maximum 1
		    0xB1,0x02,                   //    Feature (Variable)
		    0x75,0x06,                   //    Report Size 6
		    0x95,0x01,                   //    Report Count 1
		    0xB1,0x03,                   //    Feature (Constant, Variable)
		    0xC0,    //    End Collection
		 0xC0    //    End Collection
};*/


typedef struct
{
	__IO uint16_t ADDR_TX;
	__IO uint16_t COUNT_TX;
	__IO uint16_t ADDR_RX;
	__IO uint16_t COUNT_RX;
} BTableLayout;

#endif /* USB_DEFINITIONS_H_ */
