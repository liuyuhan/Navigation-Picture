#include "StdAfx.h"
#include "LyPoint.h"


LyPoint::LyPoint(void){

}

LyPoint::LyPoint(LyPoint &p){
	pointID = p.pointID;
	x = p.x;
	y = p.y;
	pointName = p.pointName;
}


LyPoint::~LyPoint(void)
{
}
