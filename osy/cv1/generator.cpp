#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <optional>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    uint32_t count = static_cast<uint32_t>(atoi(argv[1]));

    std::optional<uint32_t> min = std::nullopt;
    std::optional<uint32_t> max = std::nullopt;

    bool binary = false;

    if (argc > 3) {
        min = static_cast<uint32_t>(atoi(argv[2]));
        max = static_cast<uint32_t>(atoi(argv[3]));
        binary = (argc > 4 && strcmp(argv[4], "-b") == 0) ? true : false;
    } else {
        binary = (argc > 2 && strcmp(argv[2], "-b") == 0) ? true : false;
    }

    std::srand(std::time(nullptr));

    for (; count > 0; count--) {
        int generated = 0;

        if (min.has_value()) {
            generated = std::rand() % (max.value() - min.value()) + min.value();
        } else {
            generated = std::rand();
        }

        if (binary) {
            fwrite(&generated, sizeof(int), 1, stdout);
        } else {
            printf("%d\n", generated);
        }
    }

    return 0;
}
