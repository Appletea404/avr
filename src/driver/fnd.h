#include "../common/def.h"

#define FND_DATA_DDR      DDRA         //DATA 포트 설정
#define FND_SELECT_DDR    DDRB         //DATB 포트 설정
#define FND_DATA_PORT     PORTA        //데이터 레지스터 설정
#define FND_SELECT_PORT   PORTB        //셀렉트 레지스터 설정

void fndDisplay(uint16_t data);
