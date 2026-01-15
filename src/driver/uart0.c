#include "uart0.h"

// stdio.h 에 있는 표준 입출력 스트링 함수 
// FILE OUTPUT = FDEV_SETUP_STREAM(UART0_PutChar, NULL, _FDEV_SETUP_WRITE);
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_PutChar, NULL, _FDEV_SETUP_WRITE);

volatile char rxBuff[100] = {0}; // 수신 버퍼 설정
volatile uint8_t rxFlag = 0;     // 수신 완료 플래그를 설정

ISR(USART0_RX_vect){    // 수신 인터럽트 핸들러
    static uint8_t rxHead = 0;      // 수신된 데이터의 인덱스
    uint8_t rxData = UDR0;          // 수신된 데이터를 rxData로 대입

    if(rxData == '\n' || rxData == '\r'){ // 수신 데이터 마지막이 개행이라 리턴이면
        
        rxBuff[rxHead] = '\0';      // 널문자 넣어주고
        rxHead = 0;                 // 인덱스 초기화해주고
        rxFlag = 1;                 // 문자열이 수신되엇음
    }
      else
    {
        if (rxHead < sizeof(rxBuff) - 1)
            rxBuff[rxHead++] = (char)rxData;
        // else: overflow면 버리거나 rxHead=0 등 정책 선택
    }
    // else{
    //     rxBuff[rxHead] = rxData;    // 수신된 데이터 버퍼에 추가
    //     rxHead++;                   // 인덱스 1 증가 
    // }
}

// ISR(USART0_RX_vect){
//     // UART0_Transmit('A');
//     uint8_t rxData = UDR0;    // RXC 클리어
//     UART0_Transmit(rxData);  // 에코
// }


void UART_Init()
{
    UBRR0H = 0x00;
    UBRR0L = 207;       // 9600bps 설정
    // 비동기, 8비트데이터, 패리티비트 없음, 스톱비트 1비트
    UCSR0A |= (1<<U2X0);
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);      // 수신가능, 송신가능
    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);    // 8비트 사용

    // 수신 인터럽트만 추가
    UCSR0B |= (1<<RXCIE0);      // 수신 인터럽트 인에이블

}

void UART0_Transmit(char data)
{
    while(!(UCSR0A & (1<<UDRE0)));      // 송신 가능할때까지 대기, UDR이 비어 있는지?
    UDR0 = data;
}

uint8_t UART0_Receive()
{
    while(!(UCSR0A & (1<<RXC0)));       // 데이터 수신 대기
    return UDR0;
}
void UART0_SendByte(uint8_t data)
{
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

int UART0_PutChar(char data, FILE *stream)
{
    UART0_SendByte((uint8_t)data);
    return 0;
}
// int UART0_PutChar(char data, FILE *stream)
// {
//     while (!(UCSR0A & (1<<UDRE0)));
//     UDR0 = data;
//     return 0;
// }


// #include "uart0.h"


// // stdio.h에 있는 표준 입출력 스트림 함수임
// FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);


// volatile char rxBuff[100] = {0};     // 수신 버퍼를 설정
// volatile uint8_t rxFlag = 0;         // 수신 완료 플래그를 설정

// ISR(USART0_RX_vect)     // 수신 인터럽트 핸들러
// {
//     static uint8_t rxHead = 0;          // 수신된 데이터의 인덱스
//     uint8_t rxData = UDR0;              // 수신된 데이터를 rxData로 대입
//     if(rxData == '\n' || rxData == '\r')    // 수신데이터 마지막이 개행이나 리턴이면
//     {
//         rxBuff[rxHead] = '\0';          // 널문자 넣어주고
//         rxHead = 0;                     // 인덱스 초기화 해주고
//         rxFlag = 1;                     // 문자열이 수신됬음을 깃발 세우고
//     }
//     else                                // 그렇지 않으면 문자열을 계속 받음
//     {
//         rxBuff[rxHead] = rxData;        // 수신된 데이터 버퍼에 추가
//         rxHead++;                       // 인덱스 1 증가
//     }
// }


// void UART_Init()
// {
//     UBRR0H = 0x00;
//     UBRR0L = 207;       // 9600bps 설정
//     // 비동기, 8비트데이터, 패리티비트 없음, 스톱비트 1비트
//     UCSR0A = (1<<U2X0);    // 2배속 설정
//     UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);      // 수신가능, 송신가능
//     UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);    // 8비트 사용

//     // 수신 인터럽트 만 추가했음
//     // UCSR0B = (1<<RXCIE0);      // 수신 인터럽트 인에이블

//     //SREG |= (1<<7);


//     sei();                  // 전역 인터럽트 활성화
// }


// uint8_t UART0_Receive()
// {
//     while(!(UCSR0A & (1<<RXC0)));       // 데이터 수신 대기
//     return UDR0;
// }

// // int UART0_Transmit(char data, FILE *stream)
// // {
// //     while (!(UCSR0A & (1<< UDRE0)));
// //     UDR0 = data;
// //     return 0;
// // }

// void UART0_Transmit(char data)
// {
//     while(!(UCSR0A & (1<<UDRE0)));      // 송신 가능할때까지 대기, UDR이 비어 있는지?
//     UDR0 = data;
// }
