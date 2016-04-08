/*TEACHER.H文件：实现教师链表的创建、插入、修改、查找、删除、销毁、排序、显示、存储、读取*/
/*时间：2014-1-25*/
/*版本：1.0*/
#ifndef TEACHER_H
#define TEACHER_H

#include "public.h"

//创建教师链表
typedef struct teacher
{
	int num;
	char name[16];
	int age;
	char class_num[16];
	char passwd[32];
	char course[16];
}tea_t;


//加载教师数据
node_t *read_teacher_file(void);
//添加教师
int add_teacher(node_t *teahead);
//选择教师所任课程
void choice_course(tea_t *tea_temp);
//删除链表中所有教师成员
int delete_all_teacher(node_t *teahead);
//显示全部教师信息
int show_all_teacher(node_t *teahead, showfun_t f);
//显示教师姓名
void show_teacher_name(void *data);
//显示教师的全部信息
void show_atea(void *data);
//查找教师
node_t *find_teacher(node_t *teahead, void *data, cmpfun_t f);
//显示某个教师的全部信息
int show_me_teacher(node_t *teahead, showfun_t f);
//比较两个成员的年龄
int cmp_teacher_age(void *data1, void *data2);
//比较两个成员的编号
int cmp_teacher_num(void *data1, void *data2);
//比较两个成员的姓名
int cmp_teacher_name(void *data1, void *data2);
//删除该教师成员
int delete_me_teacher(node_t *teahead, void *data, cmpfun_t f);
//排序教师函数
int sort_teacher(node_t *teahead, cmpfun_t f);
//写教师数据函数
int write_teacher_file(node_t *teahead);
//销毁教师链表
int destroy_teacher_clist(node_t *teahead);

#endif
