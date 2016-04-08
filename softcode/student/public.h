/*PUBLIC.H文件：实现底层链表的创建、插入、修改、查找、删除、销毁、排序*/
/*时间：2014-1-25*/
/*版本：1.0*/
#ifndef PUBLIC_H
#define PUBLIC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//宏定义错误检查
#define ERROR(x, y, message, z)		if (x == y)		\
					{			\
						perror(message);\
						return z;	\
					}


//定义链表结构体成员
typedef struct clist
{
	void *data;
	struct clist *next;
}node_t;


//显示欢迎logo
void show_start_logo(void);
//用于接收多余输入的字符
void get_char(void);
//创建学生编号函数
int id_student_num(int *num);
//创建教师编号函数
int id_teacher_num(int *num);
//创建一个空的单项循环链表
node_t *create_clist(void);
//向空链表中增加节点，size为要储存数据的大小
int insert_clist(node_t *head, void *data, int size);	
//删除链表中所有的成员
int delete_all_clist(node_t *head);
typedef void (*showfun_t) (void *data);
//显示链表的全部信息
void show_all_clist(node_t *head, showfun_t f);
typedef int (*cmpfun_t) (void *data1, void *data2);
//查找链表中的某个成员
node_t *find_clist(node_t *head, void *data, cmpfun_t f);
//显示链表中的某个成员信息
void show_me_clist(node_t *head, showfun_t f);
//删除该成员
int delete_me_clist(node_t *head, void *data, cmpfun_t f);
//排序链表中的成员
int sort_clist(node_t *head, cmpfun_t f, int size);
//销毁整个链表
int destroy_clist(node_t **head);
//显示结束logo
void show_end_logo(void);
//检测输入的是不是数字
int input_num(void);
//接收多余字符串
int f_gets(char *temp, int size);

#endif
