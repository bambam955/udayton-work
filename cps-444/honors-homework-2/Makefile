BUILD_DIR = build
CC = gcc
CFLAGS = -I $(BUILD_DIR)
# LDFLAGS = -lm
SRCS = main.c
# HEADERS = mydefs.h printers.h question20.h question25.h
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
# GCHS = $(addprefix $(BUILD_DIR)/, $(HEADERS:.h=.h.gch))
TARGET = $(BUILD_DIR)/wc

all: $(BUILD_DIR) $(GCHS) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.h.gch: %.h | $(BUILD_DIR)
	$(CC) -c $< -o $@

$(TARGET): $(GCHS) $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)