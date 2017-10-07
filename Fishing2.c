#include "Fishing2.h"
static Bool pooped = FALSE;
static Bool bookRead = FALSE;

void mainMenu(void)
{
	fishAnimation();
	system("cls");
}

void printFish(int offset)
{
	printf(TITLE"\n");
	switch (offset)
	{
	case 1:
		printf("   _.-=-._     .-,\n");
		printf(" .\'       \"-.,' / \n");
		printf("(          _.  <\n");
		printf(" `=.____.=\"  `._\\\n");
		break;
	case 2:
		printf("    _.-=-._     .-,\n");
		printf("  .\'       \"-.,' / \n");
		printf(" (          _.  <\n");
		printf("  `=.____.=\"  `._\\\n");
		break;
	case 3:
		printf("     _.-=-._     .-,\n");
		printf("   .\'       \"-.,' / \n");
		printf("  (          _.  <\n");
		printf("   `=.____.=\"  `._\\\n");
		printf("");
		break;
	case 4:
		printf("      _.-=-._     .-,\n");
		printf("    .\'       \"-.,' / \n");
		printf("   (          _.  <\n");
		printf("    `=.____.=\"  `._\\\n");
		break;
	case 5:
		printf("       _.-=-._     .-,\n");
		printf("     .\'       \"-.,' / \n");
		printf("    (          _.  <\n");
		printf("     `=.____.=\"  `._\\\n");
		break;
	}
	puts("");
	puts("Press any key to start playing!");
	puts("Type \"help me\" during the game if you need tips!");
	
}

void printTitle(void)
{
	FILE *infile;
	char line[200] = "";

	infile = fopen("title.txt", "r");

	if (infile != NULL)
	{
		for (int i = 0; i < 18; i++)
		{
			fgets(line, 200, infile);
			printf("%s", line);
		}
		_sleep(1000);

		for (int i = 0; i < 6; i++)
		{
			fgets(line, 200, infile);
			printf("%s", line);
		}
		_sleep(1000);
	}

	else
		puts("File could not be opened");

	fclose(infile);
	clearBuffer();
}

void fishAnimation(void)
{
	int frames[8] = { 1, 2, 3, 4, 5, 4, 3, 2 }, i = 0;
	
	while (!_kbhit())
	{
		for (i = 0; i < 8; i++)
		{
			system("cls");
			printFish(frames[i]);
			_sleep(FISH_FRAMERATE);
		}
	}
	
	clearBuffer();
}

void saveProgress(unsigned int level)
{
	FILE *outfile = fopen("savefile.txt", "w");

	if (outfile != NULL)
	{
		fprintf(outfile, "%d", level);
		fclose(outfile);
	}	
}

//Needs access to linked lists, location and more. Dang
int loadProgress (void)
{
	FILE *infile = fopen("savefile.txt", "r");
	char ch;
	int level = 0;

	if (infile != NULL)
	{
		fscanf(infile, "%d", &level);
		if (level != 0)
		{
			do {
				puts("Would you like to load your progress? (Type Y or N)");
				ch = getc(stdin);
				system("cls");
			} while (ch != 'N' && ch != 'n' && ch != 'y' && ch != 'Y');
			if (ch == 'Y' || ch == 'y')
				puts("Loaded successfully");
			else
				level = 0;
		}
		fclose(infile);
	}
	return level;
}

void levelOne(void)
{
	Inv inventory;
	inventory.FirstItem = NULL;
	insertAtFront(&inventory, makeItem(FALSE, "gun", SHOOT));
	roomRoom(&inventory);
}

void levelTwo(void)
{
	Inv inventory;
	inventory.FirstItem = NULL;
	roomCar(&inventory);
}

void levelThree(void)
{
	Inv inventory;
	inventory.FirstItem = NULL;
	roomLake(&inventory);
}

//Creates and initializes new inventory item node
Node *makeNode(Item newItem)
{
	Node *pNew = (Node *)malloc(sizeof(Node));

	pNew->item.used = newItem.used;
	strcpy(pNew->item.name, newItem.name);
	pNew->item.verb = newItem.verb;

	pNew->pNext = NULL;

	return pNew;
}

