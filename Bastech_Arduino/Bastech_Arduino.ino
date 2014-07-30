/*
 -----BASTECH rev 75------
 -----Autor: Emiliano Galmarini------
 -----Bajo Licencia GPLv3 -PROHIBIDO SU USO PARA CREAR PROYECTOS DE EGRESO DE EMT-UTU O SU USO EXCLUSIVO PARA CLUBES DE CIENCIA SIN LA AUTORIZACION DEL AUTOR-----------
 */
#include <NewPing.h> //Libreria

#define TRIGGER_PIN 11 //Pin de pulso del sensor de abajo
#define ECHO_PIN 12  //Pin de lectura del sensor de abajo
#define MAX_DISTANCE 130 //Distancia de medicion en cm del sensor de abajo

#define TRIGGER_PIN2 5 //Pin de pulso del sensor de arriba
#define ECHO_PIN2 7  //Pin de lectura del sensor de abajo
#define MAX_DISTANCE2 130 //Distancia de medicion en cm del sensor de Arriba

#define TRIGGER_PIN3 6  //Pin de pulso del sensor para escaleras
#define ECHO_PIN3 2  //Pin de lectura del sensor para escaleras
#define MAX_DISTANCE3 130 //Distancia de medicion en cm del sensor para escaleras

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing configuracion para sensor de abajo.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2); // NewPing configuracion para sensor de arriba.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE3); // NewPing configuracion para sensor de escaleras.

int motor = 10; //Vibrador 1
int motor2 = 9; //Vibrador 2
int motor3 = 3; //Vibrador 3
int speaker = 1; //Speaker 1
int speaker_2= 0; //Speaker 2 (testeo)
int input; //debug

/* Deteccion de escaleras */
int dato1=0; //Variable para alojar una medida
int dato2=0; //Variable para alojar una medida
int delta=0; //Variable para calcular abs
/* Deteccion de escaleras */

boolean flag=false; //Bandera
boolean flag2=false; //Bandera

void setup () {
  Serial.begin(115200); //Inia puerto serial a 9600 bauds
  pinMode(motor,OUTPUT);// Habilita pin 9 como salida Analogica
  pinMode(motor2,OUTPUT);// Habilita pin 6 como salida Analogica
  pinMode(motor3,OUTPUT);// Habilita pin 3 como salida Analogica
  pinMode(speaker, OUTPUT); //Habilita Pin 3 (speaker) como salida Analogica
  pinMode(speaker_2, OUTPUT); //Habilita Pin 10 (speaker_2) como salida Analogica
  Serial.println("BastecH  1.0 "); //Imprime Bienvenida
  beep(); //Variable de beep "ok"
  Serial.println("OK"); //Imprime OK
}

void beep() {
  analogWrite(speaker,128); //Envia un pulso modulado de 128 analogico
  delay(250); //Pausa de 250ms
  analogWrite(speaker,LOW); //Apaga Pin modulado de Speaker 
}

void srf05_abajo() {
  // delay(50); // Envia 2/pulsosseg. 30ms mas la distancia de tiempo mas corta entrwe pulso y pulso.
  unsigned int uS = sonar.ping(); //Envia ping entre microsecons.
  Serial.print("Ping: "); //Imprime "Ping: " en puerto serial
  Serial.print(sonar.convert_cm(uS)); //Convierte la distancia en resultado
  Serial.println("cm");//Imprime "cm" en puerto serial
  int value = uS;//Rango de lectura (0,1023)
  int motor_speed = -(uS/29);//PWM solo puede variar entre 255 valores
  analogWrite(motor,motor_speed);// Modula el pulso segun la distancia pra uqe el vibrador gire mas o menos
  Serial.println(motor_speed); // Imprime velocidad del motor en el puerto serial
  if(motor_speed>256 && motor_speed<1){
    delay(1);
  }
  if(motor_speed>-70) { //Si el valor de giro del motor es mayor a -70
    analogWrite(speaker,100); //Prende Speaker a 100 de valor de 255
  }
  else
    if(motor_speed<-70){ //Si es menor a -70
      analogWrite(speaker,LOW); //Apaga el Speaker
    }
  if(motor_speed<-256){ //En caso que este fuera del rango
    analogWrite(motor,LOW); //Apaga vibrador
    delay(1); //Delay en 1 ms
  }
  if(motor_speed>-70 && motor_speed<-1){
    Serial.println("Objeto cerca (Sensor de abajo)"); //Imprime en el puerto que hay un objeto cerca del sensor de abajo
  }
}

