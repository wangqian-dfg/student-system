OBJECTS := public.o student.o teacher.o menu.o main.o
SOURCES := public.c student.c teacher.c menu.c main.c
HEADERS := public.h student.h teacher.h menu.h
main: $(OBJECTS)
	gcc -lm -Wall $(OBJECTS) -o main
	rm *.o
public.o:public.c public.h
	gcc -c public.c
student.o:student.c student.h public.h
	gcc -c student.c
teacher.o:teacher.c teacher.h public.h
	gcc -c teacher.c
menu.o:menu.c menu.h student.h teacher.h public.h
	gcc -c menu.c
main.o:main.c menu.h student.h teacher.h public.h
	gcc -c main.c
