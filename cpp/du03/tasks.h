#include <functional>
#include <regex>
#include <vector>

using Parser = std::function<const char *(const char *)>;

Parser create_char_parser(const char c);
Parser regex_match(const char *regex);
Parser skip_ws();
Parser any_of(std::vector<Parser> parsers);
Parser sequence(std::vector<Parser> parsers);
Parser repeat(Parser parser, int n);
Parser create_word_parser(std::string word);
