/*项目名称：学生管理系统*/
/*完成时间：2014-2-12*/
/*版本：1.0*/
/*主要功能:实现学生、教师的增、删、改、查、显示、排序*/

#include "menu.h"

int main(void)
{
	menu_init();		//初始化系统
	while (1)
		menu();		//系统菜单
	
	return 0;
}
