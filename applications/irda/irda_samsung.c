#include "flipper.h"
#include "irda_samsung.h"
#include "irda_protocols.h"

void ir_samsung_preambula(void) {
    hal_pwm_set(SAMSUNG_DUTY_CYCLE, SAMSUNG_CARRIER_FREQUENCY, &htim2, TIM_CHANNEL_4);
    delay_us(4500);
    hal_pwm_stop(&htim2, TIM_CHANNEL_4);
    delay_us(4500);
}

void ir_samsung_send_bit(bool bit) {
    hal_pwm_set(SAMSUNG_DUTY_CYCLE, SAMSUNG_CARRIER_FREQUENCY, &htim2, TIM_CHANNEL_4);
    delay_us(560);
    hal_pwm_stop(&htim2, TIM_CHANNEL_4);
    if(bit) {
        delay_us(1590);
    } else {
        delay_us(560);
    }
}

void ir_samsung_send_byte(uint8_t data) {
    for(uint8_t i = 0; i < 8; i++) {
        ir_samsung_send_bit((data & (1 << (i))) != 0);
    }
}

void ir_samsung_send(uint16_t addr, uint16_t data) {
    uint8_t samsung_packet[4] = {
        (uint8_t)addr, (uint8_t)(addr >> 8), (uint8_t)data, (uint8_t)(data >> 8)};
    ir_samsung_preambula();
    ir_samsung_send_byte(samsung_packet[0]);
    ir_samsung_send_byte(samsung_packet[1]);
    ir_samsung_send_byte(samsung_packet[2]);
    ir_samsung_send_byte(samsung_packet[3]);
    ir_samsung_send_bit(0);
}