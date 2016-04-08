/*MENU.C文件：实现MENU.H的函数功能*/
/*时间：2014-1-25*/
/*版本：1.0*/
#include "menu.h"

int key = 3;		//用于确定验证次数
int flog = 0;		//返回上级菜单标志位
static node_t *stuhead;	//定义静态全局变量的学生链表头指针	
static node_t *teahead;	//定义静态全局变量的教师链表头指针
node_t *tea_self;	//保存教师自己登录以后的指针
node_t *stu_self;	//保存学生自己登录以后的指针

/*功能：初始化系统*/
/*参数：无*/
/*返回值：无*/
void menu_init(void)
{
	show_start_logo();		//显示系统logo
	stuhead = read_student_file();	//加载学生信息
	teahead = read_teacher_file();	//加载教师信息
	return;
}


/*功能：选择模式*/
/*参数：无*/
/*返回值：无*/
void menu(void)
{
	system("clear");
	char ch = main_menu();		//调用显示主菜单

	switch (ch)
	{
		case '1': 
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					key = 3;
					break;
				}
				admin_menu();	//调用管理员验证
			}
			break;
		case '2':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					key = 3;
					break;
				}
				teacher_menu();	//调用教师验证
			}
			break;
		case '3':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					key = 3;
					break;
				}
				student_menu();	//调用学生验证
			}
			break;
		case 'q':
			quit();		//退出学生系统
			break;
		default	:
			break;
	}

	return;
}


/*功能：显示主菜单*/
/*参数：无*/
/*返回值：ch为选择模式参数*/
char main_menu(void)
{
	puts("\n\n\n\n\t\t\t\t\t欢迎进入教务系统");
	puts("\n\n\t\t\t\t1.管理员登录");
	puts("\n\t\t\t\t2.教师登录");
	puts("\n\t\t\t\t3.学生登录");

	puts("\n\n\n\t\t\t\tq.退出系统");
	printf("\n\n\n\t\t\t\t请选择登录方式：");
	char ch = getchar();
	get_char();			//用于接收多余输入的字符

	return ch;
}


/*功能：输入管理员用户名和密码函数*/
/*参数：无*/
/*返回值：无*/
void admin_menu(void)
{
	system("clear");
	char user[16], passwd[32];
	puts("\n\n\n\n\t\t\t\t\t欢迎管理员登录");
	puts("\n\n\t\t\t\t请输入用户名和密码");

	printf("\n\t\t\t\t用户名：");
	bzero(user, sizeof(user));		//清空user数组
	fgets(user, sizeof(user), stdin);
	f_gets(user, sizeof(user));

	printf("\t\t\t\t密码：");
	bzero(passwd, sizeof(passwd));		//清空passwd数组
	fgets(passwd, sizeof(passwd), stdin);
	f_gets(passwd, sizeof(passwd));	
	test_admin_menu(user, passwd);		//验证管理员登录
	
	return;
}


/*功能：管理员验证函数*/
/*参数：user为用户名； passwd为密码*/
/*返回值：0为成功， -1为失败*/
int test_admin_menu(char *user, char *passwd)
{
	ERROR(user, NULL, "user is null", -1);
	ERROR(passwd, NULL, "passwd is null", -1);

	while (0 != key)
	{
		key--;
		if (!strcmp(user, "admin\n") && !strcmp(passwd, "admin\n"))		//判断用户名和密码
		{
			while (1)
			{
				if (1 == flog)
				{
					break;
				}
				admin_login_menu();		//管理员子系统
			}
			break;
		}
		else
		{
			if (key == 0)
				flog = 1;
			break;
		}
	}

	return 0;
}


/*功能：输入教师用户名和密码*/
/*参数：无*/
/*返回值：无*/
void teacher_menu(void)
{
	system("clear");
	char user[16], passwd[32];
	puts("\n\n\n\n\t\t\t\t\t欢迎教师登录");
	puts("\n\n\t\t\t\t请输入用户名和密码");

	printf("\n\t\t\t\t用户名：");
	bzero(user, sizeof(user));		//清空user数组
	fgets(user, sizeof(user), stdin);
	f_gets(user, sizeof(user));
	
	printf("\t\t\t\t密码：");
	bzero(passwd, sizeof(passwd));		//清空passwd数组
	fgets(passwd, sizeof(passwd), stdin);
	f_gets(passwd, sizeof(passwd));
	test_teacher_menu(user, passwd);	//验证教师登录
	
	return;
}


