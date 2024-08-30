#define _XOPEN_SOURCE 700
#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cjson/cJSON.h>

#define MAX_REQUEST_LEN 1024
#define BUFSIZE 8192

// Function to fetch exchange rate JSON response for a specific country code
char *fetch_exchange_rate(const char *base_currency, const char *target_currency)
{
	char buffer[BUFSIZE];
	char request[MAX_REQUEST_LEN];
	struct protoent *protoent;
	const char *hostname = "open.er-api.com";
	int request_len;
	int socket_file_descriptor;
	ssize_t nbytes_total, nbytes_last;
	struct sockaddr_in sockaddr_in;
	unsigned short server_port = 80;

	// Create the HTTP request string with dynamic base currency
	char request_template[] = "GET /v6/latest/%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
	request_len = snprintf(request, MAX_REQUEST_LEN, request_template, base_currency, hostname);
	if (request_len >= MAX_REQUEST_LEN)
	{
		fprintf(stderr, "Request length too large: %d\n", request_len);
		return NULL;
	}

	protoent = getprotobyname("tcp");
	if (protoent == NULL)
	{
		perror("getprotobyname");
		return NULL;
	}

	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
	if (socket_file_descriptor == -1)
	{
		perror("socket");
		return NULL;
	}

	struct hostent *hostent = gethostbyname(hostname);
	if (hostent == NULL)
	{
		fprintf(stderr, "Error: gethostbyname(\"%s\")\n", hostname);
		return NULL;
	}
	sockaddr_in.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*(hostent->h_addr_list)));
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(server_port);

	if (connect(socket_file_descriptor, (struct sockaddr *)&sockaddr_in, sizeof(sockaddr_in)) == -1)
	{
		perror("connect");
		return NULL;
	}

	nbytes_total = 0;
	while (nbytes_total < request_len)
	{
		nbytes_last = write(socket_file_descriptor, request + nbytes_total, request_len - nbytes_total);
		if (nbytes_last == -1)
		{
			perror("write");
			return NULL;
		}
		nbytes_total += nbytes_last;
	}

	nbytes_total = 0;
	while ((nbytes_last = read(socket_file_descriptor, buffer + nbytes_total, BUFSIZE - nbytes_total)) > 0)
	{
		nbytes_total += nbytes_last;
	}
	if (nbytes_last == -1)
	{
		perror("read");
		return NULL;
	}

	close(socket_file_descriptor);

	// Find the start of the JSON data (after the headers)
	char *json_start = strstr(buffer, "\r\n\r\n");
	if (json_start)
	{
		json_start += 4; // Move past the "\r\n\r\n"
		return strdup(json_start);
	}
	else
	{
		fprintf(stderr, "Error: Invalid response format\n");
		return NULL;
	}
}

// Function to get the exchange rate from JSON response for a specific country code
double get_exchange_rate(char *json_response, const char *country_code)
{
	printf("%s\n", json_response);
	json_response = json_response + 3;
	json_response[strlen(json_response) - 1] = '\0';

	cJSON *root = cJSON_Parse(json_response);
	if (!root)
	{
		fprintf(stderr, "Error parsing JSON\n");
		return -1.0;
	}

	cJSON *rates = cJSON_GetObjectItem(root, "rates");
	if (!rates)
	{
		fprintf(stderr, "Error: No 'rates' field found in JSON\n");
		cJSON_Delete(root);
		return -1.0;
	}

	cJSON *rate = cJSON_GetObjectItem(rates, country_code);
	double exchange_rate = -1.0;
	if (rate)
	{
		exchange_rate = rate->valuedouble;
	}
	else
	{
		fprintf(stderr, "No exchange rate found for %s\n", country_code);
	}

	cJSON_Delete(root);
	return exchange_rate;
}


/*
int main() {

	char *json_response = fetch_exchange_rate("PLN", "EUR");
	if (json_response)
	{
		double rate = get_exchange_rate(json_response, "EUR");
		printf("5 PLN to EUR exchange rate: %.2f\n", 5 * rate);
		printf("PLN to EUR exchange rate: %.2f\n", rate);
		free(json_response);
	}
	else
	{
		printf("Failed to fetch exchange rate\n");
	}

    return 0;
}
*/