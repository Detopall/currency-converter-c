#ifndef SERVER_H
#define SERVER_H

char *fetch_exchange_rate(const char *country_code);

double get_exchange_rate(const char *json_response, const char *country_code);

#endif
