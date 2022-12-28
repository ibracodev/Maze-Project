#include <iostream>
#include "Maze.h"
#include "Cell.h"
using namespace std;

Maze loadMaze(bool & loaded, bool & startSet, bool & goalSet);
int main()
{
    bool loaded = false, solved = false, flag = true, goalSet = false, startSet = false;
    int choice;
    Maze maze; //maze object
    Maze backupMaze; //backup maze to prevent overlapping of algorithms
    int Srow, Scol, Grow, Gcol; //rows and cols of start and goal
    while (flag)
    {
        cout << "1) Load Maze\n";
        cout << "2) Display Maze\n";
        cout << "3) Set start\n";
        cout << "4) Set goal\n";
        cout << "5) Find path (DFS)\n";
        cout << "6) Find path (BFS)\n";
        cout << "7) Find path (DA)\n";
        cout << "8) Display Path\n";
        cout << "9) Exit\n>> ";
        do { cin >> choice; } while (choice < 0 || choice > 9);
        switch (choice) {
            case 1:
                solved = false; goalSet = false; startSet = false; //initializing all bools to false
                maze = loadMaze(loaded, startSet, goalSet);
                backupMaze = maze; //Backup maze
                break;
            case 2:
                if (loaded) backupMaze.displayMaze();
                else cout << "Please load a maze file!\n"; //Error message if user chooses to display maze before loading it
                break;
                
            case 3:
                if (loaded)
                {
                    cout << "Please enter start coordinates starting from 1 (row, column): ";
                    //Behind the scenes uses indices starting from 0, but starting from 1 is more user friendly.
                    //Therefore, -= 1 is applied to the user's entry to allow for easier programming, but good UI
                    cin >> Srow;
                    Srow -= 1;
                    cin >> Scol;
                    Scol -= 1;


                    if (Srow < 0 || Scol < 0 || Srow >= maze.getWidth() || Scol >= maze.getHeight()) //Prevents invalid coordinates
                    {
                        cout << "Invalid start coordinates!\n"; //Error message for invalid coordinates
                    }
                    else
                    {
                        solved = false;
                        startSet = true;
                        if (solved) maze = backupMaze; //Resets the maze if it has been solved
                        maze.setStart(Srow, Scol); //setting start co-ordinates
                        backupMaze = maze; //Backs up maze
                        cout << "Start coordinates are now set!\n";
                    }
                }
                else                {
                    cout << "Please load a maze file first!\n"; //Error message setting coordinates before loading a maze
                }
                break;
            case 4:
                if (loaded)
                {
                    cout << "Please enter goal coordinates starting from 1 (row, column): ";
                    cin >> Grow; Grow -= 1;
                    cin >> Gcol; Gcol -= 1;

                    if (Grow < 0 || Gcol < 0 || Grow >= maze.getWidth() || Gcol >= maze.getHeight())
                    {
                        cout << "Invalid goal coordinates!\n"; //Error message
                    }
                    else
                    {
                        solved = false;
                        goalSet = true;
                        if (solved) maze = backupMaze; //Resets the maze if its solved
                        maze.setGoal(Grow, Gcol); //Sets new goal for maze
                        backupMaze = maze; //Backs up maze
                        cout << "Goal coordinates set successfully!\n"; //Success Message
                    }
                }
                else
                {
                    cout << "Please load a maze file first!\n"; //Error message if setting goal coordinates before loading a maze
                }
                break;
            case 5:
                if (loaded && startSet && goalSet)
                {
                    if (backupMaze != maze) //Resets maze if it has been solved
                    {
                    maze = backupMaze; //Calls DFS function
                    
                    }
                    solved = maze.DFS();
                }
                else
                {
                    cout << "Please make sure to load, set a start and a goal!\n";
                }
                break;
            case 6:
                if (loaded && startSet && goalSet){
                    if (backupMaze != maze) //Resets maze if it has already been solved
                    {
                        maze = backupMaze;
                    }
                solved = maze.BFS(); //Calls BFS function
                }
                else
                {
                cout << "Please make sure to load, set a start and a goal!\n";
                }
                break;
            case 7://finding with DA
                if (loaded && startSet && goalSet){
                    
                if (backupMaze != maze) //Resets maze if it has already been solved
                {
                    maze = backupMaze;
                }
                solved = maze.DA(); //Calls DA function
                }
                else
                {
                cout << "Please make sure to load, set a start and a goal!\n";
                }
                break;
            case 8:
                if (solved) maze.displayMaze(); //Displays solution if there exists one
                else cout << "No solution created yet! Use a BFS, DFS or DA search!\n"; //Displays error message if there's no solution
                break;
            case 9:
                flag = false;
                break;
            default:
                cout << "Wrong choice!\n";
                break;
        }
    }
    cout << "Thank You for using this program!\n";
    return 0;
}


