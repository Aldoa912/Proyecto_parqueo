//Proyecto 3 electronica digital 2

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"

#define TARGET_IS_TM4C123_RA1

#define LED_PIN GPIO_PIN_6
#define LED_PORT GPIO_PORTA_BASE
#define LED_PIN_FULL GPIO_PIN_7
#define LED_PORT_FULL GPIO_PORTA_BASE
#define PHOTO_PIN GPIO_PIN_4
#define PHOTO_PORT GPIO_PORTB_BASE

#define LED2_PIN GPIO_PIN_6
#define LED2_PORT GPIO_PORTD_BASE
#define LED2_PIN_FULL GPIO_PIN_4
#define LED2_PORT_FULL GPIO_PORTA_BASE
#define PHOTO2_PIN GPIO_PIN_5
#define PHOTO2_PORT GPIO_PORTB_BASE

#define LED3_PIN GPIO_PIN_6
#define LED3_PORT GPIO_PORTB_BASE
#define LED3_PIN_FULL GPIO_PIN_7
#define LED3_PORT_FULL GPIO_PORTB_BASE
#define PHOTO3_PIN GPIO_PIN_2
#define PHOTO3_PORT GPIO_PORTE_BASE

#define LED4_PIN GPIO_PIN_2
#define LED4_PORT GPIO_PORTB_BASE
#define LED4_PIN_FULL GPIO_PIN_3
#define LED4_PORT_FULL GPIO_PORTB_BASE
#define PHOTO4_PIN GPIO_PIN_1
#define PHOTO4_PORT GPIO_PORTE_BASE

#define ADC_SEQ_NUM 0
#define ADC_SEQ_NUM2 1
#define ADC_SEQ_NUM3 2
#define ADC_SEQ_NUM4 3

int parqueo;

void setup() {
  // Configurar el sistema
  SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

  // Habilitar los periféricos necesarios
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

  // Configurar los pines
  GPIOPinTypeADC(PHOTO_PORT, PHOTO_PIN);
  GPIOPinTypeGPIOOutput(LED_PORT, LED_PIN);
  GPIOPinTypeGPIOOutput(LED_PORT_FULL, LED_PIN_FULL);

  GPIOPinTypeADC(PHOTO2_PORT, PHOTO2_PIN);
  GPIOPinTypeGPIOOutput(LED2_PORT, LED2_PIN);
  GPIOPinTypeGPIOOutput(LED2_PORT_FULL, LED2_PIN_FULL);

  GPIOPinTypeADC(PHOTO3_PORT, PHOTO3_PIN);
  GPIOPinTypeGPIOOutput(LED3_PORT, LED3_PIN);
  GPIOPinTypeGPIOOutput(LED3_PORT_FULL, LED3_PIN_FULL);

  GPIOPinTypeADC(PHOTO4_PORT, PHOTO4_PIN);
  GPIOPinTypeGPIOOutput(LED4_PORT, LED4_PIN);
  GPIOPinTypeGPIOOutput(LED4_PORT_FULL, LED4_PIN_FULL);

  // Configurar la ADC
  ADCSequenceConfigure(ADC0_BASE, ADC_SEQ_NUM, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQ_NUM, 0, ADC_CTL_CH10 | ADC_CTL_IE | ADC_CTL_END);
  ADCSequenceConfigure(ADC0_BASE, ADC_SEQ_NUM2, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQ_NUM2, 0, ADC_CTL_CH11 | ADC_CTL_IE | ADC_CTL_END);
  ADCSequenceConfigure(ADC0_BASE, ADC_SEQ_NUM3, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQ_NUM3, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
  ADCSequenceConfigure(ADC0_BASE, ADC_SEQ_NUM4, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQ_NUM4, 0, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);

  ADCSequenceEnable(ADC0_BASE, ADC_SEQ_NUM);
  ADCSequenceEnable(ADC0_BASE, ADC_SEQ_NUM2);
  ADCSequenceEnable(ADC0_BASE, ADC_SEQ_NUM3);
  ADCSequenceEnable(ADC0_BASE, ADC_SEQ_NUM4);

  // se habilita y configura el UART
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  GPIOPinConfigure(GPIO_PB0_U1RX);
  GPIOPinConfigure(GPIO_PB1_U1TX);
  GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1);
  UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));
  UARTEnable(UART1_BASE);


  // se habilita la interrupcion del UART0
