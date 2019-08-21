#include <NectisCellular.h>

#define WEBHOOK_EVENTNAME ""
#define WEBHOOK_KEY       ""
#define WEBHOOK_URL       "https://maker.ifttt.com/trigger/" WEBHOOK_EVENTNAME "/with/key/" WEBHOOK_KEY

NectisCellular Nectis;

void setup() {
  char data[100];
  int status;

  delay(4000);

  Serial.begin(115200);
  Serial.println("");
  Serial.println("--- START ---------------------------------------------------");

  Serial.println("### I/O Initialize.");
  Nectis.Init();
  delay(100);
  Serial.println("### Power supply cellular ON.");
  Nectis.PowerSupplyCellular(true);
  delay(100);

  Nectis.Bg96Begin();
  Nectis.InitLteM();

  Serial.println("### Setup completed.");

  delay(3000);
  
  Serial.println("### Post.");
  sprintf(data, "{\"value1\":\"uptime %lu\"}", millis() / 1000);
  Serial.print("Post:");
  Serial.print(data);
  Serial.println("");

  if (!Nectis.HttpPost(WEBHOOK_URL, data, &status)) {
    Serial.println("### ERROR! ###");
  }
  
  Serial.print("Status:");
  Serial.println(status);
}

void loop() {
}