Maze loadMaze(bool & loaded, bool & startSet, bool & goalSet){
    
    int Xcurr, Ycurr; //coodinates for cell position
    Cell newCell; //creating a cell then adding cell into a vector
    vector<Cell> cellVector; //will be filled with cells which are in maze
    
    ifstream in("/Users/ibrahim/Desktop/Lab7/maze.txt"); //Opens text file
    
    if (!in.fail()) {
        //3 strings since each cell consists of 3 lines.
        char str1[100], str2[100], str3[100];
        in.getline(str1, 100);
        in.getline(str2, 100);
        in.getline(str3, 100);
        int line = 1, cell = 1; //Counters for cells and lines
        while (!in.eof()) //While the file didn't reach its end
        {
            cell = 1;
            int i = 0; //Cell row index (For string 1)
            bool top, down, right, left;
            top = down = right = left = false; //Default value for top, down, right, left is false (No walls)
            int j = 0; //Cell row index (For string 2)
            int k = 1; //Cell row index (For string 3)
            while (i < strlen(str1) - 1) //Keeps looping throw the row until all cells have been read properly
            {
                top = down = right = left = false; //Default value for top, down, right, left is false
                if (str1[i] == '+')
                     i++; //Checks for '+' which indicates a new cell then increments i by 1 (Moving it to the cell's top wall to check it)
                if (str1[i] == '-')
                    top = true;
                    else if (str1[i] == ' ')
                            top = false;
                
                i = i + 3; //Checks if there is a wall above. Then increment i by 3 (Moving it to the next cell's '+')
                
                if (str2[j] == '|')
                        left = true;
                    else if (str2[j] == ' ')
                            left = false;
                
                j = j + 4; //Checks if there is a wall on the left. Then increments j by 4 (Moving it to this cell's right wall / Next cell's left wall)
                
                
                char status = str2[j - 2]; //Gets status of cell
                int cost =0;
                
                if (status == 'S') //If the cell is a start
                {
                    startSet = true;
                }
                else if (status == 'G') //If the cell is a goal
                {
                    goalSet = true;
                }
                else if (status == '1'){
                    cost =1;
                    cout << cost << endl;
                }
                else if (status == '2'){
                    cost =2;
                    cout << cost << endl;
                }
                else if (status == '3'){
                    cost =3;
                    cout << cost << endl;
                }
                
                if (str2[j] == '|')
                    right = true;
                    else if (str2[j] == ' ')
                        right = false; //Checks if there is a wall on the right of the current cell
                
                if (str3[k] == ' ')
                    down = false;
                      else if (str3[k] == '-')
                          down = true; k = k + 4; //Checks if there is a wall on the bottom. Then increments k by 4 (Moving it to the next cell's bottom wall)
               
                cell++; //Increments number of cells existing a row
                Xcurr = cell - 2; //column index of new cell
                Ycurr = line - 1; //row index of new cell
                Cell newCell(Ycurr, Xcurr, top, down, left, right, status, cost); //Creation of cell object to be inserted to cellVector
                cellVector.push_back(newCell); //Push a new cell into the vector of cells
            }
            strcpy(str1, str3);
            in.getline(str2, 100); //Read body of new row of cells normally
            in.getline(str3, 100); //Read bottom of new row of cells normally
            line++; //Increments number of rows of the maze
    }
        cell = 1;
        int i = 0;
        bool top, down, right, left;
        top = down = right = left = false;
        int j = 0, k = 1;
        
        while (i < strlen(str1) - 1)
        {
            top = down = right = left = false;
            if (str1[i] == '+') i++; //new cell
            if (str1[i] == '-')top = true; else if (str1[i] == ' ')top = false;   i = i + 3;
            if (str2[j] == '|') left = true; else if (str2[j] == ' ')left = false; j = j + 4;
            char status = str2[j - 2];
            if (status == 'S')
            {
                startSet = true;
            }
            else if (status == 'G')
            {
                goalSet = true;
            }
            if (str2[j] == '|')
                right = true;
               else if (str2[j] == ' ')
                   right = false;
           
            if (str3[k] == ' ') down = false;
                else if (str3[k] == '-')
                    down = true;
            
            k = k + 4;
            cell++;
            Xcurr = cell - 2;
            Ycurr = line - 1;
            Cell newCell(Ycurr, Xcurr, top, down, left, right, status);
            cellVector.push_back(newCell);
        }
      
        Maze maze(Ycurr + 1, Xcurr + 1); //Creates object of maze
        
        for (int i = 0; i < cellVector.size(); i++)
        {
            maze.insertCell(cellVector.at(i)); //Inserts each cell in the vector into the maze
        }
        
        
        cout << "Maze loaded successfully!\n";
        loaded = true;
        return maze;
    }
    else
    {
        cout << "Failed to open maze file!\n";
        Maze failedMaze;
        return failedMaze; //returning empty maze as the function returns maze
        
    }
}
