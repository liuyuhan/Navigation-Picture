#pragma once
class LyPath
{
public:
	
	LyPath(void);
	LyPath(CString name,int pointNumTemp);
	

	CString getPathName(){
		return pathName;
	}

	int getPointNum(){
		return pointNum;
	}

	void setPathName(CString  name){
		pathName = name;
	}

	void setPointNum(int num){
		pointNum = num;
	}

	~LyPath(void);

private:
	CString pathName;
	int pointNum;   //路线包含的point数量
};

