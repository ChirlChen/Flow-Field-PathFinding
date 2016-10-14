#include "PathFinding.h"

int main(int argc, char *argv[])  
{  
	//PRINT("%d")
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);  
	glutInitWindowPosition(300, 300);  
	glutCreateWindow("FlowFieldPathFinding");  
	Initial(); 
	glutDisplayFunc(PathFindDisplay);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	//glutReshapeFunc(ReshapeWin);
	glutTimerFunc(40, TimeerFunc, 1);
	glutMainLoop();  

	return 0;  
}
