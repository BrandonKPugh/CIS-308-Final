#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "sudoku.h"
#include "sudoku.c"

struct messageResponse {
        char * response;
        int respond;
};

typedef struct messageResponse messageResponse;

struct args {
        int count;
        char ** words;
};

typedef struct args args;

args * parseCommand(const char * content);

messageResponse * getOutput(messageResponse * output, args * command);

messageResponse * frameworkMessageReceived(const char * content)
{
	messageResponse * output = malloc(sizeof(messageResponse *)); //malloc(sizeof(messageResponse));
	output->respond = 1;

	if(!((*(content) == 'c' || (*(content) == 'C')) && *(content + 1) == ' '))
	{
		output->respond = 0;
		return output;
	}

	printf("content right now: %s\n", content);
	int len = strlen(content);
	char * parsed = malloc((len + 1) * sizeof(char *));
	int pointer = 0;
	int words = 0;
	for(int i = 0; i < len; i++)
	{
		if(isalnum(*(content + i)))
		{
			*(parsed + pointer) = tolower(*(content + i));
			pointer++;
		}
		else if(i > 0  && !isalnum(*(content + (i - 1))))
		{

		}
		else
		{
			*(parsed + pointer) = '\0';
			pointer++;
			words++;
		}
	}
	*(parsed + pointer) = '\0';
	words++;

	args * command = malloc(sizeof(args*));
	command->count = words;
	pointer = 0;
	command->words = malloc(words * sizeof(args*));
	printf("Wordcount = %i\n", words);
	printf("Open forloop\n");
	for(int i = 0; i < words; i++)
	{
		printf("Starting word %i.\n", i);
		*(command->words + i) = malloc(sizeof(char *));
		printf("Allocated space for new word\n");
		strcpy(*(command->words + i), parsed + pointer);
		printf("Adding this word: %s\n", parsed + pointer);
		pointer += strlen(parsed + pointer) + 1;
	}
	printf("Close forloop. command->words 1 is: %s\n", *(command->words));

	if(strlen(*(command->words + command->count - 1)) == 0)
		command->count--;

	free(parsed);
	output->response = malloc(sizeof(char *));
	/*
	// For Bug testing.
	for(int i = 0; i < command->count; i++)
	{
		char * header = malloc(sizeof(char *));
		snprintf(header, 1024, "\nArgument %i:\t", i);
		if(i == 0)
			strcpy(output->response, header);
		else
			strcat(output->response, header);
		strcat(output->response, *(command->words + i));
	}
	*/

	//printf("Calling getOutput\n");
	output = getOutput(output, command);
	//printf("Back from getOutput\n");
	free(command);
	printf("Outputting the following response with the C Library:\n");
	printf("%s\n", output->response);
	return output;
}

char * RPS (char userChoice){
    	if (userChoice == NULL)
      		{return "I Have Already Won, Human.";}
   	int r = rand () % 3 + 1;
    	char *result = "";
    	if(userChoice == 'r')
	{
		if (r == 1)
  			result = "I choose Rock. Tie.";
		else if (r == 2)
  			result = "I choose Paper. Bot Wins, Puny Human.";
		else
  			result = "I choose Scissors. Player Wins... For Now.";
	}
	else if (userChoice == 'p')
	{
		if (r == 1)
			result = "I choose Rock. Fleshy Human Wins Once";
		else if (r == 2)
			result = "I choose Paper. Tie";
		else
			result = "I choose Scissors. Robot Victory is Assured";
      	}
	else if(userChoice == 's')
	{
		if (r == 1)
  			result = "I choose Rock. Silicon Mind Is Superior To Organics";
		else if (r == 2)
  			result = "I choose Paper. Enjoy Your Victory While It Lasts";
		else
  			result = "I choose Scissors. Tie";
	}
	else
	{
		result = "Please Choose Rock, Paper, or Scissors.";
      	}
    	return result;
}

