#########################
#		VARIABLES		#
#########################

# Folders and names
NAME			:=	pipex

HEADERS			:=	inc
HEADERS_FILES	:=	pipex.h
HEADER_FILES_B	:=	pipex_bonus.h

SRC_DIR			:=	src
SRC_FILES		:=	pipex.c \
					parse_program.c \
					exec.c \
					errors.c \
					utils.c

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRC_DIR_B		:=	src_bonus
SRC_FILES_B		:=	pipex_bonus.c \
					parse_program_bonus.c \
					child_bonus.c \
					here_doc_bonus.c \
					errors_bonus.c \
					files_bonus.c \
					utils_bonus.c

SRCS_B			:= $(addprefix $(SRC_DIR_B)/, $(SRC_FILES_B))

LIB_NAMES		:=	lib/libft
LIBS			:=	$(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD			:=	$(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS		:=	$(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS		:=	$(foreach lib,$(LIB_NAMES),-I$(lib)/inc/)

BUILD_DIR		:=	build
OBJS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
BUILD_DIR_B		:=	build_bonus
OBJS_B			:=	$(SRC_FILES_B:%.c=$(BUILD_DIR_B)/%.o)

# Compiler options
CC				:=	cc
CC_FLAGS		:=	-Wextra -Werror -Wall -O2
DEBUG_FLAG		:=	-g3 #-fsanitize=address

MAKE			:=	make -C

# define standard colors
_END			:=	\x1b[0m
_BOLD			:=	\x1b[1m
_UNDER			:=	\x1b[4m
_REV			:=	\x1b[7m
_GREY			:=	\x1b[30m
_RED			:=	\x1b[31m
_GREEN			:=	\x1b[32m
_YELLOW			:=	\x1b[33m
_BLUE			:=	\x1b[34m
_PURPLE			:=	\x1b[35m
_CYAN			:=	\x1b[36m
_WHITE			:=	\x1b[37m

#########################
# 		RULES			#
#########################

all: build_libs $(NAME)

$(NAME): $(LIB_PATHS) $(OBJS)
	@$(CC) $(CC_FLAGS) $(DEBUG_FLAG) $(OBJS) $(LIB_LD) $(LIBS) -o $@ 
	@echo "> $(NAME) Done!\n"
	
build_libs:
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib); \
	)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_PATHS) $(HEADERS)/$(HEADERS_FILES)
	@mkdir -p $(@D)
	@echo "$(_GREEN)compiling: $<$(_END)"
	@$(CC) $(CC_FLAGS) $(DEBUG_FLAG) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

bonus: build_libs $(LIB_PATHS) $(OBJS_B)
	@$(CC) $(CC_FLAGS) $(OBJS_B) $(LIB_LD) $(LIBS) -o $(NAME)
	@echo "> $(NAME) bonus Done!\n"

$(BUILD_DIR_B)/%.o: $(SRC_DIR_B)/%.c $(LIB_PATHS) $(HEADERS)/$(HEADERS_FILES_B)
	@mkdir -p $(@D)
	@echo "$(_GREEN)compiling: $<$(_END)"
	@$(CC) $(CC_FLAGS) $(DEBUG_FLAG) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@

# clean commands
clean:
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) clean; \
	)
	@rm -rf $(BUILD_DIR)

fclean: clean
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) fclean; \
	)
	@echo "remove $(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re build_libs
