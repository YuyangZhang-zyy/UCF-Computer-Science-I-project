//Yuyang Zhang
//Dr. Steinberg
//COP3502C Spring 2022
//Programming Assignment 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 20

char ** doubleIt(char **arr, int *maxsize);
char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize);
char * generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize); //write sentence to console window
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr); //write story to txt file
void displaySentence(char * sentence);
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize);

int main()
{
	//setup randomness
	int x;
	printf("Enter seed: ");
	scanf("%d", &x);
	srand(x); //set seed

	//declare necessary variables
	int nounsize = 0;
	int verbsize = 0;
	int adjsize = 0;
	int prepositionsize = 0;

	int nounmaxsize = 5;
	int verbmaxsize = 5;
	int adjmaxsize = 5;
	int prepositionmaxsize = 5;
	const int articlemaxsize = 3; //there are only 3 articles in the english language a, an, and the. that is why const is applied

	printf("Welcome to the random sentence generator.\n");

	//double pointers
	char ** nouns = NULL;
	char ** verbs = NULL;
	char ** adjectives = NULL;
	char ** preposition = NULL;
	char ** articles = NULL;

	nouns = (char **) malloc(sizeof(char *) * nounmaxsize);
	verbs = (char **) malloc(sizeof(char *) * verbmaxsize);
	adjectives = (char **) malloc(sizeof(char *) * adjmaxsize);
	preposition = (char **) malloc(sizeof(char *) * prepositionmaxsize);
	articles = (char **) malloc(sizeof(char *) * articlemaxsize);

	//make sure malloc was able to allocate memory
	if(nouns == NULL || verbs == NULL || adjectives == NULL || preposition == NULL || articles == NULL)
	{
		printf("malloc was not successful\n");
		printf("Program will now terminate.\n");
		exit(1);
	}

	//populate articles using strcpy. numbers represent how many characters are needed. this includes \0 character
	articles[0] = (char *) malloc(sizeof(char) * 2);
	strcpy(articles[0], "A");
	articles[1] = (char *) malloc(sizeof(char) * 3);
	strcpy(articles[1], "An");
	articles[2] = (char *) malloc(sizeof(char) * 4);
	strcpy(articles[2], "The");

	//open the file of words
	FILE *fptr = fopen("nouns.txt", "r");
	FILE *fptr2 = fopen("verbs.txt", "r");
	FILE *fptr3 = fopen("adjectives.txt", "r");
	FILE *fptr4 = fopen("preposition.txt", "r");

	//make sure the files were opened properly
	if(fptr == NULL || fptr2 == NULL || fptr3 == NULL || fptr4 == NULL)
	{
		printf("file was not successful in opening.");
		printf("Program will now terminate.\n");
		exit(1);
	}

	//populate the dynamic array
	nouns = populate(nouns, fptr, &nounsize, &nounmaxsize); //populate nouns
	verbs = populate(verbs, fptr2, &verbsize, &verbmaxsize); //populate verbs
	adjectives = populate(adjectives, fptr3, &adjsize, &adjmaxsize); //populate adjectives
	preposition = populate(preposition, fptr4, &prepositionsize, &prepositionmaxsize); //populate prepositions

	//close the files
	fclose(fptr);
	fclose(fptr2);
	fclose(fptr3);
	fclose(fptr4);

	//now lets generate 5 sentences and write them to the console window

    printf("Let's generate some random sentences that don't make sense.\n");

	for(int x = 0; x < 5; ++x)
	{
		char * sentence = generateSentence(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize);
		displaySentence(sentence);
		free(sentence);
		sentence = NULL;
	}

	printf("Now let's create three stories that just don't make sense.\n");
	fptr = fopen("story1.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 1
	fclose(fptr);

    fptr = fopen("story2.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 2
	fclose(fptr);

	fptr = fopen("story3.txt", "w");
	generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 3
	fclose(fptr);

	cleanUp(nouns,verbs, adjectives, preposition, articles, nounmaxsize, verbmaxsize, adjmaxsize, prepositionmaxsize, 3);

	printf("The stories were generated successfully and stored in their respective text files.\n");
	printf("Check them out!\n");

	return 0;
}

char ** doubleIt(char **arr, int *maxsize)
{
    char ** newarr = NULL;
    newarr = (char **) malloc (2 * (*maxsize) * sizeof(char*));

    if (newarr == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }

    for(int i = 0; i < *maxsize; i++)
    {
        int size = strlen(arr[i]);
        newarr[i] = (char *) malloc(sizeof(char) * size);

        if(newarr[i] == NULL)
        {
            printf("Memory allocation error!");
            exit(1);
        }
        strcpy(newarr[i], arr[i]);
    }
    *maxsize = 2 * *maxsize;
    return newarr;
}

char ** populate(char ** words, FILE *fptr, int *currentsize, int *maxsize)
{
    char temp[LIMIT] = {0};
    int size = 0;

    while(!feof(fptr))
    {
         for(int i = *currentsize; i < *maxsize; i++)
        {
            fgets(temp, LIMIT, fptr);

            if(temp[strlen(temp) - 1] == '\n')
                temp[strlen(temp) - 1] = '\0';

            size = strlen(temp);

            words[i] = (char*)malloc(sizeof(char) * size);

            if (words[i] == NULL)
            {
                printf("Memory allocation error!");
                exit(1);
            }
            strcpy(words[i], temp);
            *currentsize = *currentsize + 1;

            if(feof(fptr) != 0)
            {
                strcat(words[i], " ");
                break;
            }
        }
        if (*currentsize >= *maxsize)
            words = doubleIt(words, maxsize);
    }
    return words;
}

char * generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize)
{
    char * sentence = (char*) malloc(sizeof(char)* (3 * 2 + 9 * 2 + 10 * 2 + 5 + 7 + 7 + 2 + 1));
    sentence[0] = NULL;

    int i1 = rand()%(articlesize);
    strcat(sentence, article[i1]);
    strcat(sentence, " ");

    int i2 = rand()%(adjsize);
    strcat(sentence, adjective[i2]);
    sentence[strlen(sentence) - 1] = ' ';

    int i3 = rand()%(nounsize);
    strcat(sentence, noun[i3]);
    sentence[strlen(sentence) - 1] = ' ';

    int i4 = rand()%(verbsize);
    strcat(sentence, verb[i4]);
    sentence[strlen(sentence) - 1] = ' ';

    int i5 = rand()%(prepositionsize);
    strcat(sentence, preposition[i5]);
    sentence[strlen(sentence) - 1] = ' ';

    int i6 = rand()%(articlesize);
    strcat(sentence, article[i6]);
    strcat(sentence, " ");

    int i7 = rand()%(adjsize);
    strcat(sentence, adjective[i7]);
    sentence[strlen(sentence) - 1] = ' ';

    int i8 = rand()%(nounsize);
    strcat(sentence, noun[i8]);
    sentence[strlen(sentence) -1] = '.';
    sentence[strlen(sentence)] = '\0';

    return sentence;
}

void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE *fptr)
{
    int amount = rand()%401 + 100;

    for(int i = 1; i <= amount; i++)
    {
        char * singlesentence = NULL;
        singlesentence = generateSentence(noun, verb, adjective, preposition, article, nounsize, verbsize, adjsize, prepositionsize, articlesize);
        fprintf(fptr,"%s\n", singlesentence);
        free(singlesentence);
        singlesentence = NULL;
    }
}

void displaySentence(char * sentence)
{
    printf("%s\n", sentence);
}

void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize)
{
    for(int i = 0; i < nounsize; i++)
    {
        free(nouns[i]);
        nouns[i] = NULL;
    }
    free(nouns);
    nouns = NULL;

    for(int i = 0; i < verbsize; i++)
    {
        free(verbs[i]);
        verbs[i] = NULL;
    }
    free(verbs);
    verbs = NULL;

    for(int i = 0; i < adjsize; i++)
    {
        free(adjectives[i]);
        adjectives[i] = NULL;
    }
    free(adjectives);
    adjectives = NULL;

    for(int i = 0; i < prepositionsize; i++)
    {
        free(prepositions[i]);
        prepositions[i] = NULL;
    }
    free(prepositions);
    prepositions = NULL;

    for(int i = 0; i < articlesize; i++)
    {
        free(articles[i]);
        articles[i] = NULL;
    }
    free(articles);
    articles = NULL;
}
