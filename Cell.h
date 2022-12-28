//Cell header file
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;
class Cell{
    
private:
    int x, y; //Coordiantes of the cell
    char status; //' ', @, *, S, G
    int cost; //for DA
    bool top, down, left, right; //Bools to indicate if there is a wall
    Cell * prev; //Pointer to previous cell for backwards traversal when solution is found
    
public:
    Cell( int Ny = -1, int Nx = -1, bool t = 0, bool d = 0, bool l = 0, bool r = 0, char s = ' ', int cst =0, Cell * c = nullptr){ //Constructor
         y = Ny; x = Nx;
        status = s;
        cost = cst;
        top = t;
        down = d;
        left = l;
        right = r;
    }

    
    Cell(const Cell & c){ //Copy constructor
        y = c.y;
        x = c.x;
        status = c.status;
        prev = c.prev;
        top = c.top;
        down = c.down;
        left = c.left;
        right = c.right;
        cost = c.cost;
    }
    
    Cell operator=(const Cell & c){ //Assignment operator
        if (this != &c){
            x = c.x;
            y = c.y;
            status = c.status;
            prev = c.prev;
            top = c.top;
            down = c.down;
            left = c.left;
            right = c.right;
            cost = c.cost;
        }
        return *this; //To allow for CellObj1 = CellObj2 = CellObj3 = ...
    }
    
    bool operator==(const Cell & c){ //Equality check
        if (x != c.x || y != c.y || status != c.status || down != c.down || left != c.left || right != c.right || cost !=c.cost)
            return false;
        return true;
    }
    
    bool operator!=(const Cell & c){ //Inequality Check
        return !(*this == c);
    }
    
    //Setters
    void setStatus(char s){ //Changes status
        status = s;
    }
    void setPrev(Cell * p){ //Sets the previous cell connected to this one
        prev = p;
    }
    
    
    void setCost (char c){//sets the cost of the cell
        cost = c;
    }
    
    
    //Getters
    bool getTop() const{
        return top;
    }
    bool getDown() const{
        return down;
    }
    bool getRight() const{
        return right;
    }
    bool getLeft() const{
        return left;
    }
    char getStatus() const{
        return status;
    }
    int getX() const {
        return x;

    }
    int getY() const{
        return y;
    }
    
    char getCost()const {
        return cost;
    }
    
    Cell * getPrev() const{
        return prev;
    }
};


