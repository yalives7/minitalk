#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char message[1024];  // Mesajı tutmak için bir dizi
int bit_index = 0;   // Mesajın bitlerini takip etmek için bir sayaç
char current_char = 0;  // Şu anda oluşturulmakta olan karakter

void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        current_char |= (1 << (7 - bit_index));  // 1 bitini ekle
    }
    // SIGUSR2 için zaten bir şey yapmamıza gerek yok; 0 olarak kalacak

    bit_index++;
    if (bit_index == 8) {  // Bir karakter tamamlandı
        message[bit_index / 8 - 1] = current_char;
        if (current_char == '\0') {  // Mesaj tamamlandı
            printf("Received message: %s\n", message);
        }
        current_char = 0;  // Yeni karakter için sıfırlama
        bit_index = 0;     // Sayaç sıfırlama
    }
}

int main() {
    // Server PID’sini yazdır
    printf("Server PID: %d\n", getpid());

    // Sinyal işleyicisini ayarla
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    // Server sürekli çalışacak
    while (1) {
        pause(); // Sinyal bekle
    }
    return 0;
}
