CC = gcc
CFLAGS = -O0 -Wall -g
ASFLAGS = -g -gstabs
CXXFLAGS = -O0 -Wall -g
LDFLAGS = -g
CSRC = main.c
CCSRC = 
EXE = main
INC = 
ASRC = strdcpy.s

$(EXE):	$(CSRC:.c=.o) $(ASRC:.s=.o) $(CCSRC:.cpp=.o)

%.d: %.c
	$(CC) $^ -MM -MF $@

%.d: %.cpp
	$(CC) $^ -MM -MF $@

%.d: %.s
	$(CC) $^ -MM -MF $@

clean:	
	rm -f $(EXE) $(CSRC:.c=.o) $(ASRC:.s=.o) $(CSRC:.c=.d) $(ASRC:.s=.d) $(INC) $(CCSRC:.cpp=.o)

$(EXE).gdb: $(EXE)
	gdb $(EXE)

$(EXE).test: $(EXE)
	gdb $(EXE) < test.gdb

include $(CSRC:.c=.d)
include $(ASRC:.s=.d)
