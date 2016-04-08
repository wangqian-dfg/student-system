/*PUBLIC.C文件：实现PUBLIC的函数功能*/
/*时间：2014-1-25*/
/*版本：1.0*/
#include "public.h"

int num_temp_student = 0;		//用于保存学生编号
int num_temp_teacher = 0;		//用于保存教师编号
extern int fun_stu;
extern int flog;


/*功能：显示系统启动logo*/
/*参数：无*/
/*返回值：无*/
void show_start_logo(void)
{
	int i = 1000;
	while (i--)
	{
		puts("\n\n\n\n\n\n\n\n\t\t\t\t欢迎使用教务管理系统");
		system("clear");
	}
	return;
}


/*功能：用于接收多余输入的字符*/
/*参数：无*/
/*返回值：无*/
void get_char(void)
{
	char temp[128];
	fgets(temp, sizeof(temp), stdin);
	return;
}


/*功能：创建编号*/
/*参数：num为该学生的编号*/
/*返回值：0为成功*/
int id_student_num(int *num)
{
	(*num) += 1;
	num_temp_student = *num;
	return 0;
}


/*功能：创建编号*/
/*参数：num为该教师的编号*/
/*返回值：0为成功*/
int id_teacher_num(int *num)
{
	(*num) += 1;
	num_temp_teacher = *num;
	return 0;
}


/*功能：创建一个空的单项循环链表*/
/*参数：无*/
/*返回值：创建好链表的头指针*/
node_t *create_clist(void)
{
	node_t *head = (node_t *)malloc(sizeof(node_t));		//动态分配链表头指针
	ERROR(head, NULL, "create clist error", NULL);
	head->data = NULL;
	head->next = head;

	return head;
}


/*功能：向空链表尾部增加成员*/
/*参数：head为链表的头指针； data要加入成员的数据； size为要加入数据所占的字节数*/
/*返回值：0代表成功； -1代表失败*/
int insert_clist(node_t *head, void *data, int size)
{
	ERROR(head, NULL, "head is null", -1);
	ERROR(data, NULL, "data is null", -1);
	node_t *newnode = (node_t *)malloc(sizeof(node_t));	//动态分配字节点空间
	ERROR(newnode, NULL, "malloc newnode error", -1);

	newnode->data = malloc(size);				//动态分配数据空间
	ERROR(newnode->data, NULL, "malloc newnode->data is error", -1);
	memcpy(newnode->data, data, size);			//拷贝数据到链表
	node_t *temp = head;

	while (temp->next != head)
		temp = temp->next;	
	newnode->next = temp->next;
	temp->next = newnode;

	return 0;
}


/*功能：删除链表中的所有成员*/
/*参数：head为链表的头指针*/
/*返回值：0代表成功； -1代表失败*/
int delete_all_clist(node_t *head)
{
	ERROR(head, NULL, "head is null", -1);
	node_t *temp, *before; 
	temp = before = head;

	while (temp->next != head)
	{
		before->next = temp->next->next;
		before = temp->next;
		free(temp->next->data);		//释放链表中的数据
		free(temp->next);		//释放链表成员
		temp->next = temp->next->next;
	}

	return 0;
}


/*功能：以什么方式来显示链表中的成员*/
/*参数：head为链表的头指针； f具体显示函数*/
/*返回值：无*/
void show_all_clist(node_t *head, showfun_t f)
{
	ERROR(head, NULL, "head is null", );
	ERROR(f, NULL, "f is null", );
	node_t *temp = head->next;
	
	while (temp != head)
	{
		f(temp->data);
		temp = temp->next;
	}
	
	return;
}


/*功能：按照要求在链表中查找成员*/
/*参数：head为链表的头指针； data为要查找的数据； f为比较函数*/
/*返回值：temp为查找到的成员指针； NULL为错误输出*/
node_t *find_clist(node_t *head, void *data, cmpfun_t f)
{
	ERROR(head, NULL, "head is null", NULL);
	ERROR(data, NULL, "data is null", NULL);
	ERROR(f, NULL, "f is null", NULL);
	node_t *temp = head->next;

	while (temp != head)
	{	
		if (!f(temp->data, data))
			return temp;
		temp = temp->next;
	}

	return NULL;
}


