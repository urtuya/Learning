ASM_NAME = asm
VM_NAME = corewar

FLAGGS = -Wall -Wextra -Werror

VM_DIR = VM/
ASM_DIR = assembler/
LIBFT_DIR = libft/
LIB = $(LIBFT_DIR)libft.a

VM_CFILES = main.c validation.c init.c init_main_struct.c in_cycle.c check.c\
	op.c operations13_16.c values_calculation.c print.c parse_args.c\
	operations1_3.c operations4_8.c operations9_12.c setting_ids.c\
	flags.c reading_bytes.c error.c

VM_FILES = $(addprefix src/, $(VM_CFILES))
VM_SRC = $(addprefix $(VM_DIR), $(VM_FILES)) 

ASM_FILES = check_args.c get_strings.c main.c parser.c encoder.c read_file.c\
	token.c errors.c helpful.c size_help.c utils.c init.c op.c\
	string_size.c values.c free.c label.c
ASM_SRC = $(addprefix $(ASM_DIR), $(ASM_FILES))


LIB_INC = -I ./$(LIBFT_DIR)inc
VM_INC = -I ./$(VM_DIR)inc $(LIB_INC)
ASM_INC = -I ./$(ASM_DIR) $(LIB_INC)



all: $(ASM_NAME) $(VM_NAME)

$(ASM_NAME): $(LIB)
	gcc $(FLAGGS) $(ASM_SRC) $(ASM_INC) $(LIB) -o $(ASM_NAME)

$(VM_NAME):
	gcc $(FLAGGS) $(VM_SRC) $(VM_INC) $(LIB) -o $(VM_NAME)

$(LIB):
	make -C $(LIBFT_DIR)

clean:
	rm -f *.gch
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(ASM_NAME) $(VM_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: re all clean fclean
