/*STUDENT.H文件：实现学生链表的创建、插入、修改、查找、删除、销毁、排序、显示、存储、读取*/
/*时间：2014-1-25*/
/*版本：1.0*/
#ifndef STUDENT_H
#define STUDENT_H

#include "public.h"

//创建学生成绩结构体
typedef struct student_score
{
	float chinese;
	float math;
	float cprogram;
}stuscore_t;
//创建学生结构体
typedef struct student
{
	int num;
	char name[16];
	char class_num[16];
	int age;
	char passwd[32];
	int rank;
	stuscore_t score;
}stu_t;


//加载学生数据
node_t *read_student_file(void);
//添加学生
int add_student(node_t *stuhead);
//删除所有学生信息
int delete_all_student(node_t *stuhead);
//显示全部学生信息
int show_all_student(node_t *stuhead, showfun_t f);
//显示已经存储学生的姓名
void show_student_name(void *data);	
//显示已经存储学生的全部信息
void show_astu(void *data);
//显示已经存储学生的语文成绩和名次
void show_score_chinese(void *data);
//显示已经存储学生的数学成绩和名次
void show_score_math(void *data);
//显示已经存储学生的C语言成绩和名次
void show_score_cprogram(void *data);
//显示已经存储学生的全部成绩和名次
void show_ascore(void *data);
//以某种方式查找学生
node_t *find_student(node_t *stuhead, void *data, cmpfun_t f);
//以某种方式排序
int sort_student(node_t *stuhead, cmpfun_t f);
//比较两个成员的总成绩
int cmp_student_ascore(void *data1, void *data2);
//比较两个成员的语文成绩
int cmp_student_chinese(void *data1, void *data2);
//比较两个成员的数学成绩
int cmp_student_math(void *data1, void *data2);
//比较两个成员的c语言成绩
int cmp_student_cprogram(void *data1, void *data2);
//比较两个成员的年龄
int cmp_student_age(void *data1, void *data2);
//比较两个成员的学号
int cmp_student_num(void *data1, void *data2);
//比较两个学生的姓名
int cmp_student_name(void *data1, void *data2);
//显示某个学生信息
int show_me_student(node_t *stuhead, showfun_t f);
//删除某个学生信息
int delete_me_student(node_t *stuhead, void *data, cmpfun_t f);
//显示自己的所有信息
void show_astudent(void *data);
//销毁学生链表函数
int destroy_student_clist(node_t *stuhead);
//写学生数据函数
int write_student_file(node_t *stuhead);
//写入名次函数
int write_rank(node_t *stuhead);

#endif
