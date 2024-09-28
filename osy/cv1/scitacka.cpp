#include <cstdint>
#include <cstdio>
#include <cstring>
int main(int argc, char** argv) {
    int read_num = 0;
    int error = 0;
    int64_t total = 0;

    bool binary = (argc > 1 && strcmp(argv[1], "-b") == 0) ? true : false;

    while (1) {
        if (!binary) {
            error = scanf("%d", &read_num);
            if (error == EOF) break;

            total += static_cast<int64_t>(read_num);
        } else {
            error = fread(&read_num, sizeof(int), 1, stdin);
            if (error == 0) break;

            total += static_cast<int64_t>(read_num);
        }
    }

    printf("total: %ld\n", total);

    return 0;
}
