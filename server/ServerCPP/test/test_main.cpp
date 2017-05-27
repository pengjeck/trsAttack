//
// Created by pj on 17-4-28.
//

#include "pistache/endpoint.h"

using namespace Net;
using namespace std;


class AlignmentHandler : public Http::Handler{
public:
HTTP_PROTOTYPE(AlignmentHandler)
  void onRequest(const Http::Request &request, Http::ResponseWriter response){
    auto stream = response.stream(Http::Code::Ok);
    stream << "hello";
//    stream << flush;
  //   sleep(1);
      stream << end;
  }
};

int main(){
  Net::Address addr(Net::Ipv4::any(), Net::Port(9080));

  auto opts = Http::Endpoint::options().threads(1);
  Http::Endpoint server(addr);
  server.init(opts);
  server.setHandler(std::make_shared<AlignmentHandler>());
  server.serve();
}
