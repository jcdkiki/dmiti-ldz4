.PHONY: all clean
all: task1 task2 task3 task4a task4b task4c

task1: common.h common.c task1.c
	gcc common.c task1.c -o task1 -lm

task2: common.h common.c task2.c
	gcc common.c task2.c -o task2 -lm

task3: common.h common.c task3.c
	gcc common.c task3.c -o task3 -lm

task4a: common.h common.c task4a.c
	gcc common.c task4a.c -o task4a -lm

task4b: common.h common.c task4b.c
	gcc common.c task4b.c -o task4b -lm

task4c: common.h common.c task4c.c
	gcc common.c task4c.c -o task4c -lm

clean:
	rm -rf task1 task2 task3 task4a task4b task4c
