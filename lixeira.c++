#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 12, 8, 11, 7);
float const echo=6;
float const trig=5;

float const echo2 = 9;
float const trig2 = 10;

double larguraCaixa = 20;
double comprimentoCaixa = 17.5;
double alturaCaixa = 24;
double volumeCaixa = alturaCaixa * larguraCaixa * comprimentoCaixa; //7525cm³

long leituraUm, leituraDois;
long alturaLida;

long duracao,altura;
long duracaoDois, altura2;

void setup(){
 analogWrite(A5, 120);
  lcd.begin(16,2);
  lcd.clear();
  pinMode(echo, INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig2,OUTPUT);
  Serial.begin(9600);
}


void loop(){
   
    leituraUm = alturaUm();
    delay(1000);
    leituraDois = alturaDois();
    delay(1000);
    Serial.println(leituraUm);
    Serial.println(leituraDois);
   
    double volumeUm = calculaVolume(leituraUm);
    double volumeDois = calculaVolume(leituraDois);

    double mediaDosVolumes = (volumeUm + volumeDois) / 2;
    
    double porcentoOcupado = (mediaDosVolumes * 100) / volumeCaixa;
    int ocupado = (int)porcentoOcupado;
    if (ocupado >= 1000) {
         lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Lixeira cheia!2);
     }
    else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Disponivel: ");
      lcd.print("        ");
      lcd.setCursor(0,1);
      lcd.print(ocupado);
      lcd.print("%");
      delay(100);
    }

}

long alturaUm(){
    digitalWrite(trig, LOW);
    delayMicroseconds(1);
    digitalWrite(trig, HIGH);
    delayMicroseconds(1);
    digitalWrite(trig,LOW);
 
    duracao=pulseIn(echo, HIGH);
    altura =(duracao/2) / 29.1;
    return altura;
}


long alturaDois(){
    digitalWrite(trig2, LOW);
    delayMicroseconds(1);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(1);
    digitalWrite(trig2,LOW);
 
    duracaoDois=pulseIn(echo2, HIGH);
    altura2 =(duracaoDois/2) / 29.1;
    return altura2;
}

double calculaVolume(float alturaLida) {
    double volume = alturaLida * comprimentoCaixa * larguraCaixa;
    return volume;
}