
#include <stdio.h>
#include "driver/i2c.h"

#include "lcd1602_lib.h"

uint8_t lcd1602_addr;

int lcd1602_write_cmd(uint8_t addr, uint8_t cmd)
{
    i2c_cmd_handle_t hCmd = i2c_cmd_link_create();
    i2c_master_start(hCmd);
    i2c_master_write_byte(hCmd, ( addr << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(hCmd, cmd, ACK_CHECK_EN);
    i2c_master_stop(hCmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, hCmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(hCmd);

    if (ret != ESP_OK) {
        printf("%s(%x, %x) error [0x%x]\n", __func__, addr, cmd, ret);
	}

    return ret;
}

int lcd1602_write_data(uint8_t addr, uint8_t data[], int len)
{
    i2c_cmd_handle_t hCmd = i2c_cmd_link_create();
    i2c_master_start(hCmd);
    i2c_master_write_byte(hCmd, ( addr << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write(hCmd, data, len, ACK_CHECK_EN);
    i2c_master_stop(hCmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, hCmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(hCmd);

    if (ret != ESP_OK) {
        printf("%s(%x, %x.., %d) error [0x%x]\n", __func__, addr, data[0], len, ret);
	}

    return ret;
}

int lcd1602_write_cmdNdata(uint8_t addr, uint8_t cmd, uint8_t data)
{
    i2c_cmd_handle_t hCmd = i2c_cmd_link_create();
    i2c_master_start(hCmd);
    i2c_master_write_byte(hCmd, ( addr << 1 ) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(hCmd, cmd, ACK_CHECK_EN);
    i2c_master_write_byte(hCmd, data, ACK_CHECK_EN);
    i2c_master_stop(hCmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, hCmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(hCmd);

    if (ret != ESP_OK) {
        printf("%s(%x, %x, %x) error [0x%x]\n", __func__, addr, cmd, data, ret);
	}

    return ret;
}

int lcd1602_SendInternal(uint8_t data, uint8_t flags)
{
	int ret;
	uint8_t up = data & 0xF0;
	uint8_t lo = (data << 4) & 0xF0;

	uint8_t data_arr[4];
	data_arr[0] = up|flags|BACKLIGHT|PIN_EN;
	data_arr[1] = up|flags|BACKLIGHT;
	data_arr[2] = lo|flags|BACKLIGHT|PIN_EN;
	data_arr[3] = lo|flags|BACKLIGHT;

    ret = lcd1602_write_data(lcd1602_addr, data_arr, 4);

    if (ret != ESP_OK) {
        printf("%s(%x, %x) error [0x%x]\n", __func__, data, flags, ret);
	}

    vTaskDelay(LCD_DELAY_MS / portTICK_PERIOD_MS);
	return ret;
}

void lcd1602_SendCommand(uint8_t cmd)
{
	lcd1602_SendInternal(cmd, 0);
}

void lcd1602_SendData(uint8_t data)
{
	lcd1602_SendInternal(data, PIN_RS);
}

void lcd1602_SendString(char *str)
{
	while(*str)
	{
		lcd1602_SendData((uint8_t)(*str));
		str++;
	}
}

void lcd1602_Init(void)
{
	// 4-bit mode, 2 lines, 5x7 format
	lcd1602_SendCommand(0x30);
	// display & cursor home (keep this!)
	lcd1602_SendCommand(0x02);
	// display on, right shift, underline off, blink off
	lcd1602_SendCommand(0x0C);
	// clear display (optional here)
	lcd1602_SendCommand(0x01);
}

void i2c_scan(void)
{
    uint8_t addr;

	printf("scanning I2C bus...\r\n");
	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");

    for (int i = 0; i < 128; i += 16) {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++) {
            fflush(stdout);
            addr = i + j;
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (addr << 1) | WRITE_BIT, ACK_CHECK_EN);
            i2c_master_stop(cmd);
            esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 50 / portTICK_PERIOD_MS);
            i2c_cmd_link_delete(cmd);
            if (ret == ESP_OK) {
                printf("%02x ", addr);
				if (addr == 0x27 || addr == 0x3f) {
					lcd1602_addr = addr;
				}
            } else if (ret == ESP_ERR_TIMEOUT) {
                printf("UU ");
            } else {
                printf("-- ");
            }
        }
        printf("\r\n");
    }
	printf("lcd1602_addr = 0x%02x\r\n", lcd1602_addr);
}

void lcd1602_i2c_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = LCD1602_GPIO_SDA;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = LCD1602_GPIO_SCL;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_MASTER_RX_BUF_DISABLE,
                       I2C_MASTER_TX_BUF_DISABLE, 0);
	printf("I2C mode  = %d\r\n", conf.mode);
	printf("SDA pin   = %d\r\n", conf.sda_io_num);
	printf("SCL pin   = %d\r\n", conf.scl_io_num);
	printf("CLK_speed = %lu Hz\r\n", conf.master.clk_speed);
}
