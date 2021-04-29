CC          := g++
MKDIR       := mkdir -p
RM          := rm -rf

SRC_DIR     := src
OBJ_DIR     := obj
TST_DIR     := test
UNITY_DIR   := tool-unity

TARGET      := unittest.elf

SRCS        := \
	$(SRC_DIR)/cobs.cpp \

TSTS        := \
	$(UNITY_DIR)/unity.c \
	$(TST_DIR)/test_cobs.cpp \

INCS        := \
	$(SRC_DIR) \
	$(TST_DIR) \
	$(UNITY_DIR) \

TSTS_C      := $(filter %.c,$(TSTS))
TSTS_CPP    := $(filter %.cpp,$(TSTS))

OBJS        := \
	$(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o)) \
	$(addprefix $(OBJ_DIR)/,$(TSTS_C:.c=.o)) \
	$(addprefix $(OBJ_DIR)/,$(TSTS_CPP:.cpp=.o)) \

DEPS        := $(OBJS:.o=.d)
INCLUDES    := $(addprefix -I,$(INCS))

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(info Linking $@)
	@$(CC) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@if [ ! -d $(dir $@) ]; then $(MKDIR) $(dir $@); fi
	$(info Compiling $<)
	@$(CC) $(INCLUDES) -c -o $@ $<

$(OBJ_DIR)/%.o: %.cpp
	@if [ ! -d $(dir $@) ]; then $(MKDIR) $(dir $@); fi
	$(info Compiling $<)
	@$(CC) $(INCLUDES) -c -o $@ $<

