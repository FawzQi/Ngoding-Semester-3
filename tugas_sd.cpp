#include <time.h>

#include <iostream>

double time1, timedif; /* use doubles to show small values */

int main() {
    time1 = (double)clock();        /* get initial time */
    time1 = time1 / CLOCKS_PER_SEC; /*    in seconds    */

    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= 2024; i++) {
        for (int j = 1; j <= 2024; j++) {
            // Cara 1: a + b + c = 2024
            // elapsed time: 6.017000 secs
            for (int k = 2024; k >= 1; k--) {
                if (i + j + k == 2024) {
                    cnt1 += 1;
                    break;
                }
            }
        }
    }

    /* call clock a second time */
    timedif = (((double)clock()) / CLOCKS_PER_SEC) - time1;
    printf("Waktu untuk cara 1 %lf seconds\n", timedif);
    printf("Banyak Kombinasi: %d\n", cnt1);

    time1 = (double)clock();        /* get initial time */
    time1 = time1 / CLOCKS_PER_SEC; /*    in seconds    */

    for (int i = 1; i <= 2024; i++) {
        for (int j = 1; j <= 2024; j++) {
            // Cara 2: c = n - (a + b)
            // elapsed time: 0.007000 secs
            for (int k = 2024; k >= 1; k--) {
                if (k == 2024 - (i + j)) {
                    cnt2 += 1;
                    break;
                }
            }
        }
    }
    timedif = (((double)clock()) / CLOCKS_PER_SEC) - time1;
    printf("Waktu untuk cara 2 %lf seconds\n", timedif);
    printf("Banyak Kombinasi: %d\n", cnt2);
}