Node *insertAtFront(Inv *inventory, Item newitem)
{
	Node *pNew = makeNode(newitem);
	pNew->pNext = NULL;

	if (pNew != NULL)
	{
		//if list isn't empty
		if (inventory->FirstItem != NULL)
		{
			pNew->pNext = inventory->FirstItem;
		}
		inventory->FirstItem = pNew;
	}
}

void printInv(const Inv *inventory)
{
	Node *pCur = inventory->FirstItem;

	puts("You are holding:");

	while (pCur != NULL)
	{
		if (pCur->item.used == FALSE)
			printf("%s\n", pCur->item.name);

		pCur = pCur->pNext;
	}
}

Bool searchInv (char *item, const Inv *inventory)
{
	Node *pCur = inventory->FirstItem;

	while (pCur != NULL)
	{
		if (caseCompare(item, pCur->item.name) && pCur->item.used == FALSE)
			return TRUE;
		else
		{
			pCur = pCur->pNext;
		}
	}
	return FALSE;
}

void runIntro(void)
{
	type("The clock strikes three, sending echoing chimes through your delapidated house.", TDEL);
	type("The creaking of the walls stirs you from your sleep.", TDEL);
	type("You sit up, seizing the pistol off your bedside table instinctively, just as you have hundreds of times before on restless nights like these.", TDEL);
	type("But this time your paranoia is justified.", TDEL * 1.5);
	type("A rush of air blows through the house as the front door slams.", TDEL);

	CLEAR
	
	type("It was happening again...", TDEL * 2);
	type("Dad was back", TDEL * 3);

	CLEAR

	_sleep(1500);
}

void runIntermission(void)
{
	//the way to do this would be to make the line pos a variable that is passed into every string as a reference
	type("Energizing the lamp with your mastery of electricity, you light up the hallway. It turns out that dad's shadow is really just the shadow of a fork that has been stuck in the top of the stairs.", TDEL);
	type("You walk over to the fork, but you accidentally trip over it, breaking up to or including 206 bones during your tumble down the stairs.", TDEL);
	type("Your mangled body falls directly into the clutches of dad.", TDEL * 2);
	type("\"Alright boy... it's time to go fishing.\"", TDEL * 3.5);
	CLEAR
	printTitle();
	CLEAR
	type("You come to. You can feel blood running down your face from a wound on your forehead.", TDEL);
	type("Your vision focuses on the road. The car is barreling down the highway at 100 mph.", TDEL);
	type("Your dad is staring directly at you, his eyes wide and a grin plastered on his face. He doesn't need to look at the road. He's been practicing for this moment for 15 years.", TDEL * 2);
	CLEAR;
}

void runIntermission2(void)
{
	type("You shift gears to park. The car begins to tumble.", TDEL * 1.5);
	puts("");
	type("The world slows down. Dad stares you right in the eyes, expression unchanging, as he is ripped through the windshield of the car by the rapid deceleration.", TDEL * 1.5);
	type("Your airbag deploys just in time to slow you down, but you too shoot through the windshield, finishing off most of your bones that still remained intact.", TDEL * 1.5);
	type("As you fly through the air, you realize with great horror that you were too late.", TDEL * 1.5);
	type("You crash into a muddy bank. You barely feel the impact as you let out a scream.", TDEL * 2); 
	type("You haven't been here in 15 years.", TDEL * 4);
	CLEAR
}

