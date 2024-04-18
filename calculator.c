#include <stdio.h>
#include <stdlib.h>

static char exp[1000];
static int idx = 0;

typedef struct {
	int type; // 0: number, 1: (, 2: ), 3: operator
	int value;
} token;

int isNumeric(char c) {
	return '0' <= c && c <= '9';
}

int getNumberToken() {
	char c = exp[idx];
	if(c == '-') {
		idx++;
		return -getNumberToken();
	}
	int value = 0;
	while(isNumeric(c)) {
		int digit = c-'0';
		value *= 10;
		value += digit;
		c = exp[++idx];
	}
	return value;
}

token getTokenExceptOperator() {
	char c = exp[idx++];
	if(c == '(') return {1,0};
	if(c == ')' || c == ';' || c == '\0') return {2,0};
	idx--;
	int v = getNumberToken();
	return {0,v};
}

token getToken() {
	char c = exp[idx++];
	if(c == '(') return {1,0};
	if(c == ')' || c == ';' || c == '\0') return {2,0};
	if(!isNumeric(c)) return {3, c};
	idx--;
	return {0,getNumberToken()};
}

int calc(int a, int op, int b) {
	switch(op) {
		case '*': return a*b;
		case '/': return a/b;
		case '+':
		case '-': return a+b;
	}
	printf("error");
	exit(1);
}

// 0+ (p,num) (op, p) (p,num) (op, p) (p,num) (op, p)
// 3+2*3*4+5
int compute(int initial) {
	int value = initial;
	int temp = 0;
	int tempMul = 1;
	int lastOp = '+';
	while(1) {
		int rv = 0;
		token t = getTokenExceptOperator();
		printf("value1: %d, temp1: %d\n", value, temp);
		printf("token 1: %d %d\n", t.type, t.value);
		if(t.type == 2) {
			value += temp*tempMul;
			return value;
		}
		if(t.type == 1) {
			rv = compute(0);
		} else {
			rv = t.value;
		}
		token rt = getToken(); // rb or op
		printf("token 2: %d %d\n", rt.type, rt.value);
		printf("temp2: %d\n", temp);
		int lastOpType = lastOp == '*' || lastOp =='/';
		temp = calc(temp, lastOp, rv);
		if(rt.type == 2) {
			value += temp*tempMul;
			return value;
		}
		char op = rt.value;
		printf("calcT: %d\n", temp);
		lastOp = op;
		if(op == '+') {
			value += temp*tempMul;
			temp = 0;
			tempMul = 1;
		} else if(op == '-') {
			value += temp*tempMul;
			temp = 0;
			tempMul = -1;
		}
	}
}

int main(void) {
	char input = 'N';
	do {
		printf("수식 입력: ");
		scanf("%s", exp);
		int value = compute(0);
		printf("result: %d\n", value);
		printf("다른 수식을 입력겠습니까? (Y/N): ");
		fflush(stdin);
		scanf("%c", &input);
	} while(input == 'Y' || input == 'y');
}
