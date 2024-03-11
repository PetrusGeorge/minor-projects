CC = gcc
CFLAGS = -Wall -pthread
TARGET = pthread_compare

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

atomic: CFLAGS += -DATOMIC
atomic: clean $(TARGET)

mutex: CFLAGS += -DMUTEX
mutex: clean $(TARGET)

while: CFLAGS += -DWHILE
while: clean $(TARGET)

clean:
	rm -f $(TARGET)
