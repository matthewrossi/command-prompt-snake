CC = cl.exe
CFLAGS = /EHsc
LINK = link.exe

PROGRAM = snake

INCLUDEDIR = include
SRCDIR = src
BUILDDIR = build
BINDIR = $(BUILDDIR)\bin

LICENSE_TYPE   = "mit"
LICENSE_HOLDER = "Matthew Rossi"

.PHONY: all
all: $(PROGRAM)

# Create bin directory
$(BINDIR):
    mkdir $(BINDIR)

# Link the object files and dependent libraries into a binary
.PHONY: $(PROGRAM)
$(PROGRAM): $(BUILDDIR)\bar.o $(BUILDDIR)\bonus.o $(BUILDDIR)\controls.o $(BUILDDIR)\level.o $(BUILDDIR)\main.o $(BUILDDIR)\snake.o $(BUILDDIR)\utils.o $(BUILDDIR)\wall.o $(BINDIR)
    $(LINK) /OUT:$(BINDIR)\$(PROGRAM).exe $(BUILDDIR)\bar.o $(BUILDDIR)\bonus.o $(BUILDDIR)\controls.o $(BUILDDIR)\level.o $(BUILDDIR)\main.o $(BUILDDIR)\snake.o $(BUILDDIR)\utils.o $(BUILDDIR)\wall.o

# Create build directory
$(BUILDDIR):
    mkdir $(BUILDDIR)

# Compile the source files into object files
$(BUILDDIR)\bar.o: $(BUILDDIR) $(SRCDIR)\bar.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\bar.cpp /Fo$@

$(BUILDDIR)\bonus.o: $(BUILDDIR) $(SRCDIR)\bonus.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\bonus.cpp /Fo$@

$(BUILDDIR)\controls.o: $(BUILDDIR) $(SRCDIR)\controls.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\controls.cpp /Fo$@

$(BUILDDIR)\level.o: $(BUILDDIR) $(SRCDIR)\level.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\level.cpp /Fo$@

$(BUILDDIR)\main.o: $(BUILDDIR) $(SRCDIR)\main.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\main.cpp /Fo$@

$(BUILDDIR)\snake.o: $(BUILDDIR) $(SRCDIR)\snake.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\snake.cpp /Fo$@

$(BUILDDIR)\utils.o: $(BUILDDIR) $(SRCDIR)\utils.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\utils.cpp /Fo$@

$(BUILDDIR)\wall.o: $(BUILDDIR) $(SRCDIR)\wall.cpp
    $(CC) $(CFLAGS) /I $(INCLUDEDIR) /c $(SRCDIR)\wall.cpp /Fo$@

.PHONY: clean
clean:
    rmdir /Q /S $(BUILDDIR)

.PHONY: run
run: $(PROGRAM)
	$(BINDIR)\$(PROGRAM).exe

.PHONY: addlicense
addlicense:
	go get -u github.com/google/addlicense
    $(GOPATH)\bin\addlicense -c $(LICENSE_HOLDER) -l $(LICENSE_TYPE) .
