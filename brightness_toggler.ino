

#define inputCLK 5
#define inputDT 4

int counter = 0;
int current_clk;
int previousStateClk;

const char* SSID = "Debi lan";
const char* PSK = "HubbaBubbaGang799";
const char* MQTT_BROKER = "192.168.0.108";

#define TOPIC "chris/led"

void setup() {
  // put your setup code here, to run once:
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);

  Serial.begin(115200);
  previousStateClk = digitalRead(inputCLK);

  setup_wifi();
  client.setServer(MQTT_BROKER, 1883);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  current_clk = digitalRead(inputCLK);

  if(current_clk != previousStateClk) {
      if(digitalRead(inputDT) != current_clk) {
        //rotating counterclockwise
        Serial.print("Bightness up!");
        send_mqtt("b_up");
        
    }
    
    else {
      //counterclockwise
      Serial.print("Bightness down!");
      send_mqtt("b_down");
    }
  }
}

void send_mqtt(char *message) {
  client.publish(TOPIC, message");
}

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);

    //WiFi.config(ip, gateway, subnet);
    WiFi.begin(SSID, PSK);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
