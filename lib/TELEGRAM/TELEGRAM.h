#ifndef TELEGRAM_h
#define TELEGRAM_h

#include <Arduino.h>
#include <tg_config.h>

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class TELEGRAM{
  public:
    void begin();
    void updates();
  private:
    void handleNewMessages(int newNensaages);
};

#endif