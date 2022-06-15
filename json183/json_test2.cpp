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
    ifs.open("data_ad1.json");
    assert(ifs.is_open());
    Json::Reader reader;
    Json::Value root;
    if (!reader.parse(ifs, root, false))
    {
        cout << "reader parse error: " << strerror(errno) << endl;
        return -1;
    }
    size_t size = root.size();
    cout << "total " << size << " elements" << endl;
    cout << "exist batch_request_spec" << root.isMember("batch_request_spec") << endl;
    cout << "exist account_id" << root.isMember("account_id") << endl;
    //Json::Value body =root["batch_request_spec"][0]["body"];
    //cout << body.toStyledString() << endl;
    //bool isAccountIdExist =body.isMember("account_id") ;
    //cout << "batch_request_spec size" << isAccountIdExist << endl;
    return 0;
}
