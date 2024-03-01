#include <16F887.h> //libreria del PIC.h (ha tutte le funzioni)
#device ICD=TRUE //abilita ICD (traduttore per passare da linguaggio in ambiente C a linguaggio del PIC) x scrivere sulla ROM (program memory)
#fuses HS,NOLVP,NOWDT //compilatore configura automaticamente alcuni dei bit di configurazione (#fuses) in base al codice
#use delay (clock=20000000) //tempo di clock
#use rs232 (stream=PROMI,baud=9600,  xmit=PIN_A1, rcv=PIN_A3) // protocollo UART (baud rate, xmit=pin che emette,rcv=pin che riceve)
#define pin_triggerMDX PIN_E0    //definisco i PIN DI TRIGGER per controllare 
#define pin_triggerMSX PIN_E1

int8 tmp; //lettera a 8 bit su cui diamo i comandi (lettera a cui associo un'azione sul PIC)

void main () {   
   
   
   
   while(true){ //modo facile di creare un loop che si ferma quando chiudiamo il codice
      tmp = getc();; //prendiamo in ingresso un comando (che viene da Tera term)
      if(tmp == 'w'){//il motore andava avanti
         output_high(pin_triggerMDX);//output alto al motore dx
         delay_us(1300); //andiamo a dire al motore dx di girare in senso orario 
         output_low(pin_triggerMDX); 
         delay_ms(20); //di default uguale a 20 
         
        output_high(pin_triggerMSX);
        delay_us(1700); //motore di SX in senso antiorario
        output_low(pin_triggerMSX);
        delay_ms(20);
               }
      
      if(tmp == 'd'){ //gira dx 
         output_high(pin_triggerMDX);
         delay_us(1500);
         output_low(pin_triggerMDX);
         delay_ms(20);
      
      
         output_high(pin_triggerMSX);
         delay_us(1700);
         output_low(pin_triggerMSX);
         delay_ms(20);
         
         
               }
      
      if(tmp == 'a'){ //gira sx
         output_high(pin_triggerMDX);
         delay_us(1300);
         output_low(pin_triggerMDX);
         delay_ms(20);
      
      
         output_high(pin_triggerMSX);
         delay_us(1500);
         output_low(pin_triggerMSX);
         delay_ms(20);

      }
      
      if(tmp == 's'){ //retromarcia
         output_high(pin_triggerMDX);
         delay_us(1700);
         output_low(pin_triggerMDX);
         delay_ms(20);
         
         output_high(pin_triggerMSX);
         delay_us(1300);
         output_low(pin_triggerMSX);
         delay_ms(20);
         }
      
      
      }
   }


