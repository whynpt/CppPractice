#include <iostream>
#include <optional>
#include "DemoClass.h"

using namespace std;

unordered_map<int, DemoClass> sMap;
// 不加std出现重载错误，原因可能跟c++版本相关
// std::reference_wrapper不会解决析构问题，析构问题的根源在于map里存的是object不是pointer
std::optional<DemoClass> getEle(int key) {
    auto it = sMap.find(key);
    if (it != sMap.end()) {
        return it->second;
    } else {
        cout << key << "is not found\n";
        return std::nullopt;
    }
}

int main()
{
    cout << "start to run\n";
    sMap[1] = DemoClass(); //执行完会有析构
    sMap[2] = DemoClass(2, 2.0, 20, 20.0); //执行完会有析构
    if (auto ele = getEle(1)) {
        cout << "get value: " << ele->pubInt << endl;
        ele->pubInt = 999;
        cout << "get value after change: " << getEle(1)->pubInt << endl;
    }
    if (auto ele = getEle(2)) {
        cout << "get value: " << ele->pubInt << endl;
        ele->pubInt = 9999;
        cout << "get value after change: " << getEle(2)->pubInt << endl;
    }
    cout << "done\n";
    return 0;
}