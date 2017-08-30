CC=gcc
CFLAGS=-Wall

SOURCE_DIR = src
BUILD_DIR = bin
TARGET = $(BUILD_DIR)/program
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

$(TARGET): $(OBJECTS) $(HEADERS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
		rm -f $(TARGET) $(OBJECTS)
