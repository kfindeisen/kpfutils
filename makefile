# Compilation make for utilities library
# by Krzysztof Findeisen
# Created June 17, 2010
# Last modified June 17, 2013

include makefile.inc

#---------------------------------------
# Select all files
PROJ     := kpfutils
PROJ     := lib$(PROJ).a
SOURCES  := stats_except.cpp
OBJS     := $(SOURCES:.cpp=.o)
# No subdirectories -- will cause naming conflicts in final archive
DIRS     := 

#---------------------------------------
# Primary build option
$(PROJ): $(OBJS)
	@echo "Packaging $@..."
	$(AR) $(ARFLAGS) $@ $^

#---------------------------------------
# Subdirectories
# Can't declare the directories phony directly, or the executable will be built every time
.PHONY: cd

tests: cd
	@make -C tests --no-print-directory $(MFLAGS)

include makefile.common

#---------------------------------------
# Doxygen
.PHONY: doc
doc: doc/
doc/: $(OBJS) $(DIRS) doxygen.cfg
	doxygen doxygen.cfg
	cd doc/latex && make

#---------------------------------------
# Test cases
.PHONY: unittest
unittest: tests | $(PROJ)

.PHONY: autotest
autotest: $(PROJ) unittest
	@echo "Beginning regression test suite..."
	@echo "Tests started on `date`"
	@cd tests && ./test ; echo "Tests completed on `date`"

#---------------------------------------
# Build program, test suite, and documentation
.PHONY: all
all: $(PROJ) unittest doc