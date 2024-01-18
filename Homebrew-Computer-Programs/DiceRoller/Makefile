PROJECT_NAME=dice

ASM=sjasmplus

BUILD_DIR=build
BIN=${BUILD_DIR}/${PROJECT_NAME}.bin
LST=${BUILD_DIR}/${PROJECT_NAME}.lst
SYM=${BUILD_DIR}/${PROJECT_NAME}.sym

SRC_DIR=src
SRCS=${SRC_DIR}/main.asm ${SRC_DIR}/lcd.asm ${SRC_DIR}/main.asm ${SRC_DIR}/variables.asm \
${SRC_DIR}/menu.asm

AFLAGS=--raw=${BIN} --lst=${LST} --sym=${SYM}

.PHONY: clean all


${BIN}: ${SRCS}
	${ASM} ${AFLAGS} $^


all: ${BIN}


clean:
	rm ${BUILD_DIR}/*
