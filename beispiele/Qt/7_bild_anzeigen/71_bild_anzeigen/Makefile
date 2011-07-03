# ---------------------------------
# Makefile for BabyDevelop projects
# ---------------------------------

CC          = g++
LD          = g++
QTDIR       = /usr/include/qt4
MOC         = moc
RM          = rm -f
RUN         = ./$(BIN)
CFLAGS      = -c -Wall -g -I$(QTDIR) -I$(QTDIR)/Qt -I$(QTDIR)/QtCore -I$(QTDIR)/QtGui
LDFLAGS     = -L/usr/lib
LIBS        = -lQtCore -lQtGui -lQt3Support
PROGRAMMFENSTER_OBJ        = /opt/babyDevelop/programmfenster.moc.o /opt/babyDevelop/programmfenster.o

# ---------------------------------
OBJECTS     = main.o steuerung.o steuerung.moc.o ufgbild.o ufgbild.moc.o
BIN         = Steuerung
# ---------------------------------

all: clean $(OBJECTS) link

clean:
	-$(RM) *.moc.cpp
	-$(RM) *.moc.o
	-$(RM) *.o
	-$(RM) $(BIN)

compile_all: $(OBJECTS)

link:
	$(CC) $(OBJECTS) $(PROGRAMMFENSTER_OBJ) $(LDFLAGS) $(LIBS) -o $(BIN)

.cpp.o:
	$(CC) $(CFLAGS) $<

%.moc.cpp: %.h
	$(MOC) -o $@ $<

%.moc.o: %.moc.cpp
	$(CC) $(CFLAGS) -o $@ $<

run:
	$(RUN)