void getAction(char *noun, Verb *verb)
{
	char line[30], *str[3] = { NULL, NULL, NULL };

	while (str[1] == NULL)
	{
		printf(">");
		fgets(line, 29, stdin);

		str[0] = strtok(line, " ");
		str[1] = strtok(NULL, " ");
		str[2] = strtok(NULL, "\n");
		for (int i = 0; i < 3; i++)
			strtok(str[i], "\n");
	}

	if (str[0] != NULL)
	{
		if (caseCompare(str[0], "help"))
		{
			puts("Help:");
			puts("Your best bet to solve a puzzle is to look at everything in the room.");
			puts("Also don't forget to think outside the box. Most puzzles don't make sense.");
			puts("Common commands: go to, use, look at...");
			puts("Remember to include a noun with your verbs. Most actions won't work without one.");
			puts("Most common adventure game commands DO NOT WORK in FwD2, such as i to look in inventory.");
			puts("TYPE: \"look inventory \"");
			puts("There are also many more that you will have to discover for yourself!");
			*verb = POOP;
		}
		else if (caseCompare(str[0], "go") || caseCompare(str[0], "walk") || caseCompare(str[0], "run") || caseCompare(str[0], "skedaddle") || caseCompare(str[0], "saunter"))
		{
			*verb = GO;
			if (str[2] != NULL)
				strcpy(noun, str[2]); //Uses third word to deal with the fact that go has an extra preposition (i.e. go to)
		}
		else if (caseCompare(str[0], "use") || caseCompare(str[0], "utilize"))
		{
			*verb = USE;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "say") || caseCompare(str[1], "dad?"))
		{
			*verb = DAD;
		}
		else if (caseCompare(str[0], "turn") && caseCompare(str[1], "on"))
		{
			*verb = USE;
			strcpy(noun, str[2]);
		}
		else if (caseCompare(str[0], "look") && !caseCompare(str[1], "at") || caseCompare(str[0], "see") || caseCompare(str[0], "examine") || caseCompare(str[0], "check"))
		{
			*verb = LOOK;
			strcpy(noun, str[1]);
		}
		else if ((caseCompare(str[0], "look") && caseCompare(str[1], "at")) || (caseCompare(str[0], "check") && caseCompare(str[1], "out")))
		{
			*verb = LOOK;
			strcpy(noun, str[2]);
		}
		else if (caseCompare(str[0], "throw") || caseCompare(str[0], "toss"))
		{
			*verb = THROW;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "grab"))
		{
			*verb = GRAB;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "unbuckle"))
		{
			*verb = UNBUCKLE;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "pick") && caseCompare(str[1], "up"))
		{
			*verb = PICKUP;
			strcpy(noun, str[2]);
		}
		else if (caseCompare(str[0], "acquire") || caseCompare(str[0], "obtain") || caseCompare(str[0], "pickup") || caseCompare(str[0], "grab") || caseCompare(str[0], "get") || caseCompare(str[0], "take"))
		{
			*verb = PICKUP;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "ply") || caseCompare(str[0], "plyify") || caseCompare(str[0], "pry"))
		{
			*verb = PLY;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "shoot"))
		{
			*verb = SHOOT;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "open"))
		{
			*verb = OPEN;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "read") && !caseCompare(str[1], "to"))
		{
			*verb = READ;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "read") && caseCompare(str[1], "to"))
		{
			*verb = READTO;
			strcpy(noun, str[2]);
		}
		else if (caseCompare(str[0], "switch"))
		{
			*verb = SWITCH;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "shift"))
		{
			*verb = SHIFT;
			strcpy(noun, str[1]);
		}
		else if (caseCompare(str[0], "poop"))
		{
			if (FALSE == pooped)
			{
				puts("You grunt and a dribble runs down your leg.");
				pooped = TRUE;
			}
			else
				puts("There's none left.");
			*verb = POOP;
		}
		else
		{
			if (str[0][0] != '\n')
			{
				if (str[0][strlen(str[0]) - 1] != 'e') //I'm a grammar genius
					printf("Sorry, I've never %sed before\n", str[0]);
				else
					printf("Sorry, I've never %sd before\n", str[0]);
			}
			*verb = POOP;
		}
	}
	puts("");
}

//for getting the verb fish only
Bool getFishing(void)
{
	char line[30];

	while (caseCompare(line, "fish") == FALSE)
	{
		printf(">");
		fgets(line, 29, stdin);
		strtok(line, "\n ");
	}

	return TRUE;
}

Bool caseCompare(const char *str1, const char *str2)
{
	int length1 = strlen(str1), length2 = strlen(str2), i = 0;
	Bool same = TRUE;

	if (length2 != length1)
		same = FALSE;
	else
		while (i < length1)
		{
			if (tolower(str1[i]) == tolower(str2[i]))
				i++;
			else
			{
				i = length1;
				same = FALSE;
			}
		}
	return same;
}

