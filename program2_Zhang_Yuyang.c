//Yuyang Zhang
//Dr. Steinberg
//COP3502 Spring 2022
//Programming Assignment 2

#include<stdio.h>
#include<stdlib.h>

int blobDetect(int ** picture, int x, int y, int limit);

int main()
{
	//setup randomness
    int x;

    printf("Enter seed: ");
    scanf("%d", &x);

    srand(x); //set seed

	printf("Enter the size of the picture: ");

	int size;
	scanf("%d", &size);

	int ** picture = (int **) malloc(size * sizeof(int *));

	for(int x = 0; x < size; ++x)
		picture[x] = (int *) malloc(size * sizeof(int));

	for(int test = 1; test <= 5; ++test)
	{
		printf("Test %d\n", test);

		for(int r = 0; r < size; ++r)
			for(int c = 0; c < size; ++c)
				picture[r][c] = rand() % 2; //generate random number between 0 and 1


		int numblobs = 0;

		for(int r = 0; r < size; ++r)
			for(int c = 0; c < size; ++c)
				if(blobDetect(picture, r, c, size) > 0)
					++numblobs;

		printf("There are %d blob(s) in the picture.\n", numblobs);
	}

	//Super important! I don't think I can emphasize how important this is to do!
	for(int x = 0; x < size; ++x)
		free(picture[x]);

	free(picture);

	return 0;
}

int blobDetect(int ** picture, int x, int y, int limit)
{
    int g1 = 0, g2 = 0, g3 = 0, g4 = 0, g5 = 0, g6 = 0, g7 = 0, g8 = 0;
    if(picture[x][y] == 0)
        return 0;
    else
    {
        if(picture[x][y] == 1 && ( x + 1 == limit || picture[x + 1][y] == 0 ) && ( y + 1 == limit || picture[x][y + 1] == 0 ) && ( x + 1 == limit || y + 1 == limit || picture[x + 1][y + 1] == 0 ) && ( x - 1 < 0 || picture[x - 1][y] == 0 ) && ( y - 1 < 0 || picture[x][y - 1] == 0 ) && ( x - 1 < 0 || y - 1 < 0 || picture[x - 1][y - 1] == 0 ) && ( x + 1 == limit || y - 1 < 0 || picture[x + 1][y - 1] == 0 ) && ( x - 1 < 0 || y + 1 == limit || picture[x - 1][y + 1] == 0 ))
        {
            picture[x][y] = 0;
            return 1;
        }

        picture[x][y] = 0;

        if((x - 1 >= 0) && (y - 1 >= 0) && (picture[x - 1][y - 1] == 1))
            g1 = blobDetect(picture, x - 1, y - 1, limit);
        if((x - 1 >= 0) && (y >= 0) && (picture[x - 1][y] == 1))
            g2 = blobDetect(picture, x - 1, y, limit);
        if((x - 1 >= 0) && (y + 1 <= limit) && (picture[x - 1][y + 1] == 1))
            g3 = blobDetect(picture, x - 1, y + 1, limit);
        if((x >= 0) && (y - 1 >= 0) && (picture[x][y - 1] == 1))
            g4 = blobDetect(picture, x, y - 1, limit);
        if(x >= 0 && (y + 1 < limit) && (picture[x][y + 1] == 1))
            g5 = blobDetect(picture, x, y + 1, limit);
        if((x + 1 < limit) && (y - 1 >= 0) && (picture[x + 1][y - 1] == 1))
            g6 = blobDetect(picture, x + 1, y - 1, limit);
        if((x + 1 < limit) && (y >= 0) && (picture[x + 1][y] == 1))
            g7 = blobDetect(picture, x + 1, y, limit);
        if((x + 1 < limit) && (y + 1 < limit) && (picture[x + 1][y + 1] == 1))
            g8 = blobDetect(picture, x + 1, y + 1, limit);

        if(g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8 > 0)
            return 1;
    }
}



