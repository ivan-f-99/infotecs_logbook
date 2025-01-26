CC=g++
CFLAGS=-Wall -std=c++17

LIBSRCDIR=./library/src
LIBHEADERDIR=./library/include
LIBNAME=library.so

TASRCDIR=./testapp/src
TAHEADERDIR=./testapp/include
TANAME=testapp.exe
TMPDIR=./tmp

all : library testapp

library : $(TMPDIR)/library.o
	$(CC) $(CFLAGS) -shared -fPIC -o $(LIBNAME) $(TMPDIR)/library.o 
	echo -e '\n$(LIBNAME) was create.\n'

testapp : $(TMPDIR)/testapp.o
	$(CC) $(CFLAGS) -o $(TANAME) $(TMPDIR)/testapp.o -L./ -lrary -I $(TAHEADERDIR) -I $(LIBHEADERDIR) -Wl,-rpath,./ 
	echo -e '\n$(TANAME) was create.\n'

$(TMPDIR)/library.o : $(LIBSRCDIR)/library.cpp 
	mkdir -p $(TMPDIR)
	$(CC) $(CFLAGS) -shared -fPIC -c $(LIBSRCDIR)/library.cpp -I $(LIBHEADERDIR) -o $(TMPDIR)/library.o  

$(TMPDIR)/testapp.o : $(TASRCDIR)/testapp.cpp
	mkdir -p $(TMPDIR) 
	$(CC) $(CFLAGS) -c $(TASRCDIR)/testapp.cpp -L./ -lrary -I$(TAHEADERDIR) -I $(LIBHEADERDIR) -Wl,-rpath,./ -o $(TMPDIR)/testapp.o 

clean:
	rm -rf $(TMPDIR) 
	echo -e '\nClean done.\n'