/*功能：教师验证函数*/
/*参数：user为用户名； passwd为密码*/
/*返回值：0为成功， -1为失败*/
int test_teacher_menu(char *user, char *passwd)
{
	ERROR(user, NULL, "user is null", -1);
	ERROR(passwd, NULL, "passwd is null", -1);
	tea_t *tea_temp;
	node_t *temp = teahead->next;
	
	while (0 != key)			
	{
		key--;
		while (temp != teahead)			//用于查找整个教师链表
		{
			tea_temp = (tea_t *)temp->data;
			if (!strcmp(user, tea_temp->name) && !strcmp(passwd, tea_temp->passwd))		//判断用户名和密码
			{
				tea_self = temp;
				while (1)
				{
					if (1 == flog)
					{
						break;
					}
					teacher_login_menu();		//教师子系统
				}
				break;
			}
			temp = temp->next;		//指向链表中的下一个成员
			
		}
		if (key == 0)
			flog = 1;
		break;		
	}

	return 0;
}


/*功能：输入学生用户名和密码*/
/*参数：无*/
/*返回值：无*/
void student_menu(void)
{
	system("clear");
	char user[16],passwd[32];
	puts("\n\n\n\n\t\t\t\t\t欢迎学生登录");
	puts("\n\n\t\t\t\t请输入用户名和密码");

	printf("\n\t\t\t\t用户名：");
	bzero(user, sizeof(user));		//清空user数组
	fgets(user, sizeof(user), stdin);
	f_gets(user, sizeof(user));
	
	printf("\t\t\t\t密码：");
	bzero(passwd, sizeof(passwd));		//清空passwd数组
	fgets(passwd, sizeof(passwd), stdin);
	f_gets(passwd, sizeof(passwd));
	test_student_menu(user, passwd);	//验证学生登录

	return;
}


/*功能：学生验证函数*/
/*参数：user为用户名； passwd为密码*/
/*返回值：0为成功， -1为失败*/
int test_student_menu(char *user, char *passwd)
{
	ERROR(user, NULL, "user is null", -1);
	ERROR(passwd, NULL, "passwd is null", -1);
	stu_t *stu_temp;
	node_t *temp = stuhead->next;
	
	while (0 != key)		
	{
		key--;
		while (temp != stuhead)			//用于查找整个学生链表
		{
			stu_temp = (stu_t *)temp->data;
			if (!strcmp(user, stu_temp->name) && !strcmp(passwd, stu_temp->passwd))		//判断用户名和密码
			{
				stu_self = temp;
				while (1)
				{
					if (1 == flog)
					{
						break;
					}
					student_login_menu();		//教师子系统
				}
				break;
			}		
			temp = temp->next;		//指向链表中的下一个成员			
		}

		if (key == 0)
			flog = 1;
		break;		
	}

	return 0;
}


/*功能：管理员子系统*/
/*参数：无*/
/*返回值：无*/
void admin_login_menu(void)
{
	char ch = admin_inside_menu();				//管理员显示菜单
	int res;

	switch (ch)
	{
		case '1': 
			res = add_student(stuhead);		//向链表尾部增加学生成员
			if (0 == res)
				printf("\n\n\t\t\t\t添加学生成功");
			printf("\n\n\t\t\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符
			break;
		case '2':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				find_student_login(change_admstudent_login);	//查找、修改学生信息菜单
			}
			break;
		case '3':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				show_student_login();		//进入显示全部学生子菜单
			}
			break;
		case '4':
			res = delete_all_student(stuhead);	//删除链表中的所有学生成员
			if (0 == res)
				printf("\n\n\n\n\t\t\t\t学生已被全部删除");
			printf("\n\n\t\t\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符
			break;
		case '5':
			res = add_teacher(teahead);		//向链表尾部添加教师成员
			if (0 == res)
				printf("\n\n\t\t\t\t添加教师成功");
			printf("\n\n\t\t\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符
			break;
		case '6':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				find_teacher_login();		//查找、修改教师信息菜单
			}
			break;
		case '7':	
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				show_teacher_login();		//进入显示全部教师子菜单
			}
			break;
		case '8':
			res = delete_all_teacher(teahead);	//删除链表中的所有教师成员
			if (0 == res)
				printf("\n\n\n\n\t\t\t\t教师已被全部删除");
			printf("\n\n\t\t\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	return;
}


/*功能：管理员显示菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char admin_inside_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t欢迎管理员");
	puts("\n\n\t\t1.添加学生\t2.查找、修改学生\t3.查看全部学生\t4.删除全部学生");
	puts("\n\t\t5.添加教师\t6.查找、修改教师\t7.查看全部教师\t8.删除全部教师");

	puts("\n\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\t\t请输入你的选择：");
	char ch = getchar();
	get_char();		//用于接收多余输入的字符

	return ch;	
}


/*功能：教师子系统*/
/*参数：无*/
/*返回值：无*/
void teacher_login_menu(void)
{
	char ch = teacher_inside_menu();			//教师显示菜单
	
	switch (ch)
	{
		case '1':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				show_teacher_self();
			}
			break;
		case '2':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				show_teastudent_login();
			}
			break;
		case '3':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				find_student_login(change_teastudent_login);
			}
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	return;
}


