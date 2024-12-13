#include <WiFi.h>
#include <HTTPClient.h>

#define led_azul 9 // Pino utilizado para controle do led azul
#define led_verde 41 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 2 // Pino utilizado para controle do led amarelo

const int botãoPin = 18;  // o número do pino do botão
int botãoEstado = 0;  // variável para leitura do status do botão

const int ldrPin = 4;  // o número do pino do botão
int limite=600;

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(led_amarelo,OUTPUT);

  // Inicialização das entradas
  pinMode(botãoPin, INPUT); // Inicialize o pino do botão como uma entrada

  digitalWrite(led_azul, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  // Verifica estado do botão
  botãoEstado = digitalRead(botãoPin);
  if (botãoEstado == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Disconnected");
  }
}

void loop() {
  int ldrstatus=analogRead(ldrPin);

  if(ldrstatus<=limite){
    digitalWrite(led_amarelo, HIGH); // Liga o LED
    delay(1000); // Espera 1 segundo
    digitalWrite(led_amarelo, LOW); // Desliga o LED

    Serial.print("seu led escuro acende");
    Serial.println(ldrstatus);

  }else{
    Serial.print("sua luz brilhante apaga");

    digitalWrite(led_verde, HIGH); // Liga o LED
    delay(3000); // Espera 3 segundos
    digitalWrite(led_verde, LOW); // Desliga o LED

    digitalWrite(led_amarelo, HIGH); // Liga o LED
    delay(2000); // Espera 2 segundos
    digitalWrite(led_amarelo, LOW); // Desliga o LED

    digitalWrite(led_vermelho, HIGH); // Liga o LED
    delay(5000); // Espera 5 segundos
    digitalWrite(led_vermelho, LOW); // Desliga o LED

    Serial.println(ldrstatus);
  }
}
