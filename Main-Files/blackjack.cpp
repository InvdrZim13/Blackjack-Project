#include <iostream>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include "gotoxy.h"
using namespace std;

// Function Declarations
void print_header();
void shuffle_deck(int deck[]);
void starter_deal(int deck[], int totals[], int& row, int& t);
int get_value(int card);
char get_suit(int card);
void print_card(int num, char suit);
void deal_card(int deck[], int totals[], int row, int& t, int i);
void print_totals(int totals[]);
void deal_player(int deck[], int totals[], int row, int& t, int j);
void deal_dealer(int deck[], int totals[], int row, int& t);
void print_results(int totals[]);



int main()
{
	// Local Declarations
	int deck[52];
	int totals[8];
	int cardsdealt;
	int row;
	char playagain;

	// Statements

	system("color 37"); // Change console color
	srand(time(NULL)); // Change random number seed each time

	do
	{
		// Clear screen for new games
		system("cls");

		// Resets values for new game
		cardsdealt = 0;
		row = 7;
		for (int i = 0; i < 8; i++)
			totals[i] = 0;

		// Prints out board
		print_header();

		// Randomizes deck array values
		shuffle_deck(deck);

		// Deals first two cards for each player and the dealer
		starter_deal(deck, totals, row, cardsdealt);

		// For each player, deals cards until player stays or busts
		for (int i = 1; i < 8; i++)
			deal_player(deck, totals, row, cardsdealt, i);

		// Reveals and deals dealer's cards until he reaches 17
		deal_dealer(deck, totals, row, cardsdealt);

		// Prints out win or lose for each player, depending on if they beat the dealer or not
		print_results(totals);

		// Asks if user wants to play again
		gotoxy(4, 21);
		cout << "Would you like to play again? (y/n): ";
		cin >> playagain;
		playagain = tolower(playagain);

	} while (playagain == 'y'); // If user answers yes (y), new game starts
	if (playagain != 'n')
		playagain = 'n';

	gotoxy(0, 24);
	getchar();
	return 0;
}

/*
print_header
Prints out header, dealer and player names, and other parts of the board.
*/

void print_header()
{
	// Local Declarations
	int x = 0;
	int y = 0;
	const int MAX_X = 75; // Sets maximum horizontal size for boundaries
	const int MAX_Y = 23; // Sets maximum vertical size for boundaries

	// Statements

	// Prints out "*" boundaries
	for (int i = 0; i <= MAX_Y; i++)
	{
		gotoxy(0, i);
		cout << "*";
		y = i;
	}

	for (int i = 0; i <= MAX_X; i++)
	{
		gotoxy(i, 0);
		cout << "*";
		x = i;
	}

	for (int i = 0; i <= MAX_Y; i++)
	{
		gotoxy(x, i);
		cout << "*";
	}

	for (int i = 0; i <= MAX_X; i++)
	{
		gotoxy(i, y);
		cout << "*";
	}

	// Prints title
	gotoxy((MAX_X - 13) / 2, 3);
	cout << "LTU BLACKJACK";

	// Prints Dealer name
	gotoxy(3, 6);
	cout << "Dealer";

	// Prints player names
	for (int i = 1; i < 8; i++)
	{
		cout << " Player " << i;
	}

	// Prints total lines for dealer
	gotoxy(3, 16);
	cout << "______  ";

	// Prints total lines for each player
	for (int i = 1; i < 8; i++)
	{
		cout << "_______  ";
	}
}

/*
shuffle_deck
Shuffles deck array for random cards in each slot.
*/

void shuffle_deck(int deck[])
{
	// Local Declarations
	int k;
	int picked[52];

	// Statements

	for (int i = 0; i < 52; i++)
		picked[i] = 0;

	for (int i = 0; i< 52; i++)
	{
		k = rand() % 52;
		while (picked[k])
			k = rand() % 52;
		picked[k] = 1;
		deck[i] = k;
	}
}

/*
starter_deal
Deals two cards to all players and the dealer and hides the dealer's first card.
*/

void starter_deal(int deck[], int totals[], int& row, int& t)
{
	// Hides dealer's first card
	gotoxy(8, row);
	cout << "?";

	// Deal cards to all players on the first row
	for (int i = 1; i < 8; i++)
	{
		deal_card(deck, totals, row, t, i);
	}
	row++;

	// Deal cards to all players and the dealer on the second row
	for (int i = 0; i < 8; i++)
	{
		deal_card(deck, totals, row, t, i);
	}
	row++;
}

/*
get_value
Given the card's number from the deck, it returns the card's value, between 1-13
*/

int get_value(int card)
{
	return (card % 13) + 1;
}

