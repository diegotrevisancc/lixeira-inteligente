#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 9, 5, 4, 3, 2);

float const echo=10;
float const trig=11;

float const echo2 = 7;
float const trig2 = 6;


//20x17.5x21.5
double larguraCaixa = 20; 
double comprimentoCaixa = 17.5;
double alturaCaixa = 21.5;
double volumeCaixa = 20 * 17.5 * 21.5; //7525cm³

long leituraUm, leituraDois;
long alturaLida;

long duracao,altura;
long duracaoDois, altura2;

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
    
  	Serial.println(leituraUm);
  	Serial.println(leituraDois);
    
  	double volumeUm = calculaVolume(leituraUm);
    double volumeDois = calculaVolume(leituraDois);

    double mediaDosVolumes = (volumeUm + volumeDois) / 2;
    delay(3000);
	
  	
  
    double porcentoOcupado = (mediaDosVolumes * 100) / volumeCaixa;
    
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
    altura =(duracao/2) / 29.1;
    return altura;
}


long alturaDois(){
    digitalWrite(trig2, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2,LOW);
  
    duracaoDois=pulseIn(echo2, HIGH);
    altura2 =(duracaoDois/2) / 29.1;
    return altura2;
}

double calculaVolume(float alturaLida) {
    double volume = alturaLida * comprimentoCaixa * larguraCaixa;
    return volume;
}