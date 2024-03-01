#include <16F887.h> //libreria del PIC.h (ha tutte le funzioni)
#device ICD=TRUE //abilita ICD (traduttore per passare da linguaggio in ambiente C a linguaggio del PIC) x scrivere sulla ROM (program memory)
#fuses HS,NOLVP,NOWDT //compilatore configura automaticamente alcuni dei bit di configurazione (#fuses) in base al codice
#use delay(clock=20000000) //tempo di clock=20MHZ
#use rs232 (DEBUGGER) // non ci sta protocollo di comunicazione, i dati scambiati erano tra sensore e micro


#define SENSOR_1SX PIN_A1 //pin di trigger per controllare il sensore
#define SENSOR_3DX PIN_A2
#define SENSOR_2C PIN_A3 //accensione led del micro associato al sensore
#define GREEN_LED_Sx PIN_A5
#define YELLOW_LED_C PIN_B4
#define RED_LED_Dx PIN_B5
#define pin_triggerMDX PIN_E0  //pin di trigger per controllare il motore
#define pin_triggerMSX PIN_E1

int1 sens_1sx,sens_2c,sens_3dx; //creiamo le variabili dei sensori

void leggi_sensori() {
   set_tris_a (0b00000000); //gli zeri (dopo la b) identificano l'indirizzo 1 byte=8bit, li mettiamo tutti a 0 e rappresentano i bit delle porte dei sensori
   output_high(SENSOR_1SX);
   output_high(SENSOR_2C);
   output_high(SENSOR_3DX);
   delay_us(10); //aspettiamo 10 micro secondi e andiamo a porre i pin A1 A2 A3
   set_tris_a (0b00001110); //vado a selezionare le porte per i pin dei sensori A1 A2 A2 
   delay_us(180);  //valore dato dalla calibrazione 
   
   //verifico lo stato del sensore: se é alto la variabile va a 1 altrimenti a 0
   if (input_state(SENSOR_1SX)){ 
      sens_1sx=1;
   }else{
      sens_1sx=0; }
  
   if (input_state(SENSOR_2C)){
      sens_2c=1;
   }else{
      sens_2c=0; }
   
   if (input_state(SENSOR_3DX)){
      sens_3dx=1;
   }else{
      sens_3dx=0; }
      
   delay_us(500);   
}


// I led partono tutti accesi, quindi il sensore vede tutto nero inizialmente.
// sens==0=BIANCO --> output_high -> led spento
// sens==1=NERO --> output_low  -> led acceso

void main() {
sens_1sx = 0;
sens_2c = 0;
sens_3dx = 0;
while(true){
   leggi_sensori(); 
    if (sens_1sx && sens_2c && sens_3dx){ //tutti i sensori vedono nero
         output_low(GREEN_LED_Sx); 
         output_low(YELLOW_LED_C);
         output_low(RED_LED_Dx);
    }
    else  //vedono tutti bianco
    {         output_high(GREEN_LED_Sx);
              output_high(YELLOW_LED_C);
              output_high(RED_LED_Dx);
    }
// DRITTO, solo il centrale su nero, si accende solo led centrale
if (sens_2c){                          
         output_high(GREEN_LED_Sx);
         output_low(YELLOW_LED_C); 
         output_high(RED_LED_Dx);
         
         output_high(pin_triggerMDX); 
         delay_us(1300); //senso orario 
         output_low(pin_triggerMDX);
         delay_ms(20);
         
         output_high(pin_triggerMSX); 
         delay_us(1700); //senso antiorario 
         output_low(pin_triggerMSX);
         delay_ms(20);
}
//CURVA DX, sensore centrale e destra su nero oppure solo destra sul nero
if (sens_3dx && sens_2c || sens_3dx){  
         output_high(GREEN_LED_Sx);
         output_low(YELLOW_LED_C);
         output_low(RED_LED_Dx);
         
         output_high(pin_triggerMDX);
         delay_us(1500);
         output_low(pin_triggerMDX);
         delay_ms(20);
      
      
         output_high(pin_triggerMSX);
         delay_us(1700);
         output_low(pin_triggerMSX);
         delay_ms(20);
         
         
         
         
}
//CURVA SX, sensore centrale o sinistro su nero oppure solo sinistro su nero
if (sens_1sx && sens_2c || sens_1sx){              
         output_low(GREEN_LED_Sx);
         output_low(YELLOW_LED_C);
         output_high(RED_LED_Dx);
         
         output_high(pin_triggerMDX);
         delay_us(1300);
         output_low(pin_triggerMDX);
         delay_ms(20);
      
      
         output_high(pin_triggerMSX);
         delay_us(1500);
         output_low(pin_triggerMSX);
         delay_ms(20);

}
//fermo la macchina quando tutti vedono nero (striscia finale)        
if (sens_1sx && sens_2c && sens_3dx){     
         output_low(GREEN_LED_Sx);
         output_low(YELLOW_LED_C);
         output_low(RED_LED_Dx);
         
         output_high(pin_triggerMDX);
         delay_us(1500);
         output_low(pin_triggerMDX);
         delay_ms(20);
         
         output_high(pin_triggerMSX);
         delay_us(1500);
         output_low(pin_triggerMSX);
         delay_ms(20);
         
}








}



}

