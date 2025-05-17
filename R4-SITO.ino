#include <DHT.h>
#include <WiFiNINA.h>  // Arduino UNO R4 WiFi

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi credentials
const char* ssid = "tuo_SSID";
const char* password = "tua_password";

// Altervista
const char* server = "tuosito.altervista.org";  // dominio Altervista

WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println("Connessione al Wi-Fi...");
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connesso! IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Errore nella lettura del sensore DHT11!");
    return;
  }

  String path = "/salvadati.php?temp=" + String(t) + "&humidity=" + String(h);

  if (client.connect(server, 80)) {
    client.println("GET " + path + " HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();
    Serial.println("Dati inviati: " + path);
    
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line); // Risposta server
      }
    }

    client.stop();
  } else {
    Serial.println("Errore nella connessione al server!");
  }

  delay(10000);  // 10 secondi
}
