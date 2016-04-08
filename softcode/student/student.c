/*STUDENT.C文件：实现STUDENT.H的函数功能*/
/*时间：2014-1-25*/
/*版本：1.0*/
#include "student.h"

int fun_stu = 0;			//确定函数的调用次数
int num_stu = 0;			//保存学生编号
int s_count = 0;			//保存学生总数
extern int num_temp_student;		//确定学生编号
extern int flog;

/*功能：加载学生数据*/
/*参数：无*/
/*返回值：stuhead为学生的头指针*/
node_t *read_student_file(void)
{
	FILE *fp_stu = fopen("student_data", "r");		//打开学生数据文件
	node_t * stuhead = create_clist();			//创建学生结构体链表
	ERROR(stuhead, NULL, "stuhead is null", NULL);
	ERROR(fp_stu, NULL, "fp_stu is null", NULL);

	stu_t temp;
	int i;
	fread(&s_count, sizeof(int), 1, fp_stu);		//读取文件中的学生数量
	fread(&num_stu, sizeof(int), 1, fp_stu);		//读取文件中的学生编号

	for (i=0; i<s_count; i++)
	{
		fread(&temp, sizeof(stu_t), 1, fp_stu);		//读取文件中的结构体成员
		insert_clist(stuhead, &temp, sizeof(stu_t));	//插入到学生链表中
	}

	fclose(fp_stu);						//关闭文件

	return stuhead;
}


/*功能：添加学生并初始化学生姓名、学号、密码、班级*/
/*参数：stuhead为学生链表的头指针*/
/*返回值：0为添加成功； -1为添加失败*/
int add_student(node_t *stuhead)
{
	system("clear");
	printf("\n\n\t\t\t\t\t添加学生窗口");
	ERROR(stuhead, NULL, "head is null", -1);
	fun_stu++;					//确定函数的调用次数

	stu_t *stu_temp = malloc(sizeof(stu_t));
	stu_temp->num = num_temp_student;	
	char passwd[32] = {"123456\n"};			//设置初始密码为123456
	memcpy(&(stu_temp->passwd), passwd, sizeof(passwd));

	printf("\n\n\n\n\t\t\t\t请输入学生姓名：");
	fgets(stu_temp->name, sizeof(stu_temp->name), stdin);
	f_gets(stu_temp->name, sizeof(stu_temp->name));
	printf("\n\t\t\t\t请输入学生班级：");
	gets(stu_temp->class_num);

	if (1 == fun_stu)
	{
		while (1)
		{
			printf("\n\t\t\t\t是否设置起始学生考号(Y/N):");
			char ch = getchar();
			get_char();			//用于接收多余的字符

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
					stu_temp->num = input_num();
				}
				//scanf("%d", &(stu_temp->num));
				num_temp_student = stu_temp->num;
				get_char();		//用于接收多余的字符
				break;
			}
			else if ('n' == ch || 'N' == ch)
			{
				stu_temp->num = num_stu + 1;
				num_temp_student = stu_temp->num;
				break;
			}
		}
		
	}
	else
		id_student_num(&(stu_temp->num));	//编号自增函数

	s_count++;					//学生个数加1
	num_stu = stu_temp->num;
	int size = sizeof(stu_t);
	insert_clist(stuhead, stu_temp, size);		//向学生链表中插入成员

	return 0;
 }


/*功能：删除全部学生信息*/
/*参数：stuhead为学生链表的头指针*/
/*返回值：无*/
int delete_all_student(node_t *stuhead)
{
	ERROR(stuhead, NULL, "stuhead is null", -1);
	int res = delete_all_clist(stuhead);		//删除链表中所有成员

	if (0 == res)
	{
		s_count = 0;
		num_stu = 0;
		system("clear");
		printf("\n\n\t\t\t\t\t删除全部学生窗口");
		return 0;
	}
	else
		return -1;
}


/*功能：以什么方式显示全部学生的信息*/
/*参数：stuhead为学生的数据的指针； f为以什么方式显示*/
/*返回值：0为成功； -1为失败*/
int show_all_student(node_t *stuhead, showfun_t f)
{
	ERROR(stuhead, NULL, "stuhead is null", -1);
	ERROR(f, NULL, "f is null", -1);

	show_all_clist(stuhead, f);		//显示链表中的成员
	return 0;
}


/*功能：显示学生的姓名*/
/*参数：data为学生的数据*/
/*返回值：无*/
void show_student_name(void *data)
{
	ERROR(data, NULL, "data is null", );
	stu_t *stu_temp = (stu_t *)data;
	printf("\n\t\t\t%s", stu_temp->name);
	return;
}


