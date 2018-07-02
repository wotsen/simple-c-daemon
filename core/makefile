GCC = gcc
CC = gcc

LIB = -ldl -lm -lzlog -lpthread -lssl -lcrypto -lsqlite3 -ljson-c

BUILDLIBS =

CFLAG = -Wall 
PROJECT = Daemon

SAMDIR=./
SAMINCH=$(shell find $(SAMDIR) -name '*.c')
TMPDIR=$(dir $(SAMINCH))
SAMINCDIR=$(sort $(TMPDIR))

SRCS := $(foreach dir,$(SAMINCDIR),$(wildcard $(addprefix  ${dir}*,.c)))
OBJS=$(patsubst %.c,%.o,$(SRCS))

$(PROJECT):$(OBJS)
	@ $(GCC) -o $@ $^ $(CFLAG) $(LIB) $(BUILDLIBS) 
	@ du -b $(PROJECT)
	@ du -h $(PROJECT)
	@ python3 crc16.py $(PROJECT)
	
%.o:%.c
	$(GCC) -c $(CFLAG) $(BUILDLIBS) $(INCLUDE) -o $@ $< 

	
clean:
	rm -f $(OBJS) $(PROJECT)

