#include <SoftwareSerial.h>
#include "CRC_Xmodem.h"

CRCXmodem crc;  //Inizzializzo la classe per il calcolo CRC
SoftwareSerial serial(2,3);  //Inizzializzo SoftwareSerial per comunicare con il trasponder e non avere conflitti in console (Rx, Tx)

unsigned char Buffer[]= {0x01, 0x00, 0x22, 0x01, 0x34, 0x20, 0x5b, 0x92, 0x0d, 0x01};
unsigned short Addr[]={};

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); //| 
                      //|-- Inizzializzo le seriali 
  serial.begin(9600); //| 
  
  //configuro il pin A5 come uscita per abilitare chip RS-485
  pinMode(A5, OUTPUT);
  
  Buffer[1] = sizeof(Buffer)+2;//detrmino la dimensione del buffer per un corretto CRC
  crc.Calculate(Buffer ,Addr, sizeof(Buffer)); //calcolo CRC e lo allocco sul vettore Addr
  digitalWrite(A5, HIGH); //Abilito l'ivio dati su bus RS-485
  //Avvio il ciclo di invio dati del buffer 'Buffer'
  for(int a=0; a<sizeof(Buffer);a++) {
    serial.write(Buffer[a]);
  }
  serial.write(*Addr>>8);      //|
                               //|-- Invio su seriale il CRC in coda al buffer per un correto invio dei dati
  serial.write(*Addr&0x00FF);  //|
  
  digitalWrite(A5, LOW); //Abilito ricezione dati sul bus RS-485 
  
} 


void loop() {
  // put your main code here, to run repeatedly:
  
  //Resto in attesa di una risposta del trasponder e scrivo su seriale
  while(serial.available()){    
   unsigned char Read = serial.read();
   Serial.println(Read, HEX);
  }

    
}



