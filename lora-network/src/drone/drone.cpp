/**
 * Drone station
 * 
 * this station listens for incoming transmissions
 */

#define ESP32 1
#define DEBUG 1

#include <heltec.h>
#include "utils.h"

#define BAND 915E6

#define PACKET_SIZE 5

// packet buffers
uint8_t r_packet_buf[PACKET_SIZE];
uint8_t s_packet_buf[PACKET_SIZE];

void setup()
{
  Heltec.begin(true, true, true, true, BAND);
  delay(2000);

  ECE496::Utils::displayText("I am a drone station");
}

void loop()
{
  //Listen for packets
  ECE496::Utils::awaitPacket();

  //Process incoming packets
  int bytes_received = 
    ECE496::Utils::receiveUnencryptedPacket(r_packet_buf, PACKET_SIZE);
  // first byte should be 0x00 to introduce a hospital station
  //                      0xFF                ground station
  if (ECE496::Utils::getPacketStationType(r_packet_buf) == 2)
  {
    //communicating with hospital station
    //TODO:
  }
  else if (ECE496::Utils::getPacketStationType(r_packet_buf) == 1)
  {
    ECE496::Utils::displayText("I found a ground station!");

    //communicating with ground station
    //introduce self to ground station
    ECE496::Utils::buildPacket(s_packet_buf, 3, 1, PACKET_SIZE, NULL);
    ECE496::Utils::sendUnencryptedPacket(s_packet_buf, PACKET_SIZE);

    //wait for a response
  }
  else
  {
    Serial.print("Received unrecognized packet");
  }
}