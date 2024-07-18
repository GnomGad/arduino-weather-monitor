#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

const int sampleInterval = 2000;
unsigned long lastSampleTime = 0;
const char *sensorName = "DHT11 Sensor";
const char *monitorName = "LCD1602A Monitor";

byte degreeSymbol[8] = {
    0b00111,
    0b00101,
    0b00111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000};

void displayMessage(const char *line1, const char *line2)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.createChar(0, degreeSymbol);
  displayMessage(sensorName, monitorName);
  delay(2000);
  lcd.clear();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastSampleTime >= sampleInterval)
  {
    lastSampleTime = currentMillis;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
      Serial.println("Read Error");
      displayMessage("Read Error", "");
      return;
    }

    Serial.print("H: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("T: ");
    Serial.print(t);
    Serial.println(" *C");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(t, 1);
    lcd.write(byte(0));
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print(int(h));
    lcd.print("%");
  }
}
