#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

std::vector<std::string> split(std::string str, char ch)
{
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string tok;

  while(std::getline(ss, tok, ch)) 
    tokens.push_back(tok);

  return tokens;
}

int main() {
    int64_t n, m;
    std::cin >> n;
    std::vector<int64_t> vec(n);

    for(int64_t i = 0; i < n; i++)
        std::cin >> vec.at(i);

    std::cin >> m;
    std::string op;
    std::vector<std::vector<std::string>> ops(m);

    for(int64_t i = 0; i < m; i++) {
        std::getline(std::cin, op);
        ops.at(i) = split(op, ' ');
    }

    for(int64_t i = 0; i < m; i++)
        for(int64_t j = 0; j < ops.at(i).size(); i++)
            std::cout << ops.at(i).at(j) << std::endl;
}