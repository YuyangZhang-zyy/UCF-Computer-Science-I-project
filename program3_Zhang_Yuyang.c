//Yuyang Zhang
//Dr. Steinberg
//COP3502 Spring 2022
//Programming Assignment 3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct card_s{
	int rank;    //number
	char * type; //type of card
	struct card_s * nextptr;
}card_t;

//function prototypes
void rules(); //display rules
int playRound(); //simulate round
card_t * openCardDeck(); //open the card deck and place into a linkedlist setup
card_t * insertBackSetup(card_t *node, char *name, int cardrank); //take card from orginial deck and place in back of linked list for setup of game
int empty(card_t * node); //check to see if linked list is empty
void cleanUp(card_t * head); //free memory to prevent memory leaks
int deckSize(card_t * head); //count number of nodes in the linked list
card_t * search(card_t * node, int spot); //search list for a specific spot in the card deck indexing is similar to array setup
card_t * copyCard(card_t * node); //make a deep copy of card
card_t * removeCard(card_t * node, int spot); //remove card from linkedlist
card_t * insertBackDeck(card_t *head, card_t *node); //place card at end of pile
int compareCard(card_t * cardp1, card_t * cardp2); //compare cards
card_t * moveCardBack(card_t *head); //place card at top of deck to the bottom of the deck

int main()
{
	int seed;
	printf("Enter Seed: ");
	scanf("%d", &seed);

	srand(seed); //seed set
	rules();

	int player; //1 or 2
	int result;

	printf("Would you like to be player 1 or 2?\n");
	printf("Enter 1 or 2: ");
	scanf("%d", &player); //choose player

	for(int game = 1; game <= 5; ++game) //simulate games
	{
		printf("Alright lets play game %d.\n", game);
		printf("Lets split the deck.\n");

		result = playRound(); //play game

		if((result == 1 && player == 1) || (result == 2 && player == 2)) //determine who won
			printf("You won game %d.\n", game);
		else
			printf("I won game %d.\n", game);
	}

	return 0;
}

void rules()
{
	printf("Welcome to the card game war!\n");
	printf("Here are the rules.\n");
	printf("You have a pile of cards and I have a pile of cards.\n");
	printf("We will each pull the top card off of our respective deck and compare them.\n");
	printf("The card with the highest number will win the round and take both cards.\n");
	printf("However if there is a tie, then we have to we have to place one card faced down and the next one faced up and compare the results.\n");
	printf("Winner of the tie, will grab all the cards out. However if it's a tie again, then we repeat the same action.\n");
	printf("Ready? Here we go!\n");
}

