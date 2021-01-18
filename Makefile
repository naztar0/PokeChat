NAME = uchat

SERVER_NAME = uchat_server
SERVER_DIR = server

CLIENT_DIR = client

LIBMX_DIR = frameworks/libmx
LIBCJSON_DIR = frameworks/cjson
LIBSQLITE_DIR = frameworks/sqlite3

MAKE_M = make -sf Makefile -C
RM = /bin/rm -rf

all:
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(SERVER_DIR) $@

$(NAME):
	@$(MAKE_M) $(CLIENT_DIR)

$(SERVER_NAME):
	@$(MAKE_M) $(SERVER_DIR)

clean:
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(SERVER_DIR) $@

uninstall:
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(SERVER_DIR) $@
	@$(MAKE_M) $(LIBMX_DIR) $@
	@$(MAKE_M) $(LIBCJSON_DIR) $@
	@$(MAKE_M) $(LIBSQLITE_DIR) $@
	rm database.db

reinstall: uninstall all

.PHONY: all clean uninstall reinstall $(NAME) $(SERVER_NAME)
