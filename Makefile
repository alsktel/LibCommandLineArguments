##
 # SPDX-License-Identifier: BSD-3-Clause
 # Copyright © 2022 Alexander Elunin <https://github.com/eastev>
 # 
 # 
 # Project: LibCommandLineArguments
 # Module: Buildsystem
 # File: Makefile
 #
 # LibCommandLineArguments main Makefile
##


CWD = $(shell pwd)
SRCDIR = $(CWD)/src
INCLUDEDIR = $(CWD)/include
OBJDIR = $(CWD)/build
BINDIR = $(CWD)/bin
ARCHIVEDIR = $(CWD)/archive/libcmdargs

INSTALL_INCLUDEDIR = /usr/include/libcmdargs
INSTALL_LIBDIR = /usr/lib/libcmdargs

SOURCES = $(shell find $(SRCDIR) -type f -printf "%p ")
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

LIBFILE = $(BINDIR)/libcmdargs.so
INSTALL_LIBFILE = $(INSTALL_LIBDIR)/libcmdargs.so

ARCHIVEFILENAME = libcmdargs

CC = gcc
CFLAGS = -Wall -Werror -fPIC -I $(INCLUDEDIR) -c
RELEASE_CFLAGS = -O2 $(CFLAGS)
DEBUG_CFLAGS = -g -O0 $(CFLAGS)
ACTIVE_CFLAGS = 
LDFLAGS = -shared -Wall -Werror


SHELL := /usr/bin/bash


.ONESHELL:


all: release

release: release_prep $(LIBFILE)
	@echo -e "\033[1mRelease build ended!\033[0m"
	@echo ""

release_prep: prep
	@echo ""
	@echo -e "\033[1mRelease build started!\033[0m"
	$(eval ACTIVE_CFLAGS = $(RELEASE_CFLAGS))

debug: debug_prep $(LIBFILE)
	@echo -e "\033[1mDebug build ended!\033[0m"
	@echo ""

debug_prep: prep
	@make -s clean
	@echo ""
	@echo -e "\033[1mDebug build started!\033[0m"
	$(eval ACTIVE_CFLAGS = $(DEBUG_CFLAGS))

prep:
	@if [ ! -d $(BINDIR) ]; then mkdir $(BINDIR); fi
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi

$(LIBFILE): $(OBJECTS)
	@rm -f $(OBJDIR)/cc.log
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $(LIBFILE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@set -o pipefail
	@printf "%-32s" "Compilling: $(shell basename $<)"
	@-$(CC) $(ACTIVE_CFLAGS) $< -o $@ 2> $(OBJDIR)/cc.log
	@if [ $$? == 0 ]; then \
	printf "%16s\033[0;32m%s\033[0m%s\n" "[" "OK" "]"; \
	else \
	printf "%16s\033[0;31m%s\033[0m%s\n" "[" "FAIL" "]"; \
	cat $(OBJDIR)/cc.log; \
	fi

clean:
	@rm -f $(OBJDIR)/*
	@rm -f $(BINDIR)/*
	@rm -f $(ARCHIVEDIR)/*

install:
	@if [ ! -f $(LIBFILE) ]; then \
	echo -e "\nNo library! Please run\033[1m\033[3m make\033[0m first!\n"; \
	exit; \
	fi
	@if [ ! -d $(INSTALL_LIBDIR) ]; then mkdir $(INSTALL_LIBDIR); fi
	@cp $(LIBFILE) $(INSTALL_LIBFILE)
	@cp -r $(INCLUDEDIR)/ $(INSTALL_INCLUDEDIR)/
	@echo -e "\nInstallation\033[0;32m successfull\033[0m!\n"

uninstall:
	@if [ -f $(INSTALL_LIBFILE) ]; then \
	rm $(INSTALL_LIBFILE); \
	fi
	@if [ -d $(INSTALL_INCLUDEDIR) ]; then \
	rm -rf $(INSTALL_INCLUDEDIR); \
	fi
	@echo -e "\nUninstallation\033[1m finished\033[0m!\n"

archive:
	@if [ ! -f $(LIBFILE) ]; then \
	echo -e "\nNo library! Please run\033[1m\033[3m make\033[0m first!\n"; \
	exit; \
	fi
	@if [ ! -d $(ARCHIVEDIR) ]; then mkdir -p $(ARCHIVEDIR); fi
	@echo ""
	@read -p "Enter version: "
	@tar -C $(CWD) -cjf $(ARCHIVEDIR)/$(ARCHIVEFILENAME)-$$REPLY.tar ./bin
	@echo "Archive $(ARCHIVEFILENAME)-$$REPLY.tar created!"
	@echo ""


.PHONY: all debug release release_prep prep debug_prep clean install uninstall
.PHONY: archive