/*功能：显示学生的所有信息*/
/*参数：data为学生的数据*/
/*返回值：无*/
void show_astu(void *data)
{
	ERROR(data, NULL, "data is null", );
	stu_t *stu_temp = (stu_t *)data;
	printf("\n\t\t%d\t%s\t%d\t%s", stu_temp->num, stu_temp->class_num, stu_temp->age, stu_temp->name);
	
	return;
}


/*功能：显示学生的所有信息*/
/*参数：data为学生的数据*/
/*返回值：无*/
void show_astudent(void *data)
{
	ERROR(data, NULL, "data is null", );
	stu_t *stu_temp = (stu_t *)data;
	printf("\n\t\t%d\t%s\t%d\t%s\t\t%.2f\t%.2f\t%.2f\t%d", stu_temp->num, stu_temp->class_num, stu_temp->age, stu_temp->name, stu_temp->score.chinese, stu_temp->score.math, stu_temp->score.cprogram, stu_temp->rank);
	
	return;
}


/*功能：显示学生的语文成绩和名次*/
/*参数：data为学生的数据*/
/*返回值：无*/
void show_score_chinese(void *data)
{
	ERROR(data, NULL, "data is null", );
	stu_t *stu_temp = (stu_t *)data;
	printf("\n\t\t%d\t%.2f\t\t%d", stu_temp->num, stu_temp->score.chinese, stu_temp->rank);
	return;
}


/*功能：显示学生的数学成绩和名次*/
/*参数：data为学生的数据*/
/*返回值：无*/
void show_score_math(void *data)
{
	ERROR(data, NULL, "data is null", );
	stu_t *stu_temp = (stu_t *)data;
	printf("\n\t\t%d\t%.2f\t\t%d", stu_temp->num, stu_temp->score.math, stu_temp->rank);
	return;
}


/*功能：显示学生的c语言成绩和名次*/
/*参数：data为学生的数据*/
/*返回值：无*/
void show_score_cprogram(void *data)
{
	ERROR(data, NULL, "data is null", );
	stu_t *stu_temp = (stu_t *)data;
	printf("\n\t\t%d\t%.2f\t\t%d", stu_temp->num, stu_temp->score.cprogram, stu_temp->rank);
	return;
}


/*功能：显示学生的所有成绩和名次*/
/*参数：data为学生的数据*/
/*返回值：无*/
void show_ascore(void *data)
{
	ERROR(data, NULL, "data is null", );
	stu_t *stu_temp = (stu_t *)data;
	printf("\n\t\t%d\t%.2f\t\t%.2f\t\t%.2f\t\t%d", stu_temp->num, stu_temp->score.chinese, stu_temp->score.math, stu_temp->score.cprogram, stu_temp->rank);
	return;
}


/*功能：查找学生函数*/
/*参数：stuhead为学生链表头指针； data为学生的数据； f为以什么方式比较*/
/*返回值：stu_temp为查找到的指针*/
node_t *find_student(node_t *stuhead, void *data, cmpfun_t f)
{
	ERROR(stuhead, NULL, "stuhead is null", NULL);
	ERROR(data, NULL, "data is null", NULL);
	ERROR(f, NULL, "f is null", NULL);
	node_t *stu_temp = find_clist(stuhead, data, f);	//查找整个链表
	return stu_temp;
}


/*功能：排序学生函数*/
/*参数：stuhead为学生链表头指针； f为以什么方式比较*/
/*返回值：0为成功； -1为失败*/
int sort_student(node_t *stuhead, cmpfun_t f)
{
	ERROR(stuhead, NULL, "stuhead is null", -1);
	ERROR(f, NULL, "f is null", -1);
	int size = sizeof(stu_t);
	sort_clist(stuhead, f, size);			//排序整个链表

	return 0;
}


/*功能：比较两个成员的总成绩*/
/*参数：data1为学生的数据； data2为学生数据*/
/*返回值：d1->age - d2->age*/
int cmp_student_ascore(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	stu_t *d1 = (stu_t *)data1;
	stu_t *d2 = (stu_t *)data2;

	float a1, a2;
	a1 = d1->score.chinese + d1->score.math + d1->score.cprogram;
	a2 = d2->score.chinese + d2->score.math + d2->score.cprogram;
	return a1 - a2;
}


/*功能：比较两个成员的语文成绩*/
/*参数：data1为学生的数据； data2为学生数据*/
/*返回值：d1->age - d2->age*/
int cmp_student_chinese(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	stu_t *d1 = (stu_t *)data1;
	stu_t *d2 = (stu_t *)data2;

	return d1->score.chinese - d2->score.chinese;
}


