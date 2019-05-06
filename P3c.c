//Variables globales
      short int dec = 0;
      short int uni = 0;
      
void interrupt (){ //Rutina llamada para gestión de interrupciones
        if(uni == 9 && dec == 9){
                uni =0;
                dec=0;
        }
        else if(uni == 9){
             uni=0;
             dec++;
        }
        else{
             uni++;
        }

       INTCON.INT0IF=0;//Borra el flag de interrupción de INT0
}
void main() {
      //Variables
      short int t;
      
      //Valores para el display
      short int valores[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x67};
      
     //Configura los terminales del micro a digitales
     ADCON1=0x07;
     
     //Habilita la resistencia pull up de RB0
     RBPU_bit = 0;
     
     //Configuración terminales de salida
     TRISB = 0x01;//El único terminal de entrada es RB0
     TRISD = 0;//Puerto D tiene todos los terminales de salida
     TRISA = 0xFC; //Terminales de salida 1 y 2 del puerto A
     
     //Inicializa la señal de los pines
     //Display 1
     PORTA = 0xFE;
     PORTD = 0x3F;
     //Display 2
     PORTA = 0xFD;
     PORTD = 0x3F;
             
     //Se habilitan interrupciones
     INTCON2.INTEDG0=0; //Con este valor la interrupcioón la produce un flanco de bajada
     INTCON.INT0IF = 0;//Se inicializa el flag de interrupcion
     INTCON.INT0IE = 1;//Se habilita la interrupcion en INT0
     INTCON.GIE=1; //Se habilitan las interrupciones en general

     while(1){//Bucle infinito para que no se reinicie


           //Bucle que alterna los display y carga los valores
                   for(t=0;t<25;t++){
                        //Display 1 decenas
                        PORTA = 0xFD;
                        PORTD = valores[dec];

                        //Delay necesario
                        delay_ms(20);

                        //Display 2 unidades
                        PORTA = 0xFE;
                        PORTD = valores[uni];
                        //Delay necesario
                        delay_ms(20);
                   }
     }
}
