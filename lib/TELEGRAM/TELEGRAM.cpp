#include <TELEGRAM.h>

#define TELEGRAM_DEBUG

const unsigned long BOT_MTBS = 1000;
unsigned long bot_lastTime = 0;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void TELEGRAM::begin(){
  secured_client.setTrustAnchors(&cert);
}

//const String _idTelegram, String _message, const String &parse_mode = ""

void TELEGRAM::updates(){
  unsigned long startMillis = millis();
  if (startMillis - bot_lastTime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages){
      this->handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
  bot_lastTime = startMillis;
  }
}

void TELEGRAM::handleNewMessages(int numMessages){
  for (uint8_t i = 0; i < numMessages; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    bot.sendChatAction(chat_id, "typing");
    delay(300);
    if (chat_id != ID_MY_TG_USER) {
      bot.sendMessage(ID_MY_TG_USER, 
      "El ID: " + chat_id + 
      " de nombre: " + from_name + 
      " envio un msj con el texto: " + text + 
      "\n", "");
    }

    /**
     * A partir de aca se deben incluir los comandos
     * necesarios para la ejecucion tomando como
     * ejemplo los ya incluidos.
     */

    if(text == "/saludo"){
      bot.sendMessage(chat_id, "Hola " + from_name + " como estas?", "");
    }
    if(text == "/ledOn"){
      digitalWrite(LedPin, LOW);
    }
    if(text == "/ledOff"){
      digitalWrite(LedPin, HIGH);
    }
    if(text == "/inicio"){
      String welcome = "Bienvenido " + from_name + "\n\n";
      welcome += "* COLDMIND SOLUCIONES - IOT *\n\n";
      welcome += "/inicio : este mensaje\n";
      welcome += "/saludo : un saludito\n";
      welcome += "/ledOn : para apagar led\n";
      welcome += "/ledOff : para encender led\n\n";
      welcome += "coldmindsoluciones@gmail.com\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }

}

