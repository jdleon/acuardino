#include <NewPing.h>

/*
 * Control de acuponica base arduino
*/
#define Offset 0.00            //compensacion de voltaje de pH
#define LED

//DEFINICION DE PINES

#define Luz 4
#define Agua 5

#define redPin 11
#define grnPin 10
#define bluPin 9

#define SensorPin A0              //ping de sensor de pH
#define SensorPin2 A1
#define SensorPin3 A2

#define SonarTrig 13
#define SonarEcho 12

#define DOSIS_PIN 8

//CONFIGURACION DE MUESTREO
#define samplingInterval 100
#define printInterval 3000
#define ArrayLenth  30    //times of collection
#define PING_INTERVAL 3000 // Milliseconds between pings.

#define MAX_DISTANCE 300 // Max distance in cm.


NewPing sonar(SonarTrig,SonarEcho, MAX_DISTANCE);


//CONFIGURACION CONDICIONES
#define UMBRAL_MIN 3 //minimo de agua para cortar
#define UMBRAL_MAX 6 //cuando debe abrir valvula

//VARIABLES


int hArray[ArrayLenth]; 
int hArrayIndex=0;
double altura; //almacena el valor medio de altura de agua

//SONAR

int sensorValue = 0;
unsigned long pingTimer; // 
unsigned long cm; // Almacena la distancia de agua

void setup(void)
{
  pinMode(redPin, OUTPUT);   // sets the pins as output
  pinMode(grnPin, OUTPUT);   
  pinMode(bluPin, OUTPUT); 
  
  pinMode(DOSIS_PIN, INPUT);
  
  pinMode(13, INPUT);   
  pinMode(12, INPUT); 
  
  pinMode(Luz, OUTPUT);   
  pinMode(Agua, OUTPUT);
 
  digitalWrite(Luz, HIGH);
  digitalWrite(Agua, LOW);


Serial.begin(9600);  
Serial.println("Controlador de Acuario");
Serial.println("Juan Pedro Leon");

}

void loop(void)
{
//comienza a ver cada sonar para verificar la altura de agua
    if (millis() >= pingTimer) {
      pingTimer += PING_INTERVAL * SONAR_NUM;
      oneSensorCycle(); // Do something with results.
      sonar.timer_stop();
      cm = 0;
      sonar.ping_timer(echoCheck);
        
//calcular el promedio de las alturas obtenidas
      hArray[hArrayIndex++]=cm;
      if(hArrayIndex==ArrayLenth)hArrayIndex=0;
      altura = avergearray(hArray, ArrayLenth);
      
    digitalWrite(redPin, 10);
    digitalWrite(grnPin, 10);
    digitalWrite(bluPin, 255);   

       if (cm <= UMBRAL_MIN){
      digitalWrite(Agua, LOW);
      }  
 
       if (cm >=UMBRAL_MAX){
      digitalWrite(Agua, HIGH); 
      }
   
      }//fin de ping
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

void oneSensorCycle() { // Do something with the results. 
Serial.print("Distancia = ");
Serial.print(cm);
Serial.print(" cm ");
Serial.println();
}

void echoCheck() { // If ping echo, set distance to variable
  if (sonar.check_timer())
    cm = sonar.ping_result / US_ROUNDTRIP_CM;
}

void indicador(float value){
 //segun el valor se presenta un color del LED
if(value >=0 & value <=2){
      digitalWrite(redPin, 153);
      digitalWrite(grnPin, 0);
      digitalWrite(bluPin, 253);
      }
    if(value >2 & value <=4){
      digitalWrite(redPin, 204);
      digitalWrite(grnPin, 0);
      digitalWrite(bluPin, 0);
      }
    if(value >4 & value <=6){
      digitalWrite(redPin, 255);
      digitalWrite(grnPin, 128);
      digitalWrite(bluPin, 0);
      }
    if(value >6 & value <=8){
      digitalWrite(redPin, 0);
      digitalWrite(grnPin, 204);
      digitalWrite(bluPin, 0);
      }
     if(value >8 & value <=10){
      digitalWrite(redPin, 102);
      digitalWrite(grnPin, 0);
      digitalWrite(bluPin, 102);
      }
    if(value >10 & value <=12){
      digitalWrite(redPin, 0);
      digitalWrite(grnPin, 102);
      digitalWrite(bluPin, 204);    
      }
    if(value >12 & value <=14){
      digitalWrite(redPin, 0);
      digitalWrite(grnPin, 0);
      digitalWrite(bluPin, 153);
      }  
  }
  
