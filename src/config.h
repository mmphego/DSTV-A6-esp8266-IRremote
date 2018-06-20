#include <FS.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <PubSubClient.h>
#include <RgbIrLed.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "fauxmoESP.h"

#ifndef config_h
#define config_h

// SAMSUNG POWER ON/OFF
uint16_t Samsung_power_toggle[71] = {38000,1,1,170,170,20,63,20,63,20,63,20,20,20,20,20,
                                     20,20,20,20,20,20,63,20,63,20,63,20,20,20,20,20,20,
                                     20,20,20,20,20,20,20,63,20,20,20,20,20,20,20,20,20,
                                     20,20,20,20,63,20,20,20,63,20,63,20,63,20,63,20,63,
                                     20,63,20,1798};

// DSTV A6
uint16_t POWER[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,500,500,
                  500,500,500,500,1499,500,1499,500,1499,500,500,500,500,500,1499,500,1499,500,1499,
                  0,500,500,500,500,500,500,500,500,500,500,500};


uint16_t CATCH_UP[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,1499,500,
                  500,500,1499,500,1499,500,1499,500,1499,500,500,500,500,500,500,500,1499,500,500,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t PLAYLIST[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,1499,500,
                  1499,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,500,500,500,500,500,
                  500,1499,500,500,500,500,500,500,500,500,500};


uint16_t BOX_OFFICE[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,1499,500,
                  1499,500,500,500,1499,500,1499,500,1499,500,500,500,500,500,500,500,500,500,1499,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t TV_GUIDE[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,500,500,
                  1499,500,500,500,1499,500,1499,500,1499,500,500,500,500,500,1499,500,500,500,1499,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t SEARCH_[68] = {7961,3981,504,504,504,1486,504,1486,504,504,504,1486,504,1486,504,1486,504,1486,
                  504,1486,504,504,504,504,504,1486,504,504,504,504,504,1486,504,1486,504,504,504,
                  504,504,1486,504,1486,504,1486,504,1486,504,504,504,504,504,1486,504,1486,504,504,
                  504,504,504,504,504,504,504,504,504,504,504};


uint16_t DSTV[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,
                  1499,500,500,500,500,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,1499,
                  500,1499,500,500,500,500,500,500,500,500,500};


uint16_t INFO[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,500,500,
                  1499,500,1499,500,1499,500,1499,500,1499,500,500,500,500,500,1499,500,500,500,500,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t EXIT[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,500,500,
                  1499,500,500,500,500,500,1499,500,1499,500,500,500,500,500,1499,500,500,500,1499,
                  500,1499,500,500,500,500,500,500,500,500,500};


uint16_t PROFILE[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,500,500,
                  500,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,1499,500,1499,500,500,
                  500,1499,500,500,500,500,500,500,500,500,500};


uint16_t TV[68] = {7994,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,500,500,
                  1499,500,1499,500,500,500,1499,500,500,500,1499,500,1499,500,1499,500,500,500,500,
                  500,1499,500,500,500,500,500,500,500,500,500};

uint16_t UP[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,500,500,
                  1499,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,1499,500,500,500,500,
                  500,1499,500,500,500,500,500,500,500,500,500};


uint16_t DOWN[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,1499,500,
                  1499,500,500,500,500,500,1499,500,1499,500,500,500,500,500,500,500,500,500,1499,
                  500,1499,500,500,500,500,500,500,500,500,500};


uint16_t LEFT[68] = {7988,3981,504,504,504,1486,504,1486,504,504,504,1486,504,1486,504,1486,504,1486,
                  504,1486,504,504,504,504,504,1486,504,504,504,504,504,1486,504,1486,504,1486,504,
                  504,504,504,504,504,504,1486,504,1486,504,504,504,504,504,504,504,1486,504,1486,
                  504,1486,504,504,504,504,504,504,504,504,504};


uint16_t RIGHT[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,1499,500,
                  500,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,500,500,1499,500,500,
                  500,1499,500,500,500,500,500,500,500,500,500};


uint16_t OK_BUTTON[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,1499,500,
                  500,500,500,500,1499,500,1499,500,1499,500,500,500,500,500,500,500,1499,500,1499,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t OPTIONS[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,
                  1499,500,1499,500,1499,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,500,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t ALT[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,1499,500,1499,500,1499,500,
                  1499,500,1499,500,1499,500,1499,500,1499,500,500,500,500,500,500,500,500,500,500,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t MUTE[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,1499,500,500,500,500,
                  500,500,500,1499,500,1499,500,500,500,1499,500,500,500,1499,500,1499,500,1499,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t P_PLUS[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,500,500,1499,
                  500,500,500,500,500,1499,500,500,500,1499,500,1499,500,1499,500,500,500,1499,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t P_MINUS[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,500,500,1499,
                  500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,500,500,1499,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t VOL_PLUS[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,500,500,500,
                  500,1499,500,500,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,500,500,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t VOL_MINUS[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,500,500,500,
                  500,1499,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,500,500,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t PLAY_PAUSE[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,500,
                  500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t STOP[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,500,
                  500,1499,500,1499,500,1499,500,500,500,1499,500,1499,500,500,500,1499,500,500,0,
                  500,500,500,500,500,500,500,500,500,500,500};


uint16_t RECORD[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,1499,
                  500,1499,500,500,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,500,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t REWIND[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,500,
                  500,500,500,500,500,1499,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t FORWARD[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,500,
                  500,1499,500,500,500,1499,500,500,500,1499,500,1499,500,500,500,1499,500,500,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t NUM_1[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,500,
                  500,500,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t NUM_2[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,500,
                  500,1499,500,500,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,500,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t  NUM_3[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,500,
                  500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,500,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t NUM_4[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,1499,
                  500,500,500,500,500,1499,500,1499,500,1499,500,1499,500,1499,500,500,500,1499,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t NUM_5[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,1499,
                  500,500,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,500,500,1499,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t NUM_6[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,1499,
                  500,1499,500,500,500,1499,500,1499,500,1499,500,1499,500,1499,500,500,500,500,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t NUM_7[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,1499,
                  500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,500,500,500,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t NUM_8[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,1499,500,500,
                  500,500,500,500,500,1499,500,1499,500,1499,500,1499,500,500,500,1499,500,1499,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t NUM_9[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,1499,500,500,
                  500,500,500,1499,500,1499,500,1499,500,1499,500,1499,500,500,500,1499,500,1499,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t NUM_0[68] = {7968,3971,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,500,500,500,
                  500,500,500,500,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,1499,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t ARC[68] = {7941,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,500,500,500,500,1499,500,1499,
                  500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,500,500,500,500,1499,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t HELP[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,1499,500,1499,500,500,500,1499,
                  500,1499,500,1499,500,1499,500,500,500,500,500,500,500,1499,500,500,500,500,500,
                  500,500,500,500,500,500,500,500,500,500};


uint16_t DISCRETE_ON[68] = {7968,3997,500,500,500,1499,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,
                  500,1499,500,500,500,500,500,1499,500,500,500,1499,500,1499,500,1499,500,1499,500,500,
                  500,500,500,500,500,1499,500,500,500,500,500,500,500,500,500,1499,500,1499,500,
                  1499,500,500,500,500,500,500,500,500,500};


uint16_t DISCRETE_OFF[68] = {7988,3981,504,504,504,1486,504,1486,504,504,504,1486,504,1486,504,1486,504,1486,
                  504,1486,504,504,504,504,504,1486,504,504,504,1486,504,1486,504,1486,504,1486,504,504,
                  504,504,504,1486,504,1486,504,504,504,504,504,504,504,504,504,1486,504,1486,504,
                  504,504,504,504,504,504,504,504,504,504};

#define freq_strip               32 //khz
#define freq                     38 //khz
#define IRPin                    D2

#define hostname                 "remote"
#define ssid                     "GetUrOwnWiFi"
#define password                 "Livhu300312"

#define mqtt_server              "192.168.1.11"
#define mqttTopicTV              "/IRControl/TV"
#define mqttTopicDStv            "/IRControl/DSTV"
#define mqttTopicLog             "/IRControl/log"

#define LEDStrip                 0
#define mqttTopicAmbiLite        "/IRControl/AmbiLite"

#define  MOVIETIME               "Movie Time"
#define YOUTUBE                  "Youtube"
#define  TV                      "TV"
#define JSON_BUF_SIZE            256

//byte xbmchost[] = {192,168,1,105};
IPAddress xbmchost(192,168,1,105);

// NETWORK: Static IP details...
IPAddress ip(192, 168, 1, 15);
IPAddress gateway(192, 168, 1, 1);
IPAddress dns(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

char receivedChar[100];
bool running = false;
bool stopped = true;
char msg[50];
char message[65];
// NTP Servers:
static const char ntpServerName[] = "us.pool.ntp.org";
//static const char ntpServerName[] = "time.nist.gov";

const int timeZone = 2; // Jozi Time

unsigned int localPort = 8888;  // local port to listen for UDP packets

#endif
