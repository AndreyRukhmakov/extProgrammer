#include "nand.h"
#include "appConfig.h"

static const char *TAG = "NAND:";

#define CMD_READ_ID        0x90
#define CMD_READ_STATUS    0x70

typedef union {
    unsigned char byte;
    struct {
    	unsigned char _0 :1;
    	unsigned char _1 :1;
    	unsigned char _2 :1;
    	unsigned char _3 :1;
    	unsigned char _4 :1;
    	unsigned char _5 :1;
    	unsigned char _6 :1;
    	unsigned char _7 :1;
    }bit;
}bitField08t;

/******************************************************************************************
 *
 ******************************************************************************************/
void nandIdleBus(void)
{
	gpio_set_level(NAND_PIN_CE, 1);
	gpio_set_level(NAND_PIN_RE, 1);
	gpio_set_level(NAND_PIN_WE, 1);
	gpio_set_level(NAND_PIN_CLE, 0);
	gpio_set_level(NAND_PIN_ALE, 0);
}

/******************************************************************************************
 *
 ******************************************************************************************/
void controlGpioSetup(void)
{
	gpio_reset_pin((gpio_num_t)NAND_PIN_CE);
	gpio_set_direction((gpio_num_t)NAND_PIN_CE, GPIO_MODE_OUTPUT);
	gpio_set_level(NAND_PIN_CE, 1);

	gpio_reset_pin((gpio_num_t)NAND_PIN_RB);
	gpio_set_direction((gpio_num_t)NAND_PIN_RB, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_RB, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_RE);
	gpio_set_direction((gpio_num_t)NAND_PIN_RE, GPIO_MODE_OUTPUT);
	gpio_set_level(NAND_PIN_RE, 1);

	gpio_reset_pin((gpio_num_t)NAND_PIN_CLE);
	gpio_set_direction((gpio_num_t)NAND_PIN_CLE, GPIO_MODE_OUTPUT);
	gpio_set_level(NAND_PIN_CLE, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_ALE);
	gpio_set_direction((gpio_num_t)NAND_PIN_ALE, GPIO_MODE_OUTPUT);
	gpio_set_level(NAND_PIN_ALE, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_WE);
	gpio_set_direction((gpio_num_t)NAND_PIN_WE, GPIO_MODE_OUTPUT);
	gpio_set_level(NAND_PIN_WE, 1);
}

/******************************************************************************************
 *
 ******************************************************************************************/
void dataPortSetOutput(void)
{
	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_0);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_0, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_0, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_1);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_1, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_1, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_2);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_2, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_2, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_3);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_3, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_3, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_4);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_4, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_4, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_5);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_5, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_5, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_6);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_6, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_6, 0);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_7);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_7, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)NAND_PIN_IO_7, 0);
}

/******************************************************************************************
 *
 ******************************************************************************************/
void dataPortSetInput(void)
{
	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_0);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_0, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_0, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_1);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_1, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_1, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_2);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_2, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_2, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_3);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_3, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_3, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_4);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_4, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_4, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_5);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_5, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_5, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_6);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_6, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_6, GPIO_PULLUP_ONLY);

	gpio_reset_pin((gpio_num_t)NAND_PIN_IO_7);
	gpio_set_direction((gpio_num_t)NAND_PIN_IO_7, GPIO_MODE_INPUT);
	gpio_set_pull_mode((gpio_num_t)NAND_PIN_IO_7, GPIO_PULLUP_ONLY);
}

/******************************************************************************************
 *
 ******************************************************************************************/
void dataPortRead(unsigned char *data)
{
	bitField08t bitField08;

	bitField08.bit._0 = gpio_get_level((gpio_num_t)NAND_PIN_IO_0);
	bitField08.bit._1 = gpio_get_level((gpio_num_t)NAND_PIN_IO_1);
	bitField08.bit._2 = gpio_get_level((gpio_num_t)NAND_PIN_IO_2);
	bitField08.bit._3 = gpio_get_level((gpio_num_t)NAND_PIN_IO_3);
	bitField08.bit._4 = gpio_get_level((gpio_num_t)NAND_PIN_IO_4);
	bitField08.bit._5 = gpio_get_level((gpio_num_t)NAND_PIN_IO_5);
	bitField08.bit._6 = gpio_get_level((gpio_num_t)NAND_PIN_IO_6);
	bitField08.bit._7 = gpio_get_level((gpio_num_t)NAND_PIN_IO_7);

	*data = bitField08.byte;
}

/******************************************************************************************
 *
 ******************************************************************************************/
