//Programa : Controle 2 motores DC usando Ponte H L298N
//Autor : FILIPEFLOP

//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

#define motor1_frente digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
#define motor1_parar  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH);
#define motor1_tras   digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);

void setup()
{
    //Define os pinos como saida
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop()
{
    motor1_frente;
    delay(2000);
    motor1_parar;
    delay(1000);
    motor1_tras;
    delay(2000);
    
    // //Gira o Motor A no sentido horario
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, LOW);
    // delay(2000);
    // //Para o motor A
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, HIGH);
    // delay(500);
    // //Gira o Motor B no sentido horario
    // digitalWrite(IN3, HIGH);
    // digitalWrite(IN4, LOW);
    // delay(2000);
    // //Para o motor B
    // digitalWrite(IN3, HIGH);
    // digitalWrite(IN4, HIGH);
    // delay(500);

    // //Gira o Motor A no sentido anti-horario
    // digitalWrite(IN1, LOW);
    // digitalWrite(IN2, HIGH);
    // delay(2000);
    // //Para o motor A
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, HIGH);
    // delay(500);
    // //Gira o Motor B no sentido anti-horario
    // digitalWrite(IN3, LOW);
    // digitalWrite(IN4, HIGH);
    // delay(2000);
    // //Para o motor B
    // digitalWrite(IN3, HIGH);
    // digitalWrite(IN4, HIGH);
    // delay(500);
}
