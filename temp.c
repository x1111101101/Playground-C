#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int size, memSize, unitSize, offset;
	char* arr;
} Dequeue;

Dequeue* newDequeue(int unitSize) {
	Dequeue* d = malloc(sizeof(Dequeue));
	d->unitSize = unitSize/sizeof(char);
	d->size = 0;
	d->offset = 0;
	d->memSize = 100;
	d->arr = malloc(d->memSize*unitSize);
	return d;
}

void* dqGet(Dequeue* d, int index) {
	if (index < 0 || index >= d->size) return NULL;
	int addr = (d->offset + index) % d->memSize;
	char* p = d->arr;
	return (p+addr*d->unitSize);
}

void* dqPushBack(Dequeue* d, int index) {
	if (d->memSize == d->size) {
		int newSize = d->memSize * d->unitSize * sizeof(char) * 2;
		char* newArr = malloc(newSize);
		for (int i = d->offset; i < d->memSize; i++) {

		}
	}
	
	
}

typedef struct {
	int scale;
	char *digits;
	int point;
	int sign; // -1 or 1
} BigDecimal;

void finalize(BigDecimal* b) {
	if(b->digits != NULL)
		free(b->digits);
	free(b);
}

// 123.456 -> s: 6, p: 3
char* toString(BigDecimal* b) {
	char* str = malloc(b->scale + 2);
	int i = 0, k = 0;
	while (i < b->point) {
		str[k++] = b->digits[i++] + '0';
	}
	int rlen = b->scale - b->point;
	if(rlen > 0) str[k++] = '.';
	while (i < b->scale) {
		str[k++] = b->digits[i++] + '0';
	}
	str[k] = '\0';
	return str;
}

BigDecimal* sum(BigDecimal *a, BigDecimal *b) {
	
}

BigDecimal* newBigDecimal(char* str) {
	int len = strlen(str);
	if (len == 0) return NULL;
	int i = 0, k = 0;
	BigDecimal *b = malloc(sizeof(BigDecimal));
	b->point = -1;
	b->sign = 1;
	b->digits = malloc(sizeof(char) * len);
	if (str[0] == '-') {
		b->sign = -1;
		i++;
	}
	while (i < len) {
		char c = str[i];
		if (c == '.') {
			if (b->point != -1) {
				finalize(b);
				return NULL; // 소숫점이 여러개
			}
			b->point = i;
		}
		else if ('0' <= c && c <= '9') {
			b->digits[k++] = c - '0';
		}
		else {
			finalize(b);
			return NULL;
		}
		i++;
	}
	b->scale = k;
	if (b->point == -1) {
		b->point = k;
	}
	return b;
}

int main(void) {
	BigDecimal* b = newBigDecimal("121231231231231231231231233.45612312321312312312312312312");
	printf("%s", toString(b));
}
