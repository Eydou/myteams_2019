##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

SERVER	=	src/server/
CLIENT	=	src/client/

all: server client

server:
	@ make -C $(SERVER) -s

client:
	@ make -C $(CLIENT) -s

clean:
	@ make clean -C $(SERVER) -s
	@ make clean -C $(CLIENT) -s

fclean:
	@ make fclean -C $(SERVER) -s
	@ make fclean -C $(CLIENT) -s

re:
	@ make re -C $(SERVER) -s
	@ make re -C $(CLIENT) -s

.PHONY: all server client clean fclean re