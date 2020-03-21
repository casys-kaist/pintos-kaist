BUILD_SUBDIRS = threads filesys

all::
	@echo "Run 'make' in subdirectories: $(BUILD_SUBDIRS)."
	@echo "This top-level make has only 'clean' targets."

CLEAN_SUBDIRS = $(BUILD_SUBDIRS) examples

clean::
	for d in $(CLEAN_SUBDIRS); do $(MAKE) -C $$d $@; done
	rm -f TAGS tags

distclean:: clean
	find . -name '*~' -exec rm '{}' \;

TAGS_SUBDIRS = $(BUILD_SUBDIRS) devices lib
TAGS_SOURCES = find $(TAGS_SUBDIRS) -name \*.[chS] -print

TAGS::
	etags `$(TAGS_SOURCES)`

tags::
	ctags `$(TAGS_SOURCES)`

cscope.files::
	$(TAGS_SOURCES) > cscope.files

cscope:: cscope.files
	cscope -b -q -k
