#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

/* ================= Süreler (saniye) ================= */
#define CAR_GREEN_DURATION    30
#define CAR_YELLOW_DURATION    5
#define CAR_RED_DURATION      15

/* Bir yaya düğmeye basarsa, bu basma olayı rand() fonksiyonu kullanılarak
 * 0 ile 99 saniye arasında rastgele bir zamanda gerçekleşecek şekilde simüle edilir. */
#define BUTTON_RANDOM_RANGE 100

/* ================= Işık Durumları ================= */
typedef enum {
    CAR_GREEN,
    CAR_YELLOW,
    CAR_RED
} car_light_state_t;

typedef enum {
    PED_RED,
    PED_YELLOW,
    PED_GREEN
} pedestrian_light_state_t;

/* Simülasyonun tüm durumunu tutan yapı aşağıdaki gibi. */
typedef struct {
    car_light_state_t        car_state;
    pedestrian_light_state_t ped_state;
    int time_left;          /* Geçerli fazda kalan saniye sayısı             */
    int total_elapsed;      /* Simülasyonun başlamasından beri geçen süre    */
    int button_pressed;     /* Bu zaman adımında yaya düğmesine basıldı mı?  */
    int next_button_press;  /* Bir sonraki rastgele düğmeye basma zamanı     */
} traffic_state_t;

/* ================= Fonksiyon Prototipleri ================= */

/* Durumu başlangıç değerleriyle başlatır ve ilk rastgele düğmeye basma
 * zamanını belirler. */
void traffic_state_init(traffic_state_t *state);

/* Mevcut araç/yaya ışığı durumunu ve kalan süreyi yazdırır. */
void print_light_state(const traffic_state_t *state);

/* Bir sonraki aşamaya geçer (yeşil->sarı->kırmızı->yeşil ...). */
void advance_to_next_phase(traffic_state_t *state);

/* Rastgele planlanan yaya düğmesinin şu anda tetiklenip tetiklenmediğini kontrol eder.
 * Eğer tetiklenirse ve araç ışığı zaten kırmızı değilse, araç ışığını zorla kırmızıya
 * ve yaya ışığını hemen yeşile çevirir. */
void check_pedestrian_button(traffic_state_t *state);

/* Bir saniye bekler. (simülasyon saatini ilerletir) */
void wait_one_second(void);

/* Tüm simülasyonu 'total_duration' saniye boyunca çalıştırır. */
void run_simulation(int total_duration);

#endif /* TRAFFIC_LIGHT_H */