void type(char *str, int delay)
{
	int length = strlen(str);
	Bool line_trig = FALSE;

	for (int i = 0; i < length; i++)
	{
		if (i != 0 && i % LINE_LENGTH == 0)
			line_trig = TRUE;
		if (str[i] == ' ' && line_trig == TRUE)
		{
			printf("\n");
			line_trig = FALSE;
		}
		else
			printf("%c", str[i]);
		if (delay != 0);
			_sleep(delay);
	}

	clearBuffer();
}

//Used to change typing speed without newline
void typeNoBreak(char *str, int delay)
{
	int length = strlen(str);
	Bool line_trig = FALSE;

	for (int i = 0; i < length; i++)
	{
		if (i != 0 && i % LINE_LENGTH == 0)
			line_trig = TRUE;
		if (str[i] == ' ' && line_trig == TRUE)
		{
			printf("\n");
			line_trig = FALSE;
		}
		else
			printf("%c", str[i]);
		_sleep(delay);
	}
	printf(" ");
}

void typeRoom(char *str)
{
	int length = strlen(str);
	Bool line_trig = FALSE;

	for (int i = 0; i < length; i++)
	{
		if (i != 0 && i % LINE_LENGTH == 0)
			line_trig = TRUE;
		if (str[i] == ' ' && line_trig == TRUE)
		{
			printf("\n");
			line_trig = FALSE;
		}
		else
			printf("%c", str[i]);
	}
	printf("\n");
}

