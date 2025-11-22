BUILD_DIR = build
CC = gcc
CFLAGS = -I $(BUILD_DIR)
LDFLAGS = -lm
SRCS = main.c \
       question1.c \
       question2.c \
       question3.c \
       question4.c \
       question5.c \
       question6.c \
	   question7.c \
	   question8.c \
	   question9.c \
	   question10.c \
	   question11.c \
	   question12.c \
	   question13.c \
	   question14.c \
	   question15.c \
	   question16.c \
	   question17.c \
	   question18.c \
	   question19.c \
	   question20.c \
	   question21.c \
	   question22.c \
	   question23.c
HEADERS = mydefs.h printers.h question20.h
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
GCHS = $(addprefix $(BUILD_DIR)/, $(HEADERS:.h=.h.gch))
TARGET = $(BUILD_DIR)/program

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