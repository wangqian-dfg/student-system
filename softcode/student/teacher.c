/*TEACHER.C文件：实现TEACHER.H的函数功能*/
/*时间：2014-1-25*/
/*版本：1.0*/
#include "teacher.h"

extern int flog;			//标志位
int fun_tea = 0;			//确定函数的调用次数
int num_tea = 0;			//保存教师编号
int t_count = 0;			//保存教师人数
extern int num_temp_teacher;		//确定教师编号


/*功能：加载教师数据*/
/*参数：无*/
/*返回值：teahead为教师链表的头指针*/
node_t *read_teacher_file(void)
{
	FILE *fp_tea = fopen("teacher_data", "r");		//打开教师数据文件
	node_t * teahead = create_clist();			//创建教师链表
	ERROR(teahead, NULL, "teahead is null", NULL);
	ERROR(fp_tea, NULL, "fp_tea is null", NULL);

	tea_t temp;
	int i;
	fread(&t_count, sizeof(int), 1, fp_tea);		//读取文件中的教师数量
	fread(&num_tea, sizeof(int), 1, fp_tea);		//读取文件中的教师编号

	for (i=0; i<t_count; i++)
	{
		fread(&temp, sizeof(tea_t), 1, fp_tea);		//读取文件中的教师数据
		insert_clist(teahead, &temp, sizeof(tea_t));	//保存到教师链表中
	}

	fclose(fp_tea);						//关闭文件

	return teahead;
}


/*功能：添加教师并初始化教师姓名、编号、密码、班级*/
/*参数：teahead为教师链表的头指针*/
/*返回值：0为添加成功； -1为添加失败*/
int add_teacher(node_t *teahead)
{
	system("clear");
	printf("\n\n\t\t\t\t\t添加教师窗口");
	ERROR(teahead, NULL, "head is null", -1);
	fun_tea++;				//确定函数的调用次数

	tea_t *tea_temp = malloc(sizeof(tea_t));
	tea_temp->num = num_temp_teacher;	
	char passwd[32] = {"123456\n"};		//设置教师初始密码为123456
	memcpy(&(tea_temp->passwd), passwd, sizeof(passwd));

	printf("\n\n\n\n\t\t\t\t请输入教师姓名：");
	fgets(tea_temp->name, sizeof(tea_temp->name), stdin);
	f_gets(tea_temp->name, sizeof(tea_temp->name));
	printf("\n\t\t\t\t请输入教师所任班级：");
	gets(tea_temp->class_num);

	if (1 == fun_tea)
	{
		printf("\n\t\t\t\t是否设置起始教师编号(Y/N):");
		char ch = getchar();
		get_char();			//接收多余字符

		if ('y' == ch || 'Y' == ch)
		{	
			printf("\n\t\t\t\t请设置起始编号：");
			while (1)	
			{	
				if (flog == 1)
				{
					flog = 0;
					break;
				}
				tea_temp->num = input_num();
			}
			//scanf("%d", &(tea_temp->num));
			num_temp_teacher = tea_temp->num;
			get_char();			//接收多余字符
		}
		else if ('n' == ch || 'N' == ch)
		{
			tea_temp->num = num_tea + 1;
			num_temp_teacher = tea_temp->num;
		}
	}
	else
		id_teacher_num(&(tea_temp->num));	//教师编号自加函数
	
	while (1)
	{
		if (flog == 1)
		{
			flog = 0;
			break;
		}
		choice_course(tea_temp);		//选择教师所任课程
	}

	t_count++;
	num_tea = tea_temp->num;
	int size = sizeof(tea_t);
	insert_clist(teahead, tea_temp, size);

	return 0;
 }


/*功能：选择教师所任课程*/
/*参数：tea_temp为教师链表指针*/
/*返回值：无*/
void choice_course(tea_t *tea_temp)
{
	system("clear");
	puts("\n\n\t\t\t\t\t选择课程菜单");
	puts("\n\t\t\t\t1.语文");
	puts("\n\t\t\t\t2.数学");

	puts("\n\t\t\t\t3.c语言");
	printf("\n\n\t\t\t\t请选择课程：");
	char ch = getchar();
	get_char();
	
	switch (ch)
	{
		case '1':
			flog = 1;
			strcpy(tea_temp->course, "chinese\t");
			break;
		case '2':
			flog = 1;
			strcpy(tea_temp->course, "math\t");
			break;
		case '3':
			flog = 1;
			strcpy(tea_temp->course, "cprogram");
			break;
		default:
			break;
	}

	return;
}


/*功能：删除链表中所有教师成员*/
/*参数：teahead为教师链表的头指针*/
/*返回值：0为成功； -1为失败*/
int delete_all_teacher(node_t *teahead)
{
	ERROR(teahead, NULL, "teahead is null", -1);
	int res = delete_all_clist(teahead);		//删除链表中的成员

	if (0 == res)
	{
		system("clear");
		t_count = 0;
		num_tea = 0;
		printf("\n\n\t\t\t\t\t删除全部教师窗口");
		return 0;
	}
	else
		return -1;
}