int playRound()
{
    int size1 = 26, size2 = 26, result1 = -1, result = 0;//set size and judgment varable
    card_t * deck = openCardDeck();

    card_t * deck1 = (card_t *) malloc(sizeof(card_t));//allocate player 1's deck
    if(empty(deck1)) //check to see if malloc worked
    {
        printf("Did not allocate head successfully...");
        printf("Program Terminating...\n");
        exit(1);
    }

    card_t * deck2 = (card_t *) malloc(sizeof(card_t));//allocate player 2's deck
    if(empty(deck2)) //check to see if malloc worked
    {
        printf("Did not allocate head successfully...");
        printf("Program Terminating...\n");
        exit(1);
    }

    //set the pointer to point to the corresponding linked list
    card_t * temp1 = deck1;
    card_t * temp2 = deck2;
    card_t * temp3 = deck1;
    card_t * temp4 = deck2;
    card_t * deck1move = NULL;
    card_t * deck2move = NULL;
    card_t * temp5 = NULL;

    printf("There are 52 cards in the deck.\n");

    for(int i = 26; i > 0; --i)//assign each player's deck randomly
    {
        size2 = rand()%(2*i);
        temp2->nextptr = copyCard(search(deck, size2));
        temp2 = temp2->nextptr;
        deck = removeCard(deck, size2);

        size1 = rand()%(2*i-1);
        temp1->nextptr = copyCard(search(deck, size1));
        temp1 = temp1->nextptr;
        deck = removeCard(deck, size1);
    }



    //remove empty headers
    deck2 = deck2->nextptr;
    free(temp4);
    temp4 = NULL;
    deck1 = deck1->nextptr;
    free(temp3);
    temp3 = NULL;

    while(!(empty(deck1) || empty(deck2)))
    {
        result1 = compareCard(deck1, deck2);//decide the winner

        //winner takes the other's card(linked list)
        if(result1 == 1)
        {
            printf("Player 1 won that round.\n");
            deck1 = moveCardBack(deck1);
            deck2move = copyCard(search(deck2, 0));
            deck1 = insertBackDeck(deck1, deck2move);
            deck2 = removeCard(deck2, 0);
         }
        else if(result1 == 2)
        {
            printf("Player 2 won that round.\n");
            deck2 = moveCardBack(deck2);
            deck1move = copyCard(search(deck1, 0));
            deck2 = insertBackDeck(deck2, deck1move);
            deck1 = removeCard(deck1, 0);

        }
        else if(result1 == 0)//tie condition
        {
            printf("Ugh oh...We have a tie! W-A-R!\n");

            int result2 = 0;//set second result
            card_t * profit = (card_t *) malloc(sizeof(card_t));//allocate profit linked list
            if(empty(profit)) //check to see if malloc worked
            {
                printf("Did not allocate head successfully...");
                printf("Program Terminating...\n");
                exit(1);
            }
            temp5 = profit;//set pointer

            while(result2 == 0)//loop judgment to deal with multiple ties
            {
                if(deckSize(deck1) >= 3 && deckSize(deck2) >= 3)//regular profit
                {
                    temp5->nextptr = copyCard(search(deck1, 0));
                    temp5 = temp5->nextptr;
                    deck1 = removeCard(deck1, 0);

                    temp5->nextptr = copyCard(search(deck1, 0));
                    temp5 = temp5->nextptr;
                    deck1 = removeCard(deck1, 0);

                    temp5->nextptr = copyCard(search(deck2, 0));
                    temp5 = temp5->nextptr;
                    deck2 = removeCard(deck2, 0);

                    temp5->nextptr = copyCard(search(deck2, 0));
                    temp5 = temp5->nextptr;
                    deck2 = removeCard(deck2, 0);

                    result2 = compareCard(deck1, deck2);//judge the next tie
                    if(result2 == 0)
                    {
                        printf("Player 1 has %d cards.\n", deckSize(deck1));
                        printf("Player 2 has %d cards.\n", deckSize(deck2));
                        printf("Ugh oh...We have a tie! W-A-R!\n");
                    }

                }
                else if(deckSize(deck1) == 2 || deckSize(deck2) == 2)//profit when only 2 cards in deck
                {
                    temp5->nextptr = copyCard(search(deck1, 0));
                    temp5 = temp5->nextptr;
                    deck1 = removeCard(deck1, 0);

                    temp5->nextptr = copyCard(search(deck2, 0));
                    temp5 = temp5->nextptr;
                    deck2 = removeCard(deck2, 0);

                    result2 = compareCard(deck1, deck2);
                    if(result2 == 0)
                    {
                        printf("Player 1 has %d cards.\n", deckSize(deck1));
                        printf("Player 2 has %d cards.\n", deckSize(deck2));
                        printf("Ugh oh...We have a tie! W-A-R!\n");
                    }
                }
                //decide winner when only 1 card in deck
                else if(deckSize(deck1) == 1)
                    result2 = 2;
                else if(deckSize(deck2) == 1)
                    result2 = 1;

            }

            //fixed profit
            temp5->nextptr = copyCard(search(deck1, 0));
            temp5 = temp5->nextptr;

            temp5->nextptr = copyCard(search(deck2, 0));
            temp5 = temp5->nextptr;

            temp5 = profit;
            profit = profit->nextptr;
            free(temp5);
            temp5 = NULL;

            //winner get profit
            if(result2 == 1)
            {
                deck1 = insertBackDeck(deck1, profit);
                printf("Player 1 won that W-A-R!\n");
            }

            if(result2 == 2)
            {
                deck2 = insertBackDeck(deck2, profit);
                printf("Player 2 won that W-A-R!\n");
            }

            //draw the first card of each deck
            deck1 = removeCard(deck1, 0);
            deck2 = removeCard(deck2, 0);

        }
        printf("Player 1 has %d cards.\n", deckSize(deck1));
        printf("Player 2 has %d cards.\n", deckSize(deck2));

    }

    //free allocated memory
    if(empty(deck1))
    {
        result = 2;
        cleanUp(deck2);
    }

    if(empty(deck2))
    {
        result = 1;
        cleanUp(deck1);
    }

    return result;
}

card_t * openCardDeck()
{
	FILE *fptr = fopen("deck.txt", "r");

	char *name = (char *) malloc(sizeof(char) * 20);

	if (name == NULL)
	{
		printf("Error in malloc...\n");
		exit(1);
	}

	card_t * head = NULL;

	int cardrank = 13;
	int tracker = 1;
	while(fscanf(fptr, "%s", name) == 1)
	{
		strcat(name, " ");

		if(tracker % 5 == 1)
		{
			strcat(name, "of Clubs");
			head = insertBackSetup(head, name, cardrank);
		}
		else if(tracker % 5 == 2)
		{
			strcat(name, "of Diamonds");
			head = insertBackSetup(head, name, cardrank);
		}
		else if(tracker % 5 == 3)
		{
			strcat(name, "of Hearts");
			head = insertBackSetup(head, name, cardrank);
		}
		else if(tracker % 5 == 4)
		{
			strcat(name, "of Spades");
			head = insertBackSetup(head, name, cardrank);
			tracker = 0;
			--cardrank;
		}

		++tracker;

	}

	free(name);
	fclose(fptr);

	return head;
}

