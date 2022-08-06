/////////////////////////////////////////////////////////////////////////////////////
// 
// 
// 
// This program implements an algorithm to solve a maze. The program is already
// given a 2D array of 10 by 16 characters which represents the entire maze.
// The “mouse” in the maze is represented as the character ‘ * ’, the “walls” of 
// the maze are represented as the character ‘O’, and any open spaces are represented 
// with the character  ‘ ‘.The ‘* ’ starts in row 1, column 1 of the 2d maze and must 
// reach position row 8, 13 of the maze. To do this, it follows this path: go right first,
// go down, go left, go up. If it can't go right then it will go left, if it can't go down
// it will go left, and so on. If the “mouse” got stuck, it would backtrackand 
// mark the position it visited with the letter ‘D’.
// 
// 
// 
// ////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <stdio.h>
#include <stack>

// Keeps track of the position (row then column) the * character takes as it follows the maze

struct Position
{
    int row;
    int column;
};

int main() 
{
    char maze[10][16] = { "OOOOOOOOOOOOOOO",  // Maze Layout
                          "O O O OOO O  OO",
                          "O             O",
                          "O O OOOOOOOO  O",
                          "O O   O   O   O",
                          "O OOO  OO  OOOO",
                          "O    O O    OOO",
                          "OO O O O OO  OO",
                          "OO   O   O    O",
                          "OOOOOOOOOOOOOOO" };

    char Mouse = '*'; // Mouse

    Position CurrentLocation{}; // Location of the mouse

    // Starting Position for the mouse (row 1,column 1)

    CurrentLocation.row = 1;
    CurrentLocation.column = 1;
    maze[CurrentLocation.row][CurrentLocation.column] = Mouse;

    // Printing out the 2D maze (Before the mouse completes it)

    int row, column;

    printf("Maze Before: \n");
    printf("-----------\n");
    for (row = 0; row < 10;row++)
    {
        for (column = 0; column < 15;column++)
        {
            printf("%c", maze[row][column]);
        }
        printf("\n");
    }

    std::stack<Position> PositionVisited;

    bool CompletedWithMaze = false; 

    
    while (!CompletedWithMaze) // While The maze is not completed
    {

        if (maze[CurrentLocation.row][CurrentLocation.column + 1] == ' ')  // Go right (if possible)
        {   
            PositionVisited.push(CurrentLocation);
            maze[CurrentLocation.row][CurrentLocation.column] = Mouse;
            CurrentLocation.column++;
        }

        else if (maze[CurrentLocation.row + 1][CurrentLocation.column] == ' ') // Go down (if possible)
        {   
            PositionVisited.push(CurrentLocation);
            maze[CurrentLocation.row][CurrentLocation.column] = Mouse;
            CurrentLocation.row++;
        }

        else if (maze[CurrentLocation.row][CurrentLocation.column - 1] == ' ') // Go back (if possible)
        {   
            PositionVisited.push(CurrentLocation);
            maze[CurrentLocation.row][CurrentLocation.column] = Mouse;
            CurrentLocation.column--;
        }

        else if (maze[CurrentLocation.row - 1][CurrentLocation.column] == ' ') // Go up (if possible)
        {   
            PositionVisited.push(CurrentLocation);
            maze[CurrentLocation.row][CurrentLocation.column] = Mouse;
            CurrentLocation.row--;
        }

        // If we there is no other way to go

        else if (!PositionVisited.empty()) // If there is no other way to go
        {
            // If it completes the maze, we do not want the final position of the maze
            // to be makred with the letter 'D'(it has nowhere to go technically, but it completed the maze)

            if (CurrentLocation.row == 8 && CurrentLocation.column == 13)
            {
                maze[CurrentLocation.row][CurrentLocation.column] = Mouse;
                CompletedWithMaze = true; // Maze Completed
            }

            else // Reaches a spot where it cannot move (the mouse got stuck)
            {
                maze[CurrentLocation.row][CurrentLocation.column] = 'D';  // as you pop mark the [row][column] with the letter 'D' (A dead end for the mouse)
                CurrentLocation = PositionVisited.top();
                PositionVisited.pop(); // backtrack by popping the stack 
            }
        } 
    }


   // Printing out the path the mouse took of the maze after 

    printf("\n");
    printf("Maze After: \n");
    printf("------------\n");
    for (row = 0; row < 10;row++)
    {
        for (column = 0; column < 15;column++)
        {
            printf("%c", maze[row][column]);
        }
        printf("\n");
    }
    return 0;
}
