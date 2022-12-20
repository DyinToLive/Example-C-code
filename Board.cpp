#include "Board.h"
#include "Piece.h"
#include <fstream>
/*
Function name: getPiece

Purpose: used to inquire about a piece on the board
at the given x/y coordinate.

Details: makes a copy of the piece that is at the location
of the given x/y coordinates.

Argument: function input x/y. 

Return value description: returns a pieceptr at the location
of grid[x][y].
//////////////////////////////////////
Function name: isOccupied

Purpose: used to inquire if a spot on the board at the given
x/y coordinate is occupied or not

Details: if the spot at the given grid[x][y] is not NULL
then the spot is occupied.

Argument: function input x/y

Return value description: returns a boolean true if the spot
is occupied and false if the spot is not occupied.
//////////////////////////////////////
Function name: move

Purpose: checks if there is a piece at the from location and
no piece at the to location. If so then the piece moves to 
the new location and the from location is set to NULL.
hasMoved at the pieces location is then set to true.

Argument: Function input/output: The game board, x/y of the 
from location and x/y of the to location.

Return value description: returns a boolean true if the piece
is successfully moved.
//////////////////////////////////////
Function name: place

Purpose: checks if a given x/y is NULL in order to place
a piece.

Details: returns true if the given location is empty and
false otherwise. Places the piece at the given grid[x][y]
if the location is NULL.

Argument: function input x/y and a pieceptr p.

Return value description: returns a boolean true if the 
location is empty and false otherwise.
//////////////////////////////////////
Function name: remove

Purpose: removes an item at the given x/y if the location is
not NULL. 

Details: searches the given grid[x][y], deletes the item,
then sets the location to NULL.

Argument: function input used to find location.

Return value description: boolean true if there is a piece at
the given location and false otherwise.
//////////////////////////////////////
Function name: write

Purpose: writes a game board X rows down by Y columns across.

Details: if there is a piece at any point on the grid[x][y] the
piece will be written to the board.

Argument: output stream.

Return value description: returns void. function does the printing
and returns the printed board to the output stream.

*/
Board::Board()
{
    initBoard();
    return;
}

Board::Board(const Board& other)
{
    copyBoard(other);
    return;
}

Board::~Board()
{
    int rows, columns;
    ofstream fout;
    fout.open("final_board.txt");
    
    for(rows = 0;rows < MAXROWS;rows++)
    {
	for (columns = 0; columns < MAXCOLS;columns++)
	{
	    if (grid[rows][columns] != NULL)
	    {
		fout << "P " << rows << " " << columns << endl;
	    }
	}
    }
    fout.close();
    clearBoard();
    return;
}

bool Board::isOccupied (int x, int y) const
{
    bool spotIsOccupied = false;
    
    if (grid[x][y] != NULL)
    {
	spotIsOccupied = true;
    }
    return spotIsOccupied;
}

PiecePtr Board::getPiece(int x, int y) const
{
    PiecePtr p = NULL;
    
    if (grid[x][y] != NULL)
    {
	p = new Piece(grid[x][y]);
    }
    
    return p;
}

Board& Board::operator= (const Board& other)
{
    if (this != &other)
    {
	copyBoard(other);
    }
    return (*this);
}

ostream& operator<< (ostream& out, const Board& b)
{
    b.write(out);
    return out;
}

bool Board::move (const Board& b,int fromX, int fromY, int toX, int toY)
{
    bool pieceCanMove = false;

    if (b.grid[fromX][fromY] != NULL && b.grid[toX][toY] == NULL)
    {
	pieceCanMove = true;
	grid[toX][toY] = grid[fromX][fromY];
	grid[fromX][fromY] = NULL;
	b.grid[toX][toY]->notifyMoved();
    }
    return pieceCanMove;
}

bool Board::place(const PiecePtr& p, int x, int y)
{
    bool canPlace = false;
 
    if (x <= MAXROWS && x >= 0)
    {
	if (y <= MAXCOLS && y >= 0)
	    
	{
	    if (grid[x][y] == NULL)
	    {
		grid[x][y] = p;
		canPlace = true;
	    }
	}
    }
    return canPlace;
}

bool Board::remove(int x, int y)
{
    bool canRemove = false;
    if (x <= MAXROWS && x >= 0)
    {
	if (y <= MAXCOLS && y >= 0)
	{
	    if (grid[x][y] != NULL)
	    {
		delete grid[x][y];
		grid[x][y] = NULL;
		canRemove = true;
	    }
	}
    }
    return canRemove;
}

void Board::write(ostream& out) const
{
    int rows, columns;

    out << "   ";
    
    for (columns = 0; columns < MAXCOLS; columns++)
    {
	out << columns << "   ";
    }
    out << endl;

    for (rows = 0; rows < MAXROWS; rows++)
    {
	out << " ";
	out << "+---+---+---+---+---+---+---+---+" << endl;
	out << rows;
	
	for (columns = 0; columns < MAXCOLS; columns++)
	{
	    if (grid[rows][columns] != NULL && columns < MAXCOLS)
	    {
		out << "| " << "P ";
	    }
	    else
	    {
		out << "|   ";
	    }
	}
	out << "|" << endl;
    }
    out << " +---+---+---+---+---+---+---+---+" << endl;
    return;
}

void Board::initBoard()
{
    int rows, columns;
    
    for(rows = 0;rows < MAXROWS;rows++)
    {
	for (columns = 0; columns < MAXCOLS;columns++)
	{
	    grid[rows][columns] = NULL;
	}
    }
    return;
}

void Board::clearBoard()
{
    int rows, columns;
    
    for (rows = 0; rows < MAXROWS;rows++)
    {
	for (columns = 0; columns < MAXCOLS; columns++)
	{
	    if (grid[rows][columns] != NULL)
	    {
		delete grid[rows][columns]; 
		grid[rows][columns] = NULL;
	    }
	}
    }
    return;
}

void Board::copyBoard(const Board& other)
{
    int rows, columns;
    
    for (rows = 0; rows < MAXROWS;rows++)
    {
	for (columns = 0; columns < MAXCOLS; columns++)
	{
	    grid[rows][columns] = other.grid[rows][columns];
	}
    }
    return;
}


