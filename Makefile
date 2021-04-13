# Reference: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-std=c11 -I src

# Executables
EXEC=sha512
EXEC_TEST=test.o

# Directories
SDIR=src
ODIR=obj
TEST_DIR=tests
INS_DIR=/usr/local/bin

# Object files
OBJS=$(patsubst %,$(ODIR)/%,$(_OBJS))
_OBJS=main.o sha512.o utils.o

OBJS_TEST=$(patsubst %,$(ODIR)/%,$(_OBJS_TEST))
_OBJS_TEST=test_sha512.o sha512.o utils.o

all: init $(EXEC)
	@echo "Build complete."

init:
	@mkdir -p $(ODIR)/

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(ODIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC_TEST): $(OBJS_TEST)
	$(CC) $(CFLAGS) -o $@ $^

test: init $(EXEC_TEST)
	./$(EXEC_TEST)
	@rm $(EXEC_TEST)

install:
	cp $(EXEC) $(INS_DIR)/

uninstall:
	rm $(INS_DIR)/$(EXEC)

clean:
	rm -rf $(ODIR)/
	rm $(EXEC)
