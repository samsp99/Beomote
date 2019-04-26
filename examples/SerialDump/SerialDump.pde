#include <Beomote.h>
#include <Commands.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("initialized");
  Beo.initialize(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  BeoCommand cmd;

  if (Beo.receive(cmd))  {
    Serial.print("Link:");
    Serial.print(cmd.link, HEX);
    Serial.print(", Address:");
    Serial.print(cmd.address, HEX);
    Serial.print(", Command:");
    Serial.println(cmd.command, HEX);
  }

}