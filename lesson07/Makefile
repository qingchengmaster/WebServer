#定义变量
src=$(wildcard ./*.c) 
objs=$(patsubst %.c,%.o, $(src))
target=app

$(target):$(objs)
	$(CC) $(objs) -o $(target)
%.o:%.c
	$(CC) -c $< -o $@
#伪目标
.PHONY:clean
clean: 
	rm $(objs) -f
