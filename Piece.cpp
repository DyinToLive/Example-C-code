#include "Piece.h"
#include "Board.h"
/*
Function name: getSymbol

Purpose: gets the symbol of a piece

Return value description: character
//////////////////////////////////////
Function name: getColour

Purpose: gets the colour of a piece

Return value description: boolean true or false for white or black
respectively.
//////////////////////////////////////
Function name: canMove

Purpose: uses all of the classes private functions to determine how
the pawn piece is going to move.

Details: a pawn is checked to see if it can move forward two spaces
or not. A diagonal move is checked for but not used in Part 2 of the
project.

Argument:  i/o Board, and grid locations that the piece is
on and attempting to move to. 

Return value description: a boolean true if the piece is able to move
to the proposed location.
//////////////////////////////////////
Function name: notifyMoved

Purpose: notifies the caller if the piece has moved. 

Details: used for a pawn because a pawn can move two squares 
forward on its first move.

Return value description: sets the boolean hasMoved to true in
a piece function.
//////////////////////////////////////
Function name: isVertical

Purpose: uses vertDistance and horizDistance to determine if a piece
is moving vertically.

Details: if the vertical distance is greater than 0 and the 
horizontal distance is 0 the piece is moving vertically.

Argument: x/y coordinates for the from and to locations of the piece
and proposed spot respectively.

Return value description: a boolean true if the function can move
vertically and false otherwise.
//////////////////////////////////////
Function name: isHorizontal

Purpose: uses vertDistance and horizDistance to determine if a piece
is moving horizontally.

Details: if the vertical distance is 0 and the horizontal distance
is greater than 0 the piece is moving horizontally.

Argument: x/y coordinates for the from and to locations of the piece
and proposed spot respectively.

Return value description: a boolean true if the function can move
horizontally and false otherwise.
//////////////////////////////////////
Function name: isDiagonal

Purpose: uses vertDistance and horizDistance to determine if a piece
is moving diagonally.

Details: if the vertical and horizontal distance are the same then 
the piece is moving diagonally.

Argument: x/y coordinates for the from and to locations of the piece
and proposed spot respectively.

Return value description: a boolean true if the piece can move
diagonally and false if otherwise.
//////////////////////////////////////
Function name: isForward

Purpose: checks if a piece is moving foward.

Details: uses vertDistance to determine if the piece is moving forward.

Argument: function input X to determine the how far the piece is moving
forward.

Return value description: a boolean true if the piece is moving forward
and false otherwise.
//////////////////////////////////////
Function name: vertDistance

Purpose: checks if a piece is going to move vertically.

Details: recieves the x coordinates to determine if how far
the piece is going to move. 

Argument: function input x coordinate for the from and to location.

Return value description: an integer value. The distance that the
piece will move vertically.
//////////////////////////////////////
Function name: horizDistance

Purpose: checks if the piece is going to move horizontally.

Details: recieves the y coordinates to determine if how far
the piece is going to move. 

Argument: function input y coordinate for the from and to location.

Return value description: an integer value. The distance that the
piece will move horizontally.
//////////////////////////////////////
Function name: isPathClear

Purpose: checks if the path is clear for a pawn

Details: A pawn can only move forward twice if it hasn't
moved or once if it has moved. Function checks if the
pawn has moved and if their is another piece in the path
it is trying to take.

Argument: i/o Board, and grid locations that the piece is
on and attempting to move to.

Return value description: returns a boolean true if the path
is clear to the proposed location.
//////////////////////////////////////
*/
Piece::Piece (bool col)
{
    colour = col;
    hasMoved = false;
    return;
}

char Piece::getSymbol() const
{
    char symbol;
    bool colour;
    colour = getColour();

    if (colour == WHITE)
	symbol = 'P';
    if (colour == BLACK)
	symbol = 'p';
    
    return symbol;
}
bool Piece::getColour() const
{
    return colour;
}

