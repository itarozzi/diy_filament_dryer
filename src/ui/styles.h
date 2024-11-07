#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: sensorMain
lv_style_t *get_style_sensor_main_MAIN_DEFAULT();
void add_style_sensor_main(lv_obj_t *obj);
void remove_style_sensor_main(lv_obj_t *obj);

// Style: sensorUm
lv_style_t *get_style_sensor_um_MAIN_DEFAULT();
void add_style_sensor_um(lv_obj_t *obj);
void remove_style_sensor_um(lv_obj_t *obj);

// Style: pwm
lv_style_t *get_style_pwm_MAIN_DEFAULT();
void add_style_pwm(lv_obj_t *obj);
void remove_style_pwm(lv_obj_t *obj);

// Style: buttonMode
lv_style_t *get_style_button_mode_MAIN_DEFAULT();
void add_style_button_mode(lv_obj_t *obj);
void remove_style_button_mode(lv_obj_t *obj);

// Style: target
lv_style_t *get_style_target_MAIN_DEFAULT();
void add_style_target(lv_obj_t *obj);
void remove_style_target(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/