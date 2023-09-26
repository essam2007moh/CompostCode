//Made By: Essam Elkholy, ©ECO STRAW
//Compost with LCD

//Include the DHT11 and LiquidCrystal libraries
#include <dht11.h>
#include <LiquidCrystal.h>

//Define the pins for the DHT11 sensor, the relay, and the LCD
const int dhtPin = 4;
const int relayPin = 3;
const int rs = 12;
const int en = 11;
const int d4 = 10;
const int d5 = 9;
const int d6 = 8;
const int d7 = 7;

//Create a LiquidCrystal object named lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Create a dht11 object named DHT11
dht11 DHT11;

//Setup function
void setup() {
  //Start the serial monitor
  Serial.begin(9600);

  //Set the pin mode for the relay as output
  pinMode(relayPin, OUTPUT);

  //Initialize the LCD
  lcd.begin(16, 2);
}

//Loop function
void loop() {
  //Read the temperature and humidity from the DHT11 sensor
  int chk = DHT11.read(dhtPin);
  if (chk == 0) {
    //Get the temperature and humidity values
    float temp = DHT11.temperature;
    float humidity = DHT11.humidity;

    //Clear the LCD
    lcd.clear();

    //Set the cursor to column 0, row 0
    lcd.setCursor(0, 0);

    //Print the humidity value
    lcd.print("Humidity: ");
    lcd.print((float)humidity, 2);
    lcd.print("%");

    //Set the cursor to column 0, row 1
    lcd.setCursor(0, 1);

    //Print the temperature value
    lcd.print("Temperature: ");
    lcd.print((float)temp, 2);
    lcd.print("C");

    //Check if the humidity is less than 75%
    if (humidity < 75) {
      //Turn on the relay
      digitalWrite(relayPin, HIGH);
    } else if (humidity > 80) {
      //Turn off the relay
      digitalWrite(relayPin, LOW);
    } else if (temp < 70) {
      //Turn on the relay
      digitalWrite(relayPin, HIGH);
    } else if (temp > 80) {
      //Turn off the relay
      digitalWrite(relayPin, LOW);
    }
  } else {
    //Serial print an error message
    Serial.println("Error reading DHT11");
  }

  //Wait for 2 seconds
  delay(2000);
}
