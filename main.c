#include <stdio.h>
#include <stdlib.h>
#define X 'X'
#define O 'O'
#define WAIT 4

struct node
{
    int position;
    char character;
    struct node *next;
}*start = NULL;

struct node *new_node = NULL, *current_node = NULL;


void printWelcomeMessage()
{
    system("clear");
    printf("'########:'####::'######:::::'########::::'###:::::'######:::::'########::'#######::'########:\n");
    printf("... ##..::. ##::'##... ##::::... ##..::::'## ##:::'##... ##::::... ##..::'##.... ##: ##.....::\n");
    printf("::: ##::::: ##:: ##:::..:::::::: ##:::::'##:. ##:: ##:::..:::::::: ##:::: ##:::: ##: ##:::::::\n");
    printf("::: ##::::: ##:: ##::::::::::::: ##::::'##:::. ##: ##::::::::::::: ##:::: ##:::: ##: ######:::\n");
    printf("::: ##::::: ##:: ##::::::::::::: ##:::: #########: ##::::::::::::: ##:::: ##:::: ##: ##...::::\n");
    printf("::: ##::::: ##:: ##::: ##::::::: ##:::: ##.... ##: ##::: ##::::::: ##:::: ##:::: ##: ##:::::::\n");
    printf("::: ##::::'####:. ######:::::::: ##:::: ##:::: ##:. ######:::::::: ##::::. #######:: ########:\n");
    printf(":::..:::::....:::......:::::::::..:::::..:::::..:::......:::::::::..::::::.......:::........::\n");
    printf("\n");
    printf("--------------------\n");
    printf("|    CREATORS:     |\n");
    printf("|   Apoorv Gupta   |\n");
    printf("|  Vishesh Dvivedi |\n");
    printf("--------------------\n");
    printf("\n");
    
}


void insertNode(int position, char character)
{
    new_node = (struct node*)malloc(sizeof(struct node));
    
    if(new_node == NULL)
    {
        printf("Memory cannot be assigned");
    }
    else
    {
        new_node->position = position;
        new_node->character = character;
        new_node->next = NULL;
        
        current_node->next = new_node;
        current_node = new_node;
    }
}

void createBoard()
{
    start = (struct node*)malloc(sizeof(struct node));
    if(start == NULL)
    {
        printf("Memory cannot be allocated");
    }
    else
    {
        start->position = 1;
        start->character = '1';
        start->next = NULL;
        current_node = start;
    }
    
    for (int i=2; i<10; i++)
    {
        insertNode(i, i+'0');
    }
}

int checkPosition(int position)
{
    struct node *current_node = start;
    while (current_node!= NULL)
    {
        if(current_node->position == position)
        {
            if ((current_node->character==X) || (current_node->character==O))
            {
                printf("[ERROR] Position %d is already occupied. Please choose another position.\n\n", position);
                sleep(WAIT);
                return 0;
            }
            else
            {
                return 1;
            }
        }
        current_node = current_node->next;
    }
}

void insertCharacterAtPosition(int position, char character)
{
    struct node *current_node = start;
    while (current_node!= NULL)
    {
        if(current_node->position == position)
        {
            current_node->character = character;
        }
        current_node = current_node->next;
    }
}

int checkWin()
{
    struct node *current_node = start;
    char charList[9] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'};
    
    for(int i=0; i<9; i++)
    {
        charList[i] = current_node->character;
        current_node = current_node->next;
    }
    
    // Checking for horizontal win
    for(int i=0; i<3; i++)
    {
        if ((charList[i] == charList[i+1]) && (charList[i] == charList[i+2]))
        {
            return 1;
        }
        else if ((charList[i] == charList[i+3]) && (charList[i] == charList[i+6]))
        {
            return 1;
        }
    }
    
    // Checking for diagonal victory
    if ((charList[0] == charList[4]) && (charList[4] == charList[9]))
    {
        return 1;
    }
    else if ((charList[2] == charList[4]) && (charList[4] == charList[7]))
    {
        return 1;
    }
    
    return 0;
}

void display()
{
    printWelcomeMessage();
    struct node *current_node;
    if(start == NULL)
    {
        printf("The list is empty");
    }
    else
    {
        int counter=0;
        current_node = start;
        printf("\n");
        while(current_node!=NULL)
        {
            for (int i=0; i<3; i++)
            {
                printf("     |     |     \n");
                for (int j=0; j<3; j++)
                {
                    if (j != 2)
                    {
                        printf("  %c  |", current_node->character);
                        current_node = current_node->next;
                        counter ++;
                    }
                    else
                    {
                        printf("  %c  ", current_node->character);
                        current_node = current_node->next;
                        counter++;
                    }
                }
                if (counter != 9)
                {
                    printf("\n_____|_____|_____\n");
                }
                else
                {
                    printf("\n     |     |     \n");
                }
            }
        }
        printf("\n");
    }
}

void printData()
{
    struct node *current_node = start;
    while (current_node != NULL)
    {
        printf("\nPosition = %d, character = %c\n", current_node->position, current_node->character);
        current_node = current_node->next;
    }
}

void main()
{
    int counter = 0, position=0, num=0;
    char character, choice[100];
    createBoard();
    while (counter < 9)
    {
        display();
        num = counter % 2;
        if (num == 0)
        {
            character = X;
        }
        else
        {
            character = O;
        }
        
        printf("Player %d, enter your choice: ", num+1);
        gets(choice);
        position = atoi(choice);
        if ((position >= 1) && (position <= 9))
        {
            if (checkPosition(position))
            {
                insertCharacterAtPosition(position, character);
                if(checkWin())
                {
                    display();
                    printf("Conguratulations !!! Player %d won !!!", num+1);
                    break;
                }
            }
            else
            {
                continue;
            }
            counter++;
        }
        else
        {
            printf("[ERROR] Invalid input...Please enter a number between 1 and 9\n");
            sleep(WAIT);
        }
    }
    if(counter == 9)
    {
        display();
        printf("The match ended with a DRAW !!! Better Luck Next Time !!!");
    }
}
