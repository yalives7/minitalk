#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void send_char(pid_t server_pid, char c) {
    for (int i = 7; i >= 0; i--) {
        if ((c >> i) & 1) {
            kill(server_pid, SIGUSR1);  // 1 için SIGUSR1
        } else {
            kill(server_pid, SIGUSR2);  // 0 için SIGUSR2
        }
        usleep(10);  // Daha hızlı bir iletişim için uyku süresi azaltıldı
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./client <server_pid> <message>\n");
        return 1;
    }

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    for (int i = 0; message[i] != '\0'; i++) {
        send_char(server_pid, message[i]);  // Her karakteri gönder
    }

    return 0;
}
