#include "../common/def.h"

#define LED_DDR DDRD
#define LED_PORTD PORTD     //여기 변경

// include와 함수의 원형을 분리

typedef struct
{
    volatile uint8_t *port;         //LED가 연결된 포트
    uint8_t          pinNumber;     //LED가 연결된 핀번호
}LED;


// 함수의 원형선언
void ledInit(LED *led);
void ledOn(LED *led);
void ledOff(LED *led);
void GPIO_OUTPUT(LED *led);
void ledLeftShift(LED *led);
void ledRightShift(LED *led);
// void GPIO_OUTPUT(uint8_t data);
// void ledLeftShift(uint8_t *data);
// void ledRightShift(uint8_t *data);