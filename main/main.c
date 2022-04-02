#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "st7789.h"

#define TAG "main"
#define DELAY 200

static void AlienTest(TFT_t * dev, int width, int height, int key)
{
    int bg = WHITE;
    int fg = BLACK;
    for (int x = 0; x < width; x++)
    {
        bg = rgb565_conv((31 - x / 5) << 3, (x / 3) << 2, 0);
        for (int y = 0; y < height; y++)
        {
            int16_t color = fg;
            if ((x ^ y) % key) color = bg;
            lcdDrawPixel(dev, x, y, color);
        }
    }
}

static void ST7789(void *pvParameters)
{
    TFT_t lcd;

    spi_master_init(&lcd, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
    lcdInit(&lcd, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);

    while(1)
    {
        AlienTest(&lcd, CONFIG_WIDTH, CONFIG_HEIGHT, 9);
        AlienTest(&lcd, CONFIG_WIDTH, CONFIG_HEIGHT, 17);
        AlienTest(&lcd, CONFIG_WIDTH, CONFIG_HEIGHT, 33);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG,"Hello!");

    xTaskCreate(ST7789, "ST7789", 1024*6, NULL, 0, NULL);
}
