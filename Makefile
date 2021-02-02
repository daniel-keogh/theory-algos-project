# Reference: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=

# Executable
EXEC=sha512

# Directories
SDIR=src
ODIR=obj

# Object files
OBJS=$(patsubst %,$(ODIR)/%,$(_OBJS))
_OBJS=main.o

all: init $(EXEC)

init:
	@mkdir -p $(ODIR)/

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# test:

clean:
	rm -rf $(ODIR)/
	rm $(EXEC)
