/*MENU.H文件：实现系统的各个子系统菜单*/
/*时间：2014-1-25*/
/*版本：1.0*/
#ifndef MENU_H
#define MENU_H

#include "student.h"
#include "teacher.h"
#include "public.h"

//初始化系统
void menu_init(void);
//退出系统函数
void quit(void);		
//选择模式
void menu(void);		
//显示主菜单
char main_menu(void);
//输入管理员用户名和密码		
void admin_menu(void);
//管理员验证
int test_admin_menu(char *user, char *passwd);
//输入教师用户名和密码
void teacher_menu(void);
//教师验证
int test_teacher_menu(char *user, char *passwd);
//输入学生用户名和密码
void student_menu(void);
//学生验证
int test_student_menu(char *user, char *passwd);
//管理员子系统
void admin_login_menu(void);
//教师子系统
void teacher_login_menu(void);
//学生子系统
void student_login_menu(void);
//管理员显示菜单
char admin_inside_menu(void);
//教师显示菜单
char teacher_inside_menu(void);
//学生显示菜单
char student_inside_menu(void);
//显示全部学生子菜单
char show_student_menu(void);
//显示全部学生子系统
void show_student_login(void);
//显示全部教师子菜单
char show_teacher_menu(void);
//显示全部教师子系统
void show_teacher_login(void);
//查找、修改学生信息子系统
typedef void (* cstu_t) (node_t *student_temp);
void find_student_login(cstu_t f);
//查找、修改学生信息菜单
char find_student_menu(void);
//查找、修改教师信息子系统
void find_teacher_login(void);
//查找、修改教师信息菜单
char find_teacher_menu(void);
//管理员修改学生子系统
void change_admstudent_login(node_t *student_temp);
//管理员修改教师子系统
void change_admteacher_login(node_t *teacher_temp);
//教师修改学生子系统
void change_teastudent_login(node_t *student_temp);
//管理员修改学生菜单
char change_admstudent_menu(void);
//管理员修改教师菜单
char change_admteacher_menu(void);
//显示自己信息菜单
char change_me_menu(void);
//显示自己信息子系统
void change_teame_login(void);
//查看自己信息
void show_teacher_self(void);
//显示自己信息子系统
void change_stume_login(void);
//查看自己信息
void show_student_self(void);
//教师显示全部学生子菜单
char show_teastudent_menu(void);
//教师显示全部学生子系统
void show_teastudent_login(void);
//修改密码函数
int change_teacher_passwd(tea_t *self);
//修改密码函数
int change_student_passwd(stu_t *self);
//菜单结束函数
void menu_end(void);



#endif
