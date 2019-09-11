#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "runAsX.h"

wchar_t *convertToWChar(const char *input);

int main(int argc, char **argv) {

    // params:
    // -u user
    // -p password
    // -d domain
    // -n netonly
    // command + command parameter
    int opt;
    wchar_t *user = NULL;
    wchar_t *password = NULL;
    wchar_t *domain = NULL;
    int netOnlyFlag = 0;
    while ((opt = getopt(argc, argv, "u:p:d:n")) != -1) {
        switch (opt) {
            case 'u':
                user = convertToWChar(optarg);
                break;
            case 'p':
                password = convertToWChar(optarg);
                break;
            case 'd':
                domain = convertToWChar(optarg);
                break;
            case 'n':
                netOnlyFlag = 1;
                break;
            default:
                printf("usage: updn cmd args");
                break;
        }
    }

    for (int index = optind; index < argc; index++) {
        printf("argv[%d]: %s\n", index, argv[index]);
    }

    wchar_t *cmd = convertToWChar(argv[optind]);
    wchar_t *args = NULL;
    if (optind + 1 < argc) {
        size_t diff = argc - (optind + 1);

        args = malloc(sizeof(wchar_t) * _MAX_PATH);
        memset(args, 0, sizeof(wchar_t) * _MAX_PATH);

        for (size_t i = 0; i < diff; i++) {
            char *c = argv[i + optind + 1];
            char *pos = NULL;
            if((pos = strchr(c, ' ')) != NULL) {
                char *s = malloc(strlen(c) + 2);
                memset(s, 0, sizeof(c) + 2);
                strcat(s, "\"");
                strcat(s, c);
                strcat(s, "\"");
                c = s;
            }
            wchar_t *tmp = convertToWChar(c);
            args = wcscat(args, tmp);
        }
    }

    startProcessAsUser(user,
                       password,
                       domain,
                       netOnlyFlag,
                       cmd,
                       args
    );

    return 0;
}

wchar_t *convertToWChar(const char *input) {
    if(input == NULL)
        return NULL;

    size_t size = strlen(input);
    wchar_t *dst = malloc(size * sizeof(wchar_t) + 2);
    memset(dst, 0, size * sizeof(wchar_t) + 2);
    mbstowcs(dst, input, size + 2);
    return dst;
}