/*功能：以什么方式显示全部教师的信息*/
/*参数：teahead为教师的数据的指针； f为以什么方式显示*/
/*返回值：0为成功； -1为失败*/
int show_all_teacher(node_t *teahead, showfun_t f)
{
	ERROR(teahead, NULL, "teahead is null", -1);
	ERROR(f, NULL, "f is null", -1);

	show_all_clist(teahead, f);		//显示链表中的全部成员
	return 0;
}


/*功能：显示教师的姓名*/
/*参数：data为教师的数据*/
/*返回值：无*/
void show_teacher_name(void *data)
{
	tea_t *tea_temp = (tea_t *)data;
	printf("\n\t\t\t%s", tea_temp->name);
	return;
}


/*功能：显示教师的所有信息*/
/*参数：data为教师的数据*/
/*返回值：无*/
void show_atea(void *data)
{
	ERROR(data, NULL, "data is null", );
	tea_t *tea_temp = (tea_t *)data;
	printf("\n\t\t\t%d\t%d\t%s\t%s\t\t%s", tea_temp->num, tea_temp->age, tea_temp->course, tea_temp->class_num, tea_temp->name);
	return;
}


/*功能：以什么方式显示某个教师的信息*/
/*参数：teahead为教师的数据的指针； f为以什么方式显示*/
/*返回值：0为成功； -1为失败*/
int show_me_teacher(node_t *teahead, showfun_t f)
{
	system("clear");
	printf("\n\n\t\t\t显示学生个人信息窗口\n");
	puts("\n\n\t\t\t编号\t年龄\t所任课程\t所任班级\t姓名\t");
	ERROR(teahead, NULL, "teahead is null", -1);
	
	ERROR(f, NULL, "f is null", -1);
	show_me_clist(teahead, f);		//显示链表中的某个成员
	return 0;
}


/*功能：查找教师信息*/
/*参数：teahead为教师头指针； data为教师的数据； f为以什么方式*/
/*返回值：tea_temp为目标指针*/
node_t *find_teacher(node_t *teahead, void *data, cmpfun_t f)
{
	ERROR(teahead, NULL, "teahead is null", NULL);
	ERROR(data, NULL, "data is null", NULL);
	ERROR(f, NULL, "f is null", NULL);
	node_t *tea_temp = find_clist(teahead, data, f);	//查找整个链表
	return tea_temp;
}

/*功能：排序教师函数*/
/*参数：teahead为教师链表头指针； f为以什么方式比较*/
/*返回值：0为成功； -1为失败*/
int sort_teacher(node_t *teahead, cmpfun_t f)
{
	ERROR(teahead, NULL, "teahead is null", -1);
	ERROR(f, NULL, "f is null", -1);
	int size = sizeof(tea_t);
	sort_clist(teahead, f, size);			//排序整个链表

	return 0;
}


/*功能：比较两个成员的年龄*/
/*参数：data1为教师的数据； data2为教师数据*/
/*返回值：d1->age - d2->age*/
int cmp_teacher_age(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	tea_t *d1 = (tea_t *)data1;
	tea_t *d2 = (tea_t *)data2;

	return d1->age - d2->age;
}


/*功能：比较两个成员的编号*/
/*参数：data1为教师的数据； data2为教师数据*/
/*返回值：d1->num - d2->num*/
int cmp_teacher_num(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	tea_t *d1 = (tea_t *)data1;
	tea_t *d2 = (tea_t *)data2;

	return d1->num - d2->num;
}


/*功能：比较两个成员的姓名*/
/*参数：data1为教师的数据； data2为教师数据*/
/*返回值：strcmp(d1->name, d2->name)*/
int cmp_teacher_name(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	tea_t *d1 = (tea_t *)data1;
	tea_t *d2 = (tea_t *)data2;

	return strcmp(d1->name, d2->name);
}


/*功能：删除某个教师*/
/*参数：teahead为该生指针*/
/*返回值：0为成功， -1为失败*/
int delete_me_teacher(node_t *teahead, void *data, cmpfun_t f)
{
	ERROR(teahead, NULL, "teahead is null", -1);
	ERROR(data, NULL, "data is null", -1);
	ERROR(f, NULL, "f is null", -1);
	int res = delete_me_clist(teahead, data, f);		//删除该链表成员
	if (0 == res)
	{
		t_count--;
		return 0;
	}
	else 
		return -1;
}


/*功能：显示学生的学号*/
/*参数：data为学生的数据*/
/*返回值：无*/
int write_teacher_file(node_t *teahead)
{
	FILE *fp_tea = fopen("teacher_data", "w");
	ERROR(fp_tea, NULL, "fp_tea is null", -1);
	ERROR(teahead, NULL, "teahead is null", -1);
	int i;

	node_t *temp = teahead->next;
	fwrite(&t_count, sizeof(int), 1, fp_tea);
	fwrite(&num_tea, sizeof(int), 1, fp_tea);

	for(i=0; i<t_count; i++)
	{
		fwrite(temp->data, sizeof(tea_t), 1, fp_tea);
		temp = temp->next;
	}

	fclose(fp_tea);
	return 0;
}


/*功能：显示学生的学号*/
/*参数：data为学生的数据*/
/*返回值：无*/
int destroy_teacher_clist(node_t *teahead)
{
	ERROR(teahead, NULL, "teahead is null", -1);
	destroy_clist(&teahead);
	return 0;
}
