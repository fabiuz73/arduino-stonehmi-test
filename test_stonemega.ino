#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);    // USB verso PC
  Serial1.begin(115200);   // Collegato a Stone HMI tramite TX1/RX1
  Serial.println("Pronto: accendo LED quando ricevo un comando dal display!");
}

void loop() {
  static bool ledOn = false;
  static unsigned long ledTimer = 0;

  // Riceve e visualizza byte
  while (Serial1.available()) {
    byte c = Serial1.read();
    Serial.print("0x");
    if (c < 16) Serial.print("0");
    Serial.print(c, HEX);
    Serial.print(" ");
    
    // Quando riceve un byte (o frame), accendi il LED!
    ledOn = true;
    ledTimer = millis();
    digitalWrite(LED_PIN, HIGH);
  }

  // Spegne il LED dopo 1 secondo
  if (ledOn && (millis() - ledTimer > 1000)) {
    digitalWrite(LED_PIN, LOW);
    ledOn = false;
  }
}