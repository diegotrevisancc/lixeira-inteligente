#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 9, 5, 4, 3, 2);

float const echo=10;
float const trig=11;

float const echo2 = 7;
float const trig2 = 6;

double altura, leituraUm, leituraDois, duracao;

double larguraCaixa = 30; 
double comprimentoCaixa = 20;
double alturaCaixa = 40;
long alturaLida;
void setup(){
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
    leituraDois = alturaDois();
    
    double volumeUm = calculaVolume(leituraUm);
    double volumeDois = calculaVolume(leituraDois);

    double mediaDosVolumes = (volumeUm + volumeDois) / 2;
    delay(6000);
    double volumeCaixaVazia = larguraCaixa * alturaCaixa * comprimentoCaixa;
    double porcentoOcupado = (mediaDosVolumes * 100) / volumeCaixaVazia;
    //configLCD
    lcd.setCursor(0,0);
    lcd.print("Volume Ocupado: ");
    lcd.print("        ");
    lcd.setCursor(0,1);
    lcd.print(porcentoOcupado);
}




long alturaUm(){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
  
    duracao=pulseIn(echo, HIGH);
    duracao=(double)duracao;
    altura =(duracao/2) / 29.1;
    return altura;
}


long alturaDois(){
    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2,LOW);
  
    duracao=pulseIn(echo2, HIGH);
    duracao=(double)duracao;
    altura =(duracao/2) / 29.1;
    return altura;
  }

float calculaVolume(float alturaLida) {
    float volume = alturaLida * comprimentoCaixa * larguraCaixa;
    return volume;
}