card_t * insertBackSetup(card_t *node, char *name, int cardrank)
{

    if(empty(node)) //check to see if list is empty
    {
		node = (card_t *) malloc(sizeof(card_t));

		if(empty(node)) //check to see if malloc worked
		{
			printf("Did not allocate head successfully...");
			printf("Program Terminating...\n");
			exit(1);
		}
		else //otherwise populate data of new head node
		{
			node->type = (char *) malloc(sizeof(char) * 20);

			if(node->type == NULL)
			{
				printf("Error with malloc...\n");
				exit(1);
			}

			strcpy(node->type, name);
			node->rank = cardrank;
			node->nextptr = NULL; //must make new tail nextptr NULL!!!

			return node;  //terminate
		}

    }

	//here we know that the list has at least one node

	card_t *head = node; //keep pointer to head since we will need to return this address

	while(node->nextptr != NULL) //traverse to tail
		node = node->nextptr;

	node->nextptr = (card_t *) malloc(sizeof(card_t));

	if(node->nextptr == NULL) //see if new tail was allocated successfully
	{
		printf("Did not allocate node successfully...");
		return head; //terminate if tail didn't get created
	}

	//populate new node
	node->nextptr->type = (char *) malloc(sizeof(char) * 20);

	if(node->nextptr->type == NULL)
	{
		printf("Error with malloc...\n");
		exit(1);
	}

	strcpy(node->nextptr->type, name);
	node->nextptr->rank = cardrank;
	node->nextptr->nextptr = NULL; //very important

	return head; //return head node since we need our starting point of the linked list
}

int empty(card_t * node)
{
	return (node == NULL); //return condition result
}

void cleanUp(card_t * head)
{
    card_t * temp3 = head;
    card_t * temp4 = NULL;

    //traverse linked list and free each node
    while(temp3 != NULL)
    {
        temp4 = temp3->nextptr;
        free(temp3->type);
        free(temp3);
        temp3 = temp4;
    }
    head = NULL;
}


int deckSize(card_t * head)
{
    int count = 0;//set counter

    //counter increase when traversing each node
    while(head != NULL)
    {
        head = head->nextptr;
        count++;
    }
    return count;
}

card_t * search(card_t * node, int spot)
{
    card_t * temp = node;

    //traverse each node
    for(int i = 0; i < deckSize(node); ++i)
    {
        if(i == spot)//find corresponding node
            return temp;

        temp = temp->nextptr;
    }
    return NULL;
}

card_t * copyCard(card_t * node)
{
    card_t * copy = (card_t *) malloc(sizeof(card_t));//allocate node's copy
    if(copy == NULL)//check if malloc success
	{
		printf("malloc wasn't successful");
		return NULL;
	}

	//set node
    copy->rank = node->rank;
    copy->type = node->type;
    copy->nextptr = NULL;

    return copy;
}

card_t * removeCard(card_t * node, int spot)
{
    if(empty(node))//determine if it is an empty node
		return NULL;

    card_t * temp = node;
    card_t * target = search(node, spot);//Find the target node

    if(target == NULL)
		return temp;
    if(temp == target)//if the target is the head node
    {
		temp = temp->nextptr;
		free(target);
		return temp;
	}
    while(temp->nextptr != target)//move to the previous node of the target node
        temp = temp->nextptr;
    temp->nextptr = target->nextptr;//connect next pointer
    free(target);//free target node

    return node;
}

card_t * insertBackDeck(card_t *head, card_t *node)
{
    card_t * temp = head;
    while(temp->nextptr != NULL)//traverse to find the tail
        temp = temp->nextptr;
    temp->nextptr = node;//add node to tail
    return head;
}

int compareCard(card_t * cardp1, card_t * cardp2)
{
    printf("Player 1 pulled out %s. \t", cardp1->type);
    printf(" Player 2 pulled out %s.\n", cardp2->type);
    int p1 = cardp1->rank;
    int p2 = cardp2->rank;

    //returns the corresponding number by compare ranks
    if(p1 > p2)
        return 1;

    if(p1 < p2)
        return 2;

    if(p1 == p2)
        return 0;

}

card_t * moveCardBack(card_t *head)
{
    //set pointers to point to head
    card_t * temp = head;
    card_t * temp2 = head;
    while(temp2->nextptr != NULL)//set pointer to node's tail
        temp2 = temp2->nextptr;
    temp2->nextptr = temp;//connect head to tail
    head = temp->nextptr;//set new head
    temp->nextptr = NULL;//set new tail
    return head;
}
