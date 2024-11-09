#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_COUNTER = 0
};

// Native global variables

extern int32_t get_var_mode();
extern void set_var_mode(int32_t value);
extern bool get_var_running();
extern void set_var_running(bool value);
extern bool get_var_wifi_connected();
extern void set_var_wifi_connected(bool value);
extern bool get_var_mqtt_connected();
extern void set_var_mqtt_connected(bool value);
extern float get_var_current_temp();
extern void set_var_current_temp(float value);
extern float get_var_current_humi();
extern void set_var_current_humi(float value);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/