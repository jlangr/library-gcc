# ftplibpp makefile

SONAME = 2
SOVERSION = $(SONAME).0

TARGETS = libftp++.a # libftp++.so
OBJECTS = ftplib.o
SOURCES = ftplib.cpp

EXT_PREFIX ?= /usr/local
INSTALL_PREFIX ?= $(EXT_PREFIX)

CPPFLAGS = -I. $(INCLUDES) -I$(EXT_PREFIX)/include $(DEFINES)
LDFLAGS = -L. -L$(EXT_PREFIX)/lib
CXXFLAGS = -Wall $(DEBUG)
DEPFLAGS =

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
 LIBS = -lssl -lcrypto
endif
ifeq ($(UNAME), Linux)
 LIBS = -lssl
endif

all : $(TARGETS)

clean :
	rm -f $(OBJECTS) core *.bak
	rm -rf unshared
	rm -f $(TARGETS) .depend
	rm -f libftp.so.*

uninstall :
	rm -f $(INSTALL_PREFIX)/lib/libftp.so.*
	rm -f $(INSTALL_PREFIX)/include/libftp.h

install : all
	install -m 644 libftp.so.$(SOVERSION) $(INSTALL_PREFIX)/lib
	install -m 644 ftplib.h $(INSTALL_PREFIX)/include
	(cd $(INSTALL_PREFIX)/lib && \
	 ln -sf libftp.so.$(SOVERSION) libftp.so.$(SONAME) && \
	 ln -sf libftp.so.$(SONAME) libftp.so)

depend :
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -M $(SOURCES) > .depend

# build without -fPIC
#unshared/ftplib.o: ftplib.cpp ftplib.h
#	-mkdir unshared
#	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -D_REENTRANT $< -o $@

ftplib.o: ftplib.cpp ftplib.h
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -fPIC -D_REENTRANT $< -o $@

libftp++.a: ftplib.o
	ar -rcs $@ $<

libftp.so.$(SOVERSION): ftplib.o
	$(CXX) -shared -Wl,-install_name,libftp.so.$(SONAME) $(LIBS) -lc -o $@ $<

libftp++.so: libftp.so.$(SOVERSION)
	ln -sf $< libftp.so.$(SONAME)
	ln -sf $< $@

ifeq (.depend,$(wildcard .depend))
include .depend
endif
