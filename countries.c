#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "countries.h"

CountryCurrency countries[] = {
	{"Afghanistan", "AFN"},
	{"Albania", "ALL"},
	{"Algeria", "DZD"},
	{"American Samoa", "USD"},
	{"Andorra", "EUR"},
	{"Angola", "AOA"},
	{"Anguilla", "XCD"},
	{"Antigua and Barbuda", "XCD"},
	{"Argentina", "ARS"},
	{"Armenia", "AMD"},
	{"Aruba", "AWG"},
	{"Australia", "AUD"},
	{"Austria", "EUR"},
	{"Azerbaijan", "AZN"},
	{"Bahamas", "BSD"},
	{"Bahrain", "BHD"},
	{"Bangladesh", "BDT"},
	{"Barbados", "BBD"},
	{"Belarus", "BYN"},
	{"Belgium", "EUR"},
	{"Belize", "BZD"},
	{"Benin", "XOF"},
	{"Bermuda", "BMD"},
	{"Bhutan", "BTN"},
	{"Bolivia", "BOB"},
	{"Bosnia and Herzegovina", "BAM"},
	{"Botswana", "BWP"},
	{"Brazil", "BRL"},
	{"Bulgaria", "BGN"},
	{"Cabo Verde", "CVE"},
	{"Cambodia", "KHR"},
	{"Cameroon", "XAF"},
	{"Canada", "CAD"},
	{"Cayman Islands", "KYD"},
	{"Chad", "XAF"},
	{"Chile", "CLP"},
	{"China", "CNY"},
	{"Colombia", "COP"},
	{"Congo, Democratic Republic of the", "CDF"},
	{"Congo, Republic of", "XAF"},
	{"Costa Rica", "CRC"},
	{"Croatia", "HRK"},
	{"Cyprus", "EUR"},
	{"Czech Republic", "CZK"},
	{"Denmark", "DKK"},
	{"Dominican Republic", "DOP"},
	{"Ecuador", "USD"},
	{"Egypt", "EGP"},
	{"El Salvador", "USD"},
	{"Equatorial Guinea", "XAF"},
	{"Estonia", "EUR"},
	{"Eswatini", "SZL"},
	{"Ethiopia", "ETB"},
	{"Fiji", "FJD"},
	{"Finland", "EUR"},
	{"France", "EUR"},
	{"Gabon", "XAF"},
	{"Gambia", "GMD"},
	{"Georgia", "GEL"},
	{"Germany", "EUR"},
	{"Ghana", "GHS"},
	{"Greece", "EUR"},
	{"Greenland", "DKK"},
	{"Grenada", "XCD"},
	{"Guatemala", "GTQ"},
	{"Guinea", "GNF"},
	{"Guinea-Bissau", "XOF"},
	{"Guyana", "GYD"},
	{"Haiti", "HTG"},
	{"Honduras", "HNL"},
	{"Hungary", "HUF"},
	{"Iceland", "ISK"},
	{"India", "INR"},
	{"Indonesia", "IDR"},
	{"Iran", "IRR"},
	{"Iraq", "IQD"},
	{"Ireland", "EUR"},
	{"Israel", "ILS"},
	{"Italy", "EUR"},
	{"Jamaica", "JMD"},
	{"Japan", "JPY"},
	{"Jordan", "JOD"},
	{"Kazakhstan", "KZT"},
	{"Kenya", "KES"},
	{"Kiribati", "AUD"},
	{"Kuwait", "KWD"},
	{"Kyrgyzstan", "KGS"},
	{"Laos", "LAK"},
	{"Latvia", "EUR"},
	{"Lebanon", "LBP"},
	{"Lesotho", "LSL"},
	{"Liberia", "LRD"},
	{"Libya", "LYD"},
	{"Liechtenstein", "CHF"},
	{"Lithuania", "EUR"},
	{"Luxembourg", "EUR"},
	{"Madagascar", "MGA"},
	{"Malawi", "MWK"},
	{"Malaysia", "MYR"},
	{"Maldives", "MVR"},
	{"Mali", "XOF"},
	{"Malta", "EUR"},
	{"Marshall Islands", "USD"},
	{"Mauritania", "MRU"},
	{"Mauritius", "MUR"},
	{"Mexico", "MXN"},
	{"Micronesia", "USD"},
	{"Moldova", "MDL"},
	{"Monaco", "EUR"},
	{"Mongolia", "MNT"},
	{"Montenegro", "EUR"},
	{"Morocco", "MAD"},
	{"Mozambique", "MZN"},
	{"Myanmar", "MMK"},
	{"Namibia", "NAD"},
	{"Nauru", "AUD"},
	{"Nepal", "NPR"},
	{"Netherlands", "EUR"},
	{"New Zealand", "NZD"},
	{"Nicaragua", "NIO"},
	{"Niger", "XOF"},
	{"Nigeria", "NGN"},
	{"North Macedonia", "MKD"},
	{"Norway", "NOK"},
	{"Oman", "OMR"},
	{"Pakistan", "PKR"},
	{"Palau", "USD"},
	{"Palestine", "ILS"},
	{"Panama", "PAB"},
	{"Papua New Guinea", "PGK"},
	{"Paraguay", "PYG"},
	{"Peru", "PEN"},
	{"Philippines", "PHP"},
	{"Poland", "PLN"},
	{"Portugal", "EUR"},
	{"Qatar", "QAR"},
	{"Romania", "RON"},
	{"Russia", "RUB"},
	{"Rwanda", "RWF"},
	{"Saint Kitts and Nevis", "XCD"},
	{"Saint Lucia", "XCD"},
	{"Saint Vincent and the Grenadines", "XCD"},
	{"Samoa", "WST"},
	{"San Marino", "EUR"},
	{"Sao Tome and Principe", "STN"},
	{"Saudi Arabia", "SAR"},
	{"Senegal", "XOF"},
	{"Serbia", "RSD"},
	{"Seychelles", "SCR"},
	{"Sierra Leone", "SLL"},
	{"Singapore", "SGD"},
	{"Slovakia", "EUR"},
	{"Slovenia", "EUR"},
	{"Solomon Islands", "AUD"},
	{"Somalia", "SOS"},
	{"South Africa", "ZAR"},
	{"South Korea", "KRW"},
	{"South Sudan", "SSP"},
	{"Spain", "EUR"},
	{"Sri Lanka", "LKR"},
	{"Sudan", "SDG"},
	{"Suriname", "SRD"},
	{"Sweden", "SEK"},
	{"Switzerland", "CHF"},
	{"Syria", "SYP"},
	{"Taiwan", "TWD"},
	{"Tajikistan", "TJS"},
	{"Tanzania", "TZS"},
	{"Thailand", "THB"},
	{"Togo", "XOF"},
	{"Tonga", "TOP"},
	{"Trinidad and Tobago", "TTD"},
	{"Tunisia", "TND"},
	{"Turkey", "TRY"},
	{"Turkmenistan", "TMT"},
	{"Tuvalu", "AUD"},
	{"Uganda", "UGX"},
	{"Ukraine", "UAH"},
	{"United Arab Emirates", "AED"},
	{"United Kingdom", "GBP"},
	{"United States", "USD"},
	{"Uruguay", "UYU"},
	{"Uzbekistan", "UZS"},
	{"Vanuatu", "VUV"},
	{"Vatican City", "EUR"},
	{"Venezuela", "VES"},
	{"Vietnam", "VND"},
	{"Yemen", "YER"},
	{"Zambia", "ZMW"},
	{"Zimbabwe", "ZWL"}};

const int num_countries = sizeof(countries) / sizeof(countries[0]);

const char *get_currency_code(const char *country_name)
{
	for (int i = 0; i < num_countries; i++)
	{
		if (strcmp(countries[i].country, country_name) == 0)
		{
			return countries[i].currency_code;
		}
	}
	return NULL;
}

char **get_all_country_names()
{
	char **country_names = (char **)malloc(num_countries * sizeof(char *));
	if (country_names == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < num_countries; i++)
	{
		country_names[i] = (char *)malloc((strlen(countries[i].country) + 1) * sizeof(char));
		if (country_names[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free(country_names[j]);
			}
			free(country_names);
			return NULL;
		}

		strcpy(country_names[i], countries[i].country);
	}

	return country_names;
}

void free_country_names(char **country_names)
{
	if (country_names == NULL)
		return;
	for (int i = 0; i < num_countries; i++)
	{
		free(country_names[i]);
	}
	free(country_names);
}