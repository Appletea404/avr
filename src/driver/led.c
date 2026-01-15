#include "led.h"

// LED 초기화 함수를 구현
void ledInit(LED *led)
{
    *(led->port - 1) |= (1 << led->pinNumber);
    // DDR 레지스터는 PORT레지스터보다 주소가 1낮게 위치하므로
    // (led->port -1)을 이용해서 PORT에서 DDR로 접근
    // (1 << led->pinNumber)와 or연산을 통해서 지정된 포트를 출력으로 설정
}

//LED On함수
void ledOn(LED *led)
{
    *(led->port) |= (1 << led-> pinNumber);
}

// LED Off함수
void ledOff(LED *led)
{
    *(led->port) &= ~(1 << led-> pinNumber);
}

void ledLeftShift(LED *led)    //파라메타가 포인터 이기 때문에 주소값을 받아야 함
{
    *(led->port) = (led->pinNumber >> 7) | (led->pinNumber << 1);    //LED 데이터를 좌측으로 1비트 이동
    // (*data >> 7) 8비트 짜리를 7번밀면 무조건 0으로 다 만듬
    // 0000 0001 처음 들어오는 값
    // 0000 0000
    // 0000 0010 위아래 OR연산
    // 0000 0010 (출력)
    GPIO_OUTPUT(led);
}
void ledRightShift(LED *led)    //파라메타가 포인터 이기 때문에 주소값을 받아야 함
{
    *(led->port) = (led->pinNumber << 7) | (led->pinNumber >> 1);    
    
    GPIO_OUTPUT(led);
}

void GPIO_OUTPUT(LED *led)
{
    LED_PORTD = led->pinNumber;
}






// void ledLeftShift(uint8_t *data)    //파라메타가 포인터 이기 때문에 주소값을 받아야 함
// {
//     *data = (*data >> 7) | (*data << 1);    //LED 데이터를 좌측으로 1비트 이동
//     // (*data >> 7) 8비트 짜리를 7번밀면 무조건 0으로 다 만듬
//     // 0000 0001 처음 들어오는 값
//     // 0000 0000
//     // 0000 0010 위아래 OR연산
//     // 0000 0010 (출력)
//     GPIO_OUTPUT(*data);
// }
// void ledRightShift(uint8_t *data)    //파라메타가 포인터 이기 때문에 주소값을 받아야 함
// {
//     *data = (*data << 7) | (*data >> 1);    //LED 데이터를 우측으로 1비트 이동
//     GPIO_OUTPUT(*data);
// }

// void GPIO_OUTPUT(uint8_t data)
// {
//     LED_PORTD = data;
// }