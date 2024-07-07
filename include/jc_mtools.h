#ifndef JC_MTOOLS_H
#define JC_MTOOLS_H

#include <cassert>      // assert
#include <ctime>        // clock(), time_t
#include <cmath>
#include <cstring>      // strlen(), memcpy()
#include <cstdlib>      // size_t

#include <string>
#include <sstream>      // stringstream
#include <iostream>     // cerr
#include <random>
#include <exception>
#include <algorithm> // reverse()
// C++11
#include <bitset>
#include <type_traits>

/*
* The function it name has 'C' suffix signify it don't change the arguments.
*/

// Get the cpp version of current environment.
#ifdef _MSVC_LANG
#define JC_MTOOLS_CPPVERS _MSVC_LANG
#else
#define JC_MTOOLS_CPPVERS __cpluscplus
#endif

#if JC_MTOOLS_CPPVERS >= 201703L
#define JC_MTOOLS17
#endif

namespace JcMtools
{

#ifdef JC_MTOOLS17
template <typename... Args>
void formatLog(Args... args) {
    (std::cerr << ... << (std::cerr << args, " "));
    std::cerr << '\n';
}
#else
void formatLog() {
    std::cerr << '\n';
}

template <typename T, typename... Args>
void formatLog(T msg, Args... args) {
    std::cerr << msg << " ";
    if (sizeof...(args) > 0)
        formatLog(args...);
    else
        formatLog();
}
#endif

// Better than std::pow(x, 2).
template<typename T>
double square(T x) {
    return x * x;
}

inline std::string lowerC(const std::string &str) {
    std::string _str = str;
    for (auto &ch : _str)
        ch = std::tolower(ch);
    return _str;
}

inline std::string &lower(std::string &str) {
    for (auto &ch : str)
        ch = std::tolower(ch);
    return str;
}

inline std::string upperC(const std::string &str) {
    std::string _str = str;
    for (auto &ch : _str)
        ch = std::toupper(ch);
    return _str;
}

inline std::string &upper(std::string &str) {
    for (auto &ch : str)
        ch = std::toupper(ch);
    return str;
}

inline bool isNumber(const std::string &str) {
    if (str.empty())
        return false;
    long long flagCount = 0;
    char ch = str[0];
    if ((ch < '0' || ch > '9') && ch != '.' && ch != '-' && ch != '+')
        return false;
    if (str.size() == 1)
        return ch < '0' || ch > '9' ? false : true;
    if (ch == '.')
        flagCount++;
    for (auto it = str.begin() + 1; it != str.end(); ++it) {
        ch = *it;
        if ((ch < '0' || ch > '9') && ch != '.')
            return false;
        if (ch == '.')
            flagCount++;
        if (flagCount > 1)
            return false;
    }
    return true;
}

// TODO
inline long double StringToNumber(const std::string &str) {

}

inline std::string toHexstr(char num, bool isUppercase = true, bool justify = true) {
    std::stringstream ss;
    if (isUppercase)
        ss << std::uppercase << std::hex << num;
    else
        ss << std::hex << num;
    std::string str = ss.str();
    if (justify && str.size() % 2 != 0)
        str.insert(0, "0");
    return str;
}

// TODO
inline std::string toHexstr(int num, bool isUppercase = true, bool justify = true) {
    return std::string();
}

// TODO
inline std::string toHexstr(const std::string &decimalStr, bool isUppercase = true, bool justify = true) {
    std::string _hexstr = lowerC(decimalStr);
    return std::string();
}

inline size_t toDecimal(const std::string &hexStr) {
    std::string _hexStr = upperC(hexStr);
    size_t decimal = 0;
    int carry = 0;
    for (auto it = _hexStr.rbegin(); it != _hexStr.rend(); ++it) {
        if (it == _hexStr.rend() - 1 && *it == '0')
            break;
        size_t ch = *it;
        assert((ch >= '0' && ch <= '9') || (ch >= '9' && ch <= 'A') || (ch >= 'A' && ch <= 'F'));
        decimal += ((ch >= '0' && ch <= '9') ? ch - '0' : ch - 'A' + 10) * static_cast<size_t>(std::pow(16, carry++));
    }
    return decimal;
}

inline std::string strReplaceC(const std::string &str, const std::string &from, const std::string &to,
                               int count = -1, bool isCaseSensitive = true) {
    size_t pos = 0;
    std::string _str = str;
    while (count-- != 0) {
        if (!isCaseSensitive)
            pos = lowerC(_str).find(lowerC(from), pos);
        else
            pos = _str.find(from, pos);
        if (pos == std::string::npos)
            break;
        _str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return _str;
}

inline std::string &strReplace(std::string &str, const std::string &from, const std::string &to,
                               int count = -1, bool isCaseSensitive = true) {
    size_t pos = 0;
    while (count-- != 0) {
        if (!isCaseSensitive)
            pos = lowerC(str).find(lowerC(from), pos);
        else
            pos = str.find(from, pos);
        if (pos == std::string::npos)
            break;
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}

inline std::vector<std::string> strSplit(const std::string &str, const char ch, size_t off = 0) {
    size_t pos1 = off;
    size_t pos2 = str.find(ch, pos1);
    std::vector<std::string> result;
    while (pos2 != std::string::npos) {
        result.push_back(str.substr(pos1, pos2 - pos1));
        if (pos2 == str.size() - 1)
            return result;
        pos1 = pos2 + 1;
        pos2 = str.find(ch, pos1);
    }
    result.push_back(str.substr(pos1, str.size() - pos1));
    return result;
}

inline std::string strJustifyC(const std::string &str, size_t length, const char ch, bool isLeftJustify = true) {
    std::string _str = str;
    size_t diff = length - _str.size();
    if (diff <= 0)
        return _str;
    if (isLeftJustify)
        _str.insert(0, std::string(diff, ch));
    else
        _str += std::string(diff, ch);
    return _str;
}

inline std::string &strJustify(std::string &str, size_t length, const char ch, bool isLeftJustify = true) {
    size_t diff = length - str.size();
    if (diff <= 0)
        return str;
    if (isLeftJustify)
        str.insert(0, std::string(diff, ch));
    else
        str += std::string(diff, ch);
    return str;
}

// @brief Reverse the string of c.
// @param size The need reverse part's size, if it is -1 signify string's length.
inline void strcReverse(char *str, size_t size = -1) {
    if (str == nullptr || (size <= 1 && size != -1))
        return;
    size = size == -1 ? std::strlen(str) : size;
    size_t n = size / 2;
    for (size_t i = 0; i < n; ++i) {
        char ch = str[i];
        str[i] = str[size - 1 - i];
        str[size - 1 - i] = ch;
    }
}

constexpr const size_t BufferSize = 8;
static char Buffer[BufferSize];

template<typename T>
T bytesToNum(const std::string &bytes, bool isReverse = false) {
    long long size = sizeof(T);
    T result = T();
    if (isReverse)
        std::reverse(bytes.begin(), bytes.end());
    std::memcpy(&result, bytes.data(), size);
    return result;
}

template<typename T>
T bytesToNum(std::istream &is, bool isReverse = false, bool resumeCursor = false) {
    size_t size = sizeof(T);
    T result = T();
    auto begpos = is.tellg();
    is.read(Buffer, size);
    size = is.gcount();
    if (isReverse)
        JcMtools::strcReverse(Buffer, size);
    std::memcpy(&result, Buffer, size);
    if (resumeCursor)
        is.seekg(begpos);
    return result;
}

template<typename T>
std::string numToBytes(T num, bool isReverse = false) {
    size_t size = sizeof(T);
    std::memcpy(Buffer, &num, size);
    if (isReverse)
        JcMtools::strcReverse(Buffer, size);
    return std::string(Buffer, size);
}

template<typename T>
void numToBytes(T num, std::ostream &os, bool isReverse = false) {
    size_t size = sizeof(T);
    std::memcpy(Buffer, &num, size);
    if (isReverse)
        JcMtools::strcReverse(Buffer, size);
    os.write(Buffer, size);
}

inline std::ostream &outCharAsBinary(char byte, std::ostream &os = std::cout) {
    std::bitset<8> bin(byte);
    return os << bin;
}

template<typename T>
std::ostream &outNumberAsBinary(T number, std::ostream &os = std::cout) {
    std::string bytes = numToBytes(number, true);
    for (auto &var : bytes)
        outCharAsBinary(var, os) << ' ';
    return os << '\n';
}

inline std::string getCharAsBinary(char byte) {
    std::bitset<8> bin(byte);
    return bin.to_string();
}

template<typename T>
std::string getNumberAsBinary(T number) {
    std::string bytes = numToBytes(number, true);
    std::stringstream ss;
    for (auto &var : bytes)
        ss << getCharAsBinary(var) << ' ';
    return ss.str();
}

// @note C++17 (std::is_floating_point_v)
// @note It can accept a float point num.
template<typename T>
T getRandom(T left, T right, int precision = 2) {
    if (left > right)
        throw std::invalid_argument("The left value should less than the right value.");
    std::random_device rd;
    std::mt19937 mt(rd());
    if (std::is_floating_point_v<T>) {
        double multi = std::pow(10, precision);
        std::uniform_int_distribution lim(int(left * multi), int(right * multi));
        return lim(mt) / multi;
    } else {
        std::uniform_int_distribution lim((int(left)), int(right));
        return lim(mt);
    }
}

inline int getRandom(int left, int right) {
    if (left > right)
        throw std::invalid_argument("The left value should less than the right value.");
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution lim(left, right);
    return lim(mt);
}

inline std::string genUuidV4() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> lim1(0, 15);
    std::uniform_int_distribution<int> lim2(8, 11);

    const char *hexmap = "0123456789abcdef";
    std::stringstream ss;
    for (int i = 0; i < 32; ++i) {
        if (i == 8 || i == 12 || i == 16 || i == 20)
            ss << '-';
        if (i == 12) {
            ss << '4';
            continue;
        }
        if (i == 16) {
            ss << hexmap[lim2(mt)];
            continue;
        }
        ss << hexmap[lim1(mt)];
    }
    return ss.str();
}

inline bool isLittleEndian() {
    static bool inited = false;
    static bool isLittle = false;
    if (inited)
        return isLittle;
    int num = 1;
    char *numPtr = reinterpret_cast<char *>(&num);
    isLittle = numPtr[0] == 1 ? true : false;
    inited = true;
    return isLittle;
}

inline bool isBigEndian() {
    static bool inited = false;
    static bool isBig = false;
    if (inited)
        return isBig;
    int num = 1;
    char *numPtr = reinterpret_cast<char *>(&num);
    isBig = numPtr[0] == 0 ? true : false;
    inited = true;
    return isBig;
}

class ProgressBar
{
public:
    explicit ProgressBar(int barWidth = 70) : barWidth_(barWidth) {};
    void setWidth(int width) {
        barWidth_ = width;
    }
    void setTitle(const std::string &title) {
        title_ = title;
    }
    void setLeftBorder(const std::string &border) {
        leftBorder_ = border;
    }
    void setRightBorder(const std::string &border) {
        rightBorder_ = border;
    }
    void setFillCh(const char ch) {
        fillCh_ = ch;
    }
    void setCurCh(const char ch) {
        curCh_ = ch;
    }
    void setBlankCh(const char ch) {
        blankCh_ = ch;
    }
    void update(int curpos, int endpos) const {
        double percentage = static_cast<double>(curpos) / endpos;
        int pos = static_cast<int>(barWidth_ * percentage);
        std::cout << title_ << leftBorder_;
        for (int i = 0; i < barWidth_; ++i) {
            if (i < pos)std::cout << fillCh_;
            else if (i == pos)std::cout << curCh_;
            else std::cout << blankCh_;
        }
        std::cout << rightBorder_ << static_cast<int>(percentage * 100.0) << " %\r";
        std::cout.flush();
    };

private:
    int barWidth_ = 70;
    std::string title_;
    std::string leftBorder_ = " [";
    std::string rightBorder_ = "] ";
    char fillCh_ = '=';
    char curCh_ = '>';
    char blankCh_ = ' ';
};

class Elapsed
{
public:
    explicit Elapsed(bool isSec = false) : isSec_(isSec), start_(clock()), pre_(start_), end_(start_) {};
    void start() {
        start_ = clock();
        pre_ = start_;
    }
    void get() {
        end_ = clock();
        if (isSec_)
            JcMtools::formatLog(hintPart_, (end_ - pre_) / CLOCKS_PER_SEC, "Sec");
        else
            JcMtools::formatLog(hintPart_, (end_ - pre_), "MSec");
        pre_ = end_;
    }
    void end() {
        end_ = clock();
        if (isSec_)
            JcMtools::formatLog(hintAll_, (end_ - start_) / CLOCKS_PER_SEC, "Sec");
        else
            JcMtools::formatLog(hintAll_, (end_ - start_), "MSec");
        pre_ = end_;
    }
    void setSec(bool isSec) {
        isSec_ = isSec;
    }
    void setHint(const std::string &hintPart, const std::string &hintAll) {
        hintPart_ = hintPart;
        hintAll_ = hintAll;
    }

private:
    bool isSec_;
    time_t start_;
    time_t pre_;
    time_t end_;
    std::string hintPart_ = "Elapsed:";
    std::string hintAll_ = "Total Elapsed:";
};

template<typename T>
struct Pos
{
    Pos() : x(T()), y(T()), z(T()) {};
    Pos(T x, T y, T z) :
        x(x), y(y), z(z) {};
    bool isNeighbour(const Pos &other, double range = 1.0) const {
        return square(x - other.x) +
            square(y - other.y) +
            square(z - other.z) <=
            square(range);
    }
    Pos &operator+=(const T &value) {
        x += value;
        y += value;
        z += value;
        return *this;
    }
    Pos &operator+=(const Pos &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Pos &operator-=(const T &value) {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }
    Pos &operator-=(const Pos &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Pos operator+(const T &value) const {
        Pos pos;
        pos.x = x + value;
        pos.y = y + value;
        pos.z = z + value;
        return pos;
    }
    Pos operator+(const Pos &other) const {
        Pos pos;
        pos.x = x + other.x;
        pos.y = y + other.y;
        pos.z = z + other.z;
        return pos;
    }
    Pos operator-(const T &value) const {
        Pos pos;
        pos.x = x - value;
        pos.y = y - value;
        pos.z = z - value;
        return pos;
    }
    Pos operator-(const Pos &other) const {
        Pos pos;
        pos.x = x - other.x;
        pos.y = y - other.y;
        pos.z = z - other.z;
        return pos;
    }

    T x;
    T y;
    T z;
};
using Posc = Pos<char>;
using Poss = Pos<short>;
using Posi = Pos<int>;
using Posli = Pos<long long>;
using Posf = Pos<float>;
using Poslf = Pos<double>;

template<typename T>
std::ostream &operator<<(std::ostream &os, const Pos<T> &pos) {
    if (std::is_same<T, char>::value || std::is_same<T, unsigned char>::value)
        os << '[' << int(pos.x) << ',' << int(pos.y) << ',' << int(pos.z) << ']';
    else
        os << '[' << pos.x << ',' << pos.y << ',' << pos.z << ']';
    return os;
}

struct Rgb
{
    Rgb() : r(0), g(0), b(0), a(0) {};
    Rgb(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 0) :
        r(r), g(g), b(b), a(alpha) {};
    std::string getHexstr(bool isUppercase = true) {
        std::string str;
        str = toHexstr(r, isUppercase) +
            toHexstr(g, isUppercase) +
            toHexstr(b, isUppercase);
        return str;
    }

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

inline std::ostream &operator<<(std::ostream &os, const Rgb &rgb) {
    os << '[' << int(rgb.r) << ',' << int(rgb.g) << ',' << int(rgb.b) << ',' << int(rgb.a) << ']';
    return os;
}

inline Rgb getRgbFromHexstr(const std::string &hexstr) {
    assert(hexstr.size() == 6);
    int rgb[3] = { 0, 0, 0 };
    for (int i = 0; i < 6; ++i) {
        char ch = toupper(hexstr[i]);
        if (ch >= '0' && ch <= '9')
            rgb[i / 2] += i % 2 ? (ch - '0') : (ch - '0') * 16;
        else if (ch >= 'A' && ch <= 'F')
            rgb[i / 2] += i % 2 ? (ch - 'A' + 10) : (ch - 'A' + 10) * 16;
        else
            throw std::invalid_argument("The hex string given is illegal.");
    }
    return Rgb(rgb[0], rgb[1], rgb[2]);
}

inline std::string rgbToHexstr(const Rgb &rgb, bool isUppercase = true) {
    std::string str;
    str = toHexstr(rgb.r, isUppercase) +
        toHexstr(rgb.g, isUppercase) +
        toHexstr(rgb.b, isUppercase);
    return str;
}

inline double rgbDistance(const Rgb &a, const Rgb &b) {
    return  square(a.r - b.r) + square(a.g - b.g) + square(a.b - b.b);
}

inline double rgbSimilarity(const Rgb &a, const Rgb &b) {
    return 1. -
        (square(a.r - b.r) * 0.32 + square(a.g - b.g) * 0.52 + square(a.b - b.b) * 0.16) /
        65025;
}

struct Version
{
    Version() : major(0), minor(0), patch(0) {};
    Version(unsigned char major, unsigned char minor, unsigned char patch) :
        major(major), minor(minor), patch(patch) {};
    inline int data() const {
        return (major << 24) ^ (minor << 16) ^ patch;
    }
    unsigned char major;
    unsigned char minor;
    unsigned char patch;
};

static bool operator==(const Rgb &lhs, const Rgb &rhs) {
    if (lhs.r == rhs.r &&
        lhs.g == rhs.g &&
        lhs.b == rhs.b)
        return true;
    return false;
}

static bool operator==(const Version &lhs, const Version &rhs) {
    if (lhs.data() == rhs.data())
        return true;
    return false;
}

static bool operator>(const Version &lhs, const Version &rhs) {
    if (lhs.data() > rhs.data())
        return true;
    return false;
}

static bool operator<(const Version &lhs, const Version &rhs) {
    if (lhs.data() < rhs.data())
        return true;
    return false;
}

static bool operator>=(const Version &lhs, const Version &rhs) {
    if (lhs > rhs || lhs == rhs)
        return true;
    return false;
}

static bool operator<=(const Version &lhs, const Version &rhs) {
    if (lhs < rhs || lhs == rhs)
        return true;
    return false;
}
}

namespace std
{
template<> struct hash<JcMtools::Rgb>
{
    size_t operator()(const JcMtools::Rgb &rgb) const {
        size_t h1 = std::hash<unsigned char>()(rgb.r);
        size_t h2 = std::hash<unsigned char>()(rgb.g);
        size_t h3 = std::hash<unsigned char>()(rgb.b);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

template<> struct hash<JcMtools::Version>
{
    size_t operator()(const JcMtools::Version &version) const {
        return version.data();
    }
};
}

#endif // !JC_MTOOLS_H
