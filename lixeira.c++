#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 9, 5, 4, 3, 2);

float const echo = 10;
float const trig = 11;
float altSensor;
long duracao;

float altVariavel;


void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    //int volumeLixeira = largura * comprimento * altura;
    int contador = 0;
    while (contador < 24) {
    Serial.println("-------");
    Serial.println("-------");
    float leituraUm = volumeLixeira(2.0, 1.5, 2.0);
    Serial.println("Leitura 1: ");
    Serial.print(leituraUm);
    Serial.println("m3");

    delay(6000); // Tempo para próxima leitura

    float leituraDois = volumeLixeira(2.0, 1.5, 2.0);
    Serial.println("Leitura 2: ");
    Serial.print(leituraDois);
    Serial.println(" Litros");

    float volumeOcupado = leituraUm - leituraDois;
    //float volumeOcupadoPorCento = (volumeOcupado * 100)/volumeLixeira;

    // configLCD
    lcd.setCursor(0, 0);
    lcd.print("Ocupado: ");
    lcd.print("        ");
    lcd.setCursor(9, 0);
    lcd.print(volumeOcupadoPorCento);
    }
    contador++;

}

float volumeLixeira(float altTotal, float largura, float comprimento)
{
    // Todos os valores estão em metros.
    leituraSensorUltrassonicoUm();
    altVariavel = altTotal - altSensor;

    double volumeAtual = largura * comprimento * altVariavel;
    return volumeAtual;
}

long leituraSensorUltrassonicoUm()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duracao = pulseIn(echo, HIGH);
    duracao = (double)duracao;
    altSensor = (duracao / 2) / 29.1;
    altSensor /= 100;
}
