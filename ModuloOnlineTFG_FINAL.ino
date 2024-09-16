/*
 * PAra hacer compilar la parte de "moduloOnlineEnlace":
 * 1)Comprobar el puerto del Arduino y compilarlo en el COM adecuado. 
 * 2)Cerrar la aplicacion Arduino para evitar problemas.. (para liberar el puerto serie y poder utilizarlo ahora en Python)
 */

#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(9,10); //Rx, tx: emplea el dispositivo para la comunicacion con Serial en que puertos esta conectado el bluetoohth
int SENSOR1  = A0;
int ledPin   = 5;
int icode  = -1;
bool BLUETOOTH = false; 
char estadoBluetooth; 
//variable para controlar el servo
Servo servoMotor;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4; 
Servo servoMotor5;

int shift1= 90;
int shift2= 10;
int shift3= 90;
int shift4= 60;
int shift5= 10;

int SERIAL_SPEED = 57600;

int movimientos(char codigo){
  icode = -1;
  if(codigo == '-1'){ //MOVER LA MANO EN POSICION PLANA
       servoMotor.write(90 + shift1);
       servoMotor2.write(0);
       servoMotor3.write(0);
       servoMotor4.write(90 + shift4);
       servoMotor5.write(90 +shift5);                        
   }
   
   if(codigo == '0'){ //no me muevo 
       servoMotor.write(90 + shift1);
       servoMotor2.write(90);
       servoMotor3.write(90);
       servoMotor4.write(90 + shift4);
       servoMotor5.write(90 +shift5);

       icode = 0;
   }
   
   if(codigo == '1'){ //MOVER LA MANO HACIA ABAJO
       servoMotor.write(90 + shift1);
       servoMotor2.write(0);
       servoMotor3.write(0);
       servoMotor4.write(90 + shift4);
       servoMotor5.write(90 +shift5);
       icode = 1;
   }
   
   if(codigo == '2'){ //no me muevo 
       servoMotor.write(0 + shift1);
       servoMotor2.write(90);
       servoMotor3.write(90);
       servoMotor4.write(0 + shift4);
       servoMotor5.write(0 +shift5);
       icode = 2;
   }
   
   if(codigo == '3'){ //no me muevo 
       servoMotor.write(0 + shift1);
       servoMotor2.write(0);
       servoMotor3.write(0);
       servoMotor4.write(0 + shift4);
       servoMotor5.write(0 +shift5);
       icode = 3;
    }
     
   //Esperamos 1 segundo
       delay(100);

     return icode;
}


//Permite hacer parpadear el led segun el movimiento que detecte...
int ledShow(int cod){
    for (int i = 0; i <= cod; i++) {
    digitalWrite(ledPin, HIGH);  // Encender el LED
    delay(200);                  // Esperar 200 ms
    digitalWrite(ledPin, LOW);   // Apagar el LED
    delay(200);                  // Esperar 200 ms
  }
  return 0;
}

void setup() {
  Serial.begin(SERIAL_SPEED); 
  bluetooth.begin(SERIAL_SPEED);
  //servo en pin 8 
   servoMotor.attach(8);
   //servo en pin 9 
   servoMotor2.attach(6);
   //servo en pin 10
   servoMotor3.attach(7);
   //servo en pin 11
   servoMotor4.attach(11);
   //servo en pin 12
   servoMotor5.attach(12);

  pinMode(8, OUTPUT); //6
  pinMode(6, OUTPUT); //7
  pinMode(7, OUTPUT);//8
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

   movimientos("START");
 
}

void loop() {
  int sensor = analogRead(A0); 
  String ssensor = String(sensor);
  
  if( BLUETOOTH){
    if(bluetooth.available()){
      estadoBluetooth = bluetooth.read(); 
      icode = movimientos(estadoBluetooth); 
      ledShow(icode);
      }
      
      bluetooth.println(ssensor);
       

      
 
   }else{ 
    if(Serial.available()){
      estadoBluetooth = Serial.read(); 
      icode = movimientos(estadoBluetooth); 
      ledShow(icode);
      }
      
      Serial.println(ssensor);
       

   }
       

    
    
  }
  
  
