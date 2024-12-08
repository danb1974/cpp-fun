#include <iostream>
#include <vector>

typedef struct PointStruct {
    int x;
    int y;

    PointStruct(int x, int y) : x(x), y(y) {
        std::cout << "new Point " << x << "," << y << std::endl;
    }

    ~PointStruct() {
        std::cout << "del Point " << x << "," << y << std::endl;
    }
} Point;

typedef struct ObjectStruct {
    int id;
    Point p;

    ObjectStruct(int id, Point p) : id(id), p(p) {
        std::cout << "new Object " << id << std::endl;
    }

    ~ObjectStruct() {
        std::cout << "del Object " << id << std::endl; 
    }
} Object;

std::vector<Object> objects;

void test() {
    objects.resize(1);
    objects[0] = Object(1, Point(1, 2));
}

int main()
{
    std::cout << "Hello!" << std::endl;

    test();

    return 0;
}
