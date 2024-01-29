#include <stdio.h>
#include <string.h>
#include "prototypes.h"


int main (int argc, char * argv[]) {

   // these are all the variables used in the program and they are being declared

   int country [COUNTRIES][MEDALCAT];

   char countryNames [COUNTRIES][MAX_LENGTH_CNAME];

   int choice, whichMedal, medalFind, minMax;

   int totalAllCountries[COUNTRIES];

   int totalAllMedals[MEDALCAT];
   char countryName[MAX_LENGTH_CNAME];
   int indexOfCountries[COUNTRIES]; 

   // call function readFromFile to populate your arrays
      readFromFile (argv[1], country, countryNames);


    // do while loop used to create the menu, and it has switch statement


    do {
        printf ("\nHere is the menu \n\n");
        printf ("1. Display all country names read from file and the total number of medals won by each\n");
        printf ("2.    Function 2 - Find total number of medals won by each country\n");
        printf ("3.    Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)\n");
        printf ("4.    Function 4 – Display horizontal histogram\n");
        printf ("5.    Function 5 – Search for a country and return the total number of medals won by it\n");
        printf ("6.    Function 6 – Rank and display top three countries in order of total medals won\n");
        printf ("7.    Function 7 – Rank and display top three countries in order of total gold medals won\n");
        printf ("8.    Function 8 – Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze\n");
        printf ("9.    Function 9 – Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze\n");
        printf ("10.   Function 10 – Find and display name of the country that has minimum or maximum length among all countries read in option 1\n");

        printf ("11.    Exit\n");

        printf ("Enter your choice: ");
        scanf ("%d", &choice);

   // the user picks one of the options in the menu and each case number in the switch statement corresponds do every function example case 1 is assoiated with function #1

   switch (choice) {

    // if the user enters in 1 as their input the first case is executed and it displays all the countries with their corresponding medals in gold, silver and bronze
    case 1:

        for (int i = 0; i < COUNTRIES; i++)
        {

        printf ("Country: %s, Gold = %d, Silver = %d, Bronze = %d\n", countryNames[i], country[i][0], country[i][1], country[i][2]);

        }


        break;

    // if the user inputs 2 this case is executed and the total number of metals won by each country are displayed
    case 2:

         findTotalPerCountry(country, totalAllCountries);
         for (int i = 0; i < COUNTRIES; i++)
         {
           printf("%s (%d)\n", countryNames[i], totalAllCountries[i]);

          }
        break;

    // if user enters in 3 case 3 is executed and it calls the findTotalPerMedal function and goes through an if-else statement based off what the user wants to see Ex Gold
    case 3:

         findTotalPerMedal(country, totalAllMedals, &whichMedal);

         printf("In findTotalPerMedal:\n");
         printf("Medal - Gold Total - %d\n", totalAllMedals[0]);
         printf("Medal - Silver Total - %d\n", totalAllMedals[1]);
         printf("Medal - Bronze Total - %d\n", totalAllMedals[2]);

         if(totalAllMedals[0] > totalAllMedals[1]  && totalAllMedals[0] > totalAllMedals[2])

         {
           printf("Maximum Number of medals - Gold (%d)\n", totalAllMedals[0]);

         }
         else if(totalAllMedals[1] > totalAllMedals[0] && totalAllMedals[1] > totalAllMedals[2])

         {
           printf("Maximum Number of medals - Silver (%d)\n",totalAllMedals[1]);

         }
         else

         {
           printf("Maximum Number of medals - Bronze (%d)\n", totalAllMedals[2]);

         }


        break;

    // user enters 4, which displays the histogram
    case 4:

         findTotalPerCountry(country, totalAllCountries);

        hHistogram(countryNames, totalAllCountries);

        break;

    // when user enters in 5 they are asked to enter in a country and the program displays the total number of medals the country won
    case 5:

        findTotalPerCountry(country, totalAllCountries);

        printf("Please input a country name (no spaces): ");
        scanf("%s", countryName);

        int countryMedals = searchCountry(countryName, countryNames, totalAllCountries);
        if(countryMedals !=-1)
        {

         printf("Total number of medals won by %s : %d\n", countryName, countryMedals);
        }

        else
        {
        printf("Invalid country name entered. Try again :)\n");

        }
        break;

    // if the user inputs 6 case 6 is executed and the 2 functions for 6 are called
    case 6:

        findTotalPerCountry(country, totalAllCountries);

        rankTopThreeByTotal(totalAllCountries, countryNames);

        break;

    // function 7 is called and displays the top three countries for gold medals
    case 7:

        rankTopThreeByMedal(country, countryNames);

        break;

    // if user enters in 8 case 8 is executed and user is prompted to enter a number from 0-2 and the program displays all countries that have no specific medal
    case 8:

        printf("Which medal (0 = Gold, 1 = Silver, 2 = Bronze) would you like to pick? ");
        scanf("%d", &medalFind);
        if(medalFind < 0 || medalFind > 2)

        {
          printf("You entered an invalid category :(\n");
        break;

        }

        int foundCountries = findAllWithNoXMedals(country, medalFind, indexOfCountries);
        for(int i = 0; i < foundCountries; i++)

        {
          printf("%s\n", countryNames[indexOfCountries[i]]);

        }

        if(foundCountries == 0)

        {
          printf("No countries found \n");

        }
        break;

    // Same as case 8 but instead the program only displays countries that HAVE only won a specific kind of medal
    case 9:

        printf("Which medal (0 = Gold, 1 = Silver, 2 = Bronze) would you like to pick? ");
        scanf("%d", &medalFind);
        if(medalFind < 0 || medalFind > 2)
        {
            printf("You entered an invalid category :(\n");
            break;
            }

        int foundCountries2 = findAllWithOnlyXMedals(country, medalFind, indexOfCountries);

        for(int i = 0; i < foundCountries2; i++)
        {
            printf("%s", countryNames[indexOfCountries[i]]);

        }
        if(foundCountries2 == 0)
        {
            printf("No countries found :(\n");
        }
        break;

    // if user enters in 10 case 10 is executed and it finds min or max length of a country
    case 10:

        printf("Do you want to find the minimum (1) or maximum (2)? ");
        scanf("%d", &minMax);
        if(minMax < 1 || minMax > 2)
        {
          printf("Invalid choice :(\n");
          break;
        }
        int indexCountry = findCountryIndexWithMinOrMaxLength(minMax, countryNames);
        printf("%s", countryNames[indexCountry]);
        break;



    default: printf ("That is an invalid choice\n");

        }

    } while (choice != 11);


   return 0;
}
