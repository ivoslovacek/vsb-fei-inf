CC = g++
CPPFLAGS = -fsanitize=address

SRCPATH = src
OBJPATH = obj
BINPATH = bin
INCPATH = include
CPPFILES := $(wildcard $(SRCPATH)/*.cpp)
OBJFILES := $(patsubst $(SRCPATH)/%.cpp,$(OBJPATH)/%.o,$(CPPFILES))
EXECUTABLE = main

all: $(BINPATH)/$(EXECUTABLE)

$(BINPATH)/$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CPPFLAGS) $(OBJFILES) -o $@

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	$(CC) $(CPPFLAGS) -I$(INCPATH) -c $< -o $@

clean:
	rm -f $(BINPATH)/$(EXECUTABLE) $(OBJFILES)
