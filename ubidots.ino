// include de libs
#include "UbidotsESPMQTT.h"
#include "CTBot.h"
#include <Servo.h>

// definição de constantes
Servo servo;
CTBot myBot;

#define TOKEN "BBFF-PRQhjGLxaEdCU9Orh7V2izzwJCy4wy" // Ubidots TOKEN
#define WIFINAME "InspectorGadget" // SSID
#define WIFIPASS "Go.Go.Gadget!" // Wifi Pass

// token do telegram
String teleToken = "1987822642:AAHQ1gJXl5_lvDbv3ZmalvglVZld9OGjhyI";

// instancia ubidots passando o token da conta utilizada
Ubidots client(TOKEN);

// função callback auxiliar
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// define variaveis utilizadas

const int pinSensor = A0;

int valueRead;

int analogDry = 800;
int analogWet = 500;
int percDry = 0;
int percWet = 100;
int count = 0;

void setup() {

  client.setDebug(true);
  Serial.begin(115200);

  // inicia conexao na rede wifi
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  
  pinMode(LED_BUILTIN, OUTPUT);

  // inicia conexao com bot
  myBot.setTelegramToken(teleToken);

  // checa conexao com o bot
  if (myBot.testConnection())
    Serial.println("OK");
  else
    Serial.println("BOT CONNECTION ERROR");
  
  // define servo e posicao
  servo.attach(5); //D1
  servo.write(0);
  pinMode(5,OUTPUT);
}

void loop() {
  // checa se conexao, caso esteja desconectado, tenta reconectar
  if(!client.connected()){
      client.reconnect();
  }
      
  delay(2000);
  // leitura do solo utilizando o sensor de umidade
  valueRead = constrain(analogRead(pinSensor), analogWet, analogDry);
  valueRead = map(valueRead, analogWet, analogDry, percWet, percDry);

  // umidity constant measure

  if (valueRead <=40){
    servo.write(90);
  } else {
    servo.write(0);
  }

  // envia para o dashboard as informacao da leitura do solo
  client.add("humidity", valueRead);
  client.ubidotsPublish("my-new-device");
  client.loop();
  delay(1000);

  // telegram implementation

  // define variavel que armazena mensagens recebidas do bot telegram
  TBMessage msg;

  // verifica se existe nova mensagem recebida no bot do telegram
  if (myBot.getNewMessage(msg)){
    // caso mensagem seja "on", liga o led embutido (utilizado apenas pra teste)
    if (msg.text.equalsIgnoreCase("on") || msg.text.equals("/on")){
      digitalWrite(LED_BUILTIN, LOW);
      myBot.sendMessage(msg.sender.id, "LED ligado");
    }
    // caso mensagem seja "off", desliga o led embutido (utilizado apenas pra teste)
    else if (msg.text.equalsIgnoreCase("off") || msg.text.equals("/off")){
      digitalWrite(LED_BUILTIN, HIGH);
      myBot.sendMessage(msg.sender.id, "LED desligado");
    }
    // caso mensagem seja "start", inicia as instrucoes do bot
    else if (msg.text.equals("/start")){
      String welcome;
      welcome = (String)"Seja bem vindo(a) " + msg.sender.username + (String)"! Escolha um comando do menu para iniciar.";
      myBot.sendMessage(msg.sender.id, welcome);
    }
    // caso mensagem seja "read", efetuará a leitura de umidade do solo 
    else if (msg.text.equalsIgnoreCase("read") || msg.text.equals("/read")){
      myBot.sendMessage(msg.sender.id, "Efeituando leitura do solo, por favor aguarde...");
      valueRead = constrain(analogRead(pinSensor), analogWet, analogDry);
      valueRead = map(valueRead, analogWet, analogDry, percWet, percDry);
      String currentValue;
      currentValue = (String)"Nível de umidade do solo: " + valueRead + "%"; 

      // caso a leitura do solo retorne menor que 40%, informa a situacao e envia o link do ubidots com as leituras e grafico
      if (valueRead <= 40){
        myBot.sendMessage(msg.sender.id, "Atenção! A umidade do solo está baixa");
        myBot.sendMessage(msg.sender.id, currentValue);
        myBot.sendMessage(msg.sender.id, "Para mais informações, acesse o link abaixo:");
        myBot.sendMessage(msg.sender.id, "https://bit.ly/3DwJteB");
        servo.write(90);
      // caso a leitura do solo retorne maior que 40%, informa a situacao e envia o link do ubidots com as leituras e grafico  
      } else if (valueRead > 40){
        myBot.sendMessage(msg.sender.id, "Excelente, a umidade do solo está no nível ideal");
        myBot.sendMessage(msg.sender.id, currentValue);
        myBot.sendMessage(msg.sender.id, "Para mais informações, acesse o link abaixo:");
        myBot.sendMessage(msg.sender.id, "https://bit.ly/3DwJteB");
        servo.write(0);
      }
      
      while(count < 3){
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        count++;
      }

    }
    else{
      // caso receba qualquer outro comando, envia uma mensagem generica no bot do telegram
      String reply;
      reply = (String)"Olá " + msg.sender.username + (String)", insira um comando válido!";
      myBot.sendMessage(msg.sender.id, reply);
    }
  }
  delay(500);

}
