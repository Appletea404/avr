    #include "ap.h"



    void apInit()
    {   
        UART_Init();            // UART 초기화   
    }



    // 실질적인 메인함수
    void apMain()
    {


        stdout = &OUTPUT;       // 출력 스트림을 지정

        sei();
        while (1)
        {
            if(rxFlag == 1)     // 문자열 수신이 완료되면
            {
                rxFlag = 0;         // 플래그 초기화
                printf("%s\n", rxBuff);     // 수신된 문자열 출력
            }
    
        }
    }