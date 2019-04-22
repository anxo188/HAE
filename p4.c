int rotacion = 0; //Guarda el estado del motor
//Valores que puede tomar el puerto, el primer valor equivale a -90º del motor
//                    -90º   A    B     C    D
short int bobinas[] = {0x06,0x08,0x04,0x02,0x01};
short int der[] = {0x01,0x08,0x04,0x02,0x01,0x08,0x04,0x02,0x03};

void interrupt(){
      short int i;
      short int r;
      if(rotacion == -90){
        //Activa B
        PORTC = bobinas[2];
             delay_ms(1000);
        //Activa A
        PORTC = bobinas[1];
              delay_ms(1000);
        //Activa D
        PORTC = bobinas[4];
              delay_ms(1000);
        //Activa D y C
        PORTC = 0x03;
        
        rotacion = -225;
      }
      else{

             for ( i=0;i<9;i++){
                  PORTC = der[i];
                  delay_ms(1000);
             }

      }
      
     INTCON.INT0IF = 0;//Borra el flag de interrupción
}

void main() {

     ADCON1 = 0x07;

     //Configuración de puertos
     TRISC = 0; //Puerto de salida
     TRISB.B0 = 1;//Puerto de entrada
     
     //Configuración de la interrupción
     RCON.IPEN = 0;
     INTCON2.INTEDG0 = 0;
     INTCON.INT0IF = 0;
     INTCON.INT0IE = 1;
     INTCON.GIE = 1;
     

     
     while(1){
              if(rotacion == 0){
              //Inicializa la posición del motor a -90º
                    PORTC = bobinas[4];
                    delay_ms(1000);
                    PORTC = bobinas[3];
                    delay_ms(1000);
                    PORTC=bobinas[0];
                    rotacion= -90;
              }
     }
}