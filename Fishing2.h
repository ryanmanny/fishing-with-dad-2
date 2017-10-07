#ifndef FISHING2_H
#define FISHING2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SEMICOLON ;

//Defines color codes
#define TITLE			"FISHING WITH DAD 2"
#define RED				"\x1B[31;1m"
#define BLUE			"\x1B[34;1m"
#define RESET			"\x1B[0m"

#define CLEAR			system("cls");

#define CANTGO			puts("You can't go there.");
#define CANTDO			if (verb != POOP) {puts("You can't do that.");}
#define VRES			verb = NONE;
#define VARS			Verb verb = NONE; char noun[30] = "";

#define FISH_FRAMERATE	100
#define TDEL			40 //standard typing delay
#define LINE_LENGTH		100

typedef enum boolean
{
	FALSE, TRUE
} Bool;


typedef enum verb
{
	NONE, USE, LOOK, GO, PICKUP, THROW, SHOOT, POOP, READTO, PLY, READ, DAD, SWITCH, SHIFT, OPEN, GRAB, UNBUCKLE
} Verb;

typedef struct item
{
	Bool used;
	char name[30];
	Verb verb;
} Item;

typedef struct node
{
	Item item;
	struct node *pNext;
} Node;

typedef struct inventory
{
	Node *FirstItem;
} Inv;

void mainMenu(void);
void printFish(int offset);
void printTitle(void);
void fishAnimation(void);
void saveProgress(unsigned int level);
int loadProgress(void);

void levelOne(void);
void levelTwo(void);
void levelThree(void);
void runIntro(void);
void runIntermission(void);
void runIntermission2(void);

//Linked list functions, used for inventory
Node *makeNode(Item newitem);
Node *insertAtFront(Inv *inventory, Item newitem);
void printInv(const Inv *inventory);
Bool searchInv(char *item, const Inv *inventory);
Item makeItem(Bool used, char *name, Verb verb);

//Text printing engine
void type(char *str, int delay);
void typeNoBreak(char *str, int delay);
void typeRoom(char *str);
void clearBuffer(void);

//Real game logic
void getAction(char *noun, Verb *verb);
Bool getFishing(void);
Bool caseCompare(char *str1, char *str2);

//Room functions (there might be a better way to do this but I can't think of it)
void roomRoom(Inv *inventory);
void roomHallway(Inv *inventory);
void roomCar(Inv *inventory);
void roomLake(Inv *inventory);

void credits(void);
#endif