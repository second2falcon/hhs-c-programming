#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)
#define PORT 5000
#define BUFLEN 512

void opdracht1_client() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Verbonden!\n");
    float temperature = 26.5f;
    char request[BUFLEN];
    snprintf(request, BUFLEN, "temp=%.1f", temperature);
    send(sock, request, strlen(request), 0);
    printf("Verstuurd: %s\n", request);
    char buf[BUFLEN];
    int len = recv(sock, buf, BUFLEN, 0);
    buf[len] = '\0';
    int fanSpeed;
    if (sscanf(buf, "fan_speed=%d", &fanSpeed) == 1) {
        printf("Ventilatorsnelheid van server: %d%%\n", fanSpeed);
    }
    else {
        printf("Antwoord: %s\n", buf);
    }
    closesocket(sock);
    WSACleanup();
}

// opdracht 2d: HTTP request naar een webserver
void opdracht2d_client() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);                         // HTTP poort
    serverAddr.sin_addr.s_addr = inet_addr("104.18.26.120"); // IP van example.com
    connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Verbonden met webserver!\n");

    // Minimaal geldig HTTP/1.1 request
    char* request = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
    send(sock, request, strlen(request), 0);
    printf("Request verstuurd:\n%s\n", request);

    // Ontvang en print de volledige response
    char buf[BUFLEN];
    int len;
    printf("Response van webserver:\n");
    while ((len = recv(sock, buf, BUFLEN - 1, 0)) > 0) {
        buf[len] = '\0';
        printf("%s", buf);
    }

    closesocket(sock);
    WSACleanup();
}

int main() {
    //opdracht1_client();
    opdracht2d_client();
}