//  IntEnable(INT_UART2);
//  UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
}

 int main(void) {
  // Inicializar el sistema
  setup();

  // Loop principal
  while (1) {
    // Leer el valor de la fotoresistencia
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQ_NUM);
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQ_NUM, false)) {}
    uint32_t photo_value;
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQ_NUM, &photo_value);

    ADCProcessorTrigger(ADC0_BASE, ADC_SEQ_NUM2);
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQ_NUM2, false)) {}
    uint32_t photo_value2;
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQ_NUM2, &photo_value2);

    ADCProcessorTrigger(ADC0_BASE, ADC_SEQ_NUM3);
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQ_NUM3, false)) {}
    uint32_t photo_value3;
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQ_NUM3, &photo_value3);

    ADCProcessorTrigger(ADC0_BASE, ADC_SEQ_NUM4);
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQ_NUM4, false)) {}
    uint32_t photo_value4;
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQ_NUM4, &photo_value4);

    // Encender la LED si la luz es suficiente
    if (photo_value > 1500) {
        GPIOPinWrite(LED_PORT, LED_PIN, LED_PIN);
        GPIOPinWrite(LED_PORT_FULL, LED_PIN_FULL, 0);
        UARTCharPut(UART1_BASE, 'a');
    } else {
        GPIOPinWrite(LED_PORT_FULL, LED_PIN_FULL, LED_PIN_FULL);
        GPIOPinWrite(LED_PORT, LED_PIN, 0);
        UARTCharPut(UART1_BASE, 'b');
    }

    if (photo_value2 > 1500) {
        GPIOPinWrite(LED2_PORT, LED2_PIN, LED2_PIN);
        GPIOPinWrite(LED2_PORT_FULL, LED2_PIN_FULL, 0);
        UARTCharPut(UART1_BASE, 'c');
    } else {
        GPIOPinWrite(LED2_PORT_FULL, LED2_PIN_FULL, LED2_PIN_FULL);
        GPIOPinWrite(LED2_PORT, LED2_PIN, 0);
        UARTCharPut(UART1_BASE, 'd');
    }

    if (photo_value3 > 1500) {
        GPIOPinWrite(LED3_PORT, LED3_PIN, LED3_PIN);
        GPIOPinWrite(LED3_PORT_FULL, LED3_PIN_FULL, 0);
        UARTCharPut(UART1_BASE, 'e');
    } else {
        GPIOPinWrite(LED3_PORT_FULL, LED3_PIN_FULL, LED3_PIN_FULL);
        GPIOPinWrite(LED3_PORT, LED3_PIN, 0);
        UARTCharPut(UART1_BASE, 'f');
    }

    if (photo_value4 > 1500) {
        GPIOPinWrite(LED4_PORT, LED4_PIN, LED4_PIN);
        GPIOPinWrite(LED4_PORT_FULL, LED4_PIN_FULL, 0);
        UARTCharPut(UART1_BASE, 'g');
    } else {
        GPIOPinWrite(LED4_PORT_FULL, LED4_PIN_FULL, LED4_PIN_FULL);
        GPIOPinWrite(LED4_PORT, LED4_PIN, 0);
        UARTCharPut(UART1_BASE, 'h');
    }
  }
}

//void UART2IntHandler(void){
//    // se baja la bandera de la interrupcion
//    UARTIntClear(UART2_BASE, UART_INT_RX | UART_INT_RT);
//    UARTCharPut(UART2_BASE, parqueo);
//
//
//}
