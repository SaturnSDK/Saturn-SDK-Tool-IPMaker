###############################################################################
#                     SEGA Saturn SDK // Tool - IP Maker Makefile [Linux x86] #
###############################################################################
ifndef TOPDIR
export TOPDIR		:= $(shell cd ../../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin/$(PLATFORM)/$(ARCH)/$(BITSIZE)
export OBJSDIR		= $(TOPDIR)/Obj/$(PLATFORM)/$(ARCH)/$(BITSIZE)/GCC/$(GCCVER)/$(BUILD)
endif
SOURCEDIR	= Source ../Common/Source

PROJECT := ipmaker
TARGET := $(PROJECT)
OUTFILE	=	$(TARGETDIR)/$(TARGET)_$(GCCVER)

PLATFORM		:= Linux
BUILD_PLATFORM	:= LINUX
BUILD_ARCH		:= X86
ARCH			:= x86
BITSIZE			:= 32

GCCVER	= $(shell $(CPP) -dumpversion)

BUILD_TYPE := debug

32BIT ?= False
64BIT ?= False

##### Get the machine type to determine which set of libraries to use #########
UNAME			= $(shell uname)
UNAME_MACHINE	= $(shell uname -m)

ifeq ($(UNAME), Linux)
	CPPFLAGS_EXT	= -ffriend-injection -std=c++0x
	SYSIPATH	= -I/usr/include/xorg
	SYSLIBS		=
	LINKFLAGS	=
##### Check for forced 32-bit or 64-bit builds ################################
ifneq ($(64BIT), False)
	ARCH		=	x86
	BITSIZE		=	64
else
ifneq ($(32BIT), False)
	ARCH		= x86
	BITSIZE		= 32
else
##### Nothing forced.  Use what the machine reports ###########################
ifeq ($(UNAME_MACHINE), x86_64)
	ARCH		=	x86
	BITSIZE		=	64
endif
ifeq ($(UNAME_MACHINE), i686)
	ARCH		= x86
	BITSIZE		= 32
endif
endif
endif
endif

CPP = g++

CPPFLAGS	=	-c -m$(BITSIZE) -DSSSDK_BUILD_$(BUILD_DEF) \
				-DSSSDK_PLATFORM_$(BUILD_PLATFORM) \
				-DSSSDK_PLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH) \
				-DSSSDK_PLATFORM_$(BUILD_PLATFORM)_$(BUILD_ARCH)_$(BITSIZE) \
				-DSSSDK_BITSIZE_$(BITSIZE) -DSSSDK_ARCH_$(BUILD_ARCH) \
				-DSSSDK_WINDOWSYSTEM_X11 \
				-I$(TOPSRC)/Linux/Headers -I$(TOPSRC)/Common/Headers
SYSIPATH	=
INCPATH		=
SYSLPATH	=	
LIBPATH		=
SYSLIBS		=	-lrt -pthread -lncurses
LINKFLAGS	=

##### Debug #######
debug:		BUILD		= Debug
debug:		BUILD_TYPE	= debug
debug:		BUILD_DEF	= DEBUG
debug:		TARGET := $(TARGET)D
debug:		CPPFLAGS += -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
debug:		LIBS =  
debug:		$(TARGET)

##### Release #####
release:	BUILD		= Release
release:	BUILD_TYPE	= release
release:	BUILD_DEF	= RELEASE
release:	TARGET := $(TARGET)
release:	CPPFLAGS += -O3 -s $(CPPFLAGS_EXT)
release:	LIBS = 
release:	LINKFLAGS += -Wl,-S
release:	$(TARGET)

##### Profile #####
profile:	BUILD		= Profile
profile:	BUILD_TYPE	= profile
profile:	BUILD_DEF	= PROFILE
profile:	TARGET := $(TARGET)P
profile:	CPPFLAGS += -O3 -g -ggdb -Wall -D_DEBUG $(CPPFLAGS_EXT)
profile:	LIBS =
profile:	$(TARGET)

##### Build the object files while not in the Obj directory ###################
ifneq ($(OBJSDIR), $(CURDIR))

