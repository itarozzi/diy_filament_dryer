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
    mqtt->subscribe(mqtt_base_topic + "/commands/#", [](const char * topic, const char * payload) {
            // payload might be binary, but PicoMQTT guarantees that it's zero-terminated
            Serial.printf("Received message in topic '%s': %s\n", topic, payload);
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