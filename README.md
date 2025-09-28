# arduino-stonehmi-test
Test e demo di comunicazione seriale tra Arduino Mega e display Stone HMI. Visualizzazione dati ricevuti e accensione LED sul comando dal display.

# arduino-stonehmi-test

**Test di comunicazione seriale tra Arduino Mega e display Stone HMI**

---

## Hardware

- **Arduino Mega**: usa la porta Serial1 (TX1=18, RX1=19)
- **STONE HMI**: collega RX/TX ai pin TX1/RX1 di Mega (incrociati) e GND in comune
- **Baud rate tipico**: 115200 (verifica nelle impostazioni del display!)

### Wiring

| Arduino Mega | STONE HMI Display |
|--------------|-------------------|
| TX1 (18)     | RX                |
| RX1 (19)     | TX                |
| GND          | GND               |

---

## Software

- **Sketch principale:** `test_stonemega.ino`
- **Libreria Stone HMI:** tutti i file sono nella cartella `lib/`

---

## Visualizzazione diretta dello sketch principale

```cpp name=test_stonemega.ino
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
```

---

## Elenco file della libreria Stone HMI (`lib/`)

- `Stone_HMI_Define.h`
- `Stone_HMI_Recv.cpp`
- `Stone_HMI_Send.cpp`
- `Stone_HMI_CmdWidget.cpp`
- `Stone_HMI_CmdGeneral.cpp`
- `Stone_HMI_CmdSystem.cpp`
- `yyjson.h`

Questi file sono inclusi nella cartella `lib/`.

---

## Funzionamento

- Visualizza ogni byte ricevuto dal display su Serial Monitor in formato HEX
- Accende il LED integrato (pin 13) per 1 secondo ogni volta che riceve almeno un byte (es. pressione pulsante sul display Stone HMI)

---

## Implementazioni future

Ecco alcune possibili evoluzioni del progetto:

- **Parsing avanzato dei frame:** decodifica del protocollo STONE per riconoscere specifici comandi (es. quale pulsante è stato premuto).
- **Gestione bidirezionale:** invio di comandi e dati da Arduino Mega verso il display, per aggiornare valori, pagine, messaggi.
- **Interfaccia utente evoluta:** gestione di più pulsanti, slider, input touch, visualizzazione di feedback sul display.
- **Logging avanzato:** salvataggio su SD card dei dati ricevuti o degli eventi generati dal display.
- **Integrazione con sensori:** azioni sul display in base a sensori (temperatura, gas, movimento) collegati ad Arduino.
- **Controllo remoto:** aggiunta di connessione WiFi/Bluetooth per gestione remota via app/web.
- **Supporto multi-protocollo:** compatibilità con altri display seriali, espansione con ESP32/STM32.
- **Documentazione e esempi:** guide dettagliate, immagini wiring, video demo, tutorial passo-passo.
- **Gestione errori e watchdog:** monitoraggio dello stato della comunicazione e riavvio in caso di problemi.
- **Test automatici:** sketch di diagnostica per verificare la connessione e la corretta trasmissione.

Suggerisci le tue idee come Issue o Pull Request!

---

## Credits

Progetto di test per la community Arduino & Stone HMI.