messageResponse * getOutput(messageResponse * output, args * command)
{
	char * ptr = "\0\0\0\0";
	strcpy(output->response, ptr);
	printf("command->words = %s\n", *(command->words + 1));
	if(strcmp(*(command->words + 1), "test") == 0)
	{
		output->respond = 1;
		output->response = "I see your test and raise you TWO tests \"test test\"";
	}
	else if(strcmp(*(command->words + 1), "welcome") == 0)
        {
                output->respond = 1;
                output->response = "Welcome to the server! For questions, type \"c help\"";
        }
	else if(strcmp(*(command->words + 1), "rps") == 0)
        {
                output->respond = 1;
		printf("letter: %c\n", *(*(command->words + 2)));
                output->response = RPS(*(*(command->words + 2)));
        }
	else if(strcmp(*(command->words + 1), "roll") == 0)
        {
		int in = atoi(*(command->words + 2));
		srand(time(0));
		int random=rand()%in+1;
		char * toOut = malloc(sizeof(char *));
		printf("You rolled a %d\n", random);
		snprintf(toOut, 1024, "You rolled a %d",random);
		printf("toOut set\n");
		strcat(output->response, toOut);
		output->respond = 1;
        }
	else if(strcmp(*(command->words + 1), "help") == 0)
	{
		output->respond = 1;
		output->response = "Help\n\tLists all commands\nWelcome\n\tShows the welcome message for new users\nRps <choice>\n\tChoice is R P or S for game of Rock Paper Scissors\nRoll <number>\n\tRolls a dice with <number> sides\nSudoku <command>\n\tCommands: Start,Clear,Solve,X Y #\n\tSudoku game\n";
	}
	else if (strcmp(*(command->words + 1), "sudoku") == 0)
	{

	    if (command->count == 3)
	    {
	        output->respond = 1;
	        if (strcmp(*(command->words + 2), "new") == 0 || strcmp(*(command->words + 2), "start") == 0)
	        {
	            sudokuNew();
	            FILE * file;
	            file = fopen("puzzle.txt", "r");
	            //char buff[500];
		    //fgets(buff, 500, file);
		    //strcpy(output->response, buff);
		    char temporary[500];
		    //output->response = malloc(sizeof(char *));
		    while(fgets(temporary, 500, file))
		    {
			strcat(output->response, temporary);
		    }
	            //fclose(file);
	        }
	        else if (strcmp(*(command->words + 2), "solve") == 0)
	        {
	            sudokuSolve();
	            FILE * file;
	            file = fopen("puzzle.txt", "r");
	            //fgets(output->response, 500, file);
		    char temporary[500];
                    //output->response = "";
                    while(fgets(temporary, 500, file))
                    {
                        strcat(output->response, temporary);
                    }

	            //fclose(file);
	        }
	        else if (strcmp(*(command->words + 2), "clear") == 0)
	        {
	            sudokuClear();
	            FILE * file;
	            file = fopen("puzzle.txt", "r");
	            //fgets(output->response, 500, file);
		    char temporary[500];
                    //output->response = "";
                    while(fgets(temporary, 500, file))
                    {
                        strcat(output->response, temporary);
                    }

	            //fclose(file);
	        }
	        else
	            output->response = "Unknown sudoku command. Please check your arguments";
	    }
	    else if (command->count == 6 && strcmp(*(command->words + 2), "edit") == 0)
	    {
printf("0\n");
	        if (atoi(*(command->words + 3)) == 0 || atoi(*(command->words + 4)) == 0 || atoi(*(command->words + 5)) == 0)
	        {
	            output->respond = 1;
	            output->response = "Error: \"edit\" must be followed by 3 single-digit numbers.";
	        }
	        else
	        {
		    printf("1\n");
	            if (sudokuEdit(atoi(*(command->words + 3)), atoi(*(command->words + 4)), atoi(*(command->words + 5))) == 0)
	            {
			printf("2\n");
	                output->respond = 1;
	                FILE * file;
	                file = fopen("puzzle.txt", "r");
	                //fgets(output->response, 500, file);
		 	char temporary[500];
                        //output->response = "";
                        while(fgets(temporary, 500, file))
                        {
                            strcat(output->response, temporary);
                        }
	                //fclose(file);
	            }
	            else
	            {              
	                FILE * file;
	                file = fopen("error.txt", "r");
	                //fgets(output->response, 500, file);
	                char temporary[500];
                        //output->response = "";
                        while(fgets(temporary, 500, file))
                        {
                            strcat(output->response, temporary);
                        }

			//fclose(file);
	            }
	        }
	    }
	    else if (command->count == 2)
	    {
	        FILE * file;
	        file = fopen("puzzle.txt", "r");
	        //fgets(output->response, 500, file);
	        char temporary[500];
                //output->response = "";
                while(fgets(temporary, 500, file))
                {
                    strcat(output->response, temporary);
                }
		//fclose(file);
	        output->respond = 1;
	    }
	    else
	    {
	        output->respond = 1;
	        output->response = "Unknown sudoku command. Please check your arguments.";
	    }
	}
	else
	{
		output->respond = 1;
		output->response = "Use \"c <command> <args>\"";
	}
	return output;
}
