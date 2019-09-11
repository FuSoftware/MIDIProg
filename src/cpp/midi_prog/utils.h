#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cctype>
#include <locale>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <unordered_map>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

static inline std::vector<std::string> split(const std::string& s, char delimiter, bool trim_token = false)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(s);
    while (std::getline(token_stream, token, delimiter))
    {
        if(trim_token) trim(token);
        tokens.push_back(token);
    }
    return tokens;
}

template <typename K, typename V>
static bool umap_has_key(std::unordered_map<K, V> m, K k){
    auto it = m.find(k);
    return it != m.end();
}

template <typename K, typename V>
static bool map_has_key(std::map<K, V> m, K k){
    auto it = m.find(k);
    return it != m.end();
}

static void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);

    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + replaceStr.size());
    }
}

static std::vector<unsigned char> stob(std::string c)
{
    c.erase(std::remove(c.begin(), c.end(), ' '), c.end());
    std::vector<unsigned char> bytes;

    size_t i = 0;
    while(i+2 < c.size())
    {
        bytes.push_back(static_cast<unsigned char>(std::stoi(c.substr(i,2),nullptr,16)));
        i++;
    }

    return bytes;
}

static std::string get_folder(std::string path)
{
    size_t found;
    found=path.find_last_of("/\\");
    std::string folder = path.substr(0,found);
    return folder;
}


#endif // UTILS_H
