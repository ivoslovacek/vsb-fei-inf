CC = g++
CPPFLAGS = -fsanitize=address

SRCPATH = src
OBJPATH = obj
BINPATH = bin
INCPATH = include
CPPFILES := $(wildcard $(SRCPATH)/*.cpp)
OBJFILES := $(patsubst $(SRCPATH)/%.cpp,$(OBJPATH)/%.o,$(CPPFILES))
EXECUTABLE = main

default: folders $(BINPATH)/$(EXECUTABLE)

folders:
	mkdir -p obj
	mkdir -p bin

$(BINPATH)/$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CPPFLAGS) $(OBJFILES) -o $@

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	$(CC) $(CPPFLAGS) -I$(INCPATH) -c $< -o $@

clean:
	rm -rf $(BINPATH)/$(EXECUTABLE) obj/
