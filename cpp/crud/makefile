NAME = CrudClinica

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET = $(BINDIR)/$(NAME)

CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -I$(INCDIR)

.PHONY: all clean mkdirs

all: mkdirs $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJDIR)/*.o $(TARGET)

mkdirs:
	@mkdir -p $(OBJDIR) $(BINDIR) $(INCDIR) $(SRCDIR)
