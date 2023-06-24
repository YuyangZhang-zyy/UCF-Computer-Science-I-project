//Felix Liu
//Dr. Andrew Steinberg
//COP3502 Computer Science 1
//Programming Assignment 5 Solution

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 2000

typedef struct{
	char * name; //dynamic string
	int rank;
}player_t;

//function prototype(s)
player_t* scanRoster(player_t *roster);
void merge(player_t * arr, int p, int q, int r);
void mergeSort(player_t * arr, int p, int r);

int main(void)
{
	int seed;
	printf("Enter seed: ");
	scanf("%d", &seed);
	srand(seed);

	player_t *roster = (player_t*) malloc(sizeof(player_t) * MAX);
	player_t *team1 = (player_t*) malloc(sizeof(player_t) * MAX / 2);
	player_t *team2 = (player_t*) malloc(sizeof(player_t) * MAX / 2);


	roster = scanRoster(roster);

	mergeSort(roster, 0, MAX -1);
	double sum1 = 0;
	double sum2 = 0;

	for(int i = 0; i < MAX/2; i++)
    {
        team1[i].name = (char *) malloc(sizeof(char) *20);
        team2[i].name = (char *) malloc(sizeof(char) *20);

        if(team1[i].name == NULL || team2[i].name == NULL)
        {
            printf("malloc not successful\n");
            printf("Program Terminating...\n");
            exit(1);
        }

        //transfer name and rank to team 1 and 2
        strcpy(team1[i].name, roster[i].name);
        strcpy(team2[i].name, roster[i + (MAX / 2)].name);
        team1[i].rank = roster[i].rank;
        team2[i].rank = roster[i + (MAX / 2)].rank;

        //count sum
        sum1 = team1[i].rank + sum1;
        sum2 = team2[i].rank + sum2;
    }

	double average1 = 0;
	double average2 = 0;

	average1 = sum1 / (MAX / 2);
	average2 = sum2 / (MAX / 2);

	printf("Team 1 Rank Average is: %f\n", average1);
	printf("Team 2 Rank Average is: %f\n", average2);

	for(int j = 0; j < MAX / 2; j++)
    {
        free(team1[j].name);
        free(team2[j].name);
	}

    for(int k = 0; k < MAX; k++)
        free(roster[k].name);

	free(roster);
	free(team1);
	free(team2);


	return 0;
}




player_t* scanRoster(player_t *roster)
{
	FILE *fptr = fopen("players.txt", "r");

	char name[20];
	int index = 0;

	while(fscanf(fptr, "%s", name) == 1)
	{
		roster[index].name = (char *) malloc(sizeof(char) * 20);
		strcpy(roster[index].name, name);
		roster[index].rank = rand() % 5 + 1;
		++index;
	}

	fclose(fptr);

	return roster;
}

void merge(player_t * arr, int p, int q, int r)
{
    int n1 = q - p +1;
    int n2 = r -q;

    player_t * leftarr = (player_t *) malloc(sizeof(player_t) * n1);
    for(int a = 0; a < n1; a++)
        leftarr[a].name = (char *) malloc(sizeof(char) * 20);

    player_t * rightarr = (player_t *) malloc(sizeof(player_t) * n2);
    for(int b = 0; b < n2; b++)
        rightarr[b].name = (char *) malloc(sizeof(char) * 20);

    for(int x = 0; x < n1; ++x)
    {
        strcpy(leftarr[x].name, arr[p + x].name);
        leftarr[x].rank = arr[p + x].rank;
    }


    for(int x = 0; x < n2; ++x)
    {
        strcpy(rightarr[x].name, arr[q + x + 1].name);
        rightarr[x].rank = arr[q + x + 1].rank;
    }


    int i = 0;
    int j = 0;
    int k = p;

    //merge
    while(i < n1 && j < n2)
    {
        if(leftarr[i].rank < rightarr[j].rank)
        {
            strcpy(arr[k].name, leftarr[i].name);
            arr[k].rank = leftarr[i].rank;
            i++;
            k++;
        }
        else
        {
            strcpy(arr[k].name, rightarr[j].name);
            arr[k].rank = rightarr[j].rank;
            j++;
            k++;
        }
    }
    //copy the remaining elements
    while(i < n1)
    {
        strcpy(arr[k].name, leftarr[i].name);
        arr[k].rank = leftarr[i].rank;
        k++;
        i++;
    }
    while(j < n2)
    {
        strcpy(arr[k].name, rightarr[j].name);
        arr[k].rank = rightarr[j].rank;
        k++;
        j++;
    }

    for(int c = 0; c < n1; c++)
        free(leftarr[c].name);
    for(int d = 0; d < n2; d++)
        free(rightarr[d].name);


    free(leftarr);
    free(rightarr);
}

void mergeSort(player_t * arr, int p, int r)
{
    if(p < r)
    {
        int q = (r + p) / 2;
        mergeSort(arr, p, q);
        mergeSort(arr, q+1, r);
        merge(arr, p, q, r);
    }
}

