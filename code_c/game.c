#include "include/parm.h"
#include "include/stdio.h"
#include "include/string.h"

void run()
{
    BEGIN();

    // random number generator parameters
    unsigned int a = 1664525;
    unsigned int b = 10904223;
    unsigned int m = 42947296;
    unsigned int seed;

    // game loop
    int verif = 1;
    int player_hand;
    int computer_hand;
    while (verif)
    {
        PUTCHAR('s', 'e', 'e', 'd', ':');
        seed = READINT();
        PUTCHAR('\n');
        PUTCHAR('R', '(', '0', ')', ',', ' ', 'P', '(', '1', ')', ',', ' ', 'S', '(', '2', ')', ':');
        player_hand = READINT();
        PUTCHAR('\n');
        computer_hand = (a * seed + b) % m % 3;
        if (player_hand == computer_hand)
        {
            PUTCHAR('T', 'i', 'e', '\n');
            seed = (a * seed + b) % m;
            if (player_hand == 0)
                PUTCHAR('R', '(', '0', ')', '\n');
            else if (player_hand == 1)
                PUTCHAR('P', '(', '1', ')', '\n');
            else
                PUTCHAR('S', '(', '2', ')', '\n');
        }
        else if (player_hand == 0 && computer_hand == 2)
        {
            PUTCHAR('C', 'o', 'm', 'p', 'u', 't', 'e', 'r', ':', ' ', 'S', '(', '2', ')', '\n');
            PUTCHAR('Y', 'o', 'u', ' ', 'W', 'i', 'n', '\n');
            verif = 0;
        }
        else if (player_hand == 1 && computer_hand == 0)
        {
            PUTCHAR('C', 'o', 'm', 'p', 'u', 't', 'e', 'r', ':', ' ', 'R', '(', '0', ')', '\n');
            PUTCHAR('Y', 'o', 'u', ' ', 'W', 'i', 'n', '\n');
            verif = 0;
        }
        else if (player_hand == 2 && computer_hand == 1)
        {
            PUTCHAR('C', 'o', 'm', 'p', 'u', 't', 'e', 'r', ':', ' ', 'P', '(', '1', ')', '\n');
            PUTCHAR('Y', 'o', 'u', ' ', 'W', 'i', 'n', '\n');
            verif = 0;
        }
        else if (player_hand == 1 && computer_hand == 2)
        {
            PUTCHAR('C', 'o', 'm', 'p', 'u', 't', 'e', 'r', ':', ' ', 'S', '(', '2', ')', '\n');
            PUTCHAR('Y', 'o', 'u', ' ', 'L', 'o', 'o', 's', 'e', '\n');
            verif = 0;
        }
        else if (player_hand == 0 && computer_hand == 2)
        {
            PUTCHAR('C', 'o', 'm', 'p', 'u', 't', 'e', 'r', ':', ' ', 'S', '(', '2', ')', '\n');
            PUTCHAR('Y', 'o', 'u', ' ', 'W', 'i', 'n', '\n');
            verif = 0;
        }
        else
        {
            PUTCHAR('C', 'o', 'm', 'p', 'u', 't', 'e', 'r', ':', ' ', 'R', '(', '0', ')', '\n');
            PUTCHAR('Y', 'o', 'u', ' ', 'L', 'o', 'o', 's', 'e', '\n');
            verif = 0;
        }
    }

    END();
}
