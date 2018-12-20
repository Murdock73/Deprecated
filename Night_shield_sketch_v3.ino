/*
 Created By S.Conigliello based on the sketch by Rui Santos (http://randomnerdtutorials.com)
 Arduino with Ethernet Shield
 */

#include <SPI.h>
#include <Ethernet.h>

int salagdn = A4;
int salagup = A5;
int salapdn = 6;
int salapup = 7;
//reserved by ethernet shield pin 10, 11, 12 and 13;
int cucinadn = A1;
int cucinaup = A0;
int studiodn = A3;
int studioup = A2;
int bagnoup =4;
int bagnodn =5;


boolean TUTTESU = false;
boolean TUTTEGIU = false;
boolean LUCIMANUALI = false;

unsigned long startsalag = 0;
unsigned long endsalag = 31000;
unsigned long startsalap = 0;
unsigned long endsalap = 24000;
unsigned long startcucina = 0;
unsigned long endcucina = 26000;
unsigned long startbagno = 0;
unsigned long endbagno = 17000;
unsigned long startstudio = 0;
unsigned long endstudio = 23000;


int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 1, 111 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 1, 254 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
 // Open serial communications and wait for port to open:
  delay(60000);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(salagup, OUTPUT);
  pinMode(salagdn, OUTPUT);
  pinMode(salapup, OUTPUT);
  pinMode(salapdn, OUTPUT);
  pinMode(cucinaup, OUTPUT);
  pinMode(cucinadn, OUTPUT);
  pinMode(studioup, OUTPUT);
  pinMode(studiodn, OUTPUT);
  pinMode(bagnoup, OUTPUT);
  pinMode(bagnodn, OUTPUT);
  digitalWrite(salagup, LOW);
  digitalWrite(salagdn, LOW);
  digitalWrite(salapup, LOW);
  digitalWrite(salapdn, LOW);
  digitalWrite(cucinaup, HIGH);
  digitalWrite(cucinadn, HIGH);
  digitalWrite(studioup, HIGH);
  digitalWrite(studiodn, HIGH);
  digitalWrite(bagnoup, HIGH);
  digitalWrite(bagnodn, HIGH);
  digitalWrite(bagnodn, HIGH);
  digitalWrite(bagnodn, HIGH);
 
  
