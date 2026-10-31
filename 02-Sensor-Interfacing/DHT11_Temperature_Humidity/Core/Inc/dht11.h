#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"

void DHT11_Init(GPIO_TypeDef *DHT_PORT, uint16_t DHT_PIN);
uint8_t DHT11_Read(uint8_t *temp, uint8_t *hum);

#endif /* INC_DHT11_H_ */