VERSIONINFO:
	@printf "%s" "------------------------- Generating Version Information ---"
	@printf "%s\n" "-------------------"
	@mkdir -p Headers
	@sh ./GitVersion.sh ./Headers/GitVersion.hpp $(PROJECT)
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

CPPFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.cpp)))
export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))
export OBJS		:= $(CPPFILES:.cpp=.o)

$(TARGET): OBJSDIR TARGETDIR VERSIONINFO
	@/usr/bin/time -f "%E" -o $(OBJSDIR)/compiletime $(MAKE) \
	--no-print-directory -C $(OBJSDIR) -f $(TOPSRC)/Linux/Makefile \
	$(BUILD_TYPE)
	@printf "\n%s" "----------------------------------------------------------"
	@printf "%s\n" "---------------------"
	@printf "Compile time: "
	@cat $(OBJSDIR)/compiletime
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n" "-------------------"

else

##### In the intermediate build directory #####################################

$(TARGET): $(OBJS)
	@printf "\n\n%s" "------------------------- MESSAGES FROM THE COMPILER ---"
	@printf "%s\n" "-----------------------"
	@cat *.cmsgs
	@printf "%s" "------------------------------------------------------------"
	@printf "%s\n\n" "-------------------"
	@printf "Creating: $(OUTFILE)... "
	@$(CPP) -o $(OUTFILE) $(LINKFLAGS) -m$(BITSIZE) $(OBJS) $(SYSLPATH) \
	$(LIBPATH) $(LIBS) $(SYSLIBS) 2> lmsgs;\
	RETVAL=$$?;\
	if env | grep -q ^TERM=; then\
		COLOURSUPPORT=`tput colors`;\
		if [ $$COLOURSUPPORT -gt -1 ]; then\
			cat lmsgs | sed ''/error/s//`printf "\033[31merror\033[0m"`/'' > lmsgs;\
			cat lmsgs | sed ''/warning/s//`printf "\034[31mwarning\033[0m"`/'' > lmsgs;\
		fi;\
	fi;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "------------------------------------ ERROR --------";\
		printf "%s\n" "----------------------------";\
		cat lmsgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n" "------------------------";\
		exit 1;\
	fi

%.o: %.cpp
	@printf "Compiling: $<... "
	@$(CPP) -MMD -MP -MF $*.d $(CPPFLAGS) $(SYSIPATH) $(INCPATH) \
	$< -o $@ 2> $*.cmsgs;\
	RETVAL=$$?;\
	if env | grep -q ^TERM=; then\
		COLOURSUPPORT=`tput colors`;\
		if [ $$COLOURSUPPORT -gt -1 ]; then\
			cat $*.cmsgs | sed ''/error/s//`printf "\033[31merror\033[0m"`/'' > $*.cmsgs;\
			cat $*.cmsgs | sed ''/warning/s//`printf "\033[34mwarning\033[0m"`/'' > $*.cmsgs;\
		fi;\
	fi;\
	if [[ $$RETVAL == 0 ]]; then\
		printf "[OK]\n";\
	else\
		printf "\n\n%s" "--------------------------------- ERROR -----------";\
		printf "%s\n" "----------------------------";\
		cat $*.cmsgs;\
		printf "%s" "-------------------------------------------------------";\
		printf "%s\n\n" "------------------------";\
		exit 1;\
	fi

-include $(OBJSDIR)/*.d

endif

.PHONY: clean completeclean
clean:
	@printf "Removing files from: $(TARGETDIR)... "
	@rm -f $(TARGETDIR)/*
	@printf "[OK]\n"
	@printf "Removing files from: $(OBJSDIR)... "
	@rm -rf $(OBJSDIR)/*
	@printf "[OK]\n"

completeclean:
	@printf "Removing files from: $(TOPDIR)/Bin... "
	@rm -rf $(TOPDIR)/Bin
	@printf "[OK]\n"
	@printf "Removing files from: $(TOPDIR)/Obj... "
	@rm -rf $(TOPDIR)/Obj
	@printf "[OK]\n"

