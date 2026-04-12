#include <stdio.h>

void my_strcpy(char *dest, char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
}

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	// TODO: 在这里添加你的代码
    my_strcpy(destination, source);
    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}