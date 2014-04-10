.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base

# Project Paths
PROJECT_ROOT=./
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
DATADIR = $(PROJECT_ROOT)/data
PLOTDIR = $(PROJECT_ROOT)/plots

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -Wall -fno-strict-aliasing
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

PFLAG= -p -O3
MODE=cmake ../

.PHONY: all setup doc clean distclean data plot report exe

all: setup $(BINDIR)/$(TARGET)

setup:
	@if test -e $(EXTERNAL_ROOT)/include/Box2D -a -e $(EXTERNAL_ROOT)/lib/Box2D;\
	then echo "Box2D has already been installed";\
	else tar xzf $(PROJECT_ROOT)/external/src/Box2D.tgz -C $(EXTERNAL_ROOT)/src \
	&& printf "Installing Box2D" \
	&& cd $(EXTERNAL_ROOT)/src/Box2D \
	&& mkdir -p build296 \
	&& cd build296 \
	&& $(MODE) \
	&& make	\
	&& make install \
	&& cd .. && cd .. && cd .. && cd .. ;\
	fi;
	@mkdir -p obj
	@mkdir -p bin

exe: setup $(BINDIR)/$(TARGET)
	
$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include -include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) $(PFLAG) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"



report: 
	@python3 ./scripts/g32_gen_html.py
	@cd  $(PROJECT_ROOT)/doc \
	&& pdflatex g32_prof_report.tex \
	&& rm  -rf  cs296_report_32.bbl cs296_report_32.blg cs296_report_32.aux cs296_report_32.log cs296_report_32.dvi;\


data: exe
	@mkdir -p data;
	@rm -f ./data/g32_data_01.csv
	@touch ./data/g32_data_01.csv
	@chmod +x -R ./scripts/g32_gen_csv.py; echo "Running g32_gen_csv.py..."; python ./scripts/g32_gen_csv.py;

plot: data
	@chmod +x -R ./scripts/g32_gen_plots.py;
	echo "Running g32_gen_plots.py...";
	@python ./scripts/g32_gen_plots.py;
clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~
	@$(RM) -rf $(DOCDIR)/html
	@$(RM) -rf $(DOCDIR)/cs296_report_32.bbl $(DOCDIR)/g32_prof_report.aux $(DOCDIR)/g32_prof_report.dvi $(DOCDIR)/g32_prof_report.log $(DOCDIR)/g32_prof_report.pdf $(DOCDIR)/g32_report.html
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html
	@$(RM) -rf $(EXTERNAL_ROOT)/src/Box2D
	@$(RM) -rf $(EXTERNAL_ROOT)/lib/libBox2D.a
	@$(RM) -rf $(EXTERNAL_ROOT)/include/Box2D

.PHONY: debug_prof release_prof 


debug_prof: MODE=cmake -DCMAKE_BUILD_TYPE=Debug ../
debug_prof: PFLAG=-g
debug_prof: setup exe
	@perf record -g -- ./bin/$(TARGET) 1000 > $(DOCDIR)/g32_debug_prof.dat

release_prof: MODE=cmake -DCMAKE_BUILD_TYPE=Release ../		
release_prof: PFLAG=-O3
release_prof: setup exe
	@perf record -g -- ./bin/$(TARGET) 1000 > $(DOCDIR)/g32_release_prof.dat
