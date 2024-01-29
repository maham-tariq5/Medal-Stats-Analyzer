#include <stdio.h>
#include <string.h>
#include "prototypes.h"



// Function #1 : reads the text file commonWealth.txt
void readFromFile (char fName [30], int country [COUNTRIES][MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
      int i = 0;

    FILE *fileWithMedals;
    fileWithMedals = fopen(fName,"r"); 
    if (fileWithMedals == NULL)
    {
       printf ("Error opening file\n");
       return;
    }
    while (fscanf (fileWithMedals,"%s %d %d %d", countryNames[i], &country[i][0], &country[i][1], &country[i][2]) !=EOF){
 
    i++;
    }

    fclose(fileWithMedals);

}


// function #2 finds total medals for each country and stores it in array totalAllCountries

void findTotalPerCountry (int country [COUNTRIES] [MEDALCAT], int totalAllCountries [COUNTRIES])
{
    for(int i = 0; i < COUNTRIES; i++)
    {
        totalAllCountries[i] = 0;
        for(int j = 0; j< MEDALCAT; j++)
        {
            totalAllCountries[i] += country[i][j];
        }
    }
}


// function #3 Finds total number of medals in each category (Gold/Silver/Bronze) and stores them in array totalAllCountries

int findTotalPerMedal (int country [COUNTRIES][MEDALCAT], int totalAllMedals [MEDALCAT], int * whichMedal)
{
    for(int i = 0; i < MEDALCAT; i++)
    {
        totalAllMedals[i] = 0;
        for(int j = 0; j < COUNTRIES; j++)
        {
            totalAllMedals[i] += country[j][i];
        }
    }

    *whichMedal = 0;
    for(int i = 1; i < MEDALCAT; i++)
    {
        if(totalAllMedals[i] > totalAllMedals[*whichMedal])
        {
            *whichMedal = i;
        }
    }
    return totalAllMedals[*whichMedal];
}


// function #4 displays a horizontal histogram of stars, each star represents 2 medals

void hHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalMedals[COUNTRIES])
{
    int maxCountryNameLength = 0;
    for(int i = 0; i < COUNTRIES; i++)
    {
        if(strlen(countryNames[i]) > maxCountryNameLength)
        {
            maxCountryNameLength = strlen(countryNames[i]);
        }
    }
        for(int i = 0; i < COUNTRIES; i++)
    {
        printf("%-*s: ", maxCountryNameLength, countryNames[i]);
        for(int j = 0; j < totalMedals[i] / 2 + totalMedals[i] % 2; j++)
        {
            printf("*");
        }
       printf(" (%d)\n", totalMedals[i]);
    }
}

// function #5 returns the total number of medals won by a country

int searchCountry (char countryName [MAX_LENGTH_CNAME], char countryNames [COUNTRIES][MAX_LENGTH_CNAME], int totalAllCountries [COUNTRIES])
{
    for(int i = 0; i < COUNTRIES; i++)
    {
        if(strcmp(countryName, countryNames[i]) == 0)
        {
            return totalAllCountries[i];
        }
        
    }
    return -1;
}

// function #6 displays the top three country names and the total medals won by each of them

void rankTopThreeByTotal (int totalAllCountries [COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
    int topcountries[3] = {-1, -1, -1}; 
    for(int i = 0; i < COUNTRIES; i++)
    {
        if(topcountries[0] == -1 || totalAllCountries[i] > totalAllCountries[topcountries[0]])
        {
            topcountries[2] = topcountries[1];
            topcountries[1] = topcountries[0];
            topcountries[0] = i;
        }
        else if (topcountries[1] == -1 || totalAllCountries[i] > totalAllCountries[topcountries[1]])
        {
            topcountries[2] = topcountries[1];
            topcountries[1] = i;
        }
        else if (topcountries[2] == -1 || totalAllCountries[i] > totalAllCountries[topcountries[2]])
        {
            topcountries[2] = i;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        if(topcountries[i] >= 0)
        {
            printf("%s (%d)\n", countryNames[topcountries[i]], totalAllCountries[topcountries[i]]);
        }
    }
}


// function #7 Displays the top three country names and the total gold medals won by each of them

void rankTopThreeByMedal (int country [COUNTRIES][MEDALCAT], char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
    int topcountries[3] = {-1, -1, -1}; //to make sure these values get replaced
    for(int i = 0; i < COUNTRIES; i++)
    {
        if(topcountries[0] == -1 || country[i][0] > country[topcountries[0]][0])
        {
            topcountries[2] = topcountries[1];
            topcountries[1] = topcountries[0];
            topcountries[0] = i;
        }
        else if (topcountries[1] == -1 || country[i][0] > country[topcountries[1]][0])
        {
            topcountries[2] = topcountries[1];
            topcountries[1] = i;
        }
        else if (topcountries[2] == -1 || country[i][0] > country[topcountries[2]][0])
        {
            topcountries[2] = i;
        }
    }
    printf("Rank top three based on gold medals:\n");
    for(int i = 0; i < 3; i++)
    {
        if(topcountries[i] >= 0)
        {
            printf("%s (%d)\n", countryNames[topcountries[i]], country[topcountries[i]][0]);
        }
    }
}


// function #8 Returns the total number of countries with no medal of a specific category, where category =  indexMedal (1 for Gold, 2 for Silver, 3 for Bronze)


int findAllWithNoXMedals (int country [COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES])
{
    int nextcountry = 0;
    for(int i = 0; i < COUNTRIES; i++)
    {
        if(country[i][indexMedal] == 0)
        {
            indexOfCountries[nextcountry++] = i; 
        }
    }
    return nextcountry;
}


// function #9 Returns the total number of countries that have ONLY won medals of a specific category, where each category = indexMedal (1 for Gold, 2 for Silver, 3 for Bronze)

int findAllWithOnlyXMedals (int country [COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES])
{
    int onlyMedals = 0; 
    for(int i = 0; i < COUNTRIES; i++)
    {
        if(country[i][indexMedal] != 0 && country[i][(indexMedal+1)%MEDALCAT] == 0 && country[i][(indexMedal+2)%MEDALCAT] == 0)
        {
            indexOfCountries[onlyMedals++] = i;
        }
    }
    return onlyMedals;
}

// function #10 Returns the index of the countryName that has min or max length - use 1 for min and 2 for max.

int findCountryIndexWithMinOrMaxLength (int minOrMax, char countryNames [COUNTRIES][MAX_LENGTH_CNAME])
{
    int indexMinOrMax = 0;
    for(int i = 1; i < COUNTRIES; i++)
    {
        if((minOrMax == 2 && strlen(countryNames[i]) > strlen(countryNames[indexMinOrMax]))
	 || (minOrMax == 1 && strlen(countryNames[i]) < strlen(countryNames[indexMinOrMax])))
        {
            indexMinOrMax = i;
        }
    }
    return indexMinOrMax;
}
