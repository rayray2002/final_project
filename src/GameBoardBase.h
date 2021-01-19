#ifndef _GAMEBOARDBASE_H
#define _GAMEBOARDBASE_H

class GameBoardBase
{
protected:
    enum PairState
    {
        UP_AND_DOWN,
        RIGHT_AND_LEFT,
        SEPERATED
    };
    bool isChanged;
    bool isChanged1;
	bool isChanged2;

};

#endif