// start the Ethernet connection and the server:
//  Ethernet.begin(mac, ip, gateway, subnet);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println(F("HTTP/1.1 200 OK")); //send new page
           client.println(F("Content-Type: text/html"));
           client.println();     
           client.println(F("<HTML>"));
           client.println(F("<HEAD>"));
           client.println(F("<meta name='android-mobile-web-app-capable' content='yes' />"));
           client.println(F("<meta name='android-mobile-web-app-status-bar-style' content='black-translucent' />"));
           client.println(F("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />"));
           client.println(F("<TITLE>CASA CONIGLIELLO</TITLE>"));
           client.println(F("</HEAD>"));
           client.println(F("<BODY>"));
           client.println(F("<H1>Controllo remoto tapparelle</H1>"));
           client.println(F("<hr />"));
           client.println(F("<br />"));  
           client.println(F("<br />"));  
           client.println(F("<a href=\"/?emergencystop\"\">STOP!</a><br />"));
           client.println(F("<br />"));  
           client.println(F("<br />"));     
           client.println(F("<H2>Tutte le tapparelle</H2>"));
           client.println(F("<br />"));  
           client.println(F("<a href=\"/?TUTTESU\"\">SU</a>"));
           client.println(F("<a href=\"/?TUTTEGIU\"\">GIU'</a><br />"));
           client.println(F("<br />"));   
           client.println(F("<br />"));   
           client.println(F("<H2>Sala Grande</H2>"));
           client.println(F("<br />"));  
           client.println(F("<a href=\"/?SALAGSU\"\">SU</a>"));
           client.println(F("<a href=\"/?SALAGGIU\"\">GIU'</a><br />"));
           client.println(F("<br />"));  
           client.println(F("<H2>Sala Piccola</H2>"));
           client.println(F("<br />"));  
           client.println(F("<a href=\"/?SALAPSU\"\">SU</a>"));
           client.println(F("<a href=\"/?SALAPGIU\"\">GIU'</a><br />"));
           client.println(F("<br />"));  
           client.println(F("<H2>Cucina</H2>"));
           client.println(F("<br />"));  
           client.println(F("<a href=\"/?CUCINASU\"\">SU</a>"));
           client.println(F("<a href=\"/?CUCINAGIU\"\">GIU'</a><br />"));
           client.println(F("<br />"));  
           client.println(F("<H2>Bagno</H2>"));
           client.println(F("<br />"));  
           client.println(F("<a href=\"/?BAGNOSU\"\">SU</a>"));
           client.println(F("<a href=\"/?BAGNOGIU\"\">GIU'</a><br />"));
           client.println(F("<br />"));  
           client.println(F("<H2>Studio</H2>"));
           client.println(F("<br />"));  
           client.println(F("<a href=\"/?STUDIOSU\"\">SU</a>"));
           client.println(F("<a href=\"/?STUDIOGIU\"\">GIU'</a><br />"));
           client.println(F("<br />"));  
           client.println(F("</BODY>"));
           client.println(F("</HTML>"));
     
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons
                  
           if (readString.indexOf("?emergencystop") >0){
               Serial.print("EMERGENCY!");
               digitalWrite(salagup, LOW);
               digitalWrite(salagdn, LOW);
               digitalWrite(salapup, LOW);
               digitalWrite(salapdn, LOW);
               digitalWrite(cucinaup, HIGH);
               digitalWrite(cucinadn, HIGH);
               digitalWrite(studioup, HIGH);
               digitalWrite(studiodn, HIGH);
               digitalWrite(bagnoup, HIGH);
               digitalWrite(bagnodn, HIGH);
               TUTTESU = false;
               TUTTEGIU = false;               
               startsalag = 0;
               startsalap = 0;
               startcucina = 0;
               startbagno = 0;
               startstudio = 0;
           }
           
           if (readString.indexOf("?TUTTESU") >0) {
             TUTTESU = true;
           }
           
           if (readString.indexOf("?TUTTEGIU") >0) {
             TUTTEGIU = true;
           }
           
           if (readString.indexOf("?SALAGSU") >0 
               || TUTTESU == true) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startsalag = millis();
                 digitalWrite(salagup, HIGH);
               }
           }

           if (readString.indexOf("?SALAGGIU") >0 
               || TUTTEGIU == true) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startsalag = millis();
                 digitalWrite(salagdn, HIGH);
               }
           }

           if (readString.indexOf("?SALAPSU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startsalap = millis();
                 digitalWrite(salapup, HIGH);
               }
           }

           if (readString.indexOf("?SALAPGIU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startsalap = millis();
                 digitalWrite(salapdn, HIGH);
               }
           }
                      
           if (readString.indexOf("CUCINASU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startcucina = millis();
                 digitalWrite(cucinaup, LOW);
               }
           }

           if (readString.indexOf("CUCINAGIU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startcucina = millis();
                 digitalWrite(cucinadn, LOW);
               }
           }        

           if (readString.indexOf("BAGNOSU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startbagno = millis();
                 digitalWrite(bagnoup, LOW);
               }
           }      

           if (readString.indexOf("BAGNOGIU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startbagno = millis();
                 digitalWrite(bagnodn, LOW);
               }
           }      

           if (readString.indexOf("STUDIOSU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startstudio = millis();
                 digitalWrite(studioup, LOW);
               }
           }      

           if (readString.indexOf("STUDIOGIU") >0) {
               if (startsalag ==0 
               && startsalap ==0 
               && startcucina ==0 
               && startstudio ==0 
               && startbagno ==0) {
                 startstudio = millis();
                 digitalWrite(studiodn, LOW);
               }
           }      
           

           //clearing string for next read
            readString="";  
           
         }
       }
    }
}

if (startsalag > 0) {
  if (millis() - startsalag > endsalag) {
    digitalWrite(salagup, LOW);
    digitalWrite(salagdn, LOW);
    startsalag = 0;
    if (TUTTESU == true) {
      startsalap = millis();
      digitalWrite(salapup, HIGH);
    }
    if (TUTTEGIU == true) {
      startsalap = millis();
      digitalWrite(salapdn, HIGH);
    }
  }
}  

if (startsalap > 0) {
  if (millis() - startsalap > endsalap) {
    digitalWrite(salapup, LOW);
    digitalWrite(salapdn, LOW);
    startsalap = 0;
    if (TUTTESU == true) {
      startcucina = millis();
      digitalWrite(cucinaup, LOW);
    }
    if (TUTTEGIU == true) {
      startcucina = millis();
      digitalWrite(cucinadn, LOW);
    }  
  }
}   

if (startcucina > 0) {
  if (millis() - startcucina > endcucina) {
    digitalWrite(cucinaup, HIGH);
    digitalWrite(cucinadn, HIGH);
    startcucina = 0;
    if (TUTTESU == true) {
      startbagno = millis();
      digitalWrite(bagnoup, LOW);
    }
    if (TUTTEGIU == true) {
      startbagno = millis();
      digitalWrite(bagnodn, LOW);
    }
  }    
}
  
if (startbagno > 0) {
  if (millis() - startbagno > endbagno) {
    digitalWrite(bagnoup, HIGH);
    digitalWrite(bagnodn, HIGH);
    startbagno = 0;
    if (TUTTESU == true) {
      startstudio = millis();
      digitalWrite(studioup, LOW);
    }
    if (TUTTEGIU == true) {
      startstudio = millis();
      digitalWrite(studiodn, LOW);
    }
  }    
}

if (startstudio > 0) {
  if (millis() - startstudio > endstudio) {
    digitalWrite(studioup, HIGH);
    digitalWrite(studiodn, HIGH);
    startstudio = 0;
    TUTTESU = false;
    TUTTEGIU = false;
  }
}  
   
}



