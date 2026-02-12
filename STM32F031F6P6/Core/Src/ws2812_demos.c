/**
 ******************************************************************************
 * @file           : ws2812_demos.h
 * @brief          : Ws2812b demos source
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 Lars Boegild Thomsen <lbthomsen@gmail.com>.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"

#include "ws2812.h"
#include "ws2812_demos.h"


uint8_t active_demo = 0;

const uint8_t led_line_colors[][3] = {
        { 100, 101, 5 },
		{ 101, 102, 5 },
		{ 102, 103, 5 },
		{ 103, 104, 5 },
		{ 104, 105, 5 },
		{ 105, 105, 5 },
		{ 106, 106, 5 },
		{ 107, 107, 5 },
		{ 108, 108, 5 },
		{ 109, 109, 5 },
        { 110, 110, 5 },
        { 120, 120, 5 },
        { 130, 130, 5 },
        { 140, 140, 5 },
        { 150, 150, 5 },
        { 140, 140, 5 },
        { 130, 130, 5 },
        { 120, 120, 5 },
        { 110, 110, 5 },
        { 100, 100, 5 }

};

void ws2812_demos_set(ws2812_handleTypeDef *ws2812, uint8_t demo) {
    active_demo = demo;
}

void ws2812_demos_tick(ws2812_handleTypeDef *ws2812, uint8_t reset) {

    static const uint32_t led_interval = 10;

    static uint16_t line_led = 0;
    static uint32_t line_count = 0;
    static uint8_t line_color = 0;
    static uint32_t next_led = led_interval;

    uint32_t now = uwTick;

//    if(reset == 1) {
//    	line_led = 0;
//    	line_count = 0;
//    	line_color = 0;
//    }

    switch (active_demo) {
    case WS2812_DEMO_LINE:
        if (now >= next_led) {
            //zeroLedValues(ws2812);
        	uint16_t rand = get_random(30, 50);
            setLedValues(ws2812, line_led, rand+50, rand+50, 5);
            ++line_led;
            ++line_count;
            if (line_count % 64 == 0)
                ++line_color;

            if (line_color >= sizeof(led_line_colors) / sizeof(led_line_colors[0]))
                line_color = 0;
            if (line_led >= ws2812->leds)
                line_led = 0;

            next_led = now + led_interval;
        }
        break;
    default:
        // De nothing really
    }
}
uint16_t get_random(uint16_t min, uint16_t max) {
    static uint32_t seed = 0;
    seed ^= HAL_GetTick();
    seed = seed * 1103515245 + 12345;
    return min + ((uint16_t)(seed >> 16) % (max - min + 1));
}
