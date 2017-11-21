#include <SoftwareSerial.h>

//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int IN5 = 8;
int IN6 = 9;
int IN7 = 10;
int IN8 = 11;

#define motor1_tras     digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
#define motor1_parar    digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH);
#define motor1_frente   digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
#define motor1_morto    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);

#define motor2_frente   digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
#define motor2_parar    digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH);
#define motor2_tras     digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
#define motor2_morto    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);

#define motor3_frente     digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
#define motor3_parar    digitalWrite(IN5, HIGH); digitalWrite(IN6, HIGH);
#define motor3_tras   digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);
#define motor3_morto    digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);

#define motor4_tras     digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
#define motor4_parar    digitalWrite(IN7, HIGH); digitalWrite(IN8, HIGH);
#define motor4_frente   digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);
#define motor4_morto    digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);

SoftwareSerial BTSerial(2, 3);
String command = "";

void setup()
{
    Serial.begin(9600);
    BTSerial.begin(9600);
    
    //Define os pinos como saida
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(IN5, OUTPUT);
    pinMode(IN6, OUTPUT);
    pinMode(IN7, OUTPUT);
    pinMode(IN8, OUTPUT);
}

void loop()
{
    if (BTSerial.available()) {
        command = (char) BTSerial.read();
        
        if (command == "S")
        {
            motor1_morto;
            motor2_morto;
            motor3_morto;
            motor4_morto;
        }
        else if (command == "F")
        {
            motor1_frente;
            motor2_frente;
            motor3_morto;
            motor4_morto;
        } else if (command == "B")
        {
            motor1_morto;
            motor2_morto;
            motor3_tras;
            motor4_tras;
        } else if (command == "R")
        {
            motor2_frente;
            motor3_frente;
            motor1_morto;
            motor4_morto;
        } else if (command = "L")
        {
            motor1_frente;
            motor4_frente;
            motor2_morto;
            motor3_morto;
        } else {
            motor1_morto;
            motor2_morto;
            motor3_morto;
            motor4_morto;
        }

        command = "";
    }
}
