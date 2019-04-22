void interrupt (){ //Rutina llamada para gestión de interrupciones

       PORTB.B1=!PORTB.B1;//Cambia el estado del Led
       INTCON.INT0IF=0;//Borra el flag de interrupción de INT0
}
void main() {

     //Configura los terminales del micro a digitales
     ADCON1=0x07;
     
     //Habilita la resistencia pull up de RB0
     RBPU_bit = 0;
     
     //Configuración terminales de salida
     TRISB = 0x01;//El único terminal de entrada es RB0

     //Se habilitan interrupciones
     INTCON2.INTEDG0=0; //Con este valor la interrupcioón la produce un flanco de bajada
     INTCON.INT0IF = 0;//Se inicializa el flag de interrupcion
     INTCON.INT0IE = 1;//Se habilita la interrupcion en INT0
     INTCON.GIE=1; //Se habilitan las interrupciones en general

     while(1){//Bucle infinito para que no se reinicie

     }
}
