#include <memory>

class Demo {
public:
    Demo();
    bool empty();
    bool full();

private:
    int front;
    int rear;
    std::shared_ptr<int> ptr[16];
};