#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_button_mode(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_PRESSED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_main_label_wifi(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 5, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_label_mqtt(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 6, 3, value, "Failed to assign Checked state");
        }
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            // buttonMode
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button_mode = obj;
            lv_obj_set_pos(obj, 3, 155);
            lv_obj_set_size(obj, 186, 34);
            lv_obj_add_event_cb(obj, event_handler_cb_main_button_mode, LV_EVENT_ALL, flowState);
            add_style_button_mode(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // labelMode
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_mode = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
                    lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // buttonSettings
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.button_settings = obj;
            lv_obj_set_pos(obj, 285, 5);
            lv_obj_set_size(obj, 30, 30);
            add_style_button_mode3(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // labelWifi
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_wifi = obj;
            lv_obj_set_pos(obj, 209, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_main_label_wifi, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfffafafa), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00701d), LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            // labelMqtt
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_mqtt = obj;
            lv_obj_set_pos(obj, 250, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_main_label_mqtt, LV_EVENT_ALL, flowState);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfffafafa), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff00701d), LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 3, 78);
            lv_obj_set_size(obj, 185, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 137, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "%");
                    add_style_sensor_um(obj);
                }
                {
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    lv_obj_set_pos(obj, -15, -10);
                    lv_obj_set_size(obj, 60, 60);
                    lv_img_set_src(obj, &img_humidity);
                    lv_img_set_zoom(obj, 160);
                }
                {
                    // labelHumi
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_humi = obj;
                    lv_obj_set_pos(obj, 48, -2);
                    lv_obj_set_size(obj, 90, LV_PCT(100));
                    lv_label_set_text(obj, "");
                    add_style_sensor_main(obj);
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 3, 3);
            lv_obj_set_size(obj, 185, 70);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // labelTemp
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_temp = obj;
                    lv_obj_set_pos(obj, 39, 2);
                    lv_obj_set_size(obj, 90, LV_PCT(100));
                    lv_label_set_text(obj, "");
                    add_style_sensor_main(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 130, 10);
                    lv_obj_set_size(obj, 38, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "°C");
                    add_style_sensor_um(obj);
                    lv_obj_set_style_length(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    lv_obj_set_pos(obj, -15, -10);
                    lv_obj_set_size(obj, 60, 60);
                    lv_img_set_src(obj, &img_temperature);
                    lv_img_set_zoom(obj, 160);
                }
            }
        }
        {
            // labelTime
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.label_time = obj;
            lv_obj_set_pos(obj, 19, 196);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "00:00:00");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 203, 155);
            lv_obj_set_size(obj, 143, 111);
            lv_obj_set_style_radius(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // labelTarget
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_target = obj;
                    lv_obj_set_pos(obj, -12, 27);
                    lv_obj_set_size(obj, 110, 37);
                    lv_label_set_text(obj, "");
                    add_style_target(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, -7, -7);
                    lv_obj_set_size(obj, 100, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "TARGET");
                    add_style_target(obj);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, -7, 13);
                    lv_obj_set_size(obj, 100, 18);
                    lv_label_set_text(obj, "");
                    add_style_target(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 373, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 203, 78);
            lv_obj_set_size(obj, 112, 70);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // labelPwmHeater
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pwm_heater = obj;
                    lv_obj_set_pos(obj, 4, 54);
                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    add_style_pwm(obj);
                }
                {
                    // labelPwmFan
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.label_pwm_fan = obj;
                    lv_obj_set_pos(obj, 59, 54);
                    lv_obj_set_size(obj, 50, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    add_style_pwm(obj);
                }
                {
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    lv_obj_set_pos(obj, 4, 6);
                    lv_obj_set_size(obj, 50, 50);
                    lv_img_set_src(obj, &img_fire);
                    lv_img_set_zoom(obj, 120);
                    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    lv_obj_set_pos(obj, 59, 7);
                    lv_obj_set_size(obj, 50, 50);
                    lv_img_set_src(obj, &img_fan);
                    lv_img_set_zoom(obj, 120);
                }
            }
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_mode);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_mode;
            lv_label_set_text(objects.label_mode, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_label_set_text(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.label_wifi, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.label_wifi;
            if (new_val) lv_obj_add_state(objects.label_wifi, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.label_wifi, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_wifi);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_wifi;
            lv_label_set_text(objects.label_wifi, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.label_mqtt, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.label_mqtt;
            if (new_val) lv_obj_add_state(objects.label_mqtt, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.label_mqtt, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_mqtt);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_mqtt;
            lv_label_set_text(objects.label_mqtt, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_humi);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_humi;
            lv_label_set_text(objects.label_humi, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_temp;
            lv_label_set_text(objects.label_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_target);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_target;
            lv_label_set_text(objects.label_target, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj1;
            lv_label_set_text(objects.obj1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj2);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj2;
            lv_label_set_text(objects.obj2, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_pwm_heater);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_pwm_heater;
            lv_label_set_text(objects.label_pwm_heater, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.label_pwm_fan);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.label_pwm_fan;
            lv_label_set_text(objects.label_pwm_fan, new_val);
            tick_value_change_obj = NULL;
        }
    }
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

static const char *screen_names[] = { "Main" };
static const char *object_names[] = { "main", "button_mode", "label_wifi", "label_mqtt", "label_mode", "button_settings", "label_humi", "label_temp", "label_time", "label_target", "label_pwm_heater", "label_pwm_fan", "obj0", "obj1", "obj2" };
static const char *style_names[] = { "sensorMain", "sensorUm", "pwm", "buttonMode", "buttonMode1", "buttonMode2", "buttonMode3", "target" };

void create_screens() {
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
