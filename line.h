#include <map>
#include <vector>
#include <TridentTD_LineNotify.h>
void DoLINE(std::vector<String> data)
{
  if(data[0] == "0"){
    LINE.setToken(data[1]);
  }
  
}
