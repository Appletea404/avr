#include "fnd.h"

void fndDisplay(uint16_t data)
{
    static uint8_t position = 0;        //디지트의 위치를 관리하기 위해서, 포지션 값 기억위해 정적변수로 선언

    uint8_t fndData[10] =
    {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
    };
    

    switch (position)
    {
    case 0:
        //첫번째 자리를 출력하기 위해서는, 0번핀 LOW, 1번핀, 2번핀, 3번핀 HIGH
        FND_SELECT_PORT |= (1 << 0);       //digir 0 HIGH
        FND_SELECT_PORT &= ~((1 << 1) | (1<<2) | (1<<3));  //digit 1,2,3  LOW
        //입력된 데이터를 천의 자리를 구해서 해당 디지트에 값을 출력
        FND_DATA_PORT = ~fndData[data/1000];
        break;
    case 1:
        FND_SELECT_PORT |= (1 << 1);       //digir 0 HIGH
        FND_SELECT_PORT &=  ~((1<<0)| (1<<2) | (1<<3));  //digit 1,2,3  LOW
        //입력된 데이터를 백의 자리를 구해서 해당 디지트에 값을 출력
        FND_DATA_PORT = ~fndData[data/100%10];
        break;
    case 2:
        FND_SELECT_PORT |= (1 << 2);       //digir 0 HIGH
        FND_SELECT_PORT &= ~((1 << 0) | (1 << 1) | (1 << 3));  //digit 1,2,3  LOW
        //입력된 데이터를 십의 자리를 구해서 해당 디지트에 값을 출력
        FND_DATA_PORT = ~fndData[data/10%10];
        break;
    case 3:
        FND_SELECT_PORT |= (1 << 3);       //digir 0 HIGH
        FND_SELECT_PORT &= ~((1 << 0) | (1<<1) | (1<<2));  //digit 1,2,3  LOW
        //입력된 데이터를 일의 자리를 구해서 해당 디지트에 값을 출력
        FND_DATA_PORT = ~fndData[data%10];
        break;
    }
    position++;     //다음 자리로 이동하기 위해서 포지션값을 증가
    position = position % 4;    //4자리를 출력후에 다시 처음
}
