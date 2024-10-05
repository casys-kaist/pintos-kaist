# -*- makefile -*-

SRCDIR = ../..

all: os.dsk

include ../../Make.config
include ../Make.vars
include ../../tests/Make.tests

# Compiler and assembler options.
os.dsk: CPPFLAGS += -I$(SRCDIR)/lib/kernel

# Core kernel.
include ../../threads/targets.mk
# User process code.
include ../../userprog/targets.mk
# Virtual memory code.
include ../../vm/targets.mk
# Filesystem code.
include ../../filesys/targets.mk
# Library code shared between kernel and user programs.
include ../../lib/targets.mk
# Kernel-specific library code.
include ../../lib/kernel/targets.mk
# Device driver code.
include ../../devices/targets.mk

SOURCES = $(foreach dir,$(KERNEL_SUBDIRS),$($(dir)_SRC))
OBJECTS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))
DEPENDS = $(patsubst %.o,%.d,$(OBJECTS))

threads/kernel.lds.s: CPPFLAGS += -P
threads/kernel.lds.s: threads/kernel.lds.S

kernel.o: threads/kernel.lds.s $(OBJECTS)
	$(LD) $(LDFLAGS) -T $< -o $@ $(OBJECTS)

kernel.bin: kernel.o
	$(OBJCOPY) -O binary -R .note -R .comment -S $< $@.tmp
	dd if=$@.tmp of=$@ bs=4096 conv=sync
	rm $@.tmp

threads/loader.o: threads/loader.S kernel.bin
	$(CC) -c $< -o $@ $(ASFLAGS) $(CPPFLAGS) $(DEFINES) -DKERNEL_LOAD_PAGES=`perl -e 'print +(-s "kernel.bin") / 4096;'`

loader.bin: threads/loader.o
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7c00 --oformat binary -o $@ $<

os.dsk: loader.bin kernel.bin
	cat $^ > $@

clean::
	rm -f $(OBJECTS) $(DEPENDS)
	rm -f threads/loader.o threads/kernel.lds.s threads/loader.d
	rm -f kernel.o kernel.lds.s
	rm -f kernel.bin loader.bin os.dsk
	rm -f bochsout.txt bochsrc.txt
	rm -f results grade

Makefile: $(SRCDIR)/Makefile.build
	cp $< $@

-include $(DEPENDS)
