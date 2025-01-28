#include <stdio.h>

int main()
{
    //random number generator parameters
    unsigned int a = 1664525;
    unsigned int b = 10904223;
    unsigned int m = 42947296;
    unsigned int seed;

    //seed entry and generation of random numbers
    printf("Enter seed: ");
    scanf("%u", &seed);

    //game loop
    int verif = 1;
    int player_hand = 3;
    int computer_hand = 3;
    while (verif)
    {
        printf("\nEnter rock (0), paper (1), scissors (2): ");
        scanf("%d", &player_hand);
        computer_hand = (a * seed + b) % m % 3;
        if(player_hand == computer_hand)
        {
            printf("Tie\n");
            seed = (a * seed + b) % m;
            if(player_hand == 0)
            {
                printf("    _______                    _______\n");
                printf("---'   ____)               ---'   ____)\n");
                printf("      (_____)                     (_____)\n");
                printf("      (_____)                     (_____)\n");
                printf("      (____)                      (____)\n");
                printf("---.__(___)               ---.__(___)\n\n");
            }
            else if (player_hand == 1)
            {
                printf("     _______                  _______\n");
                printf("---'    ____)____         ---'    ____)_____\n");
                printf("           ______)                    ______)\n");
                printf("          _______)                  _______)\n");
                printf("         _______)                  _______)\n");
                printf("---.__________)          ---.__________)\n\n");
            }
            else
            {
                printf("    _______                 _______\n");
                printf("---'   ____)____        ---'   ____)____\n");
                printf("          ______)                  ______)\n");
                printf("       __________)              __________)\n");
                printf("      (____)                    (____)\n");
                printf("---.__(___)               ---.__(___)\n\n");
            }
        }
        else if(player_hand == 0 && computer_hand == 2)
        {
            printf("You win\n");
            printf("    ________                    _______\n");
            printf("---'   _____)               ---'   ____)____\n");
            printf("      (_____)                        ______)\n");
            printf("      (_____)                     __________)\n");
            printf("      (_____)                     (____)\n");
            printf("---.__(____)               ---.__(___)\n\n");
            verif = 0;
        }
        else if(player_hand == 1 && computer_hand == 0)
        {
            printf("You win\n");
            printf("     _______                  _______\n");
            printf("---'    ____)____         ---'   ____)\n");
            printf("           ______)              (_____)\n");
            printf("          _______)              (_____)\n");
            printf("         _______)               (_____)\n");
            printf("---.__________)          ---.___(_____)\n\n");
            verif = 0;
        }
        else if(player_hand == 2 && computer_hand == 1)
        {
            
            printf("You win\n");
            printf("    _______                   _______\n");
            printf("---'   ____)____         ---'    ____)____\n");
            printf("          ______)                   ______)\n");
            printf("       __________)                  _______)\n");
            printf("      (____)                      ________)\n");
            printf("---.__(___)               ---.__________)\n\n");

            verif = 0;
        }
        else
        {
            printf("You lose\n");
            printf("     _______                  _______\n");
            printf("---'    ____)____         ---'   ____)____\n");
            printf("           ______)                   ______)\n");
            printf("          _______)               __________)\n");
            printf("         _______)               (____)\n");
            printf("---.__________)          ---.__(___)\n\n");
            verif = 0;
        }

    }
    return 0;
}
