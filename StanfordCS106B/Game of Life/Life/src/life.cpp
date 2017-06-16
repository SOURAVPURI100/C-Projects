// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;


class GameOflife{
    Grid<char> grid;
    Grid<char> grid_temp;

public:
    GameOflife(){

    }

 // *** Build the initial generation
    void buildGrid(ifstream &in){

        int noRows, noCols;
        string rows, cols, line;
        try{
            // Get number of rows
              getLine(in, rows);
              getLine(in, cols);

              noRows = stringToInteger(rows);
              noCols = stringToInteger(cols);

              grid.resize(noRows, noCols, false);
              grid_temp.resize(noRows, noCols, false);

              for(int i =0; i<noRows; i++){
                  getLine(in, line);

                  for(int j =0; j<noCols;j++){

                      grid[i][j] = line[j];

                  }

              }

        }
        catch(const exception & e){

            cout<<"Error in building the Grid"<<endl;
        }

    }
// *** Prints the grid
    void printGrid(){
        for(int i =0; i<grid.numRows(); i++){

            for(int j =0; j<grid.numCols();j++){

                cout<<grid[i][j];

            }
            cout<<endl;

        }


    }

    void Generation(string isWrap, int frames){

        if(isWrap.compare("y") == 0)
            WrapGenerate(frames);
        else
            NoWrapGenerate(frames);

    }

    void WrapGenerate(int frames){

        int prev_buffer;
        int next_buffer;
        int total_neigh;
        int rows = grid.numRows();
        int cols = grid.numCols();
        int count  =1;

        while(count <= frames){
            clearConsole();
            count++;
        for(int i =0; i<grid.numRows(); i++){

            prev_buffer = -1; next_buffer = -1;
            \
            for(int j =0; j<grid.numCols(); j++){
                total_neigh = 0;
                // If this is my first column of an= new row
                if(prev_buffer == -1 && next_buffer == -1){
                    prev_buffer = 0; next_buffer = 0;
                    if(grid[(i-1+rows)%rows][(j-1+cols)%cols] == 'X')total_neigh++;
                    if(grid[i][(j-1+cols)%cols] == 'X')total_neigh++;
                    if(grid[(i+1+rows)%rows][(j-1+cols)%cols] == 'X')total_neigh++;

                    if(grid[(i-1+rows)%rows][j] == 'X'){
                        prev_buffer++;
                        total_neigh++;
                    }
                    if(grid[(i+1+rows)%rows][j] == 'X'){
                        prev_buffer++;
                        total_neigh++;
                    }
                    if(grid[(i-1+rows)%rows][(j+1+cols)%cols] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }
                    if(grid[i][(j+1+cols)%cols] == 'X')total_neigh++;

                    if(grid[(i+1+rows)%rows][(j+1+cols)%cols] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }


                }
                else{
                    // Keep the temporary buffer for usage
                    int prev_buffer_temp = prev_buffer;
                    int next_buffer_temp = next_buffer;

                    prev_buffer = 0; next_buffer =0;

                    if(grid[(i-1+rows)%rows][(j+1+cols)%cols] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }
                    if(grid[i][(j+1+cols)%cols] == 'X')total_neigh++;

                    if(grid[(i+1+rows)%rows][(j+1+cols)%cols] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }

                    if(grid[i][(j-1+cols)%cols] == 'X')total_neigh++;

                    total_neigh = total_neigh + prev_buffer_temp + next_buffer_temp;

                    prev_buffer = next_buffer_temp;
                }

//   1. A location that has zero or one neighbors will be empty in the next generation.
//                If a cell was there, it dies.
//   2. A location with two neighbors is stable. If it had a cell, it still contains a cell.
//                If it was empty, it's still empty.
//   3. A location with three neighbors will contain a cell in the next generation.
//                If it was unoccupied before, a new cell is born. If it currently contains a cell, the cell remains.
//   4. A location with four or more neighbors will be empty in the next generation.
//                If there was a cell in that location, it dies of overcrowding.

                if(total_neigh <=1 || total_neigh >=4)grid_temp[i][j]= '-';
                else if(total_neigh == 2) grid_temp[i][j] = grid[i][j];
                else if(total_neigh == 3) grid_temp[i][j] = 'X';
            }
        }

        grid = grid_temp;
        // Print the Grid
        this->printGrid();
        pause(50);

        }

    }

