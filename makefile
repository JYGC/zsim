# Use gmake not bsdmake

EXEC	= zsim

EXECDIR	= ./Debug
SRCDIR	= ./src

CC		= mpicc
FLAGS	= -Wall -g -fopenmp -I$(SRCDIR)
LIBS	= -lm

build:
	$(CC) $(FLAGS) $(LIBS) -o $(EXECDIR)/$(EXEC) $(SRCDIR)/*.c
	
clean:
	rm -f $(EXECDIR)/$(EXEC)
