CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic
COMMON_SRCS = common/utils.c
CAT_SRCS = cat/s21_cat.c $(COMMON_SRCS)
GREP_SRCS = grep/s21_grep.c $(COMMON_SRCS)

all: s21_cat s21_grep

s21_cat:
	$(CC) $(CFLAGS) -o cat/s21_cat $(CAT_SRCS)

s21_grep:
	$(CC) $(CFLAGS) -o grep/s21_grep $(GREP_SRCS)

clean:
	rm -f cat/s21_cat grep/s21_grep


test:

	./cat/s21_cat file.txt > /dev/null && echo "cat basic ✅"
	./cat/s21_cat -n file.txt > /dev/null && echo "cat -n ✅"
	./cat/s21_cat -b file.txt > /dev/null && echo "cat -b ✅"
	./cat/s21_cat -e file.txt > /dev/null && echo "cat -e ✅"
	./cat/s21_cat -s file.txt > /dev/null && echo "cat -s ✅"
	./cat/s21_cat -t file.txt > /dev/null && echo "cat -t ✅"
	
	./grep/s21_grep "line" file.txt > /dev/null && echo "grep basic ✅"
	./grep/s21_grep -n "line" file.txt > /dev/null && echo "grep -n ✅"
	./grep/s21_grep -i "hello" file.txt > /dev/null && echo "grep -i ✅"
	./grep/s21_grep -v "line" file.txt > /dev/null && echo "grep -v ✅"
	./grep/s21_grep -c "line" file.txt > /dev/null && echo "grep -c ✅"
	./grep/s21_grep -l "line" file.txt > /dev/null && echo "grep -l ✅"
memory:
	valgrind --tool=memcheck --leak-check=yes ./cat/s21_cat file.txt
	@echo ""
	valgrind --tool=memcheck --leak-check=yes ./grep/s21_grep "line" file.txt

.PHONY: all clean test memory
