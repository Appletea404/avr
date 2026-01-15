#include "../common/def.h"

void UART_Init();
void UART0_Transmit(char data);
uint8_t UART0_Receive();
void UART0_SendByte(uint8_t data);
int UART0_PutChar(char data, FILE *stream);

extern FILE OUTPUT;
extern volatile char rxBuff[100];
extern volatile uint8_t rxFlag;


// #include "../common/def.h"



// void UART_Init();
// void UART0_Transmit(char data);
// // int UART0_Transmit(char data, FILE *stream);


// uint8_t UART0_Receive();


// extern FILE OUTPUT;
// volatile extern char rxBuff[100];
// volatile extern uint8_t rxFlag;