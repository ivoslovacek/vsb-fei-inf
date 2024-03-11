#include "tasks.h"
#include <cctype>
#include <cstring>
#include <regex>

// TODO: implement functions from tasks.h

Parser create_char_parser(const char c)
{
    return [c](const char *input) -> const char * {
        if (input == nullptr || std::strlen(input) == 0 || input[0] != c)
        {
            return nullptr;
        }
        else
        {
            return input + 1;
        }
    };
}

Parser regex_match(const char *regex)
{
    return [regex](const char *input) -> const char * {
        if (input == nullptr)
        {
            return nullptr;
        }

        std::cmatch result;
        if (std::regex_search(input, result, std::regex(regex), std::regex_constants::match_continuous))
        {
            return result.suffix().first;
        }
        else
        {
            return nullptr;
        }
    };
}

Parser skip_ws()
{
    return [](const char *input) -> const char * {
        if (input == nullptr)
        {
            return nullptr;
        }

        size_t i = 0;
        for (; i < std::strlen(input); i++)
        {
            if (!std::isspace(input[i]))
            {
                break;
            }
        }

        return input + i;
    };
}

Parser any_of(std::vector<Parser> parsers)
{
    return [parsers](const char *input) -> const char * {
        for (auto parser : parsers)
        {
            auto result = parser(input);

            if (result != nullptr)
            {
                return result;
            }
        }

        return nullptr;
    };
}

Parser sequence(std::vector<Parser> parsers)
{
    return [parsers](const char *input) -> const char * {
        const char *result = input;

        for (auto parser : parsers)
        {
            result = parser(result);

            if (result == nullptr)
            {
                return nullptr;
            }
        }

        return result;
    };
}

Parser repeat(Parser parser, int n)
{
    return sequence(std::vector<Parser>(n, parser));
}

Parser create_word_parser(std::string word)
{
    std::vector<Parser> parsers;

    for (auto c : word)
    {
        parsers.emplace_back(create_char_parser(c));
    }

    return sequence(parsers);
}
