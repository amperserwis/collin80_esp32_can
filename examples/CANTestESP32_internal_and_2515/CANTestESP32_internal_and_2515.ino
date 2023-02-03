//Demo of the second can interface Can1 which uses the MCP2517FD module

#include "esp32_can.h"

void printFrame(CAN_FRAME &frame)
{
  // Print message
  Serial.print("ID: ");
  Serial.print(frame.id,HEX);
  Serial.print(" Ext: ");
  if(frame.extended) {
    Serial.print("Y");
  } else {
    Serial.print("N");
  }
  Serial.print(" Len: ");
  Serial.print(frame.length,DEC);
  for(int i = 0;i < frame.length; i++) {
    Serial.print(frame.data.uint8[i],HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void setup() {
	Serial.begin(115200);
	
	Serial.println("Initializing ...");

  CAN0.enable();
  if(CAN0.begin(500000))
  {
    Serial.println("Builtin CAN Init OK ...");
  } else {
    Serial.println("BuiltIn CAN Init Failed ...");
  }
  
  // Initialize MCP2517FD CAN controller at the specified speed
  CAN1.enable();
  if(CAN1.begin(500000))
  {
    Serial.println("MCP2515 Init OK ...");
  } else {
    Serial.println("MCP2515 Init Failed ...");
  }

CAN0.watchFor(); //allow anything through
CAN1.watchFor(); //allow anything through


  CAN_FRAME txFrame;
  txFrame.rtr = 0;
  txFrame.id = 0x123;
  txFrame.extended = false;
  txFrame.length = 4;
  txFrame.data.byte[0] = 0x10;
  txFrame.data.byte[1] = 0x1A;
  txFrame.data.byte[2] = 0xFF;
  txFrame.data.byte[3] = 0x5D;
  //CAN1.sendFrame(txFrame);
}

byte i=0;

// CAN message frame
CAN_FRAME message;

void loop() {
	while (CAN1.available() > 0) {
    if (CAN1.read(message)) {
      printFrame(message); 	
    }
	}

  while (CAN0.available() > 0) {
    if (CAN0.read(message)) {
      printFrame(message);  
    }
  }


}
