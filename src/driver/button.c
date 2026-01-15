#include "button.h"

void buttonInit(BUTTON *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
{
    btn->ddr = ddr;
    btn->pin = pin;
    btn->btnPin = pinNum;
    btn->prevState = RELEASED;     // 초기화 상태를 의미해서 아무것도 안누른 상태
    *btn->ddr &= ~(1<<btn->btnPin); // 버튼핀을 입력으로 설정
}

uint8_t buttonGetState(BUTTON *btn)
{
    uint8_t currState = *btn -> pin & (1<<btn->btnPin);  
    // btnPin의 숫자만큼 shift 해서 pin과 동기화 해서 현재 버튼의 상태를 읽어옴
    if((currState == PUSHED) && (btn -> prevState == RELEASED)) //안누른 상태에서 누르면
    {
        _delay_ms(50);             // debounce code
        btn -> prevState = PUSHED; // 버튼을 누른 상태로 변경
        return ACT_PUSH;           // 버튼이 눌렸음을 반환
    }
    else if((currState != PUSHED) && (btn -> prevState == PUSHED)) // 버튼을 누른상태에서 떼면
    {
        _delay_ms(50);
        btn -> prevState = RELEASED; // 버튼 상태를 손뗌 상태로 변경
        return ACT_RELEASE;          // 버튼이 떨어졌음을 반환
    }
    return NO_ACT;          //아무것도 안했을 때
}