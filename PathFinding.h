#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

#include <gl/glut.h>  
#include <iostream>  
#include <windows.h>
#include <string.h>  
#include <sstream> 
#include <set>
#include <time.h>
#include "DebugFunc.h"

using namespace std;  

#pragma comment(lib,"glut32.lib") 

const float WORLD_WIDTH		= 200.0;	//世界窗口的宽度;
const float WORLD_HEIGHT	= 160.0;	//世界窗口的高度;
const float WINDOW_WIDTH	= 800.0;	//窗口宽度;
const float WINDOW_HEIGHT	= 500.0;	//窗口高度;
const float GRID_SIZE		= 4.0;		//网格的大小;
const float MOVE_STEP		= 1.8;		//对象的移动步长;
const int MAX_CHAR          = 128;		//字符串最大长度;
const int MOVE_OBJECT_NUM   = 200;		//移动目标数量;
const int INFI				= 0xFFFFFFF;//无穷值;

#define GLUT_DISABLE_ATEXIT_HACK 
#define CALC_MOVE_SPEED(_obj, _objIdx)	\
		((_obj).s * MOVE_STEP / gMap[(_objIdx).x][(_objIdx).y].c)     //根据移动目标的初始速度和所在位置的代价值计算移动目标的速度;

typedef enum EDirection	//方向枚举;
{
	ED_U	= 3,				//上;方向值由该节点与父节点的相对坐标（x,y），x*30+y*3计算得到
	ED_D	= -3,				//下;
	ED_L	= -30,				//左;
	ED_R	= 30,				//右;
	ED_UL	= -27,				//上左;
	ED_UR	= 33,				//上右;
	ED_DL	= -33,				//下左;
	ED_DR	= 27,				//下右;
	ED_NULL	= 10,				//无;
}EDirection;
typedef enum EGridType
{
	EGT_NORMAL,			//普通网格;
	EGT_OPEN,			//open列表中的网格;
	EGT_CLOSE,			//close列表中的网格;
	EGT_OBSTOCLE,		//障碍物;
	EGT_DESTINATION,	//终点;
}EGridType;

typedef struct SGridInfo 
{
	int		c;				//该经过网格点的代价;
	int		pl;				//从该网格点到终点的路径长度;
	int		d;				//该网格点的流场方向;
	int		t;				//网格类型;
	SGridInfo()
	{
		c	= 0;
		pl	= INFI;
		d	= ED_NULL;
		t   = EGT_NORMAL;
	}
}SGridInfo;
typedef struct SPoint
{
	GLfloat		x;
	GLfloat		y;
	SPoint(GLfloat ax = 0.0f, GLfloat ay = 0.0f)
	{
		x = ax;
		y = ay;
	}
}SPoint;
typedef struct SCoordinate
{
	int		x;
	int		y;
	SCoordinate(int ax = 0, int ay = 0)
	{
		x = ax;
		y = ay;
	}
	const SCoordinate &operator=(const SCoordinate &d)
	{
		x = d.x;
		y = d.y;
		return *this;
	}
}SCoordinate; 
typedef struct SColorRGB
{
	GLfloat		r;
	GLfloat		g;
	GLfloat		b;
	SColorRGB(GLfloat ar, GLfloat ag, GLfloat ab)
	{
		r = ar;
		g = ag;
		b = ab;
	}
}SColorRGB;
typedef struct SOpenGridInfo
{
	SCoordinate c;
	int			pl;			//路径长度;

	SOpenGridInfo(const SCoordinate &ac, int l = 0)
	{
		c  = ac;
		pl = l;
	}
	bool operator<(const SOpenGridInfo &o) const
	{
		return pl < o.pl;
	}
}SOpenGridInfo;
typedef struct SMoveObject
{
	SPoint	p;		//坐标;
	float	s;		//移动速度;
	SMoveObject(const SPoint ap=SPoint(), float as = 20.0f)
	{
		p = ap;
		s = as;
	}
}SMoveObject;

string Num2String(int i);  
SPoint Index2World(const SCoordinate &idx);
SPoint Pixel2World(const SPoint &pixel);
SCoordinate World2Index(const SPoint &p);

void Initial();  
void PathFindDisplay();
void ReshapeWin(int w, int h);
void MouseClick(int button, int state, int x, int y);
void MouseMove(int x, int y);
void TimeerFunc(int value);
void InitMoveObject();
/***********************地图场景**********************/
void DrawMap(int hGridNum, int vGridNum);
void DrawObstacle(int hGridNum, int vGridNum);
void DrawFlowField(int hGridNum, int vGridNum);
void DrawMoveObject(int hGridNum, int vGridNum);
void DrawDestination(const SPoint &dIdx);
/***********************基础图形**********************/
void DrawString(string strn); 
void DrawQuads(const SPoint &ldp, const SPoint &urp, const SColorRGB &c,int mode); //左下，右上世界坐标，以及绘制边线或填充;
void DrawLineSurroundQuads(const SCoordinate &idx);   //画带线围成的矩形;
void DrawPoint(const SPoint &p, GLint size, const SColorRGB &c);
void DrawArraw(const SPoint &sp, const SPoint & ep);

/***********************寻路算法**********************/
void CalcFlowField(const SCoordinate &d, int hGridNum, int vGridNum); //传入终点;
void ChangeObjectPosition();				//根据流场改变移动目标位置;
#endif