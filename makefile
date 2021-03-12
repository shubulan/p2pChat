CFLAGS +=  
.PHONY : clean
chat.out : p2pchat.o include/conf.o include/myudp.o include/reactor.o include/chat.o include/heart.o include/send_chat.o include/chat_ui.o
	gcc p2pchat.o include/conf.o include/myudp.o include/reactor.o include/chat.o include/heart.o include/send_chat.o include/chat_ui.o -pthread $(CFLAGS) -pthread -lncursesw -o chat.out
p2pchat.o : p2pchat.c include/myhead.h
	gcc -c p2pchat.c $(CFLAGS) -Iinclude -o p2pchat.o
include/conf.o : include/conf.c include/conf.h
	gcc -c include/conf.c $(CFLAGS) -Iinclude -o include/conf.o
include/myudp.o : include/myudp.c include/myudp.h
	gcc -c include/myudp.c $(CFLAGS) -Iinclude -o include/myudp.o
include/reactor.o : include/reactor.c include/reactor.h
	gcc -c include/reactor.c $(CFLAGS) -Iinclude -o include/reactor.o
include/chat.o : include/chat.c include/chat.h
	gcc -c include/chat.c $(CFLAGS) -Iinclude -o include/chat.o
include/heart.o : include/heart.c include/heart.h
	gcc -c include/heart.c $(CFLAGS) -Iinclude -o include/heart.o
include/send_chat.o : include/send_chat.c include/send_chat.h
	gcc -c include/send_chat.c $(CFLAGS) -Iinclude -o include/send_chat.o
include/chat_ui.o : include/chat_ui.c include/chat_ui.h
	gcc -c include/chat_ui.c $(CFLAGS) -Iinclude -o include/chat_ui.o
clean:
	rm -f p2pchat.o include/myudp.o include/reactor.o include/chat.o include/heart.o include/send_chat.o include/conf.o