void clearBuffer(void)
{
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

Item makeItem(Bool used, char *name, Verb verb)
{
	Item newItem;
	
	newItem.used = used;
	strcpy(newItem.name, name);
	newItem.verb = verb;

	return newItem;
}

void roomRoom(Inv *inventory)
{
	VARS

	puts("Your Room");
	typeRoom("You find yourself in your room. Your dusty mattress is in the corner, underneath a sparking power strip. Next to your mattress is your bedside table, which is actually just a cooler with a padlock on it. The only other item in the room is a crooked dresser, its left two legs broken through the floor. The door to your room opens into a dark hallway. You can hear dad stomping downstairs.");

	while (verb == NONE)
	{
		getAction(noun, &verb);

		if (verb == LOOK)
		{
			if (caseCompare(noun, "inventory"))
				printInv(inventory);
			if (caseCompare(noun, "around"))
				typeRoom("You find yourself in your room. Your dusty mattress is in the corner, underneath a sparking power strip. Next to your mattress is your bedside table, which is actually just a cooler with a padlock on it. The only other item in the room is a crooked dresser, its left two legs broken through the floor. The door to your room opens into a dark hallway. You can hear dad stomping downstairs.");
			if (caseCompare(noun, "dresser"))
				typeRoom("The dresser is totally busted. The dresser is at a strange angle. You can see something inside but unfortunately you don't have experience pulling drawers out of dressers at strange angles.");
			if (caseCompare(noun, "mattress"))
				typeRoom("Your mattress has a dusty silhouette of you crying burned into it.");
			if (caseCompare(noun, "power") || caseCompare(noun, "powerstrip") || caseCompare(noun, "cord"))
				typeRoom("The power strip is flailing around, shooting sparks everywhere, including right into your eyes. It's too dangerous to touch it without it ruining your life.");
			if (caseCompare(noun, "table") || caseCompare(noun, "cooler") || caseCompare(noun, "padlock") || caseCompare(noun, "lock"))
				typeRoom("The padlock is made of titanium, to stop you from accidentally eating all of your food supplies while you're asleep.");
			if (caseCompare(noun, "hallway"))
				typeRoom("The hallway is dark and foreboding. You get the sudden urge to go there.");
			VRES
		}
		else if (verb == DAD)
		{
			type("You whisper \"Dad?\" to the air. The word catches in your throat. You promised yourself you would never say it again...", TDEL * 1.5);
			typeNoBreak("\"WHO SAID THAT?\"", TDEL * 3);
			type("a booming voice blasts through the house, shaking it to the foundation.", TDEL * 1.5);
			type("A little bit of wee comes out. Flashbacks shoot through your mind. Even 15 years of isolation haven't cleansed the memories. A goldfish flashes across your vision. You hear the crack of the belt through the floorboards. You have to get out of here.", TDEL);
			VRES
		}
		else if (verb == SHOOT)
		{
			if (caseCompare(noun, "self") || caseCompare(noun, "yourself"))
			{
				typeNoBreak("You sit down on your mattress and hold the gun up to your temple, your hand shaking. The idea has crossed your mind every day ever since that fateful day on the lake. You cry out at the top of your lungs... but you can't do it. You have nothing left to live for... and that's exactly why you can't kill yourself. Dad must pay...", TDEL);
				type("Dad must die...", TDEL * 5);
			}
			else
				CANTDO
			VRES
		}
		else if (verb == READ)
		{
			if (caseCompare(noun, "book"))
			{
				if (searchInv("book", inventory))
				{
					if (bookRead == TRUE)
					{
						typeRoom("You begin reading the book, but fortunately you lose your ability to read as soon as the dresser transformation begins, reversing the spell.");
						
					}
					else
					{
						typeRoom("The book says on the front \"Warning: If you do not read this book directly to a dresser you may become a dresser yourself in a hilarious twist of fate.\"");
						bookRead = TRUE;
					}
					VRES
				}
				else
					CANTDO
			}
			VRES
		}
		else if (verb == READTO)
		{
			if (caseCompare(noun, "dresser"))
			{
				if (searchInv("book", inventory))
				{
					typeRoom("You incant the text of the book to the dresser. It ascends into the air and sprouts legs to become perfectly level with the floor. You fall to the floor, reading the post script of the incantation just a moment too late. The legs were generated by draining your life essence. The drawers spring open. You weakly grab the pair of pliers, noticing that the rubber grip is missing.");
					insertAtFront(inventory, makeItem(FALSE, "pliers", USE));
					VRES
				}
				else
					CANTDO
			}
			VRES
		}
		else if (verb == PLY)
		{
			if (caseCompare(noun, "power") || caseCompare(noun, "powerstrip") || caseCompare(noun, "cord"))
			{
				if (searchInv("pliers", inventory))
				{
					typeRoom("As soon as the pliers touch the powerstrip, you begin convulsing. It takes more than 10 minutes before you can wrench your arm away. Infused with the power of electricity, you \"safely\" remove the powerstrip from the wall. Unfortunately you will never be able to take a bath again without dying.");
					insertAtFront(inventory, makeItem(FALSE, "powerstrip", USE));
					VRES
				}
				else
					CANTDO
			}
			else if (caseCompare(noun, "cooler") || caseCompare(noun, "table") || caseCompare(noun, "padlock") || caseCompare(noun, "lock"))
			{
				if (searchInv("pliers", inventory))
				{
					typeRoom("You chomp the padlock off of the cooler with the pair of pliers. Half of the lock springs off and embeds itself in your eye. Also a cop sees you cutting a lock through the window and writes your name down in his notebook. There is a lamp within the cooler, along with a note that says \"Sorry but I ate all the food\" -Sleeping You. The cord of the lamp is broken off.");
					insertAtFront(inventory, makeItem(FALSE, "lamp", USE));
					VRES
				}
				else
					CANTDO
			}
			VRES
		}
		else if (verb == GO)
		{
			if (caseCompare(noun, "hallway"))
				roomHallway(inventory);
			else
			{
				CANTGO
				VRES
			}
		}
		else
		{
			CANTDO
			VRES
		}
	}
}

void roomHallway(Inv *inventory)
{
	VARS

	puts("Hallway");
	typeRoom("There is nothing in the hallway except for a loose tile on the ceiling and a shadow on the far wall at the end.");

	while (verb == NONE)
	{
		getAction(noun, &verb);
	
		if (verb == LOOK)
		{
			if (caseCompare(noun, "inventory"))
				printInv(inventory);
			if (caseCompare(noun, "around"))
				typeRoom("There is nothing in the hallway except for a loose tile on the ceiling and a shadow on the far wall at the end.");
			if (caseCompare(noun, "loose") || caseCompare(noun, "tile"))
				typeRoom("The tile is hanging precariously from the ceiling. Anything could knock it down unless it's not programmed in.");
			if (caseCompare(noun, "shadow"))
				type("As your eyes focus on the shadow you realize it's... YOUR DAD! Your breathing quickens.", TDEL);
			if (caseCompare(noun, "room") || caseCompare(noun, "bedroom"))
				typeRoom("You have rarely left your room since the incident. It is usually your beacon of safety and hope, but now that dad has found you, it is nothing more than a false sense of security. You don't have long before Dad finds you.");
			VRES
		}
		else if (verb == SHOOT)
		{
			if (caseCompare(noun, "tile"))
			{
				if (searchInv("gun", inventory))
				{
					typeRoom("You shoot the tile out from the ceiling. The bullet ricochets into your leg. A book lands on top of the tile entitled \"how to remove drawers from crooked dressers.\" You insert it in your pocket.");
					insertAtFront(inventory, makeItem(FALSE, "book", USE));
					VRES
				}
				else
					CANTDO
			}
			VRES
		}
		else if (verb == USE)
		{
			if (caseCompare(noun, "lamp"))
			{
				if (searchInv("lamp", inventory))
				{
					CLEAR
					return;
				}
				else
					CANTDO
			}
			VRES
		}
		else if (verb == GO)
		{
			if (caseCompare(noun, "room") || caseCompare(noun,"bedroom"))
				roomRoom(inventory);
			else
			{
				CANTGO
				VRES
			}
		}
		else
		{
			CANTDO
			VRES
		}
	}
}

void roomCar(Inv *inventory)
{
	VARS
	Bool dad_watching = TRUE, airbag_on = FALSE, gear = FALSE, grabber = FALSE, unbuckled = FALSE;

	puts("Car");
	typeRoom("You have a hard time moving your limbs because of all of the injuries and broken bones you have sustained. You can see the glovebox, the window crank, the airbag switch, the radio dial glowing against the darkness, the airbag switch and the gear shifter.");

	while (verb == NONE)
	{
		getAction(noun, &verb);

		if (verb == LOOK)
		{
			if (caseCompare(noun, "inventory"))
				printInv(inventory);
			if (caseCompare(noun, "around"))
			{
				typeRoom("You have a hard time moving your limbs because of all of the injuries and broken bones you have sustained. You can reach the glovebox, the window crank, the airbag switch, the radio dial glowing against the darkness and the gear shifter.");
				if (dad_watching == TRUE)
					type("Dad is watching your next move closely", TDEL * 2);
			}
			if (caseCompare(noun, "dad") || caseCompare(noun, "seatbelt") || caseCompare(noun, "dad's"))
				typeRoom("Dad is staring intently. His seatbelt is on. The buckle is slightly out of reach.");
			if (caseCompare(noun, "radio"))
				typeRoom("The light of the radio pierces through the darkness.");
			if (caseCompare(noun, "gear") || caseCompare(noun, "shifter"))
			{
				if (gear == FALSE)
					typeRoom("Dad is currently cruising along at the highest gear.");
				else if (gear == TRUE)
					typeRoom("Dad is currently cruising along at 90 mph.");
			}
			if (caseCompare(noun, "window") || caseCompare(noun, "crank"))
				typeRoom("The window is currently rolled all the way up. Your right arm is broken so you can't turn the crank.");
			if (caseCompare(noun, "glovebox"))
				typeRoom("The glovebox is open a crack. You can see a red grabbing arm inside, but you aren't able to reach it without a little extra length.");
			if (caseCompare(noun, "airbag") || caseCompare(noun, "switch") || caseCompare(noun, "button") || caseCompare(noun, "air") || caseCompare(noun, "switch"))
			{
				if (airbag_on == TRUE)
					typeRoom("The passenger airbag is turned on.");
				else if (airbag_on == FALSE)
					typeRoom("The passenger airbag is currently turned off, but the button is out of reach. Dad hasn't had a passenger in 15 years.");
			}
			VRES
		}
		//Win condition for the level. Shifting gears while you will be saved and dad will be killed
		else if ((verb == SHIFT || verb == SWITCH) && airbag_on == TRUE && unbuckled == TRUE)
		{
			if (caseCompare(noun, "gear") || caseCompare(noun, "gears") || caseCompare(noun, "shifter"))
			{
				CLEAR
				return;
			}
			else
			{
				CANTDO
			}
			VRES
		}
		//Turn on the radio to distract dad
		else if ((verb == SWITCH || verb == USE) && dad_watching == TRUE && caseCompare(noun, "radio"))
		{
			typeNoBreak("You turn the radio on.", TDEL);
			typeNoBreak("\"The cat's in the cradle and the silver spoon... Little boy blue and the man in the moon\"", TDEL * 2);
			type("echoes through the car.", TDEL);
			type("Dad slowly turns his head to look at the radio.", TDEL);
			dad_watching = FALSE;
			VRES
		}
		//Open glovebox with the crank
		else if (verb == OPEN && gear == TRUE && grabber == FALSE)
		{
			if (caseCompare(noun, "glovebox"))
			{
				typeRoom("You use the crank to leverage open the glovebox. The red grabber falls near your feet. Unfortunately, so does a brick. It lands on your left foot, reshattering the bones. You pick up the grabber, wincing through the pain.");
				insertAtFront(inventory, makeItem(FALSE, "grabber", USE));
				grabber = TRUE;
			}
			else
			{
				CANTDO
			}
			VRES
		}
		//If you have the grabber you can unbuckle dad's seatbelt
		else if (verb == UNBUCKLE)
		{
			if (caseCompare(noun, "dad") || caseCompare(noun, "dad's") || caseCompare(noun, "seatbelt"))
			{
				if (grabber == TRUE)
				{
					typeRoom("You use the grabber to reach out and unbuckle Dad's seatbelt. He is too engrossed in the radio to notice.");
					unbuckled = TRUE;
				}
				else if (grabber == FALSE)
					typeRoom("Dad's seatbelt buckle is just out of reach.");
			}
			else
				CANTDO
			VRES
		}
		//You can shift gears twice. Once here to get the crank and once at the end
		else if ((verb == SHIFT || verb == SWITCH) && gear == FALSE)
		{
			if (caseCompare(noun, "gear") || caseCompare(noun, "gears") || caseCompare(noun, "shifter"))
			{
				if (dad_watching == FALSE)
				{
					typeRoom("You shift the gear down. The car suddenly drops to 90 mph, shaking the entire chasis. The window crank falls onto the floor, where you pick it up with your working arm. The gear shifter could be changed again but it would be very dangerous.");
					insertAtFront(inventory, makeItem(FALSE, "crank", USE));
					gear = TRUE;
				}
				else
				{
					typeRoom("Dad's piercing stare stops you in your tracks.");
				}
			}
			else
			{
				CANTDO
			}
			VRES
		}
		//Using grabber to turn on airbag
		else if (verb == SWITCH && airbag_on == FALSE)
		{
			if (caseCompare(noun, "airbag") || caseCompare(noun, "switch") || caseCompare(noun, "button") || caseCompare(noun, "air") || caseCompare(noun, "switch"))
			{
				if (grabber == TRUE)
				{
					typeRoom("You press the airbag button with the grabber. The passenger airbag starts whirring and springs to life. It is ready for anything.");
					airbag_on = TRUE;
				}
				else if (grabber == FALSE)
				{
					typeRoom("You can't quite reach the airbag button.");
				}
			}
			else
			{
				CANTDO
			}
			VRES
		}
		//If all of the conditions for shifting gears aren't met yet
		else if ((verb == SHIFT || verb == SWITCH) && gear == TRUE && (airbag_on == FALSE || unbuckled == FALSE))
		{
			if (caseCompare(noun, "gear") || caseCompare(noun, "gears") || caseCompare(noun, "shifter"))
			{
				if (airbag_on == FALSE)
					typeRoom("You could change the gear to park, but this would kill you without the airbag on.");
				if (unbuckled == FALSE)
					typeRoom("Dad's seatbelt is still buckled.");
			}
			else
			{
				CANTDO
			}
			VRES
		}
		else
		{
			CANTDO
			VRES
		}
	}
}

void roomLake(Inv *inventory)
{
	typeRoom("Lake");
	type("You can hear a squelching noise behind you. Dad isn't dead. It was foolish to believe otherwise.", TDEL * 1.5);
	type("\"YOU BETTER FISH, BOY\", Dad bellows. You hear a clicking noise, as if he were fumbling with the trigger of a pistol.", TDEL * 1.5);
	type("You can only turn your head a few degrees. Enough to see a fishing pole. You throw up in your mouth and swallow some mud. It takes a few tries, but you grab the pole with your broken arm.", TDEL * 1.5);

	getFishing();
	type("Your limp arm can barely move the rod.", TDEL * 1.5);
	type("\"I NEVER TAUGHT ANY SON OF MINE TO FISH LIKE THAT!\" More clicking noises come from behind you.", TDEL * 1.5);

	getFishing();
	type("You cry out as you try to cast the line again. More unimaginable pain shoots up your arm.", TDEL * 1.5);
	type("More squelching accompanies a shadow approaching from behind.", TDEL * 2);

	getFishing();
	type("Your arm makes a cracking noise, but you can hear the line splash a few feet away.", TDEL * 1.5);
	type("\"NOW THAT'S WHAT I'M TALKING ABOUT BOY\"", TDEL * 2);
	
	getFishing();
	type("There's a small tug on the rod. You pray that you didn't just imagine it.", TDEL * 2);
	type("You feel the familiar sensation of a metal gun barrel pressing against your temple.", TDEL * 3);
	type("\"FISH\"", TDEL * 5);

	getFishing();
	type("As you try to reel the line in, your arm snaps again. It falls limp as you lose all feeling in it.", TDEL * 2);
	type("You begin crying. \"But Dad... I can't...\"", TDEL * 3);
	typeNoBreak("Your Dad's hot breath blasts into your ear,", TDEL * 2);
	type("\"FISH\"", TDEL * 5);

	getFishing();
	type("...", TDEL * 10);
	getFishing();
	type("...", TDEL * 10);
	getFishing();

	type("Your dad's boot stomps onto your back, as he grabs your arm with his.", TDEL * 2);
	type("\"I ONLY EVER ASKED ONE THING OF YOU, BOY...\"", TDEL * 3);
	type("He begins pulling your arm back and forth in a sawing motion, reeling in the line.", TDEL* 2);
	type("\"AND YOU CAN'T EVEN DO THAT.\"", TDEL * 2);
	type("For a brief second, your arm regains feeling.", TDEL * 2);
	type("You gather all of your energy.", TDEL * 2);

	getFishing();
	type("It's enough", TDEL * 2);
	type("\"YOU CAN'T EVEN CATCH ONE LOUSY\"", TDEL * 4);
	type("Your dad stops as the end of the pole pierces his eye.", TDEL * 2);
	type("His lifeless body crashes into the mud and the water begins pulling him slowly away from the shore.", TDEL * 3);
	type("You begin sobbing. He's finally dead after these 15 years of torment.", TDEL * 5);
	type("There's only one thing left to do. You can see the gun floating a few feet away in the water.", TDEL * 5);
	type("One last time.", TDEL * 5);

	getFishing();
	CLEAR
	return;
}

void credits(void)
{
	_sleep(5000);
	for (int i = 0; i < 40; i++)
	{
		puts("");
		_sleep(30);
	}
	printf("\t\t\t\t\t\tCreated by Ryan Manny");
	for (int i = 0; i < 20; i++)
	{
		puts("");
		_sleep(100);
	}
	printf("\t\t\t\t\t\tThanks for playing.");
	for (int i = 0; i < 50; i++)
	{
		puts("");
		_sleep(100);
	}
}