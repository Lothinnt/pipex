
# Nom des executables
NAME = pipex
BONUS_NAME = pipex_bonus

# Compilateur
CC = gcc
# Flags de compilation
CFLAGS = -Wall -Wextra -Werror -g

# Dossiers sources et objets
SRC_DIR = Mandatory
BONUS_SRC_DIR = Bonus
OBJ_DIR = objs
BONUS_OBJ_DIR = bonus_objs
GNL_DIR = GNL
PRINTF_DIR = ft_printf

# Fichiers sources
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
BONUS_SRC_FILES = $(wildcard $(BONUS_SRC_DIR)/*.c) $(wildcard $(BONUS_SRC_DIR)/Pipex/*.c)
GNL_FILES = $(wildcard $(GNL_DIR)/*.c)
PRINTF_FILES = $(wildcard $(PRINTF_DIR)/*.c)

# Headers
HEADER_DIR = includes
BONUS_HEADER_DIR = $(BONUS_SRC_DIR)

# Construction des chemins objets
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(notdir $(SRC_FILES:.c=.o)))
BONUS_OBJS = $(patsubst %,$(BONUS_OBJ_DIR)/%,$(notdir $(BONUS_SRC_FILES:.c=.o)))
GNL_OBJS = $(patsubst %,$(OBJ_DIR)/%,$(notdir $(GNL_FILES:.c=.o)))
PRINTF_OBJS = $(patsubst %,$(OBJ_DIR)/%,$(notdir $(PRINTF_FILES:.c=.o)))

# Règle principale
all: $(NAME)

# Règles de compilation
$(NAME): $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -c $< -o $@
$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(GNL_DIR) -c $< -o $@
$(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(PRINTF_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

# Règles bonus
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(CFLAGS) -I$(BONUS_HEADER_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) $^ -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(BONUS_HEADER_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -c $< -o $@
$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/Pipex/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(BONUS_HEADER_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -c $< -o $@

$(BONUS_OBJ_DIR):
	mkdir -p $@

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

# Nettoyage complet
fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

# Recompilation
re: fclean all

# Règle pour ne pas confondre fichiers et commandes
.PHONY: all clean fclean re bonus