bool Piece::canMove(const Board& b, int fromX, int fromY, int toX, int toY) const
{
    bool pathIsClear = isPathClear(b,fromX,fromY,toX,toY);
    PiecePtr toPawn = NULL;
    PiecePtr movingPawn = NULL;
    bool forward = isForward(fromX,toX);
    int vertical = vertDistance(fromX,toX);
    int horizontal = horizDistance(fromY,toY);
    bool pieceCanMove = false;
    bool diagonal = isDiagonal(fromX,fromY,toX,toY);
    
    movingPawn = b.getPiece(fromX,fromY);

    if (!hasMoved && forward)
    {
	if (vertical == 2 && horizontal == 0 && pathIsClear)
	{
	    pieceCanMove = true;
	}
	else if (vertical == 1 && horizontal == 0 && pathIsClear)
	{
	    pieceCanMove = true;
	}
	else if (diagonal)
	{
	    toPawn = b.getPiece(toX,toY);
	    if (movingPawn->colour != toPawn->colour)
	    {
		pieceCanMove = true;	    
	    }
	}
    }
    else if (hasMoved && forward)
    {
	if (vertical == 1 && horizontal == 0 && pathIsClear)
	{
	    pieceCanMove = true;
	}
	else if (diagonal)
	{
	    toPawn = b.getPiece(toX,toY);
	    if (movingPawn->colour != toPawn->colour)
	    {
		pieceCanMove = true;	    
	    }
	}
    }
    return (pieceCanMove);   
}

void Piece::notifyMoved()
{
    hasMoved = true;
}

bool Piece::isVertical (int fromX, int fromY, int toX, int toY) const
{
    bool verticalMove = false;
    int vertical;
    int horizontal;
    vertical = vertDistance(fromX,toX);
    horizontal = horizDistance(toX,toY);

    if (vertical > 0 && horizontal == 0)
    {
	verticalMove = true;
    }
    return verticalMove;
}

bool Piece::isHorizontal (int fromX, int fromY, int toX, int toY) const
{
    bool horizontalMove = false;
    int vertical;
    int horizontal;
    vertical = vertDistance(fromX,toX);
    horizontal = horizDistance(toX,toY);

    if (horizontal > 0 && vertical == 0)
    {
	horizontalMove = true;
    }
    return horizontalMove;
}

bool Piece::isDiagonal (int fromX, int fromY, int toX, int toY) const
{
    bool diagonalMove = false;
    int vertical;
    int horizontal;
    vertical = vertDistance(fromX,toX);
    horizontal = horizDistance(toX,toY);
    if (vertical > 0 && horizontal > 0 && vertical == horizontal)
    {
	diagonalMove = true;
    }
    return diagonalMove;
}

bool Piece::isForward (int fromX, int toX) const
{
    bool hasMovedForward = false;
    int distance;
    distance = vertDistance(fromX,toX);
    
    if (distance > 0)
	hasMovedForward = true;
    
    return hasMovedForward;
}

int Piece::vertDistance (int fromX, int toX) const
{
    int vertical;
    
    if (fromX > toX)
    {
	vertical = fromX - toX;
    }
    else
    {
	vertical = toX - fromX;
    }
    return vertical;
}

int Piece::horizDistance (int fromY, int toY) const
{
    int horizontal;
    
    if (fromY > toY)
    {
	horizontal = fromY - toY;
    }
    else
    {
	horizontal = toY - fromY;
    }
    return horizontal;
}

bool Piece::isPathClear (const Board& b, int fromX, int fromY, int toX, int toY) const
{
    bool emptyPath = false;
    int vertical;
    
    vertical = vertDistance(fromX,toX);

    if(vertical == 2)
    {
	if (colour == WHITE)
	{
	    if(!b.isOccupied(toX+1,toY))
		if(!b.isOccupied(toX,toY))
		    emptyPath = true;
	}
	else
	{
	    if(!b.isOccupied(toX-1,toY))
		if(!b.isOccupied(toX,toY))
		    emptyPath = true;
	}
    }
    if(vertical == 1)
	if(!b.isOccupied(toX,toY))
	    emptyPath = true;

    return emptyPath;
}

