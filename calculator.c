
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXP_SCALE   (1000)

void solve2();

static char exp[EXP_SCALE];
static int idx = 0;

int exceptionCaused = 0;

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
	if(!isNumeric(c)) {
	   exceptionCaused = 1;
	   return 0;
	}
	do {
	    int digit = c-'0';
		value *= 10;
		value += digit;
		c = exp[++idx];
	} while(isNumeric(c));
	return value;
}

token getTokenExceptOperator() {
	char c = exp[idx++];
	if(c == '(') return (token){1,0};
	if(c == ')' || c == '\0') return (token){2,0};
	idx--;
	int v = getNumberToken();
	return (token){0,v};
}

token getToken() {
	char c = exp[idx++];
	if(c == '(') return (token){1,0};
	if(c == ')' || c == '\0') return (token){2,0};
	if(!isNumeric(c)) return (token){3, c};
	idx--;
	return (token){0,getNumberToken()};
}

int calc(int a, int op, int b) {
	switch(op) {
		case '*': return a*b;
		case '/': return a/b;
		case '+':
		case '-': return a+b;
	}
	exceptionCaused = 1;
	return 0;
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
		if(t.type == 2) {
			value += temp*tempMul;
			return value;
		}
		rv = t.type == 1 ? compute(0) : t.value;
		token rt = getToken(); // rb or op
		temp = calc(temp, lastOp, rv);
		if(rt.type == 2) {
			value += temp*tempMul;
			return value;
		}
		char op = rt.value;
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

void removeSpaces() {
	int t = 0;
	for(int i = 0; i<EXP_SCALE; i++) {
	    char c = exp[i];
	    if(c == ' ') continue;
	    exp[t++] = c;
	    if(c == '\n') return;
	}
}



void clearBuffer() {
    char c;
    while((c=getchar()) != '\n' && c != EOF);
}

int main(void) {
	char input = 'N';
	do {
	    exceptionCaused = 0;
		printf("수식 입력: ");
		idx = 0;
		scanf("%[^\n]s", exp);
		removeSpaces();
		int value = compute(0);
		if(exceptionCaused) {
		    printf("잘못된 수식입니다.\n");
		} else {
		    printf("Result: %d\n", value);
		}
		printf("다른 수식을 입력겠습니까? (Y/N): ");
		clearBuffer();
		scanf("%c", &input);
	} while(input == 'Y' || input == 'y');
	return 0;
}

// 번외 문제 - 중간값 구하기
#define CENTER(x,a,b)   ((x > a && x < b) || (x < a && x > b))
void solve2() {
    int a,b,c,t;
	int b1, b2;	
	scanf("%d%d%d", &a, &b, &c);
	if(CENTER(a,b,c)) printf("%d", a);
	else if (CENTER(b,a,c)) printf("%d", b);
	else printf("%d", c);
}

void solve() {
	int a,b,c,t;
	int b1, b2;	
	scanf("%d%d%d", &a, &b, &c);
	if(a<b) {
		t = a; a = b; b = t;
	}
	if(b<c)  {
		t = b; b = c; c = t;
	}
	if(a<b) {
		t = a; a = b; b = t;
	}
	printf("중간값: %d\n", b);
}
