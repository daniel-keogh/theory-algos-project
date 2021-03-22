# Reference: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-std=c11

# Executable
EXEC=sha512

# Directories
SDIR=src
ODIR=obj
INS_DIR=/usr/local/bin

# Object files
OBJS=$(patsubst %,$(ODIR)/%,$(_OBJS))
_OBJS=main.o sha512.o

all: init $(EXEC)
	@echo "Build complete."

init:
	@mkdir -p $(ODIR)/

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test:
	@echo "Not implemented"

install:
	cp $(EXEC) $(INS_DIR)/

uninstall:
	rm $(INS_DIR)/$(EXEC)

clean:
	rm -rf $(ODIR)/
	rm $(EXEC)
