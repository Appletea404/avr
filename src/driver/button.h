#include "../common/def.h"

#define LED_DDR         DDRD
#define LED_PORT        PORTD
#define BUTTON_DDR      DDRG
#define BUTTON_PIN      PING
#define BUTTON_ON       0
#define BUTTON_OFF      1
#define BUTTON_TOGGLE   2

enum {PUSHED, RELEASED};
enum
{
    NO_ACT,
    ACT_PUSH,
    ACT_RELEASE
};

typedef struct 
{
    volatile uint8_t *ddr; // 당근 DDR의 주소이기 떄문에 포인터임
    volatile uint8_t *pin; // PORT처럼 PIN의 주소값을 가져오기 때문에 포인터임
    uint8_t btnPin;        // 핀 번호
    uint8_t prevState;     // 핀의 상태
}BUTTON; // BUTTON이라는 이름으로 대체

void buttonInit(BUTTON *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum);
uint8_t buttonGetState(BUTTON *btn);