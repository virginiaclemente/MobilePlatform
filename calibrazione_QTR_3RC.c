#include <16F887.h>
#device ICD=TRUE
#fuses HS,NOLVP,NOWDT
#use delay (clock=20000000)
#use rs232 (DEBUGGER)

// PIN_C1 corresponds to ccp1. It captures the rising edge of signal.
// PIN_C2 corresponds to ccp2. It captures the falling edge of signal.

#define SENSORE PIN_A1      //definiamo il pin a cui colleghiamo l'output del sensore

// Questa funzione usata per attivare il sensore. Come da datasheet necessario eseguire le seguenti operazioni
void attiva_sensore() {                   
     output_high(SENSORE); // definisco il pin come output e lo metto alto - lo porto a Vcc 
     delay_us(10); //da datasheet 
     output_float(SENSORE); // definisco il pin come input - stacco il pin dal sensore di alimentazione
}
//bisogna capire quale é il tempo di decadimento

#int_ccp2 //Queste direttive specificano che la seguente funzione è una funzione di interruzione, 
          //chiamata quando ccp2 rileva l'evento di un fronte di discesa.
          //Quando viene rilevato l'interrupt, il compilatore genererà il codice per passare alla funzione qui sotto.
void isr(){ //ROUTINE di INTERRUPT
     disable_interrupts(INT_CCP2); //disabilitiamo e lo richiamiamo dopo 
     long rise, fall, p_w, time;
     
     rise=CCP_1; //valore del TMR1 quando ho tempo di salita
     fall=CCP_2; //valore del TMR1 quando ho tempo di discesa
     p_w=fall-rise; //tempo di clock
     time=p_w/(20/4);  // tempo di clock considerando che ho clock 20MHz diviso 4 perché PIC sezione ogni 4 colpi di clock
     
     printf("\r\n Time in us is: %lu",time); //stampo il tempo
     
     enable_interrupts(INT_CCP2); // riattivo l'interrupt
}

void main() { //andiamo a settare il timer
      setup_ccp1(CCP_CAPTURE_RE);     // CCP1 tempo di salita
      setup_ccp2(CCP_CAPTURE_FE);     // CCP2 tempo di discesa
      setup_timer_1(T1_INTERNAL);     // parte timer1 che é il timer di CAPTURE e COMPARE
      enable_interrupts(INT_CCP2);    // abilito interrupt
      enable_interrupts(GLOBAL);      //un qualsiasi interrupt
   
      while(TRUE){                    
            attiva_sensore(); //trigger
            delay_ms(60);   // dopo 60 ms riattivo il sensore e prendo un'altra misura
      }
}
