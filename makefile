N_BITS = $(shell getconf LONG_BIT)
ifeq ($(N_BITS),32)
   BITS_OPTION = -m32
else
   BITS_OPTION = -m64
endif

SRCDIR := src
INCDIR := include
OBJDIR := obj
BINDIR := bin

CC := g++
CFLAGS := -Wall -Werror -I$(INCDIR) -MMD
CCLNFLAGS := -lm

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
TARGET := $(BINDIR)/conversor

.PHONY: all clean rebuild run mkdirs

all: mkdirs $(TARGET)
	@echo -e "\nBuild complete: $(TARGET)"

$(TARGET): $(OBJS)
	@echo -e "\nLinking objects to create executable: $@"
	$(CC) $(BITS_OPTION) $(CFLAGS) $(CCLNFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo -e "Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@echo -e "\nCleaning object files..."
	rm -f $(TARGET)
	find $(OBJDIR) -type f -name '*.o' -exec rm -f {} +
	find $(OBJDIR) -type f -name '*.d' -exec rm -f {} +
	@echo -e "\nClean complete."

rebuild: clean all

run: all
	@echo -e "\nRunning: $(TARGET)"
	./$(TARGET)

mkdirs:
	@echo "Making directories"
	@mkdir -p $(OBJDIR) $(BINDIR) $(INCDIR) $(SRCDIR)

#this recreates the src folder structure into the obj folder
#can be replaced with a rule that also creates the src structure and repeat on obj
	@mkdir -p $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(shell find $(SRCDIR) -type d))
