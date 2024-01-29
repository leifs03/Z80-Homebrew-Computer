# Makefile for DiceRollerC, a program written for the Ceres8 by leifs.

PROJECT_NAME := DiceRoller

CC := sdcc
AS := sdasz80
LD := sdcc

CFLAGS := -mz80 -c --allow-unsafe-read --opt-code-size --max-allocs-per-node 10000 --std sdcc99
AFLAGS := -g
LFLAGS := -mz80 --no-std-crt0 --data-loc 0x8000 --code-loc 0x0100

.PHONY: all clean vars

SRC_DIR := src
BLD_DIR := build
OBJ_DIR := $(BLD_DIR)/obj
BIN_DIR := $(BLD_DIR)/bin

# C Runtime and Main functions MUST be linked first.
ORDERED_OBJS := $(OBJ_DIR)/crt0.rel $(OBJ_DIR)/main.rel

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.s)

# I will not subject anyone to a one-liner of this
OBJS := $(filter-out %.s,$(patsubst %.c,%.rel,$(SRCS))) $(filter-out %.c,$(patsubst %.s,%.rel,$(SRCS)))
OBJS := $(subst $(SRC_DIR),$(OBJ_DIR),$(OBJS))
OBJS := $(filter-out $(ORDERED_OBJS),$(OBJS))

# It looks like this btw
#OBJS := $(filter-out $(ORDERED_OBJS),$(subst $(SRC_DIR),$(OBJ_DIR),$(filter-out %.s,$(patsubst %.c,%.rel,$(SRCS))) $(filter-out %.c,$(patsubst %.s,%.rel,$(SRCS)))))

IHX := $(BLD_DIR)/$(PROJECT_NAME).ihx
BIN := $(BIN_DIR)/$(PROJECT_NAME).bin

# Use compiler for C files in SRCS
$(OBJ_DIR)/%.rel: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

# Use assembler for S files in SRCS
$(OBJ_DIR)/%.rel: $(SRC_DIR)/%.s
	mkdir -p $(@D)
	$(AS) $(AFLAGS) -o $@ $<

$(IHX): $(ORDERED_OBJS) $(OBJS)
	$(LD) $(LFLAGS) $^ -o $@

$(BIN): $(IHX)
	mkdir -p $(@D)
	makebin -p -s 0x2000 < $< > $@



all: $(BIN)



clean:
	rm -rf $(BLD_DIR)


vars:
	$(info PROJECT_NAME is $(PROJECT_NAME))
	$(info ---)
	$(info CC is $(CC))
	$(info AS is $(AS))
	$(info LD is $(LD))
	$(info ---)
	$(info CFLAGS is $(CFLAGS))
	$(info AFLAGS is $(AFLAGS))
	$(info LFLAGS is $(LFLAGS))
	$(info ---)
	$(info SRC_DIR is $(SRC_DIR))
	$(info BLD_DIR is $(BLD_DIR))
	$(info OBJ_DIR is $(OBJ_DIR))
	$(info BIN_DIR is $(BIN_DIR))
	$(info ---)
	$(info ORDERED_OBJS is $(ORDERED_OBJS))
	$(info SRCS is $(SRCS))
	$(info OBJS is $(OBJS))
	$(info ---)
	$(info IHX is $(IHX))
	$(info BIN is $(BIN))
