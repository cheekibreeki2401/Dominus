IDIR = include
CC = gcc
CFLAGS = -Wall -Wextra -I$(IDIR)

LIBS = -lncurses

Headers = $(wildcard $(IDIR)/*.h)

ODIR = obj

SDIR = src

SRCS = $(wildcard $(SDIR)/*.c)

OBJS = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SRCS))

TARGET = dominus

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c $(Headers) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(ODIR)
