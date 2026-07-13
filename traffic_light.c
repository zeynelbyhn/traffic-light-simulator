#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "traffic_light.h"

/* Enum değerlerini okunabilir adlara dönüştüren yardımcı fonksiyonlar burada yer alıyor. */
static const char *car_light_name(car_light_state_t s) {
    switch (s) {
        case CAR_GREEN:  return "GREEN";
        case CAR_YELLOW: return "YELLOW";
        case CAR_RED:    return "RED";
    }
    return "?";
}

static const char *ped_light_name(pedestrian_light_state_t s) {
    switch (s) {
        case PED_RED:    return "RED";
        case PED_YELLOW: return "YELLOW";
        case PED_GREEN:  return "GREEN";
    }
    return "?";
}

void traffic_state_init(traffic_state_t *state) {
    state->car_state      = CAR_GREEN;
    state->ped_state      = PED_RED;
    state->time_left      = CAR_GREEN_DURATION;
    state->total_elapsed  = 0;
    state->button_pressed = 0;

    /* İlk rastgele yaya düğmesine basma anını seçiyorum. (0-99 saniye) */
    state->next_button_press = rand() % BUTTON_RANDOM_RANGE;
}

void print_light_state(const traffic_state_t *state) {
    printf("[%3d s] CAR: %-6s | PEDESTRIAN: %-6s | Time left in phase: %2d s%s\n",
           state->total_elapsed,
           car_light_name(state->car_state),
           ped_light_name(state->ped_state),
           state->time_left,
           state->button_pressed ? "   <-- PEDESTRIAN BUTTON PRESSED!" : "");
}

void advance_to_next_phase(traffic_state_t *state) {
    switch (state->car_state) {
        case CAR_GREEN:
            state->car_state = CAR_YELLOW;
            state->ped_state = PED_YELLOW;
            state->time_left = CAR_YELLOW_DURATION;
            break;
        case CAR_YELLOW:
            state->car_state = CAR_RED;
            state->ped_state = PED_GREEN;
            state->time_left = CAR_RED_DURATION;
            break;
        case CAR_RED:
            state->car_state = CAR_GREEN;
            state->ped_state = PED_RED;
            state->time_left = CAR_GREEN_DURATION;
            break;
    }
}

void check_pedestrian_button(traffic_state_t *state) {
    state->button_pressed = 0;

    if (state->total_elapsed == state->next_button_press) {
        state->button_pressed = 1;

        /* Araç ışığı zaten kırmızı değilse (yaya ışığı zaten yeşildir),
         * yaya ışığını zorla yeşile, araç ışığını ise kırmızıya çevirdim. */
        if (state->car_state != CAR_RED) {
            state->car_state = CAR_RED;
            state->ped_state = PED_GREEN;
            state->time_left = CAR_RED_DURATION;
        }

        /* Bir sonraki rastgele düğmeye basma zamanını planladım. */
        state->next_button_press = state->total_elapsed
                                    + 1
                                    + (rand() % BUTTON_RANDOM_RANGE);
    }
}

void wait_one_second(void) {
    sleep(1);
}

void run_simulation(int total_duration) {
    traffic_state_t state;
    traffic_state_init(&state);

    printf("=== Pedestrian Crossing / Traffic Light Simulation Started ===\n");
    printf("(Total duration: %d seconds)\n\n", total_duration);

    while (state.total_elapsed < total_duration) {
        check_pedestrian_button(&state);
        print_light_state(&state);

        wait_one_second();

        state.total_elapsed++;
        state.time_left--;

        if (state.time_left <= 0) {
            advance_to_next_phase(&state);
        }
    }

    printf("\n=== Simulation Finished ===\n");
}
