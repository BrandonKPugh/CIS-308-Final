#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sudoku.h"
 
// Make a new sudoku game
int sudokuNew()
{
    // Random seed
    srand(time(0));
 
    FILE * read;
    FILE * write;
    read = fopen("pull list.txt", "r");
    write = fopen("current.txt", "w+");
 
    // Open the pull list and move the reader down to the right puzzle
    char buff[100];
    char buff2[100];
    int i;
    i = rand() % 50;
    for (int j = 0; j < i; j++)
    {
        fgets(buff, 100, read);
        fgets(buff, 100, read);
    }
    fgets(buff, 100, read);
    fgets(buff2, 100, read);
 
    // Write the puzzle to the current puzzle text file
    fprintf(write, "%s%s%s", buff, buff2, buff);
 
    // Close the files and update the output
    fclose(read);
    fclose(write);
    puzzleToImage();
 
    return 0;
}
 
// Add or remove a value in a cell of the current puzzle
int sudokuEdit(int x, int y, int value)
{
    char c = value + '0';
    int index = 9 * x + y - 10;
 
    FILE * read;
    FILE * write;
    char line1[100];
    char line2[100];
    char line3[100];
 
    // Read in the 3 lines of the current puzzle
    read = fopen("current.txt", "r");
    fgets(line1, 100, read);
    fgets(line2, 100, read);
    fgets(line3, 100, read);
    fclose(read);
 
    // check that the space being edited isn't a given
    if (line1[index] != '.')
    {
        // Save an error message to error.txt?
        write = fopen("error.txt", "w+");
        fprintf(write, "Cannot change a given value.");
        fclose(write);
        return 1;
    }
 
    // Reopen the current puzzle txt file and rewrite the first two lines
    write = fopen("current.txt", "w+");
    fprintf(write, "%s\n%s\n", line1, line2);
 
    // Update the puzzle (line 3) and write it, then close the file.
    line3[index] = c;
    fprintf(write, "%s", line3);
    fclose(write);
 
    puzzleToImage();
 
    return 0;
}
 
// Solve the current puzzle
int sudokuSolve()
{
    sudokuAuto(0);
    return 0;
}
 
// Clear the current puzzle to the original state
int sudokuClear()
{
    sudokuAuto(1);
    return 0;
}
 
// Either solve or clear the puzzle. The previous two functions are so close.
int sudokuAuto(int solve)
{
    FILE * read;
    FILE * write;
    char line1[100];
    char line2[100];
 
    read = fopen("current.txt", "r");
    fgets(line1, 100, read);
    fgets(line2, 100, read);
    fclose(read);
 
    write = fopen("current.txt", "w+");
    fprintf(write, "%s\n%s\n%s", line1, line2, solve == 0 ? line2 : line1);
    fclose(write);
    puzzleToImage();
 
    return 0;
}
 
// Convert a sudoku puzzle string into an image (png or ascii, still haven't decided)
int puzzleToImage()
{
    FILE * read;
    FILE * write;
    char buff[100];
 
    read = fopen("current.txt", "r");
    fgets(buff, 100, read);
    fgets(buff, 100, read);
    fgets(buff, 100, read);
    fclose(read);
 
    for (int i = 0; i < 81; i++)
    {
        if (buff[i] == '.')
            buff[i] = '.';
    }
 
    write = fopen("puzzle.txt", "w+");
    fprintf(write, "```   1 2 3   4 5 6   7 8 9\n +-------+-------+-------+\n");
    for (int i = 0; i < 3; i++)
    {
        fprintf(write, "%d| %c %c %c | %c %c %c | %c %c %c |\n", i + 1, buff[i * 9], buff[i * 9 + 1], buff[i * 9 + 2], buff[i * 9 + 3], buff[i * 9 + 4], buff[i * 9 + 5], buff[i * 9 + 6], buff[i * 9 + 7], buff[i * 9 + 8]);
    }
    fprintf(write, " +-------+-------+-------+\n");
 
    for (int i = 3; i < 6; i++)
    {
        fprintf(write, "%d| %c %c %c | %c %c %c | %c %c %c |\n", i + 1, buff[i * 9], buff[i * 9 + 1], buff[i * 9 + 2], buff[i * 9 + 3], buff[i * 9 + 4], buff[i * 9 + 5], buff[i * 9 + 6], buff[i * 9 + 7], buff[i * 9 + 8]);
    }
    fprintf(write, " +-------+-------+-------+\n");
 
    for (int i = 6; i < 9; i++)
    {
        fprintf(write, "%d| %c %c %c | %c %c %c | %c %c %c |\n", i + 1, buff[i * 9], buff[i * 9 + 1], buff[i * 9 + 2], buff[i * 9 + 3], buff[i * 9 + 4], buff[i * 9 + 5], buff[i * 9 + 6], buff[i * 9 + 7], buff[i * 9 + 8]);
    }
    fprintf(write, " +-------+-------+-------+```");
    fclose(write);
 
    return 0;
}
