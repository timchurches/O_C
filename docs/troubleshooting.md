```

/* 
* 
* DAC output test. 
* updates outputs every two seconds in ~ 1 volt increments (-3.75v, -2.75v, -1.75v, etc)
* 
*/ 

#include <spififo.h> 

#define DAC_CS 10 // DAC CS 
#define DAC_RST 9 // DAC RST 
#define OLED_CS 8 // OLED 

#define OCTAVES 9 
#define MAX_VALUE 0xFFFF 
#define SPICLOCK_30MHz (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) 

uint16_t octaves[OCTAVES+1] = {6553, 13107, 19661, 26214, 32768, 39321, 45875, 52428, 58981, 65535}; 

void set8565_CHA(uint32_t data) { 
  uint32_t _data = MAX_VALUE - data; 

  SPIFIFO.write(0b00010000, SPI_CONTINUE); 
  SPIFIFO.write16(_data); 
  SPIFIFO.read(); 
  SPIFIFO.read(); 
} 

void set8565_CHB(uint32_t data) { 
  uint32_t _data = MAX_VALUE - data; 

  SPIFIFO.write(0b00010010, SPI_CONTINUE); 
  SPIFIFO.write16(_data); 
  SPIFIFO.read(); 
  SPIFIFO.read(); 
} 

void set8565_CHC(uint32_t data) { 
  uint32_t _data = MAX_VALUE - data; 

  SPIFIFO.write(0b00010100, SPI_CONTINUE); 
  SPIFIFO.write16(_data); 
  SPIFIFO.read(); 
  SPIFIFO.read(); 
} 

void set8565_CHD(uint32_t data) { 
  uint32_t _data = MAX_VALUE - data; 

  SPIFIFO.write(0b00010110, SPI_CONTINUE); 
  SPIFIFO.write16(_data);  
  SPIFIFO.read(); 
  SPIFIFO.read(); 
} 

void setup() { 

  delay(100); 
  pinMode(DAC_CS, OUTPUT); 
  pinMode(DAC_RST, OUTPUT); 
  pinMode(OLED_CS, OUTPUT); 

  digitalWrite(DAC_RST, HIGH); 
  digitalWrite(OLED_CS, HIGH); 

  SPIFIFO.begin(DAC_CS, SPICLOCK_30MHz, SPI_MODE0); 

  set8565_CHA(0x00); 
  set8565_CHB(0x00); 
  set8565_CHC(0x00); 
  set8565_CHD(0x00); 
} 

uint16_t i = 0x00; 

void loop() { 

  i = i++ < OCTAVES ? i : 0x00; 

  uint16_t data_ = octaves[i];
  set8565_CHA(data_); 
  set8565_CHB(data_); 
  set8565_CHC(data_); 
  set8565_CHD(data_); 

  delay(2000); 
} 
// end
```
