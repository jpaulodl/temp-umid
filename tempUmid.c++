//Baixar biblioteca DHT Sensor Library ou instalar do gerenciador de bibliotecas da IDE
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN 6 // o sensor dht11 foi conectado ao pino 6
#define DHTTYPE DHT11

// LED 
const int ledVermelho = 11; // ligar led vermelho na porta 11
const int ledVerde = 10; // ligar led verde na porta 10
const int led = ledVermelho + ledVerde;

Adafruit_SSD1306 display = Adafruit_SSD1306(); // objeto tipo Adafruit_SSD1306

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // inicializa o monitor serial
  Serial.println("DHT teste!"); // imprime o texto no serial
  dht.begin();

  Wire.begin();                              // inicia com a biblioteca
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicia o display com endereço I2C 0x3C
  display.setTextColor(WHITE);               // define cor
  display.setTextSize(1);                    // define o tamanho da fonte
  display.clearDisplay();                    // limpa as informações do display

  pinMode(led,OUTPUT); // inicia led

}

void loop() {
  //declarar as variáveis para receber os valores
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  // Se as variáveis temperatura e umidade não forem valores válidos, acusará falha de leitura.

  // escritos do display
  display.setCursor(0, 0);    // posiçao do texto no display
  display.print("TEMPERATURA E UMIDADE");   // escreve o texto no display

  display.setCursor(15, 12);    // posiçao do texto no display
  display.print("Umidade: "); // escreve o texto no display
  display.print(umidade);     // escreve o texto no display
  delay(1000);                  // intervalo de 1 segundo
  
  display.setCursor(15, 24);    // posiçao do texto no display
  display.print("Temperatura: ");   // escreve o texto no display
  display.print(temperatura);     // escreve o texto no display
  delay(1000);                  // intervalo de 1 segundo
  
  // Limpeza do display não apagar!
  display.display();            // permite a mudança de texto no display
  display.clearDisplay();       // limpa o texto do display


  if(temperatura < 30){
  digitalWrite(ledVerde, HIGH);
  delay(500);
  digitalWrite(ledVerde, LOW);
  delay(500);
  }
  else {
  digitalWrite(ledVermelho, HIGH);
  delay(500);
  digitalWrite(ledVermelho, LOW);
  delay(500);
  }


  if (isnan(temperatura) || isnan(umidade)) {
  Serial.println("Falha na leitura do dht11...");
  }
  else
  {
    // se os valores forem válidos, imprime os dados no monitor serial
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" "); //quebra de linha
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    delay(1000); //aguardar 1 segundo
  }
}
