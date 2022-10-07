PASTINHA_CONJUNTA=../
CC = $(PASTINHA_CONJUNTA)\MINGW\bin\gcc
PATH_ALLEGRO=$(PASTINHA_CONJUNTA)\allegro-5.0.10-mingw-4.7.0
LIBS=-lallegro-5.0.10-monolith-mt

all: TP_rtype.exe 

TP_rtype.exe: TP_rtype.o
	$(CC) -O2 -o TP_rtype.exe TP_rtype.o TP_funcoes.o $(PATH_ALLEGRO)\lib\liballegro-5.0.10-monolith-mt.a

TP_funcoes.o: TP_rtype.c
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c TP_funcoes.c 	

TP_rtype.o: TP_funcoes.o
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c TP_rtype.c 	




	
tp.exe: tp.o
	$(CC) -O2 -o tp.exe tp.o -L $(PATH_ALLEGRO)\lib $(LIBS)


tp.o: tp.c
	$(CC) -O2 -I $(PATH_ALLEGRO)\include -c tp.c 	