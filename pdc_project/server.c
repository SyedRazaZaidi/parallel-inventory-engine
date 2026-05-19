#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include "compute.h"  // <--- Our custom bridge file

#define PORT 8080

// --- TIME MEASUREMENT UTILITY ---
double get_time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

// --- SERVER UTILITIES ---
void send_json_response(int client_socket, double time_taken) {
    char response[256];
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\"status\": \"success\", \"time\": %.3f}", time_taken);
    write(client_socket, response, strlen(response));
}

void send_html_file(int client_socket) {
    FILE *file = fopen("index.html", "r");
    if (file == NULL) {
        char *not_found = "HTTP/1.1 404 Not Found\r\n\r\n<h1>404: index.html not found</h1>";
        write(client_socket, not_found, strlen(not_found));
        return;
    }

    char header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    write(client_socket, header, strlen(header));

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        write(client_socket, buffer, bytes_read);
    }
    fclose(file);
}

// --- MAIN HTTP SERVER ---
int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Initialize Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("========================================================\n");
    printf(" PDC Backend Server is Running! (Modular Architecture)\n");
    printf(" View the Dashboard at: http://localhost:%d\n", PORT);
    printf("========================================================\n");

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        read(new_socket, buffer, 1024);

        struct timespec start, end;
        int requested_items = 50000000; // Default

        // 1. EXTRACT DATA SIZE FROM URL
        char *items_ptr = strstr(buffer, "?items=");
        if (items_ptr != NULL) {
            sscanf(items_ptr, "?items=%d", &requested_items);
        }

        // 2. DYNAMIC MEMORY MANAGEMENT
        if (inventory == NULL || requested_items != current_num_items) {
            printf("[SYS] Reallocating memory for %d items...\n", requested_items);
            if (inventory != NULL) free(inventory); 
            
            inventory = (float*)malloc(requested_items * sizeof(float));
            current_num_items = requested_items;
            
            for (int i = 0; i < current_num_items; i++) inventory[i] = 100.0f;
        }

        // 3. API ROUTER
        if (strstr(buffer, "GET /run/linear") != NULL) {
            printf("[API] Executing Linear...\n");
            clock_gettime(CLOCK_MONOTONIC, &start);
            process_linear();
            clock_gettime(CLOCK_MONOTONIC, &end);
            send_json_response(new_socket, get_time_diff(start, end));

        } else if (strstr(buffer, "GET /run/pthreads") != NULL) {
            printf("[API] Executing Pthreads...\n");
            clock_gettime(CLOCK_MONOTONIC, &start);
            process_pthreads();
            clock_gettime(CLOCK_MONOTONIC, &end);
            send_json_response(new_socket, get_time_diff(start, end));

        } else if (strstr(buffer, "GET /run/openmp") != NULL) {
            printf("[API] Executing OpenMP...\n");
            clock_gettime(CLOCK_MONOTONIC, &start);
            process_openmp();
            clock_gettime(CLOCK_MONOTONIC, &end);
            send_json_response(new_socket, get_time_diff(start, end));

        } else if (strstr(buffer, "GET / ") != NULL || strstr(buffer, "GET /index.html") != NULL) {
            send_html_file(new_socket);
        }

        close(new_socket);
        memset(buffer, 0, sizeof(buffer)); 
    }

    if (inventory != NULL) free(inventory);
    return 0;
}