/*功能：教师显示菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char teacher_inside_menu(void)
{
	system("clear");
	tea_t *temp = (tea_t *)tea_self->data;
	printf("\n\n\n\n\t\t\t\t\t欢迎教师%s", temp->name);
	puts("\n\t\t1.查看自己信息\t2.查看全部学生\t3.查找、修改学生");
	puts("\n\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\t\t请输入你的选择：");

	char ch = getchar();
	get_char();			//用于接收多余输入的字符
	return ch;
}


/*功能：学生子系统*/
/*参数：无*/
/*返回值：无*/
void student_login_menu()
{
	char ch = student_inside_menu();			//学生显示菜单

	switch (ch)
	{
		case '1':
			while (1)
			{
				if (1 == flog)
				{
					flog = 0;
					break;
				}
				show_student_self();
			}
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;	
	}

	return;
}


/*功能：学生显示菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char student_inside_menu(void)
{
	system("clear");
	stu_t *temp = (stu_t *)stu_self->data;
	printf("\n\n\n\n\t\t\t\t\t欢迎学生%s", temp->name);
	puts("\n\t\t1.查看自己信息\tu.返回上层目录\tq.退出系统");
	printf("\n\n\t\t请输入你的选择：");

	char ch = getchar();
	get_char();		//用于接收多余输入的字符
	return ch;
}


/*功能：显示全部学生子系统*/
/*参数：无*/
/*返回值：无*/
void show_student_login(void)
{
	char ch = show_student_menu();		//显示全部学生子菜单

	switch (ch)
	{
		case '1':
			system("clear");
			puts("\n\n\n\t\t\t\t\t显示全部学生姓名窗口");
			puts("\n\n\t\t\t姓名");
			sort_student(stuhead, cmp_student_num);
			show_all_student(stuhead, show_student_name);	//显示学生链表中全部学生的姓名
			printf("\t\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符
			break;
		case '2':
			system("clear");
			puts("\n\n\n\t\t\t\t\t显示全部学生信息窗口");
			puts("\n\t\t编号\t班级\t年龄\t姓名");
			sort_student(stuhead, cmp_student_num);
			show_all_student(stuhead, show_astu);		//显示学生链表中全部学生的全部信息
			printf("\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符;
			break;
		case 'u':
			flog = 1;	
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	return;
}


/*功能：显示全部学生子菜单*/
/*参数：无*/
/*返回值：ch 为选择参数*/
char show_student_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t显示学生窗口");
	puts("\n\n\t\t\t\t1.显示学生姓名\t2.显示学生全部信息");
	puts("\n\t\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t\t请选择显示方式：");

	char ch = getchar();
	get_char();		//用于接收多余输入的字符

	return ch;
}


/*功能：显示全部学生子系统*/
/*参数：无*/
/*返回值：无*/
void show_teacher_login(void)
{
	char ch = show_teacher_menu();		//显示全部教师子菜单

	switch (ch)
	{
		case '1':
			system("clear");
			puts("\n\n\n\t\t\t\t\t显示全部教师姓名窗口");
			puts("\n\n\t\t\t姓名");
			sort_teacher(teahead, cmp_teacher_num);
			show_all_teacher(teahead, show_teacher_name);		//显示学生链表中全部教师的姓名
			printf("\t\t\t按回车键返回");
			get_char();		//用于接收多余输入的字符
			break;
		case '2':
			system("clear");
			puts("\n\n\n\t\t\t\t\t显示全部教师信息窗口");
			puts("\n\n\t\t\t编号\t年龄\t所任课程\t所任班级\t姓名\t");
			sort_teacher(teahead, cmp_teacher_num);
			show_all_teacher(teahead, show_atea);			//显示学生链表中全部教师的信息
			printf("\t\t\t按回车键返回");
			get_char();		//用于接收多余输入的字符
			break;
		case 'u':
			flog = 1;	
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	return;
}


/*功能：显示全部教师子菜单*/
/*参数：无*/
/*返回值：ch 为选择参数*/
char show_teacher_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t显示教师窗口");
	puts("\n\n\t\t\t\t1.显示教师姓名\t2.显示教师全部信息");
	puts("\n\t\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t\t请选择查找方式：");

	char ch = getchar();
	get_char();		//接收多余的字符

	return ch;
}


/*功能：查找、修改学生信息子系统*/
/*参数：无*/
/*返回值：无*/
void find_student_login(cstu_t f)
{
	char ch = find_student_menu();		//查找、修改学生信息菜单
	stu_t temp;
	node_t *student_temp;

	switch (ch)
	{
		case '1':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要查找的编号：");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				temp.num = input_num();
			}
			//scanf("%d", &temp.num);
			//get_char();		//用于接收多余输入的字符		
			student_temp = find_student(stuhead, &temp, cmp_student_num);		//查找学生函数	
			while (1)
			{
				if (student_temp != NULL)
				{
					show_me_student(student_temp, show_astu);//显示学生全部信息函数							
					printf("\n\n\t\t\t是否需要修改(Y/N):");
					ch = getchar();
					get_char();		//用于接收多余输入的字符

					if ('y' == ch || 'Y' == ch)
					{
						while (1)
						{
							if (flog == 1)
							{
								flog = 0;
								break;
							}					
							f(student_temp);			//管理员修改学生子系统
						}
						break;
					}
					else if ('n' == ch || 'N' == ch)
						break;
				}
				else
				{
					system("clear");
					puts("\t\t\t没有该学生");
					printf("\n\n\t\t\t按回车键返回");
					get_char();		//用于接收多余输入的字符
					break;
				}		
			}
			break;
		case '2':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要查找的姓名：");
			fgets(temp.name, sizeof(temp.name), stdin);
			f_gets(temp.name, sizeof(temp.name));
			student_temp = find_student(stuhead, &temp, cmp_student_name);
			
			while (1)
			{
				if (student_temp != NULL)
				{
					show_me_student(student_temp, show_astu);
					printf("\n\n\t\t\t是否需要修改(Y/N):");
					ch = getchar();
					get_char();		//用于接收多余输入的字符
				
					if ('y' == ch || 'Y' == ch)
					{
						while (1)
						{
							if (flog == 1)
							{
								flog = 0;
								break;
							}					
							f(student_temp);			//管理员修改学生子系统
						}
						break;
					}
					else if ('n' == ch || 'N' == ch)
						break;
				}
				else
				{
					system("clear");
					puts("\t\t\t没有该学生");
					printf("\n\n\t\t\t按回车键返回");
					get_char();		//用于接收多余输入的字符
					break;
				}		
			}
			break;
		case '3':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要查找的年龄：");
			scanf("%d", &temp.age);
			get_char();		//用于接收多余输入的字符
			
			student_temp = find_student(stuhead, &temp, cmp_student_age);
			
			while (1)
			{
				if (student_temp != NULL)
				{
					show_me_student(student_temp, show_astu);
					printf("\n\n\t\t\t是否需要修改(Y/N):");
					ch = getchar();
					get_char();		//用于接收多余输入的字符
				
					if ('y' == ch || 'Y' == ch)
					{
						while (1)
						{
							if (flog == 1)
							{
								flog = 0;
								break;
							}					
							f(student_temp);			//管理员修改学生子系统
						}
						break;
					}
					else if ('n' == ch || 'N' == ch)
						break;
				}
				else
				{
					system("clear");
					puts("\t\t\t没有该学生");
					printf("\n\n\t\t\t按回车键返回");
					get_char();		//用于接收多余输入的字符
					break;
				}		
			}			
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	return;
}


/*功能：查找、修改教师信息子系统*/
/*参数：无*/
/*返回值：无*/
void find_teacher_login(void)
{
	char ch = find_teacher_menu();		//查找、修改教师信息菜单
	tea_t temp;
	node_t *teacher_temp;

	switch (ch)
	{
		case '1':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要查找的编号：");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				temp.num = input_num();
			}

			teacher_temp = find_teacher(teahead, &temp, cmp_teacher_num);		//查找教师函数
							
			while (1)
			{
				if (teacher_temp != NULL)
				{
					show_me_teacher(teacher_temp, show_atea);//显示教师全部信息函数
					printf("\n\n\t\t\t是否需要修改(Y/N):");
					ch = getchar();
					get_char();		//用于接收多余输入的字符
				
					if ('y' == ch || 'Y' == ch)
					{
						while (1)
						{
							if (flog == 1)
							{
								flog = 0;
								break;
							}					
							change_admteacher_login(teacher_temp);			//管理员修改教师子系统
						}
						break;
					}
					else if ('n' == ch || 'N' == ch)
					break;
				}
				else
				{
					system("clear");
					puts("\t\t\t没有该教师");
					printf("\n\n\t\t\t按回车键返回");
					get_char();		//用于接收多余输入的字符
					break;
				}
			}		
			break;
		case '2':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要查找的姓名：");
			fgets(temp.name, sizeof(temp.name), stdin);
			f_gets(temp.name, sizeof(temp.name));
			teacher_temp = find_teacher(teahead, &temp, cmp_teacher_name);

			
			while (1)
			{
				if (teacher_temp != NULL)
				{
					show_me_teacher(teacher_temp, show_atea);
					printf("\n\n\t\t\t是否需要修改(Y/N):");
					ch = getchar();
					get_char();		//用于接收多余输入的字符
				
					if ('y' == ch || 'Y' == ch)
					{
						while (1)
						{
							if (flog == 1)
							{
								flog = 0;
								break;
							}					
							change_admteacher_login(teacher_temp);			//管理员修改教师子系统
						}
						break;
					}
					else if ('n' == ch || 'N' == ch)
						break;
				}
				else
				{
					system("clear");
					puts("\t\t\t没有该教师");
					printf("\n\n\t\t\t按回车键返回");
					get_char();		//用于接收多余输入的字符
					break;
				}
			}			
			break;
		case '3':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要查找的年龄：");
			scanf("%d", &temp.age);
			get_char();		//用于接收多余输入的字符
			
			teacher_temp = find_teacher(teahead, &temp, cmp_teacher_age);
			
			while (1)
			{
				if (teacher_temp != NULL)
				{
					show_me_teacher(teacher_temp, show_atea);
					printf("\n\n\t\t\t是否需要修改(Y/N):");
					ch = getchar();
					get_char();		//用于接收多余输入的字符
				
					if ('y' == ch || 'Y' == ch)
					{
						while (1)
						{
							if (flog == 1)
							{
								flog = 0;
								break;
							}					
							change_admteacher_login(teacher_temp);			//管理员修改教师子系统
						}
						break;
					}
					else if ('n' == ch || 'N' == ch)
						break;
				}
				else
				{
					system("clear");
					puts("\t\t\t没有该教师");
					printf("\n\n\t\t\t按回车键返回");
					get_char();		//用于接收多余输入的字符			
				}
			}
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	return;
}


/*功能：修改窗口*/
/*参数：teacher_temp为数据指针*/
/*返回值：无*/
void change_admteacher(node_t *teacher_temp)
{
	while (1)
	{
		if (flog == 1)
		{
			flog = 0;
			break;
		}					
		change_admteacher_login(teacher_temp);			//管理员修改教师子系统
	}	
			
	system("clear");
	show_me_teacher(teacher_temp, show_atea);
	printf("\n\n\t\t修改之后教师信息按回车键返回");
	get_char();		//用于接收多余输入的字符			

	return;
}


/*功能：查找、修改学生信息菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char find_student_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t查找学生窗口");
	puts("\n\n\t\t\t1.按编号查找\t2.按姓名查找\t3.按年龄查找");
	puts("\n\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t请选择查找方式：");

	char ch = getchar();
	get_char();		//用于接收多余输入的字符

	return ch;
}


/*功能：查找、修改教师信息菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char find_teacher_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t查找教师窗口");
	puts("\n\n\t\t\t1.按编号查找\t2.按姓名查找\t3.按年龄查找");
	puts("\n\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t请选择查找方式：");

	char ch = getchar();
	get_char();

	return ch;
}


/*功能：管理员修改学生子系统*/
/*参数：student_temp为该学生指针*/
/*返回值：无*/
void change_admstudent_login(node_t *student_temp)
{
	char ch = change_admstudent_menu();		//管理员修改学生菜单
	stu_t *temp =(stu_t *)student_temp->data; 
	char newpasswd[32] = {"123456\n"};

	switch (ch)
	{
		case '1':		
			memcpy(temp->passwd, newpasswd, sizeof(newpasswd)); 
			system("clear");
			puts("\n\n\n\t\t\t\t密码已被重置为123456");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			system("clear");
			show_me_student(student_temp, show_astu);
			printf("\n\n\t\t修改之后学生信息按回车键返回");
			get_char();		//用于接收多余输入的字符
			break;
		case '2':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入班级名称：");
			gets(temp->class_num);
			puts("\n\n\n\t\t\t\t班级修改成功");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			system("clear");
			show_me_student(student_temp, show_astu);
			printf("\n\n\t\t修改之后学生信息按回车键返回");
			get_char();		//用于接收多余输入的字符
			break;
		case '3':
			system("clear");
			delete_me_student(stuhead, student_temp->data, cmp_student_num);
			puts("\n\n\n\t\t\t\t删除成功");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			flog = 1;
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

		
	return;
}


/*功能：修改学生信息菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char change_admstudent_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t修改学生信息窗口");
	puts("\n\n\t\t\t\t1.修改学生密码\t2.修改学生班级\t3.删除该学生");
	puts("\n\t\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t\t请选择需要修改的信息：");

	char ch = getchar();
	get_char();

	return ch;
}


/*功能：管理员修改教师子系统*/
/*参数：teacher_temp为该教师指针*/
/*返回值：无*/
void change_admteacher_login(node_t *teacher_temp)
{
	char ch = change_admteacher_menu();		//管理员修改教师菜单
	tea_t *temp =(tea_t *)teacher_temp->data; 
	char newpasswd[32] = {"123456\n"};

	switch (ch)
	{
		case '1':		
			memcpy(temp->passwd, newpasswd, sizeof(newpasswd)); 
			system("clear");
			puts("\n\n\n\t\t\t\t密码已被重置为123456");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			system("clear");
			show_me_teacher(teacher_temp, show_atea);
			printf("\n\n\t\t修改之后教师信息按回车键返回");
			get_char();		//用于接收多余输入的字符
			break;
		case '2':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入班级名称：");
			gets(temp->class_num);
			puts("\n\n\n\t\t\t\t班级修改成功");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			system("clear");
			show_me_teacher(teacher_temp, show_atea);
			printf("\n\n\t\t修改之后教师信息按回车键返回");
			get_char();		//用于接收多余输入的字符
			break;
		case '3':
			system("clear");
			delete_me_teacher(teahead, teacher_temp, cmp_teacher_num);
			puts("\n\n\n\t\t\t\t删除成功");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			flog = 1;
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}
	
	return;
}


/*功能：修改教师信息菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char change_admteacher_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t修改教师信息窗口");
	puts("\n\n\t\t\t\t1.修改教师密码\t2.修改教师班级\t3.删除该教师");
	puts("\n\t\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t\t请选择需要修改的信息：");

	char ch = getchar();
	get_char();

	return ch;
}


/*功能：查看自己信息*/
/*参数：无*/
/*返回值：无*/
void show_teacher_self(void)
{
	show_me_teacher(tea_self, show_atea);			//显示教师全部信息函数
	while (1)
	{
		printf("\n\n\t\t\t是否需要修改(Y/N):");
		char ch = getchar();
		get_char();						//用于接收多余输入的字符

		if ('y' == ch || 'Y' == ch)
		{
			while (1)
			{
				if (flog == 1)
				{
					break;
				}
				change_teame_login();
			}
			break;
		}
		else if ('n' == ch || 'N' == ch)
			break;
	}
	flog = 1;
	return;
}


/*功能：查看自己信息菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char change_me_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t修改自己信息窗口");
	puts("\n\n\t\t\t\t1.修改姓名\t2.修改年龄\t3.修改密码");
	puts("\n\t\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t\t请选择修改内容：");

	char ch = getchar();
	get_char();

	return ch;
}


/*功能：教师查看自己信息子系统*/
/*参数：无*/
/*返回值：无*/
void change_teame_login(void)
{
	
	char ch = change_me_menu();				//查看自己信息菜单
	tea_t *self = (tea_t *)tea_self->data;

	switch (ch)
	{
		case '1':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要修改成的姓名:");
			fgets(self->name, sizeof(self->name), stdin);
			f_gets(self->name, sizeof(self->name));
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case '2':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要修改成的年龄:");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				self->age = input_num();
			}
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case '3':
			change_teacher_passwd(self);
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case 'u':
			show_me_teacher(tea_self, show_atea);			//显示教师全部信息函数
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}
	return;
}



/*功能：查看自己信息*/
/*参数：无*/
/*返回值：无*/
void show_student_self(void)
{
	show_me_student(stu_self, show_astudent);			//显示教师全部信息函数
	while (1)
	{
		printf("\n\n\t\t\t是否需要修改(Y/N):");
		char ch = getchar();
		get_char();						//用于接收多余输入的字符

		if ('y' == ch || 'Y' == ch)
		{	
			while (1)
			{
				if (flog == 1)
				{
					break;
				}
				change_stume_login();
			}
			break;
		}
		else if ('n' == ch || 'N' == ch)
			break;
	}
	flog = 1;
	return;
}


/*功能：学生查看自己信息子系统*/
/*参数：无*/
/*返回值：无*/
void change_stume_login(void)
{
	
	char ch = change_me_menu();				//查看自己信息菜单
	stu_t *self = (stu_t *)stu_self->data;

	switch (ch)
	{
		case '1':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要修改成的姓名:");
			fgets(self->name, sizeof(self->name), stdin);
			f_gets(self->name, sizeof(self->name));
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case '2':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入要修改成的年龄:");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				self->age = input_num();
			}
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case '3':
			change_student_passwd(self);
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case 'u':
			show_me_student(stu_self, show_astudent);			//显示教师全部信息函数
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}
	return;
}


//教师显示全部学生子菜单
char show_teastudent_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t显示全部学生窗口");
	puts("\n\n\t\t\t1.显示语文成绩\t2.显示数学成绩\t3.显示c语言成绩");
	puts("\n\t\t\t4.显示全部成绩\t5.按编号显示学生");
	puts("\n\t\t\tu.返回上层目录\tq.退出系统");

	printf("\n\n\n\t\t\t请选择显示方式：");
	char ch = getchar();
	get_char();		//用于接收多余输入的字符

	return ch;
}