    void NoWrapGenerate(int frames){

        int prev_buffer;
        int next_buffer;
        int total_neigh;
        int count  =1;

        while(count <= frames){
            clearConsole();
            count++;
            for(int i =0; i<grid.numRows(); i++){

                 prev_buffer = -1; next_buffer = -1;
            \
            for(int j =0; j<grid.numCols(); j++){
                total_neigh = 0;
                // If this is my first column of a new row
                if(prev_buffer == -1 && next_buffer == -1){
                    prev_buffer = 0; next_buffer = 0;

                    if(grid.inBounds(i-1,j-1) && grid[i-1][j-1] == 'X')total_neigh++;
                    if(grid.inBounds(i, j-1) && grid[i][j-1] == 'X')total_neigh++;
                    if(grid.inBounds(i+1, j-1) && grid[i+1][j-1] == 'X')total_neigh++;

                    if(grid.inBounds(i-1, j) && grid[i-1][j] == 'X'){
                        prev_buffer++;
                        total_neigh++;
                    }
                    if(grid.inBounds(i+1, j) && grid[i+1][j] == 'X'){
                        prev_buffer++;
                        total_neigh++;
                    }
                    if(grid.inBounds(i-1, j+1) && grid[i-1][j+1] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }
                    if(grid.inBounds(i, j+1) && grid[i][j+1] == 'X')total_neigh++;

                    if(grid.inBounds(i+1, j+1) && grid[i+1][j+1] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }


                }
                else{
                    // Keep the temporary buffer for usage
                    int prev_buffer_temp = prev_buffer;
                    int next_buffer_temp = next_buffer;

                    prev_buffer = 0; next_buffer =0;

                    if(grid.inBounds(i-1, j+1) && grid[i-1][j+1] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }
                    if(grid.inBounds(i, j+1) && grid[i][j+1] == 'X')total_neigh++;

                    if(grid.inBounds(i+1, j+1) && grid[i+1][j+1] == 'X'){
                        next_buffer++;
                        total_neigh++;
                    }

                    if(grid.inBounds(i, j-1) && grid[i][j-1] == 'X')total_neigh++;

                    total_neigh = total_neigh + prev_buffer_temp + next_buffer_temp;

                    prev_buffer = next_buffer_temp;
                }

//   1. A location that has zero or one neighbors will be empty in the next generation.
//                If a cell was there, it dies.
//   2. A location with two neighbors is stable. If it had a cell, it still contains a cell.
//                If it was empty, it's still empty.
//   3. A location with three neighbors will contain a cell in the next generation.
//                If it was unoccupied before, a new cell is born. If it currently contains a cell, the cell remains.
//   4. A location with four or more neighbors will be empty in the next generation.
//                If there was a cell in that location, it dies of overcrowding.

                if(total_neigh <=1 || total_neigh >=4)grid_temp[i][j]= '-';
                else if(total_neigh == 2) grid_temp[i][j] = grid[i][j];
                else if(total_neigh == 3) grid_temp[i][j] = 'X';
            }
        }

        grid = grid_temp;
        // Print the Grid
        this->printGrid();
        pause(50);

        }
    }

};

int main() {
    string filename;
    string isWrap;
    string action;
    string st_frames;
    int frames;
    ifstream in;

    cout<< "Welcome to the CS 106B Game of Life,"<<endl;
    cout<<"a simulation of the lifecycle of a bacteria colony."<<endl;
    cout<<"Cells (X) live and die by the following rules:"<<endl;
    cout<<"- A cell with 1 or fewer neighbors dies."<<endl;
    cout<<"- Locations with 2 neighbors remain stable."<<endl;
    cout<<"- Locations with 3 neighbors will create life."<<endl;
    cout<<"- A cell with 4 or more neighbors dies."<<endl;
    cout<<endl;

    cout << "Grid input file name? ";

// ***Validate the file name entered by user***
    while(true){
        getLine(cin, filename);
        in.open(filename.c_str());
        // If file is opened successfully break the loop
        if(!in.fail()) break;

        cout <<"file name is incorrect. Please try again ";
    }

    GameOflife game;
    // Build the grid using the input stream
    game.buildGrid(in);

    // Ask user about wrapping and non-wrapping option
     cout <<"Should the simulation wrap around the grid (y/n)? ";
    while(true){
        getLine(cin, isWrap);

        // convert string to lowercase
            isWrap = toLowerCase(isWrap);
            if (isWrap.compare("y") == 0 || isWrap.compare("n") == 0)break;

             cout <<"Please answer in 'y' or 'n'. Should the simulation wrap around the grid (y/n)? ";
    }

    // Print the grid
        game.printGrid();
    // Ask for user action
    while(true){
        cout<<"a)nimate, t)ick, q)uit? ";
        getLine(cin, action);

        // convert string to lowercase
            action = toLowerCase(action);
            if (action.compare("t") == 0 || action.compare("q") == 0
                    || action.compare("a") == 0){

                // if choice is valid

                if(action.compare("t") == 0)
                    game.Generation(isWrap,1);
                else if(action.compare("a") == 0){

                    while(true){
                        cout<<"How many frames? ";
                        getLine(cin, st_frames);

                        try{
                        frames = stringToInteger(st_frames);
                        }
                        catch(exception e){
                            cout<<"Illegal integer format. Try again. "<<endl;
                            continue;
                        }

                        if(frames < 1){
                            cout<<"Please choose an Integer greater than 0. ";
                        }
                        else{
                            game.Generation(isWrap, frames);
                            break;
                        }
                    }
                }

                else{
                    cout<<"Have a nice life!";
                    break;
                }

            }
            else{

             cout <<"Invalid choice; please try again.";
            }
    }
    return 0;
}