/*功能：以什么方式来显示链表中的成员*/
/*参数：head为链表成员的指针； f具体显示函数*/
/*返回值：无*/
void show_me_clist(node_t *head, showfun_t f)
{
	ERROR(head, NULL, "head is null", );
	ERROR(f, NULL, "f is null", );
	f(head->data);
	return;
}


/*功能：删除链表中的某个成员*/
/*参数：head为链表成员的指针*/
/*返回值：0代表成功； -1代表失败*/
int delete_me_clist(node_t *head, void *data, cmpfun_t f)
{
	ERROR(head, NULL, "head is null", -1);
	ERROR(data, NULL, "data is null", -1);
	ERROR(f, NULL, "f is null", -1);
	node_t *current = head->next;
	node_t *before = head;

	while (current != head)
	{	
		if (f(current->data, data))
		{
			before = current;	
			current = current->next;	
		}
		break;	
	}
	before->next = current->next;
	free(current->data);
	free(current);	
	return 0;
}


/*功能：按f函数排序链表*/
/*参数：head为链表成员的指针；f为以什么方式排序； size为数据大小*/
/*返回值：0代表成功； -1代表失败*/
int sort_clist(node_t *head, cmpfun_t f, int size)
{
	ERROR(head, NULL, "head is NULL", -1);
	int flag;				//冒泡排序标志位
	void *temp = malloc(size);
	node_t *inext, *jnext;

	for (inext=head->next; inext->next!=head; inext = inext->next)
	{
		flag = 0;
		for (jnext=head->next; jnext->next!=head; jnext = jnext->next)
		{
			if (f(jnext->next->data, jnext->data) > 0)
			{
				memcpy(temp, jnext->data, size);
				memcpy(jnext->data, jnext->next->data, size);
				memcpy(jnext->next->data, temp, size);
				flag = 1;
			}
		}
		if (!flag)
			break;
	}
	free(temp);
	return 0;	
}


/*功能：销毁整个链表*/
/*参数：**head为链表成员的指针的地址*/
/*返回值：0代表成功； -1代表失败*/
int destroy_clist(node_t **head)
{
	ERROR(head, NULL, "head is null", -1);
	node_t *after, *current;
	after = current = (*head)->next;
	
	while (current != (*head))
	{
		after = after->next;
		free(current->data);
		free(current);
		current = after;
	}
	
	free((*head)->data);
	free(*head);
	*head = NULL;

	return 0;
}


/*功能：显示系统退出logo*/
/*参数：无*/
/*返回值：无*/
void show_end_logo(void)
{
	int i = 1000;
	while (i--)
	{
		puts("\n\n\n\n\n\n\n\n\t\t\t\t谢谢使用");
		system("clear");
	}
	return;
}


/*功能：检测接收的是不是数字*/
/*参数：无*/
/*返回值：无*/
int input_num(void)
{
	char temp[128];
	int i, res;
	fgets(temp, sizeof(temp), stdin);		
	for (i=0; i<128; i++)
	{
		if (temp[i] == '\n')
		{
			flog = 1;
			break;
		}
		else
			if (!(temp[i] >= '0' && temp[i] <= '9'))
			{	
				printf("\n\n\t\t\t\t请输入数字：");
				bzero(temp, sizeof(temp));
				break;
			}
		
	}

	if (flog == 1)
		res = atoi(temp);
	

	return res;
}


/*功能：接收多余字符串*/
/*参数：temp数组； size为数组大小*/
/*返回值：无*/
int f_gets(char *temp, int size)
{
	int i;
	char buf[128];	

	while (1)
	{
		for (i=0; i<size; i++)
		{
			if (temp[i] == '\n')
				return 0;
		}
	
		while (1)
		{
			fgets(buf, sizeof(buf), stdin);
			for (i=0; i<sizeof(buf); i++)
			{
				if (buf[i] == '\n')
				{
					flog = 1;
					bzero(buf, sizeof(buf));
					break;
				}
			}
			bzero(buf, sizeof(buf));
			if (flog == 1)
				break;		
		}
	
		if (flog == 1)
		{
			flog = 0;
			break;
		}		
	}

	return 0;
}