//教师显示全部学生子系统
void show_teastudent_login(void)
{
	char ch = show_teastudent_menu();		//显示全部学生子菜单

	switch (ch)
	{
		case '1':
			system("clear");
			sort_student(stuhead, cmp_student_chinese);	//排序学生结构体
			write_rank(stuhead);				//输入学生名次
			puts("\n\n\n\t\t\t\t显示全部学生语文成绩窗口");
			puts("\n\t\t编号\t语文成绩\t名次");
			show_all_student(stuhead, show_score_chinese);	//显示学生链表中全部学生的姓名
			printf("\n\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符
			break;
		case '2':
			system("clear");
			sort_student(stuhead, cmp_student_math);
			write_rank(stuhead);				//输入学生名次
			puts("\n\n\n\t\t\t\t\t显示全部学生数学成绩窗口");
			puts("\n\t\t编号\t数学成绩\t名次");
			show_all_student(stuhead, show_score_math);		//显示学生链表中全部学生的全部信息
			printf("\n\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符;
			break;
		case '3':
			system("clear");
			sort_student(stuhead, cmp_student_cprogram);
			write_rank(stuhead);				//输入学生名次
			puts("\n\n\n\t\t\t\t\t显示全部学生c语言成绩窗口");
			puts("\n\t\t编号\tc语言成绩\t名次");
			show_all_student(stuhead, show_score_cprogram);		//显示学生链表中全部学生的全部信息
			printf("\n\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符;
			break;
		case '4':
			system("clear");
			sort_student(stuhead, cmp_student_ascore);
			write_rank(stuhead);				//输入学生名次
			puts("\n\n\n\t\t\t\t\t显示全部学生全部成绩窗口");
			puts("\n\t\t编号\t语文成绩\t数学成绩\tc语言成绩\t名次");
			show_all_student(stuhead, show_ascore);		//显示学生链表中全部学生的全部信息
			printf("\n\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符;
			break;
		case '5':
			system("clear");
			sort_student(stuhead, cmp_student_num);
			puts("\n\n\n\t\t\t\t\t显示全部学生窗口");
			puts("\n\t\t编号\t语文成绩\t数学成绩\tc语言成绩\t名次");
			show_all_student(stuhead, show_ascore);		//显示学生链表中全部学生的全部信息
			printf("\n\t\t按回车键返回");
			get_char();				//用于接收多余输入的字符;
			break;
		case 'u':
			flog = 1;	
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	return;
}


/*功能：修改学生信息菜单*/
/*参数：无*/
/*返回值：ch为选择参数*/
char change_teastudent_menu(void)
{
	system("clear");
	puts("\n\n\n\n\t\t\t\t\t修改学生信息窗口");
	puts("\n\n\t\t\t\t1.修改语文成绩\t2.修改数学成绩\t3.修改c语言成绩");
	puts("\n\t\t\t\tu.返回上层目录\tq.退出系统");
	printf("\n\n\n\t\t\t\t请选择需要修改的信息：");

	char ch = getchar();
	get_char();

	return ch;
}


/*功能：教师修改学生子系统*/
/*参数：student_temp为该学生指针*/
/*返回值：无*/
void change_teastudent_login(node_t *student_temp)
{
	char ch = change_teastudent_menu();		//教师修改学生菜单
	stu_t *temp =(stu_t *)student_temp->data;

	switch (ch)
	{
		case '1':		
			system("clear");
			printf("\n\n\n\t\t\t\t请输入语文成绩：");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				temp->score.chinese = input_num();
			}	
			puts("\n\n\n\t\t\t\t成绩修改成功");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case '2':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入数学成绩：");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				temp->score.math = input_num();
			}
			puts("\n\n\n\t\t\t\t成绩修改成功");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case '3':
			system("clear");
			printf("\n\n\n\t\t\t\t请输入c语言成绩：");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				temp->score.cprogram = input_num();
			}
			puts("\n\n\n\t\t\t\t成绩修改成功");
			printf("\n\n\t\t\t\t按回车键进行下一步");
			get_char();
			break;
		case 'u':
			flog = 1;
			break;
		case 'q':
			quit();
			break;
		default :
			break;
	}

	system("clear");
	show_me_student(student_temp, show_astudent);		//显示学生的全部信息
	printf("\n\n\t\t修改之后学生信息按回车键返回");
	get_char();		//用于接收多余输入的字符	
	return;

}


/*功能：修改密码函数*/
/*参数：无*/
/*返回值：0成功*/
int change_student_passwd(stu_t *self)
{
	char ch;	
	char passwd1[32];
	char passwd2[32];

	while (1)
	{
		system("clear");
		printf("\n\n\n\t\t\t\t请输入新密码:");
		fgets(passwd1, sizeof(passwd1), stdin);
		f_gets(passwd1, sizeof(passwd1));

		printf("\n\n\t\t\t\t请再一次输入新密码:");
		fgets(passwd2, sizeof(passwd2), stdin);
		f_gets(passwd2, sizeof(passwd2));

		if (!strcmp(passwd1, passwd2))
		{
			strcpy(self->passwd, passwd2);
			puts("\n\n\t\t\t\t密码修改成功");
			flog = 1;
		}
		else
		{
			puts("\n\n\t\t\t\t密码修改失败");
			printf("\n\t\t\t\t是否继续修改(Y/N):");
			ch = getchar();
			get_char();
			while (1)
			{
				if ('y' == ch || 'Y' == ch)
					break;	
				else if ('n' == ch || 'N' == ch)
				{
					flog = 1;
					break;
				}
			}
		}
		if (flog == 1)
		{
			flog = 0;
			break;
		}
	}
	return 0;
}


/*功能：修改密码函数*/
/*参数：无*/
/*返回值：0成功*/
int change_teacher_passwd(tea_t *self)
{
	char ch;
	char passwd1[32];
	char passwd2[32];

	while (1)
	{
		system("clear");
		printf("\n\n\n\t\t\t\t请输入新密码:");
		fgets(passwd1, sizeof(passwd1), stdin);
		f_gets(passwd1, sizeof(passwd1));

		printf("\n\n\t\t\t\t请再一次输入新密码:");
		fgets(passwd2, sizeof(passwd2), stdin);
		f_gets(passwd2, sizeof(passwd2));

		if (!strcmp(passwd1, passwd2))
		{
			strcpy(self->passwd, passwd2);
			puts("\n\n\t\t\t\t密码修改成功");
			flog = 1;
		}
		else
		{
			puts("\n\n\t\t\t\t密码修改失败");
			printf("\n\t\t\t\t是否继续修改(Y/N):");
			ch = getchar();
			get_char();
			while (1)
			{
				if ('y' == ch || 'Y' == ch)
					break;	
				else if ('n' == ch || 'N' == ch)
				{
					flog = 1;
					break;
				}
			}
		}
		if (flog == 1)
		{
			flog = 0;
			break;
		}
	}
	return 0;
}

/*功能：保存系统数据*/
/*参数：无*/
/*返回值：无*/
void menu_end(void)
{
	char ch;
	while (1)
	{
		system("clear");
		printf("\n\n\n\n\t\t\t\t是否保存更改的信息(Y/N):");
		ch = getchar();
		get_char();
		if ('y' == ch || 'Y' == ch)
		{
			write_student_file(stuhead);	//保存学生信息
			write_teacher_file(teahead);	//保存教师信息
			puts("\n\n\n\t\t\t\t写入成功");
			printf("\n\n\t\t\t\t按回车键返回");
        		get_char();     	        //用于接收多余输入的字符 	
			break;
		}
		else if ('n' == ch || 'N' == ch)
			break;
	}
	destroy_student_clist(stuhead);	//销毁学生链表
	destroy_teacher_clist(teahead);	//销毁教师链表
	return;
}


/*功能：退出系统函数*/
/*参数：无*/
/*返回值：无*/
void quit(void)
{
	menu_end();		//菜单结束处理	
	show_end_logo();	//系统退出logo
	exit(0);
	return;
}
