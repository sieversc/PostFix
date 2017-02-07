SRCS =  LLStacks.C Interface.C 
EXEC = tester

OBJS = $(SRCS:.C=.o)


$(EXEC): $(OBJS)
	g++ -o $(EXEC) $(OBJS)


%.o : %.C
	g++ -g -Wall -c $<

clean:
	rm -f *.o *~ $(EXEC)



# DO NOT DELETE THIS LINE -- make depend needs it 
