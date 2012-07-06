#pragma once
class LyPoint
{
public:

	LyPoint(void);
	
	LyPoint(int idTemp,int xx,int yy,CString pointNameTemp){
		pointID = idTemp;
		x = xx;
		y = yy;
		pointName = pointNameTemp;
	}
	

	LyPoint(LyPoint &p);

	int getPointID(){
		return pointID;
	}

	int getPointX(){
		return x;
	}

	int getPointY(){
		return y;
	}

	CString getPointName(){
		return pointName;
	}

	void setPointID(int ID){
		pointID = ID;
	}

	void setPointX(int tempX){
		x = tempX;
	}

	void setPointY(int tempY){
		y = tempY;
	}

	void setPointName(CString name){
		pointName = name;
	}

	~LyPoint(void);

private:
	int x,y;
	int pointID;
	CString pointName;
};