/*功能：比较两个成员的数学成绩*/
/*参数：data1为学生的数据； data2为学生数据*/
/*返回值：d1->age - d2->age*/
int cmp_student_math(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	stu_t *d1 = (stu_t *)data1;
	stu_t *d2 = (stu_t *)data2;

	return d1->score.math - d2->score.math;
}


/*功能：比较两个成员的c语言成绩*/
/*参数：data1为学生的数据； data2为学生数据*/
/*返回值：d1->age - d2->age*/
int cmp_student_cprogram(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	stu_t *d1 = (stu_t *)data1;
	stu_t *d2 = (stu_t *)data2;

	return d1->score.cprogram - d2->score.cprogram;
}


/*功能：比较两个成员的年龄*/
/*参数：data1为学生的数据； data2为学生数据*/
/*返回值：d1->age - d2->age*/
int cmp_student_age(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	stu_t *d1 = (stu_t *)data1;
	stu_t *d2 = (stu_t *)data2;

	return d1->age - d2->age;
}


/*功能：比较两个成员的编号*/
/*参数：data1为学生的数据； data2为学生数据*/
/*返回值：d1->num - d2->num*/
int cmp_student_num(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	stu_t *d1 = (stu_t *)data1;
	stu_t *d2 = (stu_t *)data2;

	return d1->num - d2->num;
}


/*功能：比较两个成员的姓名*/
/*参数：data1为学生的数据； data2为学生数据*/
/*返回值：strcmp(d1->name, d2->name)*/
int cmp_student_name(void *data1, void *data2)
{
	ERROR(data1, NULL, "data1 is null", -1);
	ERROR(data2, NULL, "data2 is null", -1);
	stu_t *d1 = (stu_t *)data1;
	stu_t *d2 = (stu_t *)data2;

	return strcmp(d1->name, d2->name);
}


/*功能：以什么方式显示某个学生的信息*/
/*参数：stuhead为学生的数据的指针； f为以什么方式显示*/
/*返回值：0为成功； -1为失败*/
int show_me_student(node_t *stuhead, showfun_t f)
{
	system("clear");
	printf("\n\n\t\t\t显示学生个人信息窗口\n");
	puts("\n\t\t编号\t班级\t年龄\t姓名");
	ERROR(stuhead, NULL, "stuhead is null", -1);
	ERROR(f, NULL, "f is null", -1);
	show_me_clist(stuhead, f);		//显示链表中的某个成员信息
	return 0;
}


/*功能：删除某个学生*/
/*参数：stuhead为该生指针*/
/*返回值：0为成功， -1为失败*/
int delete_me_student(node_t *stuhead, void *data, cmpfun_t f)
{
	ERROR(stuhead, NULL, "stuhead is null", -1);
	ERROR(data, NULL, "data is null", -1);
	ERROR(f, NULL, "f is null", -1);
	int res = delete_me_clist(stuhead, data, f);		//删除该链表成员
	if (0 == res)
	{
		s_count--;
		return 0;
	}
	else 
		return -1;
}


//写入名次函数
int write_rank(node_t *stuhead)
{
	ERROR(stuhead, NULL, "stuhead is null", -1);
	node_t *temp = stuhead->next;
	int rank = 1;
	stu_t *stu_temp;

	while (temp != stuhead)
	{
		stu_temp = (stu_t *)temp->data;
		stu_temp->rank = rank;
		rank++;
		temp = temp->next;		
	}

	return 0;
}


/*功能：显示学生的学号*/
/*参数：data为学生的数据*/
/*返回值：无*/
int write_student_file(node_t *stuhead)
{
	FILE *fp_stu = fopen("student_data", "w");
	ERROR(fp_stu, NULL, "fp_stu is null", -1);
	ERROR(stuhead, NULL, "stuhead is null", -1);
	int i;

	node_t *temp = stuhead->next;
	fwrite(&s_count, sizeof(int), 1, fp_stu);
	fwrite(&num_stu, sizeof(int), 1, fp_stu);

	for(i=0; i<s_count; i++)
	{
		fwrite(temp->data, sizeof(stu_t), 1, fp_stu);
		temp = temp->next;
	}

	fclose(fp_stu);
	return 0;
}


/*功能：显示学生的学号*/
/*参数：data为学生的数据*/
/*返回值：无*/
int destroy_student_clist(node_t *stuhead)
{
	ERROR(stuhead, NULL, "stuhead is null", -1);
	destroy_clist(&stuhead);
	return 0;
}
