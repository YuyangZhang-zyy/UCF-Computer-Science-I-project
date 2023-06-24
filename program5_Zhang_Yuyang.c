//Yuyang Zhang
//Dr. Andrew Steinberg
//COP3502 Computer Science 1
//Programming Assignment 5

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
void quicksort(player_t * arr, int p, int r);
int partition(player_t * arr, int p, int r);

int main(void)
{
    //Pseudo random number setting
	int seed;
	printf("Enter seed: ");
	scanf("%d", &seed);
	srand(seed);

    //malloc required pointers
	player_t *roster = (player_t*) malloc(sizeof(player_t) * MAX);
	player_t *team1 = (player_t*) malloc(sizeof(player_t) * MAX / 2);
	player_t *team2 = (player_t*) malloc(sizeof(player_t) * MAX / 2);

	if(roster == NULL || team1 == NULL || team2 == NULL)
	{
		printf("malloc not successful\n");
		printf("Program Terminating...\n");
        exit(1);
	}


	roster = scanRoster(roster);

	quicksort(roster, 0, MAX - 1);//sort function call

	double sum1 = 0, sum2 = 0;

	for(int i = 0; i < MAX / 2; i++)
    {
        //allocate name malloc
        team1[i].name = (char *) malloc(sizeof(char) * 20);
        team2[i].name = (char *) malloc(sizeof(char) * 20);
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

	//calculate average
	average1 = sum1 / (MAX / 2);
	average2 = sum2 / (MAX / 2);

	printf("Team 1 Rank Average is: %f\n", average1);
	printf("Team 2 Rank Average is: %f\n", average2);

	//free all memory allocated
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

void quicksort(player_t * arr, int p, int r)
{
    if(p < r)
    {
        int q = partition(arr, p, r);//find pivot
        //recursion on arrays on both sides of pivot
        quicksort(arr, p, q - 1);
        quicksort(arr, q + 1, r);
    }
}

int partition(player_t * arr, int p, int r)
{
    int x = arr[r].rank;//random pivot
    int i = p - 1;

    //allocate pointer to temporarily store data
    player_t *temp = (player_t*) malloc(sizeof(player_t) * 1);
    if(temp == NULL)
    {
        printf("malloc not successful\n");
        printf("Program Terminating...\n");
        exit(1);
    }

    temp->name = (char *) malloc(sizeof(char) * 20);
    if(temp->name == NULL)
    {
        printf("malloc not successful\n");
        printf("Program Terminating...\n");
        exit(1);
    }

    for(int j = p; j <= r - 1; j++)
    {
        if(arr[j].rank < x)
        {
            ++i;
            //swap pointers
            strcpy(temp->name, arr[i].name);
            temp->rank = arr[i].rank;

            strcpy(arr[i].name, arr[j].name);
            arr[i].rank = arr[j].rank;

            strcpy(arr[j].name, temp->name);
            arr[j].rank = temp->rank;
        }
    }

    //swap with the pivot
    strcpy(temp->name, arr[i + 1].name);
    temp->rank = arr[i + 1].rank;

    strcpy(arr[i + 1].name, arr[r].name);
    arr[i + 1].rank = arr[r].rank;

    strcpy(arr[r].name, temp->name);
    arr[r].rank = temp->rank;

    free(temp->name);
    free(temp);

    return (i + 1);//return pivot for next recursion

}
