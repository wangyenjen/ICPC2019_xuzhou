#ifndef VALIDATE_H_
#define VALIDATE_H_

#include <regex>
#include <cstdlib>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

namespace CompLib {

template <class CharT, class Traits>
std::basic_regex<CharT> GenRegex(const std::basic_string<CharT, Traits>& format) {
  std::basic_string<CharT, Traits> regex;
  bool flag = false;
  for (size_t i = 0; i < format.size(); i++) {
    if (flag) {
      switch (format[i]) {
        case 'd': regex += "(0|-?[1-9]\\d*)"; break;
        case 'D': regex += "-?\\d+"; break;
        case 'u': regex += "(0|[1-9]\\d*)"; break;
        case 'U': regex += "\\d+"; break;
        case 'f': regex += "(0|[1-9]\\d*)(\\.\\d*)?|\\.\\d*"; break;
        case 'F': regex += "\\d+(\\.\\d*)?|\\.\\d*"; break;
        case 'e': regex += "((0|[1-9]\\d*)(\\.\\d*)?|\\.\\d*)([eE][\\+-]?\\d+)?"; break;
        case 'W': regex += "\\w+"; break;
        case 'w': regex += "[[:alnum:]]+"; break;
        case 'C': regex += "[[:upper:]]+"; break;
        case 'c': regex += "[[:lower:]]+"; break;
        case '%': regex += "%"; break;
        default:  regex += format[i];
      }
      flag = false;
    } else if (format[i] == '%') {
      flag = true;
    } else {
      regex += format[i];
    }
  }
  return std::basic_regex<CharT>(regex);
}

inline std::regex GenRegex(const char* format) {
  return GenRegex(std::string(format));
}

template <class CharT, class Traits = std::char_traits<CharT>>
class BasicValidator {
  using String_ = std::basic_string<CharT, Traits>;
  using StrStream_ = std::basic_stringstream<CharT>;
  using IStream_ = std::basic_istream<CharT, Traits>;
  using Regex_ = std::basic_regex<CharT>;
  StrStream_ line_;
  IStream_& input_;
  void Throw_(const std::string& str, const std::string& field = "") {
    throw std::invalid_argument(field.size () ? str + " on " + field : str);
  }
 public:
  BasicValidator(IStream_& in) : input_(in) {}
  void AssertEnd() {
    CharT c;
    if (input_.get(c)) Throw_("Assert EOF failed");
  }
  void AssertEOL() {
    CharT c;
    if (line_.get(c)) Throw_("Assert EOL failed");
  }
  void ReadLine() {
    String_ tmp;
    std::getline(input_, tmp);
    line_ = StrStream_(tmp);
  }
  void ReadLine(const Regex_& format, const std::string& field = "") {
    String_ tmp;
    std::getline(input_, tmp);
    if (!std::regex_match(tmp, format)) Throw_("Regex mismatch", field);
    line_ = StrStream_(tmp);
  }
  void ReadLine(const String_& format, const std::string& field = "") {
    ReadLine(GenRegex(format), field);
  }
  template <class T> T Get(const std::string& field = "") {
    T x;
    if (!(line_ >> x)) Throw_("Cannot input from line", field);
    return x;
  }
  template <class T> T GetNoCheck() {
    T x;
    line_ >> x;
    return x;
  }
  int64_t GetLong(int64_t l, int64_t r, const std::string& field = "") {
    int64_t x = Get<int64_t>();
    if (x < l || r < x) Throw_("Integer out of range", field);
    return x;
  }
};

class StdinValidator : public BasicValidator<char> {
 public:
  StdinValidator() : BasicValidator<char>(std::cin) {
#ifdef _WIN32
    if (_setmode(_fileno(stdin), _O_BINARY) == -1) {
      throw std::runtime_error("Cannot switch to binary mode");
    }
#endif
  }
};

typedef BasicValidator<char> Validator;

} // namespace CompLib

#endif
