#include <fstream>
#include <iostream>
#include <json/json.h>
#include <cassert>
#include <errno.h>
#include <string.h>
using namespace std;
int main(void)
{
    ifstream ifs;
    ifs.open("data.json");
    assert(ifs.is_open());
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(ifs, root, false))
    {
        cout << "reader parse error: " << strerror(errno) << endl;
        return -1;
    }
    string name;
    int age;
    int size;
    size = root.size();
    cout << "total " << size << " elements" << endl;
    for (int i = 0; i < size; ++i)
    {
        name = root[i]["name"].asString();
        age = root[i]["age"].asInt();
        cout << "name: " << name << ", age: " << age << endl;
    }
    return 0;
}
