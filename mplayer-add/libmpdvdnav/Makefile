
include ../config.mak

SRCS = decoder.c \
       dvdnav.c \
       highlight.c \
       navigation.c \
       read_cache.c \
       remap.c \
       searching.c \
       settings.c \
       vm.c \
       vmcmd.c

OBJS = $(SRCS:.c=.o)

LIB=libmpdvdnav

.SUFFIXES: .c .o

ifeq ($(OPTFLAGS),)
OPTFLAGS = -mcpu=pentium -march=pentium -O4
else
OPTFLAGS += -DHAVE_MPLAYER
endif

#	 \ -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

# -funroll-loops  removed, triggered gcc 3.0.4 (3.x?) bug
CFLAGS= -I. -I.. $(OPTFLAGS) $(EXTRA_INC)\
	-DSYS_LINUX -D__USE_UNIX98 -D_REENTRANT -D_GNU_SOURCE \
	-DHAVE_DVDCSS_DVDCSS_H -DSTDC_HEADERS -DHAVE_LIMITS_H \
	-DHAVE_ERRNO_H -DHAVE_INTTYPES_H -DHAVE_UNISTD_H \
	-DHAVE_CONFIG_H \

ifeq ($(TARGET_OS),CYGWIN)
CFLAGS+=-DSYS_CYGWIN
endif

ifeq ($(TARGET_OS),Darwin)
CFLAGS+=-D__DARWIN__
endif

INCLUDE = -I.. -I../loader $(CSS_INC) $(EXTRA_INC) $(LIBAV_INC)
ifeq ($(DVDKIT2),yes)
INCLUDE += -I../libmpdvdkit2 -I../../libmpdvdkit2
else
ifeq ($(DVDKIT),yes)
INCLUDE += -I../libmpdvdkit -I../../libmpdvdkit
endif
endif

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(LIB).a
default: $(LIB).a

$(LIB).a: $(OBJS)
	$(AR) rc $(LIB).a $(OBJS)
	$(RANLIB) $(LIB).a

$(LIB).so: $(OBJS)
	$(CC) -o $(LIB).so -shared -rdynamic $(OBJS)

clean:
	rm -f *.o *.a *~ *.so

distclean: clean
	rm -f .depend

dep:    depend

depend: .depend

.depend: Makefile config.h
	$(CC) -MM $(CFLAGS) $(SRCS) 1>.depend

#
# include dependency files if they exist
#
ifneq ($(wildcard .depend),)
include .depend
endif
