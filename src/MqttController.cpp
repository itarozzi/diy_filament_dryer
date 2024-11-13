#include "MqttController.h"

MqttController::MqttController(String broker_address, int broker_port, String username, String password, String base_topic)
{
    //TODO: auth management
    mqtt = new PicoMQTT::Client(broker_address.c_str(), broker_port); // create mqtt_client
    mqtt_base_topic = base_topic;
    
    connection = false;
}

MqttController::~MqttController()
{
    delete mqtt;
}



void MqttController::connectWifi(String ssid, String password) {

    wifi_ssid = ssid;
    wifi_password = password;
    wifi_connecting = false;
    wifi_connected = false;
    connection = true;
}

void MqttController::tick() {

    if (connection) {

        // connection_required, test wifi
        if (!wifi_connecting) {
            wifi_connected = (WiFi.status() == WL_CONNECTED); 
        }

        if (!wifi_connected) {
            if (!wifi_connecting) {
                Serial.print("Connecting to WiFi SSID: ");
                Serial.println(wifi_ssid);
                wifi_connecting = true;
                WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());
            }
            else {
                //TODO: manage timeout
                if (WiFi.status() == WL_CONNECTED) {
                    Serial.println("WiFi connected");
                    Serial.println("IP address: ");
                    wifi_ip = WiFi.localIP().toString();
                    Serial.println(wifi_ip);
                    wifi_connecting = false;
                    wifi_connected = true;

                    // When connected to wifi, subscribe to topic and connect to MQTT Broker
                    mqtt_connecting = false;
                    mqtt_connected = false;
                }
                else {
                    Serial.print(".");    
                }
            }
        }
        else if (!mqtt_connecting) {
            //TODO: manage timeout
            mqtt->connected_callback = [this] {
                this->mqtt_connecting = false;
                this->mqtt_connected = true;
                Serial.println("MQTT connected");
            };

            mqtt->disconnected_callback = [this] {
                this->mqtt_connecting = false;
                this->mqtt_connected = false;
                Serial.println("MQTT disconnected");
            };
            mqtt_subscribe();
            mqtt->begin();
            mqtt_connecting = true;                    

        }
        else {
            mqtt->loop();
        }

    }
}

void MqttController::mqtt_subscribe() {

    mqtt->subscribe(mqtt_base_topic + "/commands/#", [this](const char * topic, const char * payload) {
        bool done = false;
        int cmd_mode = -1;
        int cmd_heater_pwm = -1;
        int cmd_fan_pwm = -1;
        int cmd_led_pwm = -1;

        // payload might be binary, but PicoMQTT guarantees that it's zero-terminated
        // Serial.printf("Received message in topic '%s': %s    - pwm %d  -   %d\n", topic, payload, cmd_heater_pwm, cmd_fan_pwm);

        // test if override mode command received
        String cmd_topic = this->mqtt_base_topic + "/commands/remote_mode_override";
        if (strncmp(topic, cmd_topic.c_str(), strlen(cmd_topic.c_str())) == 0) {
            int value = atoi(payload);
            Serial.print("Override mode: ");
            Serial.println(value);
            cmd_mode = value = (value > 3) ? 3 : ((value < 0) ? 0 : value);;
            done = true;
        }

        // test if heater_pwm mode command received
        cmd_topic = this->mqtt_base_topic + "/commands/heater_pwm";
        if ((!done) && (strncmp(topic, cmd_topic.c_str(), strlen(cmd_topic.c_str())) == 0)) {
            int value = atoi(payload);
            Serial.print("PWM heater: ");
            Serial.println(value);
            cmd_heater_pwm = value = (value > 255) ? 255 : ((value < 0) ? 0 : value);
            done = true;
        }

        // test if fan_pwm mode command received
        cmd_topic = this->mqtt_base_topic + "/commands/fan_pwm";
        if ((!done) && (strncmp(topic, cmd_topic.c_str(), strlen(cmd_topic.c_str())) == 0)) {
            int value = atoi(payload);
            Serial.print("PWM fan: ");
            Serial.println(value);
            cmd_fan_pwm = value = (value > 255) ? 255 : ((value < 0) ? 0 : value);
            done = true;
        }

        // test if led_pwm mode command received
        cmd_topic = this->mqtt_base_topic + "/commands/led_pwm";
        if ((!done) && (strncmp(topic, cmd_topic.c_str(), strlen(cmd_topic.c_str())) == 0)) {
            int value = atoi(payload);
            Serial.print("PWM led: ");
            Serial.println(value);
            cmd_led_pwm = value = (value > 255) ? 255 : ((value < 0) ? 0 : value);
            done = true;
        }


        if (done && remote_cmd_callback_) {
            remote_cmd_callback_(cmd_mode, cmd_heater_pwm, cmd_fan_pwm, cmd_led_pwm);
        }

    });
    
}


void MqttController::getConnectionStatus(bool *wifi_connected,  bool *mqtt_connected) {
    *wifi_connected = this->wifi_connected;
    *mqtt_connected = this->mqtt_connected;
}

void MqttController::pushSensors(float temp, float humi){
    mqtt->publish(mqtt_base_topic + "/sensors", "{\"temp\": " + String(temp) + ", \"humi\": " + String(humi) + "}"); 
}

void MqttController::pushData(int mode, float target, int heater_pwm, int fan_pwm, int led_pwm, long remaining_time) {

    mqtt->publish(mqtt_base_topic + "/rtdata", 
        "{\"mode\": " + String(mode) + 
        ", \"target\": " + String(target) + 
        ", \"heater_pwm\": " + String(heater_pwm) + 
        ", \"fan_pwm\": " + String(fan_pwm) + 
        ", \"led_pwm\": " + String(led_pwm) + 
        ", \"remaining_time\": " + String(remaining_time) + 
        "}"); 
}