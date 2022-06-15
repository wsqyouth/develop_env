#include <json/json.h>
#include <string>
#include <iostream>
using namespace std;

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

int main()
{
string test = "{\"encrptpripid\": \"f2cbfd07bb6b784f0fb5a52e17e1b3930324e1ef9065338f4aa1\", \
\"entname\": \"xx显华化工科技有限公司\",\
  \"enttype\": \"1151\",\
  \"enttypename\": \"法定代表人:\",\
  \"estdate\": \"2003年06月19日\",\
  \"lerep\": \"丰佩川\",\
  \"pripid\": \"106350010220030687030\",\
  \"regno\": \"911706007526952553\",\
  \"regorgname\": \"XX经济技术开发区市场监督管理局\",\
  \"uniscid\":\"91106007526952553\"}";

Json::Reader reader;
Json::Value value;
if(reader.parse(test,value))
{
  if(!value["encrptpripid"].isNull())
  {
  cout << value["entname"].asString() << endl;
  cout << value["regorgname"].asString()<< endl;
  }
}
return 0;
}
