#include <string>

#include "string.h"

unsigned char toHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

inline unsigned char fromHex(char ch) {  
    if (ch >= '0' && ch <= '9') return ch - '0';  
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;  
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;  
    return 0;  
}

std::string urlEncode(const std::string& str)
{
    std::string strTemp = "";
    string_size length = str.length();
    for (string_size i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
                (str[i] == '-') ||
                (str[i] == '_') ||
                (str[i] == '.') ||
                (str[i] == '~'))
            strTemp += str[i];
        else
        {
            strTemp += '%';
            strTemp += toHex((unsigned char)str[i] >> 4);
            strTemp += toHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

std::string urlDecode(const std::string& str) {  
    std::string result;  
    result.reserve(str.length());  
      
    size_t length = str.length();  
    for (size_t i = 0; i < length; i++) {  
        char c = str[i];  
          
        if (c == '+') {  
            result += ' ';  
        } else if (c == '%' && i + 2 < length) {  
            char c1 = str[i + 1];  
            char c2 = str[i + 2];  
              
            // 简化的十六进制检查  
            bool isHex1 = (c1 >= '0' && c1 <= '9') || (c1 >= 'A' && c1 <= 'F') || (c1 >= 'a' && c1 <= 'f');  
            bool isHex2 = (c2 >= '0' && c2 <= '9') || (c2 >= 'A' && c2 <= 'F') || (c2 >= 'a' && c2 <= 'f');  
              
            if (isHex1 && isHex2) {  
                result += fromHex(c1) * 16 + fromHex(c2);  
                i += 2;  
            } else {  
                result += '%';  
            }  
        } else if (c == '%' && i + 2 >= length) {  
            result += '%';  
        } else {  
            result += c;  
        }  
    }  
      
    return result;  
}

std::string joinArguments(const string_multimap &args)
{
    std::string strTemp;
    for (auto &p: args)
    {
        strTemp += p.first + "=" + urlEncode(p.second) + "&";
    }
    if (!strTemp.empty())
    {
        strTemp.pop_back();
    }
    return strTemp;
}
