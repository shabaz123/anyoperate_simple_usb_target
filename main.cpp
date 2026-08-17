#include <cstdio>
#include <cstdlib>
#include <string>
#include "pico/stdlib.h"

static uint16_t duty = 50;

static void led_init() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
}

static void led_set(bool on) {
    gpio_put(PICO_DEFAULT_LED_PIN, on);
}

static void command(const std::string& s) {
    if (s.rfind("CONNECT ", 0) == 0) {
        puts("OK");
    } else if (s == "LIST CONFIG") {
        puts("duty|Duty Cycle|uint16");
        puts("#END");
    } else if (s == "LIST STATUS") {
        puts("revision|Revision|string");
        puts("state|State|string");
        puts("#END");
    } else if (s == "STATUS") {
        puts("revision=1.1");
        puts("state=running");
        puts("#END");
    } else if (s == "GET duty") {
        printf("duty=0x%04X\n", duty);
    } else if (s == "GET revision") {
        puts("revision=1.1");
    } else if (s == "GET state") {
        puts("state=running");
    } else if (s.rfind("SET duty=", 0) == 0) {
        duty = static_cast<uint16_t>(std::strtoul(s.c_str() + 9, nullptr, 0));
        puts("OK");
    } else {
        puts("ERROR");
    }
    stdio_flush();
}

int main() {
    stdio_init_all();
    led_init();

    std::string input;
    bool receiving = false;

    while (true) {
        for (int c; (c = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT;) {
            if (c == '$') {
                input.clear();
                receiving = true;
            } else if (receiving && (c == '\n' || c == '\r')) {
                if (!input.empty()) command(input);
                receiving = false;
            } else if (receiving && c != 0) {
                input += static_cast<char>(c);
            }
        }

        const uint32_t phase = time_us_64() % 1000000;
        const uint32_t on_time = (duty > 100 ? 100 : duty) * 10000;
        led_set(phase < on_time);

        tight_loop_contents();
    }
}
