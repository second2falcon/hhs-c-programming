#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)
#define PORT 5000
#define BUFLEN 512

void opdracht1_server() {
    int RequestCounter = 0;
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(listenSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listenSock, 1);
    printf("Wacht op client...\n");
    while (1) {
        SOCKET clientSock = accept(listenSock, NULL, NULL);
        printf("Client verbonden!\n");
        char buf[BUFLEN];
        int len = recv(clientSock, buf, BUFLEN, 0);
        RequestCounter++;
        buf[len] = '\0';
        printf("Ontvangen: %s %d\n", buf, RequestCounter);
        char response[BUFLEN];
        float temp;
        int humidity;
        if (sscanf(buf, "temp=%f", &temp) == 1) {
            int fanSpeed;
            if (temp < 20) fanSpeed = 0;
            else if (temp < 25) fanSpeed = 50;
            else fanSpeed = 100;
            snprintf(response, BUFLEN, "fan_speed=%d", fanSpeed);
            printf("Temperatuur: %.1f -> Ventilatorsnelheid: %d%%\n", temp, fanSpeed);
        }
        else if (sscanf(buf, "humidity=%d", &humidity) == 1) {
            int fanSpeed = humidity > 70 ? 100 : 0;
            snprintf(response, BUFLEN, "fan_speed=%d", fanSpeed);
            printf("Luchtvochtigheid: %d -> Ventilatorsnelheid: %d%%\n", humidity, fanSpeed);
        }
        else {
            snprintf(response, BUFLEN, "Hallo van server! Dit was request nummer %d", RequestCounter);
        }
        send(clientSock, response, strlen(response), 0);
        closesocket(clientSock);
        printf("Client verbroken, wacht op volgende...\n");
    }
}

int main() {
    opdracht1_server();
}