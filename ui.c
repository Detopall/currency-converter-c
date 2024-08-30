#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "countries.h"
#include "server.h"

#define MAX_VISIBLE 10
#define INPUT_FIELD_WIDTH 10

void display_menu(char **country_names1, char **country_names2)
{
    int ch;
    int selected1 = 0;
    int selected2 = 0;
    int start_index1 = 0;
    int start_index2 = 0;
    int num_visible1 = (num_countries < MAX_VISIBLE) ? num_countries : MAX_VISIBLE;
    int num_visible2 = (num_countries < MAX_VISIBLE) ? num_countries : MAX_VISIBLE;

    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);

    char amount_input[INPUT_FIELD_WIDTH + 1] = "";
    int input_index = 0;

    while (1)
    {
        clear();

        mvprintw(0, 0, "Currency Converter");
        mvprintw(1, 0, "Move the 'From' countries with 'W' (up) and 'S' (down)");
        mvprintw(2, 0, "Move the 'To' countries with Arrow Up and Arrow Down");
        mvprintw(3, 0, "Press Enter to select countries, then enter amount");

        mvprintw(5, 0, "From:");
        mvprintw(5, width / 2 + 6, "To:");

        for (int i = start_index1; i < start_index1 + num_visible1 && i < num_countries; i++)
        {
            if (i == selected1)
            {
                attron(A_REVERSE);
                mvprintw(i - start_index1 + 6, 0, "%s", country_names1[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(i - start_index1 + 6, 0, "%s", country_names1[i]);
            }
        }

        for (int i = start_index2; i < start_index2 + num_visible2 && i < num_countries; i++)
        {
            if (i == selected2)
            {
                attron(A_REVERSE);
                mvprintw(i - start_index2 + 6, width / 2 + 6, "%s", country_names2[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(i - start_index2 + 6, width / 2 + 6, "%s", country_names2[i]);
            }
        }

        ch = getch();

        switch (ch)
        {
        case 'w':
            if (selected1 > 0)
            {
                selected1--;
                if (selected1 < start_index1)
                {
                    start_index1--;
                }
            }
            break;
        case 's':
            if (selected1 < num_countries - 1)
            {
                selected1++;
                if (selected1 >= start_index1 + num_visible1)
                {
                    start_index1++;
                }
            }
            break;
        case KEY_UP:
            if (selected2 > 0)
            {
                selected2--;
                if (selected2 < start_index2)
                {
                    start_index2--;
                }
            }
            break;
        case KEY_DOWN:
            if (selected2 < num_countries - 1)
            {
                selected2++;
                if (selected2 >= start_index2 + num_visible2)
                {
                    start_index2++;
                }
            }
            break;
        case '\n':
            clear();
            mvprintw(height / 2 - 1, (width - 30) / 2, "From: %s", country_names1[selected1]);
            mvprintw(height / 2, (width - 30) / 2, "To: %s", country_names2[selected2]);
            mvprintw(height / 2 + 1, (width - 30) / 2, "Enter amount: ");
            echo();
            curs_set(1); // Show cursor for input
            getstr(amount_input);
            noecho();
            curs_set(0); // Hide cursor

            // Fetch exchange rate
            char *json_response = fetch_exchange_rate(get_currency_code(country_names1[selected1]));
            if (json_response)
            {
                double rate = get_exchange_rate(json_response, get_currency_code(country_names2[selected2]));
                free(json_response);

                clear();
                mvprintw(height / 2 - 1, (width - 30) / 2, "From: %s", country_names1[selected1]);
                mvprintw(height / 2, (width - 30) / 2, "To: %s", country_names2[selected2]);
                mvprintw(height / 2 + 1, (width - 30) / 2, "Amount: %s", amount_input);
                mvprintw(height / 2 + 2, (width - 30) / 2, "Exchange Rate: %.3f", rate * atof(amount_input));

                mvprintw(height / 2 + 3, (width - 30) / 2, "Press any key to exit...");
            }
            else
            {
                mvprintw(height / 2 + 2, (width - 30) / 2, "Failed to fetch exchange rate.");
            }

            getch();
            endwin();
            return;
        case 'q':
            endwin();
            return;
        default:
            break;
        }

        num_visible1 = (num_countries - start_index1 < MAX_VISIBLE) ? (num_countries - start_index1) : MAX_VISIBLE;
        num_visible2 = (num_countries - start_index2 < MAX_VISIBLE) ? (num_countries - start_index2) : MAX_VISIBLE;
    }
}

int main()
{
    char **country_names1 = get_all_country_names();
    char **country_names2 = get_all_country_names();
    if (country_names1 == NULL || country_names2 == NULL)
    {
        printf("Error: Unable to get all country names\n");
        return 1;
    }

    display_menu(country_names1, country_names2);

    free_country_names(country_names1);
    free_country_names(country_names2);

    return 0;
}
