#include <math.h>
#include <PWMServo.h>
#include <Servo.h>
#include <NewPing.h>

PWMServo mainmotor;  //Ubicacion de los Pines para el motor DC
#define IN1 7
#define IN2 8
#define ENA 5

#define Velocidad 190
#define Vel_Alta 190

Servo smotordir;    //servomotor para direccionales
#define SERVO_PIN 9

#define Dir_Frente 90   //Configuración y ajuste del cero grado del motor direccional
int dir_derecha=Dir_Frente+24;
int dir_izquierda=Dir_Frente-45;

//valores de la posicion donde inicia el vehiculo
int posi_x_inicial = 0;
int posi_y_inicial = 0;
int grado_final    = 0;
int grado_inicial  = 0;
int Pto_medio_recorrido = 0;
int dist45  = 0; //distancia captada por sensor 1 a la izquierda (15 grados)
int dist145 = 0;//distancia captada por sensor 1 a la derecha (15 grados)
int dist90  = 0;//distancia captada por sensor 1 al centro (15 grados)
int grado_camino = 0;
int pos = 0;
int Distancia_segura = 30; //Distancia seguro para evitar obstaculo
double PM = 0; //punto medio en el camino
int anguloRadianes= 0;
int anguloGrados  = 0;
double catetoAdyacente = 20;//variable para indicar la distancia de separacion de la pared exterior
int grado= 0;
Servo smotorsen;   //Servomotor para sensor delantero

//sensor 3  DERECHO
int TRIG3_PIN = 11;        //cambiar pin al de conexion actual
int ECHO3_PIN = 12;        //cambiar pin al de conexion actual
//sensor 2 IZQUIERDO
int TRIG2_PIN = 4; 
int ECHO2_PIN = 6; 
//sensor 1 Dir_Frente
int TRIG1_PIN = 3; 
int ECHO1_PIN = 2; 

NewPing Sensor3(TRIG3_PIN,ECHO3_PIN);
NewPing Sensor2(TRIG2_PIN,ECHO2_PIN);
NewPing Sensor1(TRIG1_PIN,ECHO1_PIN);

int dist3 = 0;     //distancia captada por sensor 3
int dist2 = 0;     //distancia captada por sensor 2



//******************************  FUNCIONES ******************************
void mov_der()
{ 
 for(pos = 45; pos<grado_inicial; pos+=1)
 {
  smotordir.write(pos);
  delay(15);
 }  
}

void mov_izq()
{
  for(pos = 116; pos>45; pos-=1)
  grado=smotordir.read();
  Serial.print(grado);
 for(pos = grado_inicial; pos>45; pos-=1)
 {
  smotordir.write(pos);
  delay(15);
 }  
}

void mov_adelante()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, Velocidad);
}

void parar()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}
void ajuste_dir()
{
  //operacion de punto medio sumando las dos distancias captadas por los sensores laterales
  dist3 = Sensor3.ping_cm();
  Serial.print("  sensor3: ");
  Serial.print(dist3);
  delay(100);
    
  dist2 = Sensor2.ping_cm();
  Serial.print("  sensor2: ");
  Serial.print(dist2);
  delay(100);
  

   
  PM= (dist2+dist3+13)/2;
  Serial.print("  Pmedio: ");
  Serial.println(PM);
//operacion para buscar angulo
//    
  double anoguloRadianes = atan((double)(PM/catetoAdyacente));
  double anguloGrados = 180*(double)anguloRadianes/PI;
 
 //logica para ajustar la posicion del robot al centro(no terminada)
 // if(dist2!= PM)
 //  {
  int gra= 90+anguloGrados;
  for (pos=90; pos<gra;pos+=1);
  //{
    smotorsen.write(pos);
    delay(25);
    Serial.println(gra);
//  }

//   }
}

//**************************************************************************

void dif_distan(){  
  if (dist3 < 30){
    mov_adelante();
    mov_izq();
   smotordir.write(Dir_Frente);
   delay(100);
  }
  else (dist3 > 30);{
    mov_der();
  }
}
//**************************************************************************
void rot_sen1(){  //mueve el sensor frontal en tres angulos
  
smotorsen.write(30);
   dist45=Sensor1.ping_cm();
  Serial.print (dist45);  
   Serial.print(" derecha ");
     delay(500);

   smotorsen.write(190);
   dist145= Sensor1.ping_cm();
   Serial.print (dist145);
   Serial.print(" izquierda ");
    delay(500);
   
   smotorsen.write(90);
   dist90= Sensor1.ping_cm();
   Serial.print (dist90);
   Serial.println("  de frente  " );
   delay(500);    

 } 
 //**************************************************************************
void espacio_libre() //No esta terminada
{
  if(dist2 < 30){
    smotordir.write(105);
    delay(600);
    smotordir.write(68);
    delay(200);
    smotordir.write(Dir_Frente);
    delay(500);
    parar();
  }
  if (dist2 > 30){
    smotordir.write(Dir_Frente);
    delay(1000);
  }
     if(dist3 < 30){
    smotordir.write(75);
    delay(600);
    smotordir.write(105);
    delay(200);
    smotordir.write(Dir_Frente);
    delay(500);
    parar();
  }
  if (dist3 > 30){
    smotordir.write(Dir_Frente);
    delay(1000);
  }
  
}

//**************************************************************************

void cruce()
{
  if(dist2 < dist3)
  {
    smotordir.write(105);
    delay(400);
  }
  if(dist2 > dist3)
  {
    smotordir.write(75);
    delay(400);
  }
  
}
//**************************************************************************

void activacion_c(){
  if(dist90 < 40)
  {
    cruce();
  }
}

void setup() {
  Serial.begin(9600);   //Se configura el puerto serial a 9600 BAUDs
  
  //calibracion minimo y maximo de las direccionales
   smotordir.attach(9,600,1250);
   smotordir.write(Dir_Frente);
//   smotordir.write(Dir_Frente);
//   delay(200);

   //calibracion direccionales servomotor del sensor delantero
  smotorsen.attach(10,840,1870);
//  smotorsen.write(90);



}

void loop() 
 {
mov_adelante();
ajuste_dir();
espacio_libre();
rot_sen1();
activacion_c();
 
//smotordir.write(75);
//delay(1500);
//smotordir.write(100);
//smotordir.write(Dir_Frente);
 }
