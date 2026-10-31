#include "dht11.h"
#include "main.h"

GPIO_TypeDef *DHT_PORT_;
uint16_t DHT_PIN_;

void delay_us(uint16_t us) {
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (HAL_RCC_GetHCLKFreq() / 1000000);
    while ((DWT->CYCCNT - start) < ticks);
}

void DHT11_Init(GPIO_TypeDef *DHT_PORT, uint16_t DHT_PIN) {
    DHT_PORT_ = DHT_PORT;
    DHT_PIN_ = DHT_PIN;

    // Enable DWT for microsecond delay
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

static void DHT11_Start(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Output
    GPIO_InitStruct.Pin = DHT_PIN_;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT_PORT_, &GPIO_InitStruct);

    HAL_GPIO_WritePin(DHT_PORT_, DHT_PIN_, GPIO_PIN_RESET);
    HAL_Delay(18);  // Pull down for at least 18 ms
    HAL_GPIO_WritePin(DHT_PORT_, DHT_PIN_, GPIO_PIN_SET);
    delay_us(20);   // Pull up for 20–40 us

    // Input
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(DHT_PORT_, &GPIO_InitStruct);
}

static uint8_t DHT11_ReadByte(void) {
    uint8_t i, byte = 0;
    for (i = 0; i < 8; i++) {
        while (!HAL_GPIO_ReadPin(DHT_PORT_, DHT_PIN_));
        delay_us(40);
        if (HAL_GPIO_ReadPin(DHT_PORT_, DHT_PIN_))
            byte |= (1 << (7 - i));
        while (HAL_GPIO_ReadPin(DHT_PORT_, DHT_PIN_));
    }
    return byte;
}

uint8_t DHT11_Read(uint8_t *temp, uint8_t *hum) {
    uint8_t rh_integral, rh_decimal, t_integral, t_decimal, checksum;

    DHT11_Start();

    if (HAL_GPIO_ReadPin(DHT_PORT_, DHT_PIN_) == GPIO_PIN_RESET) {
        while (HAL_GPIO_ReadPin(DHT_PORT_, DHT_PIN_));
        while (!HAL_GPIO_ReadPin(DHT_PORT_, DHT_PIN_));
        while (HAL_GPIO_ReadPin(DHT_PORT_, DHT_PIN_));

        rh_integral = DHT11_ReadByte();
        rh_decimal = DHT11_ReadByte();
        t_integral = DHT11_ReadByte();
        t_decimal = DHT11_ReadByte();
        checksum = DHT11_ReadByte();

        if (checksum == (rh_integral + rh_decimal + t_integral + t_decimal)) {
            *temp = t_integral;
            *hum = rh_integral;
            return 1;  // Success
        }
    }
    return 0;  // Failure
}
