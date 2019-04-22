void main() {
     //Variables
     short int i=0;
     short int x=0;
     short int t=0;

     //Valores a pasar a los pines
     short int d1[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C};
     short int d2[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67};
     //
     ADCON1=0x07;

     //Configuración terminales de salida
     TRISD = 0; //Terminales de salida
     TRISA = 0xFC; //Terminales de salida 1 y 2 del puerto A
     PORTD = 0x7F; //Inicializa la señal de los pines
     PORTA = 0xFF;


     while(1){
             //Inicializa la señal de los pines
             //Display 1
             PORTA = 0xFE;
             PORTD = 0x3F;
             //Display 2
             PORTA = 0xFD;
             PORTD = 0x3F;

             //Bucle que regula las decenas
             for(i=0;i<6;i++){

                //Bucle que regula las unidades
                for(x=0;x<10;x++){

                   //Bucle que alterna los display y carga los valores
                   for(t=0;t<25;t++){
                        //Display 1 decenas
                        PORTA = 0xFD;
                        PORTD = d1[i];

                        //Delay necesario
                        delay_ms(20);
                        
                        //Display 2 unidades
                        PORTA = 0xFE;
                        PORTD = d2[x];
                        //Delay necesario
                        delay_ms(20);
                   }
                }
             }
     }
}