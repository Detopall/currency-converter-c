#ifndef COUNTRIES_H
#define COUNTRIES_H

typedef struct
{
    char *country;
    char *currency_code;
} CountryCurrency;

extern CountryCurrency countries[];
extern const int num_countries;

const char *get_currency_code(const char *country_name);
char **get_all_country_names();
void free_country_names(char **country_names);

#endif
