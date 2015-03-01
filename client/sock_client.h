#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "Header.h"

#define MAX_BUFFER_SIZE 2048

void client_connect(char*, char*, int*);
void send_message(string, string, int);
