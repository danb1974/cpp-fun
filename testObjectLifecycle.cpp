#include <iostream>
#include <vector>

typedef struct PointStruct {
    int x;
    int y;

    PointStruct() {
        std::cout << "new Point (empty) " << this << std::endl;
        x = 0;
        y = 0;
    }

    PointStruct(int x, int y) : x(x), y(y) {
        std::cout << "new Point " << this << " " << x << "," << y << std::endl;
    }

    ~PointStruct() {
        std::cout << "del Point " << this << " " << x << "," << y << std::endl;
    }

    PointStruct(const PointStruct &obj) {
        std::cout << "copy Point " << this << " from " << &obj << " " << obj.x << "," << obj.y << std::endl;
        x = obj.x;
        y = obj.y;
    }
} Point;

typedef struct ObjectStruct {
    int id;
    Point p;

    ObjectStruct() {
        std::cout << "new Object (empty) " << this << std::endl;
        id = 0;
        p = Point(0, 0);
    }

    ObjectStruct(int id, Point p) : id(id), p(p) {
        std::cout << "new Object " << this << " " << id << std::endl;
    }

    ~ObjectStruct() {
        std::cout << "del Object " << this << " " << id << std::endl; 
    }

    ObjectStruct(const ObjectStruct &obj) {
        std::cout << "copy Object " << this << " from " << &obj << " " << obj.id << " point " << &obj.p << std::endl;
        id = obj.id;
        p = obj.p;
    }
} Object;

std::vector<Object> objects;

void test1() {
    objects.emplace_back(Object(12, Point(1, 2)));
}

void test2() {
    objects[0] = Object(34, Point(3, 4));
}


int main()
{
    std::cout << "Hello!" << std::endl;

    std::cout << "<<< Test1" << std::endl;
    test1();
    std::cout << ">>> Test1" << std::endl;

    std::cout << "<<< Test2" << std::endl;
    test2();
    std::cout << ">>> Test2" << std::endl;

    std::cout << "Clear" << std::endl;
    objects.clear();

    return 0;
}
