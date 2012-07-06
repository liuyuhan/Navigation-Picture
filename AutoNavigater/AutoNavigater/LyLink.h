#pragma once

#include "LyPoint.h"

class LyLink
{
public:

	LyLink(void);

	LyLink(int id,LyPoint xp1,LyPoint xp2):p1(xp1),p2(xp2){
		linkID = id;
	}

	LyLink(LyLink &l);

	int getLinkID(){
		return linkID;
	}

	LyPoint getLinkXPoint(){
		return p1;
	}

	LyPoint getLinkYPoint(){
		return p2;
	}

	void setLinkID(int ID){
		linkID = ID;
	}

	void setLinkXPoint(LyPoint lp1){
		p1 = lp1;
	}

	void setLinkYPoint(LyPoint lp2){
		p2 = lp2;
	}


	~LyLink(void);

private:
	int linkID;
	LyPoint p1,p2;
};