/*
get_suit
Given the card's number from the deck, it returns the card's suit as either hearts, diamonds, clubs or spades.
*/

char get_suit(int card)
{
	switch (card / 13)
	{
	case 0: return char(3);
	case 1: return char(4);
	case 2: return char(5);
	case 3: return char(6);
	}
	return 0;
}

/*
print_card
Gives the card's value and suit
*/

void print_card(int num, char suit)
{
	// Changes text color according to card's suit
	switch (suit)
	{
	case 3:
	case 4: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x3C); // Red for hearts and diamonds
		break;
	case 5:
	case 6: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x30); // Black for clubs and spades
		break;
	}
	// Create additional space if number is not 10 (doesn't have two digits)
	if (num != 10)
		cout << " ";

	// Prints out the value of the card, either numerically or with its respective letter
	switch (num)
	{
	case 1: cout << "A";
		break;
	case 11: cout << "J";
		break;
	case 12: cout << "Q";
		break;
	case 13: cout << "K";
		break;
	default: cout << num;
	}

	// Prints out card's suit symbol
	cout << suit;

	// Sets text color back to white
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x37);
}

/*
deal_card
Takes a card from the deck and deals it to the player.
*/

void deal_card(int deck[], int totals[], int row, int& t, int i)
{
	// Local Declarations
	int card;
	char suit;

	// Statements

	// Goes to respective row and column
	gotoxy(6 + (9 * i), row);

	// Card value and suit
	card = get_value(deck[t]);
	suit = get_suit(deck[t]);

	// Adds one to cards_dealt to move on to next card for future dealings
	t++;

	// Prints out card dealt
	print_card(card, suit);

	// Changes the values of J, Q and K to 10
	if (card > 10)
		card = 10;

	// Adds the card's changed value to the current player's total
	totals[i] += card;

	// Prints out updated totals
	print_totals(totals);
}

/*
print_totals
Prints out dealer and all player's totals below each respective spot on the board.
*/

void print_totals(int totals[])
{
	for (int i = 0; i < 8; i++)
	{
		gotoxy(6 + (9 * i), 17);
		cout << setw(2) << totals[i];
	}
}

/*
deal_player
Deals cards to current player until player stays, reaches 21 or busts.
*/

void deal_player(int deck[], int totals[], int row, int& t, int j)
{
	//Local Declarations
	char hit;

	//Statements

	// Asks player if they want another card
	gotoxy(21, 20);
	cout << "Hit or stay? (h/s): ";
	cin >> hit;

	// Clears out response
	gotoxy(41, 20);
	cout << " ";

	while (tolower(hit) == 'h')
	{
		// Deals card to the player
		deal_card(deck, totals, row, t, j);

		// Moves to next row
		row++;

		// Breaks loop if player reaches 21 or busts
		if (totals[j] >= 21)
			break;

		// Asks player if they want another card
		gotoxy(21, 20);
		cout << "Hit or stay? (h/s): ";
		cin >> hit;

		// Clears response on screen
		gotoxy(41, 20);
		cout << " ";
	}
	gotoxy(21, 20);
	cout << "                    ";
	gotoxy(4 + (9 * j), 18);
	if (totals[j] > 21)
	{
		Beep(800, 800);
		cout << "Bust!"; // If player busts, prints Bust!
	}
	else
	{
		Beep(700, 800);
		cout << " Stay"; // If player stays, prints Stay
	}
}

/*
deal_dealer
Deals cards to the deal until dealer reaches 17
*/

void deal_dealer(int deck[], int totals[], int row, int& t)
{
	// Reveals dealer's hidden card.
	deal_card(deck, totals, 7, t, 0);
	// Deals cards to the deal until dealer reaches 17
	while (totals[0] < 17)
	{
		deal_card(deck, totals, row, t, 0);
		row++;
	}

	// Prints if dealer busted
	gotoxy(4, 18);
	if (totals[0] > 21)
		cout << "BUST!";
}

/*
print_results
Prints out "Win" or "Lose" depending on which condition was satisfied
*/

void print_results(int totals[])
{
	for (int i = 1; i < 8; i++)
	{
		gotoxy(4 + (9 * i), 18);
		// Player wins if total is greater than dealer or the dealer busts and the player did not bust.
		if ((totals[i] > totals[0] || totals[0] > 21) && totals[i] <= 21)
		{
			cout << " Win!";
			Beep(1400, 800);
		}
		// Player loses if total is less than dealer or player busted.
		else if (totals[i] < totals[0] || totals[i] > 21)
		{
			cout << "Lose!";
			Beep(650, 800);
		}
		// Player ties if total is the same as the dealer's.
		else
		{
			cout << "  Tie";
			Beep(1111, 800);
		}
	}
}
