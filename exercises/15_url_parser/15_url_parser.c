#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // TODO: 在这里添加你的代码

    // 找到查询参数部分 (问号之后)
    const char* query = strchr(url, '?');
    if (query == NULL) {
        goto exit;
    }
    query++; // 跳过问号

    // 逐个解析参数
    char url_copy[1024];
    strcpy(url_copy, query);

    char* token = strtok(url_copy, "&");
    while (token != NULL) {
        char* eq = strchr(token, '=');
        if (eq != NULL) {
            *eq = '\0';
            char* key = token;
            char* value = eq + 1;
            printf("key = %s, value = %s\n", key, value);
        }
        token = strtok(NULL, "&");
    }

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}