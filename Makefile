CC := g++ 
SRCDIR := src
BUILDDIR := build
TARGETDIR := lib
STATIC := lib/libalab.a
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -Wall -O3 -std=c++0x
LIB := -lpthread -lhdf5 -lhdf5_cpp
INC := -I include

$(STATIC): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo " Linking (Static)"
	@echo " ar rcs $(STATIC) $^ "; ar rcs $(STATIC) $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(STATIC)"; $(RM) -r $(BUILDDIR) $(STATIC)

.PHONY: clean


