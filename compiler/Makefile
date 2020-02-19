-include Makefile.conf

project:=protoc_ada.gpr

all: build test
build:protoc_ada.gpr Makefile.conf
	${GPRBUILD} -p -P ${project}

uninstall:protoc_ada.gpr Makefile.conf
	${GPRINSTALL} --uninstall ${project}

install:protoc_ada.gpr Makefile.conf
	@${GPRINSTALL} --uninstall ${project} --prefix=${DESTDIR}${prefix} 2>/dev/null >/dev/null ; true
	${GPRINSTALL} -p -P ${project} --prefix=${DESTDIR}${prefix}

Makefile.conf:Makefile  # <IGNORE>
	@echo "GPRBUILD:=$(shell which gprbuild)" >${@}
	@echo "GPRINSTALL:=$(shell which gprinstall)" >>${@}
	@echo "GPS:=$(shell which gps)" >>${@}
	@echo "export PATH:=${CURDIR}/bin:${PATH}" >>${@}

gps:  # <IGNORE>
	${GPS} -P ${project} &

test: Makefile.conf
	@rm -rf out *.txt
	@mkdir out
	protoc test.proto --python_out=out
	protoc -I ${CURDIR} test.proto --ada_out=out
