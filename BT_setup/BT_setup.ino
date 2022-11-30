#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX | TX

const char *BAUD = "9600";
const char *NAME = "HC6-SL";
const char *PASSOWRD = "1234";
const char *SLAVE_ADDRESS = "98D3,11,F84350"; // use your address AT+ADDR to get address, and change formatting e.g.,  "98D3:11:F84350" => "98D3,11,F84350"

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400); // HC-05 default speed in AT command more

  delay(2000);

  // Utilities (uncomment if needed)
  setupMaster();
  // setupSlave();
}

void loop()
{
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}

void setupSlave()
{
  BTSerial.write("AT\r\n");
  delay(100);
  Serial.println("Clear pairing");
  BTSerial.write("AT+RMAAD\r\n");
  delay(100);
  Serial.println("Set slave");
  BTSerial.write("AT+ROLE=0\r\n");
  delay(100);
  Serial.println("Set name");
  BTSerial.write("AT+NAME=");
  BTSerial.write(NAME);
  BTSerial.write("\r\n");
  delay(100);
  Serial.println("Set password");
  BTSerial.write("AT+PSWD=\"");
  BTSerial.write(PASSOWRD);
  BTSerial.write("\"\r\n");
  delay(100);
  BTSerial.write("AT+ADDR\r\n");
  delay(100);
  Serial.println("Set UART");
  BTSerial.write("AT+UART=");
  BTSerial.write(BAUD);       // set name
  BTSerial.write(",0,0\r\n"); // set name
  delay(100);
}

// Or manually pair with
// AT+BIND=98D3,11,F84350
// AT+PAIR=98D3,11,F84350,9

void setupMaster()
{
  BTSerial.write("AT\r\n");
  delay(100);
  Serial.println("Clear pairing");
  BTSerial.write("AT+RMAAD\r\n");
  delay(100);
  Serial.println("Set master");
  BTSerial.write("AT+ROLE=1\r\n");
  delay(100);
  BTSerial.write("AT+CMODE=1\r\n"); // connect by address
  delay(100);
  Serial.println("Set name");
  BTSerial.write("AT+NAME=");
  BTSerial.write(NAME);
  BTSerial.write("\r\n");
  delay(100);
  Serial.println("Set password");
  BTSerial.write("AT+PSWD=\"");
  BTSerial.write(PASSOWRD);
  BTSerial.write("\"\r\n");
  delay(100);
  BTSerial.write("AT+ADDR\r\n");
  delay(100);
  Serial.println("Set UART");
  BTSerial.write("AT+UART=");
  BTSerial.write(BAUD);       // set name
  BTSerial.write(",0,0\r\n"); // set name
  delay(100);
  /*BTSerial.write("AT+BIND=");
  BTSerial.write(SLAVE_ADDRESS);
  BTSerial.write("\r\n");
  delay(100);
  BTSerial.write("AT+PAIR=");
  BTSerial.write(SLAVE_ADDRESS);
  BTSerial.write(",9\r\n");
  delay(100);*/
}
