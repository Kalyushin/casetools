.PHONY: clean distclean testRun install zip documentation help

.DEFAULT:
	@echo "Error. Use help to look goals"

.SILENT: help

filter: filter.o bmp_io.o bmp_motionblur.o bmp_rezko.o
	gcc -o filter filter.o bmp_io.o bmp_motionblur.o bmp_rezko.o

%.o: %.c bmp.h
	gcc -c -Wall -Wextra $<

testRun: filter
	./filter $(baseFile) $(resFile)

install: filter  ## установка
	install ./filter images

documentation: ## сборка документации вот тут
	doxygen Doxyfile

zip:
	@make cleanall 
	zip distro.zip *

help:
	./goalMakefile

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o *.~ filter distro.zip
	rm -rf latex html