void dataPortWrite(unsigned char data)
{
	bitField08t bitField08;
	bitField08.byte = data;

    gpio_set_level((gpio_num_t)NAND_PIN_IO_0, bitField08.bit._0);
    gpio_set_level((gpio_num_t)NAND_PIN_IO_1, bitField08.bit._1);
    gpio_set_level((gpio_num_t)NAND_PIN_IO_2, bitField08.bit._2);
    gpio_set_level((gpio_num_t)NAND_PIN_IO_3, bitField08.bit._3);
    gpio_set_level((gpio_num_t)NAND_PIN_IO_4, bitField08.bit._4);
    gpio_set_level((gpio_num_t)NAND_PIN_IO_5, bitField08.bit._5);
    gpio_set_level((gpio_num_t)NAND_PIN_IO_6, bitField08.bit._6);
    gpio_set_level((gpio_num_t)NAND_PIN_IO_7, bitField08.bit._7);
}

/******************************************************************************************
 *
 ******************************************************************************************/
void nandGpioInit(void)
{
	controlGpioSetup();
//	dataPortSetInput();
	nandIdleBus();
}

/******************************************************************************************
 *
 ******************************************************************************************/
void nandChipSelect(bool value)
{
	if (true == value)
	{
		gpio_set_level((gpio_num_t)NAND_PIN_CE, 0);
	}
	else
	{
		gpio_set_level((gpio_num_t)NAND_PIN_CE, 1);
	}
}

/******************************************************************************************
 *
 ******************************************************************************************/
int getBusyStatus(void)
{
    return gpio_get_level((gpio_num_t)NAND_PIN_RB);
}

/******************************************************************************************
 *
 ******************************************************************************************/
void nandSendCommand(unsigned char command)
{
    gpio_set_level((gpio_num_t)NAND_PIN_CLE, 1);
    gpio_set_level((gpio_num_t)NAND_PIN_WE, 0);
    dataPortWrite(command);
    gpio_set_level((gpio_num_t)NAND_PIN_WE, 1);

//    if (last) digitalWrite(NAND_CL, LOW); ????
    gpio_set_level((gpio_num_t)NAND_PIN_CLE, 0);
}

/******************************************************************************************
 *
 ******************************************************************************************/
void nandSendAddress(unsigned char column, unsigned char page, unsigned int block)
{
    gpio_set_level((gpio_num_t)NAND_PIN_ALE, 1);

    gpio_set_level((gpio_num_t)NAND_PIN_WE, 0);
    dataPortWrite(column);
    gpio_set_level((gpio_num_t)NAND_PIN_WE, 1);

    gpio_set_level((gpio_num_t)NAND_PIN_WE, 0);
    dataPortWrite((page & 0x1F) | ((block & 0x07) << 5));
    gpio_set_level((gpio_num_t)NAND_PIN_WE, 1);

    gpio_set_level((gpio_num_t)NAND_PIN_WE, 0);
    dataPortWrite((block >> 3) & 0xFF);
    gpio_set_level((gpio_num_t)NAND_PIN_WE, 1);

    gpio_set_level((gpio_num_t)NAND_PIN_WE, 0);
    dataPortWrite((block >> 11) & 0x03);
    gpio_set_level((gpio_num_t)NAND_PIN_WE, 1);

    gpio_set_level((gpio_num_t)NAND_PIN_ALE, 0);
}

/******************************************************************************************
 *
 ******************************************************************************************/
unsigned char nandReadId(void)
{
  unsigned char manufacturer = 0x00, id = 0x00;

  nandChipSelect(true);

  dataPortSetOutput();
  nandSendCommand(CMD_READ_ID);
  gpio_set_level((gpio_num_t)NAND_PIN_ALE, 1);
  gpio_set_level((gpio_num_t)NAND_PIN_WE, 0);
  dataPortWrite(0);
  gpio_set_level((gpio_num_t)NAND_PIN_WE, 1);
  gpio_set_level((gpio_num_t)NAND_PIN_ALE, 0);

  dataPortSetInput();
  gpio_set_level((gpio_num_t)NAND_PIN_RE, 0);
  dataPortRead(&manufacturer);
  gpio_set_level((gpio_num_t)NAND_PIN_RE, 1);
  gpio_set_level((gpio_num_t)NAND_PIN_RE, 0);
  dataPortRead(&id);
  gpio_set_level((gpio_num_t)NAND_PIN_RE, 1);

  ESP_LOGI(TAG, "NAND manufacturer: 0x%x", manufacturer);
  ESP_LOGI(TAG, "NAND device ID   : 0x%x", id);

  nandChipSelect(false);

  return id;
}

/******************************************************************************************
 *
 ******************************************************************************************/
unsigned char nandReadStatus(void)
{
	unsigned char status = 0x00;

	nandChipSelect(true);

	dataPortSetOutput();
    nandSendCommand(CMD_READ_STATUS);

    dataPortSetInput();
    gpio_set_level((gpio_num_t)NAND_PIN_RE, 0);
    dataPortRead(&status);
    gpio_set_level((gpio_num_t)NAND_PIN_RE, 1);

    nandChipSelect(false);

    ESP_LOGI(TAG, "NAND status: 0x%x", status);

    return status;
}
