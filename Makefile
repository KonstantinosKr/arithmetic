# C files
C_SRC=

# C++ files
CPP_SRC=main.cpp

# Program name
EXE=main

CC=gcc $(CFLAGS)
CXX=g++ $(CFLAGS)

CPP_OBJS=$(addprefix objs/, $(CPP_SRC:.cpp=.o))
C_OBJS=$(addprefix objs/, $(C_SRC:.c=.o))
LIBS= 

default: dirs $(CPP_OBJS) $(C_OBJS) $(EXE)

.PHONY: dirs clean print

print:
	@echo $(CPP_OBJS)
	@echo $(C_OBJS)

dirs:
	/bin/mkdir -p objs/

del:
	find ./ -iname "*.dump" -exec rm '{}' ';'

clean:
	/bin/rm -rf objs *~ $(EXE)
	find ./ -iname "*.dump" -exec rm '{}' ';'

$(EXE): $(CPP_OBJS) $(C_OBJS)
	$(CXX) -o $@ $^ $(LIBS)

objs/%.o: %.cpp
	$(CXX) $< -c -o $@

