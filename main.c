#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "traffic_light.h"

int main(void) {
    /* sleep() sırasında çıktının anlık olarak görüntülenmesi için arabelleğe almayı devre dışı bıraktım. */
    setvbuf(stdout, NULL, _IONBF, 0);

    /* rand() fonksiyonunu başlattım. (yayaların rastgele düğmeye basma zamanlarını üretmek için kullanılır) */
    srand((unsigned int) time(NULL));

    /* Simülasyonu 120 saniye boyunca çalıştırdım.
     * Daha kısa veya daha uzun bir çalışma süresi istiyorsak bu değeri değiştirebiliriz. */
    run_simulation(120);

    return 0;
}
