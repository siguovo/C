#include <stdio.h>
#include <string.h>
#define  Max  1000

char StrCopy(char* a, char* b) {
	strcpy(a, b);
}


int main() {
	char str1 = "duanmao";
	char str2 = "victor";

	char* str3 = malloc(sizeof(char) * Max);

	str3 = StrCopy(&str1, &str2);

	printf("%s\n", str3);
;





}