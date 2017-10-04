#include "Arduino_Due_SD_HSMCI.h"
#include <SD_HSMCI/SD_HSMCI.h>

/*
 * Debug Functions (Change output channel if needed)
 */
void Debug(const char* header, const char* msg){
  if(SerialUSB && SD_DEBUG){
    SerialUSB.print(header);
    SerialUSB.print(": ");
    SerialUSB.print(msg);
  }
}

void Debug(const char* header, unsigned char msg){
  if(SerialUSB && SD_DEBUG){
    SerialUSB.print(header);
    SerialUSB.print(": ");
    SerialUSB.print(msg);
  }
}
void Debug(unsigned char msg){
  if(SerialUSB && SD_DEBUG){
    SerialUSB.print(msg);
  }
}
void Debug(const char* msg){
  if(SerialUSB && SD_DEBUG){
    SerialUSB.print(msg);
  }
}

/*
 * Pins descriptions
 */
extern const PinDescription g_APinDescription2[]=
{
#ifndef __MACCHINA_M2
    // 0 .. 53 - Digital pins
  // ----------------------
  // 0/1 - UART (Serial)
  { PIOA, PIO_PA8A_URXD,     ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT,  PIN_ATTR_DIGITAL,                 NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // URXD
  { PIOA, PIO_PA9A_UTXD,     ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT,  PIN_ATTR_DIGITAL,                 NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // UTXD

  // 2
  { PIOB, PIO_PB25B_TIOA0,   ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC0_CHA0     }, // TIOA0
  { PIOC, PIO_PC28B_TIOA7,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHA7     }, // TIOA7
  { PIOC, PIO_PC26B_TIOB6,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHB6     }, // TIOB6

  // 5
  { PIOC, PIO_PC25B_TIOA6,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHA6     }, // TIOA6
  { PIOC, PIO_PC24B_PWML7,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),   NO_ADC, NO_ADC, PWM_CH7,     NOT_ON_TIMER }, // PWML7
  { PIOC, PIO_PC23B_PWML6,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),   NO_ADC, NO_ADC, PWM_CH6,     NOT_ON_TIMER }, // PWML6
  { PIOC, PIO_PC22B_PWML5,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),   NO_ADC, NO_ADC, PWM_CH5,     NOT_ON_TIMER }, // PWML5
  { PIOC, PIO_PC21B_PWML4,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),   NO_ADC, NO_ADC, PWM_CH4,     NOT_ON_TIMER }, // PWML4
  // 10
  { PIOC, PIO_PC29B_TIOB7,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHB7     }, // TIOB7
  { PIOD, PIO_PD7B_TIOA8,    ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHA8     }, // TIOA8
  { PIOD, PIO_PD8B_TIOB8,    ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC2_CHB8     }, // TIOB8

  // 13 - AMBER LED
  { PIOB, PIO_PB27B_TIOB0,   ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_TIMER), NO_ADC, NO_ADC, NOT_ON_PWM,  TC0_CHB0     }, // TIOB0

  // 14/15 - USART3 (Serial3)
  { PIOD, PIO_PD4B_TXD3,     ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // TXD3
  { PIOD, PIO_PD5B_RXD3,     ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // RXD3

  // 16/17 - USART1 (Serial2)
  { PIOA, PIO_PA13A_TXD1,    ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // TXD1
  { PIOA, PIO_PA12A_RXD1,    ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // RXD1

  // 18/19 - USART0 (Serial1)
  { PIOA, PIO_PA11A_TXD0,    ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // TXD0
  { PIOA, PIO_PA10A_RXD0,    ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // RXD0

  // 20/21 - TWI1
  { PIOB, PIO_PB12A_TWD1,    ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // TWD1 - SDA0
  { PIOB, PIO_PB13A_TWCK1,   ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // TWCK1 - SCL0

  // 22
  { PIOB, PIO_PB26,          ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 22
  { PIOA, PIO_PA14,          ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 23
  { PIOA, PIO_PA15,          ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 24
  { PIOD, PIO_PD0,           ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 25

  // 26
  { PIOD, PIO_PD1,           ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 26
  { PIOD, PIO_PD2,           ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 27
  { PIOD, PIO_PD3,           ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 28
  { PIOD, PIO_PD6,           ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 29

  // 30
  { PIOD, PIO_PD9,           ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 30
  { PIOA, PIO_PA7,           ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 31
  { PIOD, PIO_PD10,          ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 32
  { PIOC, PIO_PC1,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 33

  // 34
  { PIOC, PIO_PC2,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 34
  { PIOC, PIO_PC3,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 35
  { PIOC, PIO_PC4,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 36
  { PIOC, PIO_PC5,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 37

  // 38
  { PIOC, PIO_PC6,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 38
  { PIOC, PIO_PC7,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 39
  { PIOC, PIO_PC8,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 40
  { PIOC, PIO_PC9,           ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 41

  // 42
  { PIOA, PIO_PA19,          ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 42
  { PIOA, PIO_PA20,          ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 43
  { PIOC, PIO_PC19,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 44
  { PIOC, PIO_PC18,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 45

  // 46
  { PIOC, PIO_PC17,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 46
  { PIOC, PIO_PC16,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 47
  { PIOC, PIO_PC15,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 48
  { PIOC, PIO_PC14,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 49

  // 50
  { PIOC, PIO_PC13,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 50
  { PIOC, PIO_PC12,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 51
  { PIOB, PIO_PB21,          ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 52
  { PIOB, PIO_PB14,          ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // PIN 53


  // 54 .. 65 - Analog pins
  // ----------------------
  { PIOA, PIO_PA16X1_AD7,    ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC0,   ADC7,   NOT_ON_PWM,  NOT_ON_TIMER }, // AD0
  { PIOA, PIO_PA24X1_AD6,    ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC1,   ADC6,   NOT_ON_PWM,  NOT_ON_TIMER }, // AD1
  { PIOA, PIO_PA23X1_AD5,    ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC2,   ADC5,   NOT_ON_PWM,  NOT_ON_TIMER }, // AD2
  { PIOA, PIO_PA22X1_AD4,    ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC3,   ADC4,   NOT_ON_PWM,  NOT_ON_TIMER }, // AD3
  // 58
  { PIOA, PIO_PA6X1_AD3,     ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC4,   ADC3,   NOT_ON_PWM,  TC0_CHB2     }, // AD4
  { PIOA, PIO_PA4X1_AD2,     ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC5,   ADC2,   NOT_ON_PWM,  NOT_ON_TIMER }, // AD5
  { PIOA, PIO_PA3X1_AD1,     ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC6,   ADC1,   NOT_ON_PWM,  TC0_CHB1     }, // AD6
  { PIOA, PIO_PA2X1_AD0,     ID_PIOA, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC7,   ADC0,   NOT_ON_PWM,  TC0_CHA1     }, // AD7
  // 62
  { PIOB, PIO_PB17X1_AD10,   ID_PIOB, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC8,   ADC10,  NOT_ON_PWM,  NOT_ON_TIMER }, // AD8
  { PIOB, PIO_PB18X1_AD11,   ID_PIOB, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC9,   ADC11,  NOT_ON_PWM,  NOT_ON_TIMER }, // AD9
  { PIOB, PIO_PB19X1_AD12,   ID_PIOB, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC10,  ADC12,  NOT_ON_PWM,  NOT_ON_TIMER }, // AD10
  { PIOB, PIO_PB20X1_AD13,   ID_PIOB, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC11,  ADC13,  NOT_ON_PWM,  NOT_ON_TIMER }, // AD11

  // 66/67 - DAC0/DAC1
  { PIOB, PIO_PB15X1_DAC0,   ID_PIOB, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC12,  DA0,    NOT_ON_PWM,  NOT_ON_TIMER }, // DAC0
  { PIOB, PIO_PB16X1_DAC1,   ID_PIOB, PIO_INPUT,    PIO_DEFAULT, PIN_ATTR_ANALOG,                   ADC13,  DA1,    NOT_ON_PWM,  NOT_ON_TIMER }, // DAC1

  // 68/69 - CANRX0/CANTX0
  { PIOA, PIO_PA1A_CANRX0,   ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  ADC14,  NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // CANRX
  { PIOA, PIO_PA0A_CANTX0,   ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  ADC15,  NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // CANTX

  // 70/71 - TWI0
  { PIOA, PIO_PA17A_TWD0,    ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // TWD0 - SDA1
  { PIOA, PIO_PA18A_TWCK0,   ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // TWCK0 - SCL1

  // 72/73 - LEDs
  { PIOC, PIO_PC30,          ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // LED AMBER RXL
  { PIOA, PIO_PA21,          ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // LED AMBER TXL

  // 74/75/76 - SPI
  { PIOA, PIO_PA25A_SPI0_MISO,ID_PIOA,PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // MISO
  { PIOA, PIO_PA26A_SPI0_MOSI,ID_PIOA,PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // MOSI
  { PIOA, PIO_PA27A_SPI0_SPCK,ID_PIOA,PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // SPCK

  // 77 - SPI CS0
  { PIOA, PIO_PA28A_SPI0_NPCS0,ID_PIOA,PIO_PERIPH_A,PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // NPCS0

  // 78 - SPI CS3 (unconnected)
  { PIOB, PIO_PB23B_SPI0_NPCS3,ID_PIOB,PIO_PERIPH_B,PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // NPCS3

  // 79 .. 84 - "All pins" masks

  // 79 - TWI0 all pins
  { PIOA, PIO_PA17A_TWD0|PIO_PA18A_TWCK0, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER },
  // 80 - TWI1 all pins
  { PIOB, PIO_PB12A_TWD1|PIO_PB13A_TWCK1, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER },
  // 81 - UART (Serial) all pins
  { PIOA, PIO_PA8A_URXD|PIO_PA9A_UTXD, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER },
  // 82 - USART0 (Serial1) all pins
  { PIOA, PIO_PA11A_TXD0|PIO_PA10A_RXD0, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER },
  // 83 - USART1 (Serial2) all pins
  { PIOA, PIO_PA13A_TXD1|PIO_PA12A_RXD1, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER },
  // 84 - USART3 (Serial3) all pins
  { PIOD, PIO_PD4B_TXD3|PIO_PD5B_RXD3, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER },

  // 85 - USB
  { PIOB, PIO_PB11A_UOTGID|PIO_PB10A_UOTGVBOF, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // ID - VBOF

  // 86 - SPI CS2
  { PIOB, PIO_PB21B_SPI0_NPCS2, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // NPCS2

  // 87 - SPI CS1
  { PIOA, PIO_PA29A_SPI0_NPCS1, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // NPCS1

  // 88/89 - CANRX1/CANTX1 (same physical pin for 66/53)
  { PIOB, PIO_PB15A_CANRX1,     ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // CANRX1
  { PIOB, PIO_PB14A_CANTX1,     ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,                  NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER }, // CANTX1

  // 90 .. 91 - "All CAN pins" masks
  // 90 - CAN0 all pins
  { PIOA, PIO_PA1A_CANRX0|PIO_PA0A_CANTX0, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC,  NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },
  // 91 - CAN1 all pins
  { PIOB, PIO_PB15A_CANRX1|PIO_PB14A_CANTX1, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_COMBO), NO_ADC, NO_ADC, NOT_ON_PWM,  NOT_ON_TIMER },

  // 92 .. 96 - PIN X0 - X4
  { PIOA, PIO_PA5,			ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN X0
  { PIOC, PIO_PC27,			ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN X1
  { PIOA, PIO_PA0,			ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN X2
  { PIOA, PIO_PA1,			ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN X3
  { PIOC, PIO_PC11,         ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN X4

  // 97 .. 100 - PWM X5 - X8
  { PIOC, PIO_PC8B_PWML3,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),	NO_ADC, NO_ADC, PWM_CH3,    NOT_ON_TIMER }, // PWM X5
  { PIOC, PIO_PC2B_PWML0,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),	NO_ADC, NO_ADC, PWM_CH0,    NOT_ON_TIMER }, // PWM X6
  { PIOC, PIO_PC6B_PWML2,   ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM),	NO_ADC, NO_ADC, PWM_CH2,    NOT_ON_TIMER }, // PWM X7
  { PIOC, PIO_PC20,			ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PWM X8

  // 101 .. 106 - HSMCI
  { PIOA, PIO_PA20A_MCCDA,  ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,   				NO_ADC, NO_ADC, NOT_ON_PWM,	NOT_ON_TIMER }, // PIN_HSMCI_MCCDA_GPIO
  { PIOA, PIO_PA19A_MCCK,	ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN_HSMCI_MCCK_GPIO
  { PIOA, PIO_PA21A_MCDA0,  ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN_HSMCI_MCDA0_GPIO
  { PIOA, PIO_PA22A_MCDA1,  ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN_HSMCI_MCDA1_GPIO
  { PIOA, PIO_PA23A_MCDA2,  ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN_HSMCI_MCDA2_GPIO
  { PIOA, PIO_PA24A_MCDA3,  ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN_HSMCI_MCDA3_GPIO

  // 107 .. 116 - ETHERNET MAC
  { PIOB, PIO_PB0A_ETXCK,   ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ETXCK
  { PIOB, PIO_PB1A_ETXEN,   ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ETXEN
  { PIOB, PIO_PB2A_ETX0,	ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ETX0
  { PIOB, PIO_PB3A_ETX1,	ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ETX1
  { PIOB, PIO_PB4A_ECRSDV,	ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ECRSDV
  { PIOB, PIO_PB5A_ERX0,	ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ERX0
  { PIOB, PIO_PB6A_ERX1,	ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ERX1
  { PIOB, PIO_PB7A_ERXER,   ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // ERXER
  { PIOB, PIO_PB8A_EMDC,	ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // EMDC
  { PIOB, PIO_PB9A_EMDIO,   ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // EMDIO

  // 117 - PIN X25
  { PIOC, PIO_PC10,			ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT, PIN_ATTR_DIGITAL,					NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }, // PIN X25

  // END
  { NULL, 0, 0, PIO_NOT_A_PIN, PIO_DEFAULT, 0, NO_ADC, NO_ADC, NOT_ON_PWM, NOT_ON_TIMER }
#endif
} ;



bool StringEquals(const char* s1, const char* s2)
{
 int i = 0;
 while(s1[i] && s2[i])
 {
   if(tolower(s1[i]) != tolower(s2[i]))
   {
     return false;
   }
   i++;
 }

 return !(s1[i] || s2[i]);
}

/*********************************************************************************

 Files & Communication

 */

MassStorage::MassStorage() : combinedName(combinedNameBuff, ARRAY_SIZE(combinedNameBuff))
{
	memset(&fileSystem, 0, sizeof(FATFS));
	findDir = new DIR();
}

bool MassStorage::Init()
{
	// Initialize SD MMC stack

  // Initialize HSMCI pins
	#ifdef __MACCHINA_M2
	PIO_Configure(g_APinDescription[PIN_HSMCI_MCCDA_GPIO].pPort, g_APinDescription[PIN_HSMCI_MCCDA_GPIO].ulPinType, g_APinDescription[PIN_HSMCI_MCCDA_GPIO].ulPin, g_APinDescription[PIN_HSMCI_MCCDA_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription[PIN_HSMCI_MCCK_GPIO].pPort, g_APinDescription[PIN_HSMCI_MCCK_GPIO].ulPinType, g_APinDescription[PIN_HSMCI_MCCK_GPIO].ulPin, g_APinDescription[PIN_HSMCI_MCCK_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription[PIN_HSMCI_MCDA0_GPIO].pPort, g_APinDescription[PIN_HSMCI_MCDA0_GPIO].ulPinType, g_APinDescription[PIN_HSMCI_MCDA0_GPIO].ulPin, g_APinDescription[PIN_HSMCI_MCDA0_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription[PIN_HSMCI_MCDA1_GPIO].pPort, g_APinDescription[PIN_HSMCI_MCDA1_GPIO].ulPinType, g_APinDescription[PIN_HSMCI_MCDA1_GPIO].ulPin, g_APinDescription[PIN_HSMCI_MCDA1_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription[PIN_HSMCI_MCDA2_GPIO].pPort, g_APinDescription[PIN_HSMCI_MCDA2_GPIO].ulPinType, g_APinDescription[PIN_HSMCI_MCDA2_GPIO].ulPin, g_APinDescription[PIN_HSMCI_MCDA2_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription[PIN_HSMCI_MCDA3_GPIO].pPort, g_APinDescription[PIN_HSMCI_MCDA3_GPIO].ulPinType, g_APinDescription[PIN_HSMCI_MCDA3_GPIO].ulPin, g_APinDescription2[PIN_HSMCI_MCDA3_GPIO].ulPinConfiguration);
	#else
	PIO_Configure(g_APinDescription2[PIN_HSMCI_MCCDA_GPIO].pPort, g_APinDescription2[PIN_HSMCI_MCCDA_GPIO].ulPinType, g_APinDescription2[PIN_HSMCI_MCCDA_GPIO].ulPin, g_APinDescription2[PIN_HSMCI_MCCDA_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription2[PIN_HSMCI_MCCK_GPIO].pPort, g_APinDescription2[PIN_HSMCI_MCCK_GPIO].ulPinType, g_APinDescription2[PIN_HSMCI_MCCK_GPIO].ulPin, g_APinDescription2[PIN_HSMCI_MCCK_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription2[PIN_HSMCI_MCDA0_GPIO].pPort, g_APinDescription2[PIN_HSMCI_MCDA0_GPIO].ulPinType, g_APinDescription2[PIN_HSMCI_MCDA0_GPIO].ulPin, g_APinDescription2[PIN_HSMCI_MCDA0_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription2[PIN_HSMCI_MCDA1_GPIO].pPort, g_APinDescription2[PIN_HSMCI_MCDA1_GPIO].ulPinType, g_APinDescription2[PIN_HSMCI_MCDA1_GPIO].ulPin, g_APinDescription2[PIN_HSMCI_MCDA1_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription2[PIN_HSMCI_MCDA2_GPIO].pPort, g_APinDescription2[PIN_HSMCI_MCDA2_GPIO].ulPinType, g_APinDescription2[PIN_HSMCI_MCDA2_GPIO].ulPin, g_APinDescription2[PIN_HSMCI_MCDA2_GPIO].ulPinConfiguration);
	PIO_Configure(g_APinDescription2[PIN_HSMCI_MCDA3_GPIO].pPort, g_APinDescription2[PIN_HSMCI_MCDA3_GPIO].ulPinType, g_APinDescription2[PIN_HSMCI_MCDA3_GPIO].ulPin, g_APinDescription2[PIN_HSMCI_MCDA3_GPIO].ulPinConfiguration);
	#endif
  //set pullups (not on clock!)
  digitalWrite(PIN_HSMCI_MCCDA_GPIO_ARDUINO, HIGH);
  digitalWrite(PIN_HSMCI_MCDA0_GPIO_ARDUINO, HIGH);
  digitalWrite(PIN_HSMCI_MCDA1_GPIO_ARDUINO, HIGH);
  digitalWrite(PIN_HSMCI_MCDA2_GPIO_ARDUINO, HIGH);
  digitalWrite(PIN_HSMCI_MCDA3_GPIO_ARDUINO, HIGH);
  pinMode(PIN_HSMCI_CARD_DETECT_ARDUINO, INPUT);


	sd_mmc_init();
	delay(20);

	bool abort = false;
	sd_mmc_err_t err;
  unsigned int now = millis();
	do {
		err = sd_mmc_check(0);
		if (err > SD_MMC_ERR_NO_CARD)
		{
			abort = true;
			delay(3000);	// Wait a few seconds, so users have a chance to see the following error message
		}
		else
		{
			abort = (err == SD_MMC_ERR_NO_CARD && (millis()-now) > 5000);
		}

		if (abort)
		{
      Debug("MS","Cannot initialize the SD card: ");

			switch (err)
			{
				case SD_MMC_ERR_NO_CARD:
					Debug("MS", "Card not found\n");
					break;
				case SD_MMC_ERR_UNUSABLE:
					Debug("MS", "Card is unusable, try another one\n");
					break;
				case SD_MMC_ERR_SLOT:
					Debug("MS", "Slot unknown\n");
					break;
				case SD_MMC_ERR_COMM:
					Debug("MS","General communication error\n");
					break;
				case SD_MMC_ERR_PARAM:
					Debug("MS","Illegal input parameter\n");
					break;
				case SD_MMC_ERR_WP:
					Debug("MS","Card write protected\n");
					break;
				default:
					Debug("MS", "Unknown (code ");
					Debug("MS",err);
					Debug("MS",")\n");
					break;
			}
			return false;
		}
	} while (err != SD_MMC_OK);

	// Print some card details (optional)

	Debug("MS", "SD card detected!\nCapacity: ");
  Debug(sd_mmc_get_capacity(0));
  Debug("\n");
	Debug("MS", "Bus clock: ");
  Debug(sd_mmc_get_bus_clock(0));
  Debug("\n");
	Debug("MS", "Bus width: ");
  Debug(sd_mmc_get_bus_width(0));
  Debug("\n");
  Debug("MS", "Card type: ");
	switch (sd_mmc_get_type(0))
	{
		case CARD_TYPE_SD | CARD_TYPE_HC:
			Debug("SDHC\n");
			break;
		case CARD_TYPE_SD:
			Debug("SD\n");
			break;
		case CARD_TYPE_MMC | CARD_TYPE_HC:
			Debug("MMC High Density\n");
			break;
		case CARD_TYPE_MMC:
			Debug("MMC\n");
			break;
		case CARD_TYPE_SDIO:
			Debug("SDIO\n");
			return false;
		case CARD_TYPE_SD_COMBO:
			Debug("SD COMBO\n");
			break;
		case CARD_TYPE_UNKNOWN:
		default:
			Debug("Unknown\n");
			return false;
	}

	// Mount the file system

	int mounted = f_mount(0, &fileSystem);
	if (mounted != FR_OK)
	{
		Debug("MS","Can't mount filesystem 0: code ");
		Debug(mounted);
        return false;
	}
    return true;
}


const char* MassStorage::CombineName(const char* directory, const char* fileName)
{
	unsigned int out = 0;
	int in = 0;

	if (directory != NULL)
	{
		while (directory[in] != 0 && directory[in] != '\n')
		{
			combinedName[out] = directory[in];
			in++;
			out++;
			if (out >= combinedName.Length())
			{
				Debug("MS","CombineName() buffer overflow.");
				out = 0;
			}
		}
	}

	if (in > 0 && directory[in -1] != '/' && out < STRING_LENGTH -1)
	{
		combinedName[out] = '/';
		out++;
	}

	in = 0;
	while (fileName[in] != 0 && fileName[in] != '\n')
	{
		combinedName[out] = fileName[in];
		in++;
		out++;
		if (out >= combinedName.Length())
		{
			Debug("MS","CombineName() buffer overflow.");
			out = 0;
		}
	}
	combinedName[out] = 0;

	return combinedName.Pointer();
}
// Open a directory to read a file list. Returns true if it contains any files, false otherwise.
bool MassStorage::FindFirst(const char *directory, FileInfo &file_info)
{
	TCHAR loc[FILENAME_LENGTH];

	// Remove the trailing '/' from the directory name
	size_t len = strnlen(directory, ARRAY_UPB(loc));
	if (len == 0)
	{
		loc[0] = 0;
	}
	else if (directory[len - 1] == '/')
	{
		strncpy(loc, directory, len - 1);
		loc[len - 1] = 0;
	}
	else
	{
		strncpy(loc, directory, len);
		loc[len] = 0;
	}

	findDir->lfn = nullptr;
	FRESULT res = f_opendir(findDir, loc);
	if (res == FR_OK)
	{
		FILINFO entry;
		entry.lfname = file_info.fileName;
		entry.lfsize = ARRAY_SIZE(file_info.fileName);

		for(;;)
		{
			res = f_readdir(findDir, &entry);
			if (res != FR_OK || entry.fname[0] == 0) break;
			if (StringEquals(entry.fname, ".") || StringEquals(entry.fname, "..")) continue;

			file_info.isDirectory = (entry.fattrib & AM_DIR);
			file_info.size = entry.fsize;
			uint16_t day = entry.fdate & 0x1F;
			if (day == 0)
			{
				// This can happen if a transfer hasn't been processed completely.
				day = 1;
			}
			file_info.day = day;
			file_info.month = (entry.fdate & 0x01E0) >> 5;
			file_info.year = (entry.fdate >> 9) + 1980;
			if (file_info.fileName[0] == 0)
			{
				strncpy(file_info.fileName, entry.fname, ARRAY_SIZE(file_info.fileName));
			}

			return true;
		}
	}

	return false;
}

// Find the next file in a directory. Returns true if another file has been read.
bool MassStorage::FindNext(FileInfo &file_info)
{
	FILINFO entry;
	entry.lfname = file_info.fileName;
	entry.lfsize = ARRAY_SIZE(file_info.fileName);

	findDir->lfn = nullptr;
	if (f_readdir(findDir, &entry) != FR_OK || entry.fname[0] == 0)
	{
		//f_closedir(findDir);
		Debug("no file found\n");
		return false;
	}
	Debug("file found\n");
	file_info.isDirectory = (entry.fattrib & AM_DIR);
	Debug("Directory: ",file_info.isDirectory);
	file_info.size = entry.fsize;
	Debug("Size: ",file_info.size);
	uint16_t day = entry.fdate & 0x1F;
	if (day == 0)
	{
		// This can happen if a transfer hasn't been processed completely.
		day = 1;
	}
	file_info.day = day;
	Debug("Day: ",file_info.day);
	file_info.month = (entry.fdate & 0x01E0) >> 5;
	Debug("Month: ",file_info.month);
	file_info.year = (entry.fdate >> 9) + 1980;
	Debug("Year: ",file_info.year);
	if (file_info.fileName[0] == 0)
	{
		strncpy(file_info.fileName, entry.fname, ARRAY_SIZE(file_info.fileName));
	}
	Debug("File name: ",file_info.fileName);
	
	return true;
}

// Month names. The first entry is used for invalid month numbers.
static const char *monthNames[13] = { "???", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

// Returns the name of the specified month or '???' if the specified value is invalid.
const char* MassStorage::GetMonthName(const uint8_t month)
{
	return (month <= 12) ? monthNames[month] : monthNames[0];
}

// Delete a file or directory
bool MassStorage::Delete(const char* directory, const char* fileName)
{
	const char* location = (directory != NULL)
							? SD.CombineName(directory, fileName)
								: fileName;
	if (f_unlink(location) != FR_OK)
	{
		Debug("MS","Can't delete file ");
		Debug("MS",location);
    Debug("MS","\n");
		return false;
	}
	Debug("MS","File and directory were deleted.\n");
	return true;
}

// Create a new directory
bool MassStorage::MakeDirectory(const char *parentDir, const char *dirName)
{
	const char* location = SD.CombineName(parentDir, dirName);
	if (f_mkdir(location) != FR_OK)
	{
		Debug("MS","Can't create directory ");
		Debug("MS",location);
		Debug("\n");
		return false;
	}
	Debug("MS","Directory ");
	Debug(location);
	Debug(" created.\n");
	return true;
}

bool MassStorage::MakeDirectory(const char *directory)
{
	if (f_mkdir(directory) != FR_OK)
	{
		Debug("MS","Can't create directory ");
		Debug("MS",directory);
		Debug("\n");
		return false;
	}
	Debug("MS","Directory ");
	Debug(directory);
	Debug(" created.\n");
	return true;
}

// Rename a file or directory
bool MassStorage::Rename(const char *oldFilename, const char *newFilename)
{
	if (f_rename(oldFilename, newFilename) != FR_OK)
	{
		Debug("MS","Can't rename file or directory ");
		Debug("MS",oldFilename);
		Debug(" to ");
		Debug("MS",newFilename);
    Debug("MS","\n");
		return false;
	}
	Debug("MS ", oldFilename);
	Debug(" was renamed to ");
	Debug(newFilename);
	Debug("\n");
	return true;
}

// Check if the specified file exists
bool MassStorage::FileExists(const char *file) const
{
 	FILINFO fil;
 	fil.lfname = nullptr;
	if(f_stat(file, &fil) == FR_OK){
		Debug("MS","File ");
		Debug(file);
		Debug(" already exists.\n");
		return true;
	}
	Debug("MS","File ");
	Debug(file);
	Debug(" was not found.\n");
	return false;
}

// Check if the specified directory exists
bool MassStorage::PathExists(const char *path) const
{
 	DIR dir;
 	dir.lfn = nullptr;
	if(f_opendir(&dir, path) == FR_OK){
		Debug("MS","Path ");
		Debug(path);
		Debug(" already exists.\n");
		return true;
	}
	Debug("MS","Path ");
	Debug(path);
	Debug(" was not found.\n");
	return false;
}

bool MassStorage::PathExists(const char* directory, const char* subDirectory)
{
	const char* location = (directory != NULL)
							? SD.CombineName(directory, subDirectory)
								: subDirectory;
	return PathExists(location);
}

//------------------------------------------------------------------------------------------------

FileStore::FileStore(void)
{
}

void FileStore::Init()
{
	bufferPointer = 0;
	inUse = false;
	writing = false;
	lastBufferEntry = 0;
	openCount = 0;
}

// Open a local file (for example on an SD card).

bool FileStore::Open(const char* directory, const char* fileName, bool write)
{
	const char* location = (directory != NULL)
							? SD.CombineName(directory, fileName)
								: fileName;
	writing = write;
	lastBufferEntry = FILE_BUF_LEN - 1;
	bytesRead = 0;

//	FRESULT openReturn = f_open(&file, location, (writing) ? FA_CREATE_ALWAYS | FA_WRITE : FA_OPEN_EXISTING | FA_READ);
    FRESULT openReturn = f_open(&file, location, (writing) ?  FA_OPEN_ALWAYS | FA_WRITE : FA_OPEN_EXISTING | FA_READ);
	if (openReturn != FR_OK)
	{
		Debug("FS","Can't open ");
		Debug(location);
		Debug(" to ");
		Debug((writing) ? "write" : "read");
		Debug(", error code ");
		Debug(openReturn);
		Debug("\n");
		return false;
	}

	bufferPointer = (writing) ? 0 : FILE_BUF_LEN;
	inUse = true;
	openCount = 1;
	Debug("FS","File opened.\n");
	return true;
}

bool FileStore::CreateNew(const char* directory, const char* fileName)
{
	const char* location = (directory != NULL)
							? SD.CombineName(directory, fileName)
								: fileName;
	writing = true;
	lastBufferEntry = FILE_BUF_LEN - 1;
	bytesRead = 0;

	FRESULT openReturn = f_open(&file, location, (writing) ? FA_CREATE_ALWAYS | FA_WRITE : FA_OPEN_EXISTING | FA_READ);
	if (openReturn != FR_OK)
	{
		Debug("FS","Can't open ");
		Debug(location);
		Debug(" to ");
		Debug((writing) ? "write" : "read");
		Debug(", error code ");
		Debug(openReturn);
		Debug("\n");
		return false;
	}

	bufferPointer = 0;
	inUse = true;
	openCount = 1;
	Debug("FS","File created.\n");
	return true;
}


void FileStore::Duplicate()
{
	if (!inUse)
	{
		Debug("FS","Attempt to dup a non-open file.\n");
		return;
	}
	++openCount;
}

bool FileStore::Close()
{
	if (!inUse)
	{
		Debug("FS","Attempt to close a non-open file.\n");
		return false;
	}
	--openCount;
	if (openCount != 0)
	{
		Debug("FS","File closed.\n");
		return true;
	}
	bool ok = true;
	if (writing)
	{
		ok = Flush();
	}
	FRESULT fr = f_close(&file);
	inUse = false;
	writing = false;
	lastBufferEntry = 0;
	if(ok && fr == FR_OK){
		Debug("FS","File closed.\n");
	}
	return ok && fr == FR_OK;
}

unsigned long FileStore::Position() const
{
	return bytesRead;
}

bool FileStore::Seek(unsigned long pos)
{
	if (!inUse)
	{
		Debug("FS","Attempt to seek on a non-open file.\n");
		return false;
	}
	if (writing)
	{
		WriteBuffer();
	}
	FRESULT fr = f_lseek(&file, pos);
	if (fr == FR_OK)
	{
		bufferPointer = (writing) ? 0 : FILE_BUF_LEN;
		bytesRead = pos;
		return true;
	}
	return false;
}

bool FileStore::GoToEnd()
{
	return Seek(Length());
}

unsigned long FileStore::Length() const
{
	if (!inUse)
	{
		Debug("FS","Attempt to size non-open file.\n");
		return 0;
	}
	return file.fsize;
}

float FileStore::FractionRead() const
{
	unsigned long len = Length();
	if(len <= 0)
	{
		return 0.0;
	}

	return (float)bytesRead / (float)len;
}

int8_t FileStore::Status()
{
	if (!inUse)
		return nothing;

	if (lastBufferEntry == FILE_BUF_LEN)
		return byteAvailable;

	if (bufferPointer < lastBufferEntry)
		return byteAvailable;

	return nothing;
}

bool FileStore::ReadBuffer()
{
	FRESULT readStatus = f_read(&file, buf, FILE_BUF_LEN, &lastBufferEntry);	// Read a chunk of file
	if (readStatus)
	{
		Debug("FS","Error reading file.\n");
		return false;
	}
	bufferPointer = 0;
	return true;
}

// Single character read via the buffer
bool FileStore::Read(char& b)
{
	if (!inUse)
	{
		Debug("FS","Attempt to read from a non-open file.\n");
		return false;
	}

	if (bufferPointer >= FILE_BUF_LEN)
	{
		bool ok = ReadBuffer();
		if (!ok)
		{
			return false;
		}
	}

	if (bufferPointer >= lastBufferEntry)
	{
		b = 0;  // Good idea?
		return false;
	}

	b = (char) buf[bufferPointer];
	bufferPointer++;
	bytesRead++;

	return true;
}

// Block read, doesn't use the buffer
int FileStore::Read(char* extBuf, unsigned int nBytes)
{
	if (!inUse)
	{
		Debug("FS","Attempt to read from a non-open file.\n");
		return -1;
	}
	bufferPointer = FILE_BUF_LEN;	// invalidate the buffer
	UINT bytes_read;
	FRESULT readStatus = f_read(&file, extBuf, nBytes, &bytes_read);
	if (readStatus)
	{
		Debug("FS","Error reading file.\n");
		return -1;
	}
	bytesRead += bytes_read;
	return (int)bytes_read;
}

bool FileStore::WriteBuffer()
{
	if (bufferPointer != 0)
	{
		bool ok = InternalWriteBlock((const char*)buf, bufferPointer);
		if (!ok)
		{
			Debug("FS","Cannot write to file. Disc may be full.\n");
			return false;
		}
		bufferPointer = 0;
	}
	return true;
}

bool FileStore::Write(char b)
{
	if (!inUse)
	{
		Debug("FS","Attempt to write byte to a non-open file.\n");
		return false;
	}
	buf[bufferPointer] = b;
	bufferPointer++;
	if (bufferPointer >= FILE_BUF_LEN)
	{
		return WriteBuffer();
	}
	return true;
}

bool FileStore::Write(const char* b)
{
	if (!inUse)
	{
		Debug("FS","Attempt to write string to a non-open file.\n");
		return false;
	}
	int i = 0;
	while (b[i])
	{
		if (!Write(b[i++]))
		{
			return false;
		}
	}
	return true;
}

// Direct block write that bypasses the buffer. Used when uploading files.
bool FileStore::Write(const char *s, unsigned int len)
{
	if (!inUse)
	{
		Debug("FS","Attempt to write block to a non-open file.\n");
		return false;
	}
	if (!WriteBuffer())
	{
		return false;
	}
	return InternalWriteBlock(s, len);
}

bool FileStore::InternalWriteBlock(const char *s, unsigned int len)
{
 	unsigned int bytesWritten;
	uint32_t time = micros();
 	FRESULT writeStatus = f_write(&file, s, len, &bytesWritten);
	time = micros() - time;
	if (time > longestWriteTime)
	{
		longestWriteTime = time;
	}
 	if ((writeStatus != FR_OK) || (bytesWritten != len))
 	{
 		Debug("FS","Cannot write to file. Disc may be full.\n");
 		return false;
 	}
 	return true;
 }

bool FileStore::Flush()
{
	if (!inUse)
	{
		Debug("FS","Attempt to flush a non-open file.\n");
		return false;
	}
	if (!WriteBuffer())
	{
		return false;
	}
	return f_sync(&file) == FR_OK;
}

float FileStore::GetAndClearLongestWriteTime()
{
	float ret = (float)longestWriteTime/1000.0;
	longestWriteTime = 0;
	return ret;
}

uint32_t FileStore::longestWriteTime = 0;

MassStorage SD;

//***************************************************************************************************
