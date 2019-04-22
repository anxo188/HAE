void main() {
     //Variables
       short int estado = 0; //0 apagado, 1 encendido
       short int viejo = 0; //Valor anterior del interruptor
       short int actual;  //Estado actual del interruptor
     //Valores a pasar a los pines

     //Configura los terminales del micro a digitales
     ADCON1=0x07;
     
     //Habilita la resistencia pull up de RB0
     RBPU_bit = 0;
     
     //Configuración terminales de salida
     TRISB = 0x01;


     while(1){
              actual = PORTB.B0;
              
              //Si se pulsa el botón se cambia el estado del led apagado-encendido o viceversa
              if(actual == 0 && viejo == 1){
                     if(estado == 1){
                               estado = 0;
                     }
                     else{
                           estado = 1;
                     }
              }
              
              //se reemplaza el valor viejo por el nuevo
              viejo=actual;
              
              //Se manda hacia el led el estado actual
              PORTB.B1 = estado;
              
              //Delay solicitado
              delay_ms(100);
     }
}