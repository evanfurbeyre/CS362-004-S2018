#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

char inputChar()
{
	return (char)(rand() % 94) + 32;
}

char *inputString()
{
	int i;
	int len_s = 5;
	char* s = (char*)malloc(sizeof(char) * len_s+1);  // allocate string on heap to return
    assert(s != NULL);
    for (i = 0; i < len_s; i++)      // insert random letters into string
    {
        s[i] = (char)(rand() % 16) + 101;       // lower case letters e thru t
    }
	return s;
}

void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	clock_t begin = clock();
	clock_t end = clock();
	while ((double)(end-begin) / CLOCKS_PER_SEC < 300)
	{
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' '&& state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
		    && s[2] == 's' && s[3] == 'e'
		    && s[4] == 't' && s[5] == '\0'
		    && state == 9)
		{
			printf("error ");
			exit(200);
		}
		end = clock();
	}
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
