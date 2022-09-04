#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <sstream>
#include <sys/types.h>
#include <memory>
#include <unordered_map>
#include<json/json.h>
using namespace std;


class GenericClient {
    public:
    GenericClient() {}
    virtual ~GenericClient() {}

    virtual std::shared_ptr<Json::Value> DoRPC(uint64_t uin, const std::string& name, string& input_data, int& rpc_ret) = 0;

    virtual bool HasMethod(const std::string& name) {
        return false;
    }
};

struct RPCMeta {
    std::shared_ptr<GenericClient> Client;
    std::string Method;
};

///////////////////////////////////////////////////////////////

// 映射表
std::unordered_map<std::string, RPCMeta> metaTable;
std::unordered_map<std::string, std::shared_ptr<GenericClient>> clientTable;

void InitClientTable() {
    clientTable["advertiserinfo"] = std::make_shared<MmocAdGetAdvertiserInfoProxyClient>();
}

void InitMetaTable(Json::Value& cfg) {
    InitClientTable();
    RPCMeta meta;
    meta.Client = client;
    meta.Method = method;
    metaTable[key] = meta;
    MMINFO("init rpc: %s", item.c_str());
    printf("rpcproxy: InitMetaTable success\n");
}

//////////////////////////////////////////////////////////////
class MmocadtargetcategoryClient{};
class GetAreaCodeMapReq{};
class GetAreaCodeMapRsp{};

class MmocAdGetAdvertiserInfoProxyClient: public GenericClient
{
private:
    MmocAdGetAdvertiserInfoClient client;
public:
    MmocAdGetAdvertiserInfoProxyClient(){};
    virtual ~MmocAdGetAdvertiserInfoProxyClient(){};

    virtual std::shared_ptr<Json::Value> DoRPC(uint64_t uin,  const std::string& name, string& input_data, int& rpc_ret);
    virtual bool HasMethod(const std::string& name);
};

int rpcGetAreaCodeMap(MmocadtargetcategoryClient* client, uint32_t uin, std::string& in, std::string& out, int timeout) {
    int ret;
    // in 转换为req
    GetAreaCodeMapReq req;
    //TODO
    GetAreaCodeMapRsp rsp;

    ret = client->GetAreaCodeMap(uin, pbin, pbout);
    if (ret >= 0 ) {
        cout << " ret = " << ret << endl;
        return -1;
    }
    // rsp 转换为 out
    //TODO
    return ret;
}

std::shared_ptr<Json::Value> MmocAdGetAdvertiserInfoProxyClient::DoRPC(uint64_t uin, const std::string& name, Json::Value* poInput, int timeout, int& rpc_ret) {
    string in, out;
    Json::FastWriter wr;
    in = wr.write(*poInput);

    static auto rpcs = std::unordered_map<std::string, std::function<int(MmocadtargetcategoryClient*, uint32_t uin,  std::string&, std::string&, int)>>{
        {"GetAreaCodeMap", rpcGetAreaCodeMap},
    };
    auto itor = rpcs.find(name);
    if (itor == rpcs.end()) {
        printf("DoRPC, call "+name+" error, invalid method "+name);
    }
    rpc_ret = itor->second(&(this->client), uin, in, out, timeout);
    if (rpc_ret < 0) {
        printf("DoRPC, call "+name+" error, ret="+std::to_string(rpc_ret));
    }

    auto r = std::make_shared<Json::Value>();
    Json::Reader rd;
    if (!rd.parse(out, *r)) {
        printf("DoRPC, parse json error, out="+out);
    }
    return r;
}

bool MmocAdGetAdvertiserInfoProxyClient::HasMethod(const std::string& name) {
    static auto methods = std::unordered_set<std::string>{
        "GetAreaCodeMap",
    };
    auto itor = methods.find(name);
    return itor != methods.end();
}

////////////////////////////////////////////////////////////////
class RPCProxyBase {
    public:
        RPCProxyBase();
        ~RPCProxyBase();

        virtual string Authenticate(string auth_info ) {
            return "";
        }
    protected:
        virtual int Process(const string& input_data);
        std::shared_ptr<Json::Value> DoRPC(const string& input_data);
        RPCMeta& GetRPCMeta(const string& key);
        int Output(Json::Value& oRoot);
}

RPCProxyBase::RPCProxyBase(int argc, char* argv[], const char* svrname, const char* config) : MMNewSimpleCGI(svrname, argc, argv, svrname) {
    this->config = parseConfig(config);
    InitMetaTable(this->config);
}

RPCProxyBase::~RPCProxyBase() {}


RPCMeta& RPCProxyBase::GetRPCMeta(const string& key) {
    auto it = metaTable.find(key);
    if (it == metaTable.end()) {
		string encoded_key = HTMLEncode(key);
        cout << "can't find rpc client for key: " << encoded_key << endl;
        return NULL;
    }
    return it->second;
}

int RPCProxyBase::Process(const string& input_data){
    auto r = this->DoRPC(input_data);
    this->Output(*r);
}

std::shared_ptr<Json::Value> RPCProxyBase::DoRPC(const string& auth_info, const string& input_data) {
    // 鉴权
    string err_msg = this->Authenticate(poInput, poOutput, meta.Auth);
    if (err_msg != "") {
        cout << "authenticate fail, " + err_msg);
    }
    // rpc调用
    auto r = client->DoRPC(uin, method, &args, timeout, rpc_ret);
    // 返回输出
    return r
}

////////////////////////////////////////////////////////////////
class RPCProxy: public RPCProxyBase {
public:
    RPCProxy():{};
    // 子类实现鉴权
    virtual string Authenticate(){
        cout << "Authentication" << endl;
        return "";
    }
    int Process(){
        cout << "Process" << endl;
        int ret = RPCProxyBase::Process(input_data string);
        return "";
    }
    string m_name;
};

////////////////////////////////////////////////////////////////
int main()
{
    return 0;
}