void srf05_arriba() {
  //delay(50); // Envia 2/pulsosseg. 30ms mas la distancia de tiempo mas corta entrwe pulso y pulso.
  unsigned int uS2 = sonar2.ping(); //Envia ping2 entre microsecons.
  Serial.print("Ping_2: "); //Imprime "Ping_2: " en puerto serial
  Serial.print(sonar2.convert_cm(uS2)); //Convierte la distancia en resultado
  Serial.println("cm"); //Imprime "cm" en puerto serial
  int value2 = uS2; // Rango de lectura (0,1023)
  int motor_speed2 = -(uS2/29); // PWM solo puede variar entre 255 valores
  analogWrite(motor2,motor_speed2); //Modula el pulso segun la distancia pra que el vibrador gire mas o menos
  Serial.println(motor_speed2); //Imprime velocidad del motor 2 en el puerto serial
  if(motor_speed2>256 && motor_speed2<1){
    delay(1);
  }
  if(motor_speed2>-70) { //Si el valor de giro del motor es mayor a -70
    analogWrite(0,100); //Prende Speaker_2 a 100 de valor de 255
  }
  else
    if(motor_speed2<-70){ //Si es menor a -70
      analogWrite(0,LOW); //Apaga el Speaker_2
    }
  if(motor_speed2<-256){ //En caso que este fuera del rango
    analogWrite(motor,LOW); //Apaga vibrador
    delay(1); //Delay en 1 ms
  }
  if(motor_speed2>-70 && motor_speed2<-1){
    Serial.println("Objeto cerca (Sensor de arriba)"); //Imprime en el puerto que hay un objeto cerca del sensor de arriba
  }
}

/*----------DETECCION DE ESCALERAS-----------*/
void srf05_escaleras() {
  //  delay(50);
  unsigned int uS3 = sonar3.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping3: ");
  Serial.print(sonar3.convert_cm(uS3)); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  unsigned int result=sonar3.convert_cm(delta); //Convierte a cm el resultado (Delta)
  int motor_speed3 = -(uS3/29); // PWM solo puede variar entre 255 valores
  analogWrite(motor2,motor_speed3); //Modula el pulso segun la distancia pra que el vibrador gire mas o menos
  Serial.println(motor_speed3); //Imprime velocidad del motor 2 en el puerto serial
  if(flag==false) { 
    dato1=sonar3.ping(); //Guarda dato 1
    flag=true; // Bandera en alto
  }
  else
    (dato1=dato2); //Dato 1 es igual Dato 2
  dato2=sonar3.ping();// Dato 2 pasa a ser otra medida
  delta=abs(dato2-dato1); // Se calcula Valor absoluto de dato 2 - dato 1
  Serial.println(sonar3.convert_cm(delta)); // Muestra resultado en Consola
  Serial.println(result); //Debug
  if(result >= 20) { 
    digitalWrite(2, HIGH); 
  }
  else
    digitalWrite(2, LOW);
}
/*----------DETECCION DE ESCALERAS-----------*/

void  loop() {
  delay(50); //50ms para los 2 sensores, asi no se retrasa el envio y se ahorra codigo
  srf05_abajo(); //Inizializa sensor de abajo
  srf05_arriba(); //Inicializa Sensor de arriba
  srf05_escaleras(); //Inicializa Sensor de deteccion de escaleras
}
