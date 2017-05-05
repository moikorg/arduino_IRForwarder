#include "RestClient.h"

#include <SPI.h>
#include <Ethernet.h>
#include <IRremote.h>

/* IRremote hex codes for received remote commands */
#define REMOTE_PLAY      0xffc23d
#define REMOTE_VOLU      0xffa857
#define REMOTE_VOLD      0xffe01f
#define REMOTE_0         0xff6897
#define REMOTE_1         0xff30cf
#define REMOTE_2         0xff18e7
#define REMOTE_3         0xff7a85
#define REMOTE_4         0xff10ef
#define REMOTE_5         0xff38c7
#define REMOTE_6         0xff5aa5
#define REMOTE_7         0xff42bd
#define REMOTE_8         0xff4ab5
#define REMOTE_9         0xff52ad
#define REMOTE_CHP       0xffe21d
#define REMOTE_CHM       0xffa25d

const int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);

String rawstring;
char _buffer[25];


/* Millisecond timer values */
unsigned long   lastcmd = 0;

RestClient client = RestClient("sonosRESTAPI.moik.org", 5000);

// Pin assignments
byte greenLedPin = 9;


void greenLedOn();
void greenLedOff();

void setup() {
  // Setup LEDs
  pinMode(greenLedPin, OUTPUT);


  /*
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    // this check is only needed on the Leonardo:
     while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("serial comm established");
  */

  client.dhcp();
  //  Serial.println("Connected and IP received");

  greenLedOn();

  irrecv.enableIRIn(); // Start the receiver

  pinMode(greenLedPin, OUTPUT);
  int a;
  for (a = 0; a < 8; a = a + 1 ){
      greenLedOn();
      delay(600);
      greenLedOff();
      delay(300);
   }
  for (a = 0; a < 40; a = a + 1 ){
      greenLedOn();
      delay(10);
      greenLedOff();
      delay(150);
   }
  greenLedOff();
}


void loop() {
  String response;
  decode_results results;
  int statusCode;

  if (irrecv.decode(&results)) {
    if (millis() > (lastcmd + 50)) {
      Serial.println(results.value, HEX);
      /* compare received IR against known commands */
      switch (results.value) {
        case REMOTE_VOLU:
          //        Serial.println("Vol Up");
          statusCode = client.get("/volUp/", &response);
          break;
        case REMOTE_VOLD:
          //      Serial.println("Vol Down");
          statusCode = client.get("/volDown/", &response);
          break;
        case REMOTE_PLAY:
          //        Serial.println("Play");
          statusCode = client.get("/playpause/", &response);
          break;
        case REMOTE_0:
          //        Serial.println("IR 0");
          statusCode = client.get("/ircode/0", &response);
          break;
        case REMOTE_1:
          //        Serial.println("IR 1");
          statusCode = client.get("/ircode/1", &response);
          break;
        case REMOTE_2:
          //        Serial.println("IR 2");
          statusCode = client.get("/ircode/2", &response);
          break;
        case REMOTE_3:
          //        Serial.println("IR 3");
          statusCode = client.get("/ircode/3", &response);
          break;
        case REMOTE_4:
          //        Serial.println("IR 4");
          statusCode = client.get("/ircode/4", &response);
          break;
        case REMOTE_5:
          //        Serial.println("IR 5");
          statusCode = client.get("/ircode/5", &response);
          break;
        case REMOTE_6:
          //        Serial.println("IR 6");
          statusCode = client.get("/ircode/6", &response);
          break;
        case REMOTE_7:
          //        Serial.println("IR 7");
          statusCode = client.get("/ircode/7", &response);
          break;
        case REMOTE_8:
          //        Serial.println("IR 8");
          statusCode = client.get("/ircode/8", &response);
          break;
        case REMOTE_9:
          //        Serial.println("IR 9");
          statusCode = client.get("/ircode/9", &response);
          break;
        default:
          //        Serial.print("Unknown code: 0x");
          //        Serial.println(results.value, HEX);
          sprintf(_buffer, "/rawcode/0x%X", results.value);
          statusCode = client.get(_buffer, &response);
          break;
      }
      /* store time at which last IR command was processed */
      lastcmd = millis();
    }
    irrecv.resume(); // Receive the next value
  }
}


void greenLedOn() {
  digitalWrite(greenLedPin, HIGH);
}

void greenLedOff() {
  digitalWrite(greenLedPin, LOW);
}



