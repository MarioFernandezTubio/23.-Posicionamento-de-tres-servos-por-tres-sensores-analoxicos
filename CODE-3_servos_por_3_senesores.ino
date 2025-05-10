/*
-----POSICIONAMENTO DUN SERVO EMPREGANDO UN SENSOR ANALÓXICO.----

Realiza unha montaxe na que tres servos (alimentados por 
unha batería externa) se conecten, como entrada de control 
(saída para Arduíno), nos pins:

                - PWM D03 (3~)
                - PWM D04 (4)
                - PWM D05 (5~)
                
Candanseu potenciómetro nos pins analóxicos A05, A04, A03 
como entrada do Arduíno. 

- O programa debe ser reactivo ao potenciómetro (8 veces por segundo).
- O potenciómetro controla o ángulo de xiro do servo.
- A precisión do potenciómetro é 
     * Ángulo horizontal (acimut)de 12º.
     * Ángulo de altura (sobre o horizonte) de 5º.
     * Ángulo abre e pecha pinza 0.5º.

*****************************************************************/
/***************************************************************

Programa feito por Mario Fernández Tubío.
Última revisión: 10/05/2025

********************************************************/
#include <Servo.h>
#define poteA A5
#define poteB A4
#define poteC A3

int posA = 0;
int posB = 0;

float posC = 0;//Esta posición será con decimais. 
//               Necesitamos FLOAT

int veloz = 125;      // Reactividade (1000 ms / 8 = 125 ms)

int pasoA = 12;       // Precisión en pasos de 12º
int pasoB = 5;       // Precisión en pasos de 5º

float pasoC = 0.5;       // Precisión en pasos de 0.5º

/*  En Arduino, os valores 
para Servo.write() só aceptan 
valores enteiros entre 0 e 180 */

int microServoC = 0;  // Con esto podemos axustar a 0.5º


Servo servoA;
Servo servoB;
Servo servoC;


/******************  SETUP ******************************/

void setup(){
  
  servoA.attach(3);
  servoB.attach(4);
  servoC.attach(5);
  Serial.begin(9600);
  
  

/******************  LOOP ******************************/  
}

void loop(){
  
// Lemos o pote 
  posA = analogRead(poteA);
  posB = analogRead(poteB);
  
  posC = analogRead(poteC);

    
/* Limitamos o rango de entrada para asegurarnos de que 
   map() só recibe valores no rango esperado.

        constrain(valor,min,max)*/
  posA = constrain(posA, 50, 975);
  posB = constrain(posB, 50, 975);
  posC = constrain(posC, 50, 975);
  
/* Remapear o rango para que "50 sexa 0" e "975 sexa 1023".
     "map(valor, fromLow, fromHigh, toLow, toHigh)"*/
  posA = map(posA, 50,    975,       0,     180); 
  posB = map(posB, 50,    975,       0,     180); 
  posC = map(posC, 50,    975,       0,     180); 
  

// Axustamos á precisión de 10 grados
  posA = (posA / pasoA) * pasoA;
  posB = (posB / pasoB) * pasoB;
  
  posC = round (posC / pasoC) * pasoC;
  /* Neste caso necesitamos redondear para que ó multiplicar
     teñamos 0.5 ou 0*/

  
  servoA.write(posA);
  servoB.write(posB);
  
  
/* Para servoC usamos writeMicroseconds() 
  para poder axustar a 0.5º */
  
//                           graosº  microsegundos
  int microServoC = map(posC, 0, 180, 544, 2400);
/*    Agora podemos enviar valores de 544 a 2400.
       é dicir 1856 valores */

// A librería servo.h define o mínimo en 544 e o máximo en 2400
  
  servoC.writeMicroseconds(microServoC);
  
  Serial.println(posA);
  Serial.println(posB);
  Serial.println(posC);
  
  delay(veloz);
  
}
