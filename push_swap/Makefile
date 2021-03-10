NAME = push_swap

# Compiler and linker
CC = clang
LD = clang

# Paths
SRCDIR = src
INCDIR = include
LIBDIR = ..

OBJDIR = obj
BINDIR = .

# Library dependencies
LIBS = $(addprefix $(LIBDIR), /libstack/libstack.a)

LIBDIRS = $(dir $(LIBS))
LIBINCS = $(addsuffix $(INCDIR), $(LIBDIRS))
LIBARS = $(notdir $(LIBS))

# Sources
INCS = $(LIBINCS) $(INCDIR)
SRCS = $(addprefix $(SRCDIR)/,\
	push_swap.c\
)

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Flags
CFLAGS = -Wall -Wextra $(INCS:%=-I%)
DFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)/$*.d
LDFLAGS = $(LIBDIRS:%=-L%)
LDLIBS = $(LIBARS:lib%.a=-l%)

# Compiling commands
COMPILE.c = $(CC) $(DFLAGS) $(CFLAGS) -c
COMPILE.o = $(LD) $(LDFLAGS)

all: $(BINDIR)/$(NAME)

# Directories
$(OBJDIR) $(BINDIR):
	@echo "MK $@"
	mkdir -p "$@"

# Libraries
$(LIBS): %.a:
	make -C $(dir $@) NAME=$(@F)

# Objects
$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)/%.d | $(OBJDIR)
	@mkdir -p '$(@D)'
	@echo "CC $<"
	$(COMPILE.c) $< -o $@

# Dependencies
$(DEPS): $(OBJDIR)/%.d:
include $(wildcard $(DEPS))

# Binaries
$(BINDIR)/$(NAME): $(OBJS) | $(BINDIR) $(LIBS)
	@echo "LD $@"
	$(COMPILE.o) $< -o $@ $(LDLIBS)

# Remove temporary objects
clean:
	$(foreach libdir, $(LIBDIRS),\
		echo "MK -C $(libdir) $@" && make -C $(libdir) $@ && ):
	@echo "RM $(OBJDIR)"
	rm -rf "$(OBJDIR)"

# Remove all binaries
fclean: clean
	$(foreach libdir, $(LIBDIRS),\
		echo "MK -C $(libdir) $@" && make -C $(libdir) $@ && ):
	@echo "RM $(BINDIR)/$(NAME)"
	rm -f "$(BINDIR)/$(NAME)"
	@rmdir "$(BINDIR)" 2>/dev/null && echo "RM $(BINDIR)" || :

# Remove and rebuild all binaries
re: fclean all

.PHONY: clean fclean re $(LIBS)

# Assign a value to VERBOSE to enable verbose output
$(VERBOSE).SILENT:
