//
// Created by pj on 17-4-28.
//

#ifndef PROPROCESS_STATSENDPOINT_H
#define PROPROCESS_STATSENDPOINT_H

#include "pistache/net.h"
#include "pistache/http.h"
#include "pistache/router.h"
#include "pistache/endpoint.h"
#include "alignment_factory.h"
#include "analysis_factory.h"

#include "json/json.h"

using namespace Net;
using namespace std;

class StatsEndpoint{
public:
  StatsEndpoint(Net::Address address)
      : httpEndpoint(std::make_shared<Net::Http::Endpoint>(address)){}

  void Init(int thr = 2){
    auto opts = Net::Http::Endpoint::options()
        .threads(thr)
        .flags(Net::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    setupRoutes();
  }

  void Start(){
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
  }

  void Shutdown(){
    httpEndpoint->shutdown();
  }


private:
  void setupRoutes();

  // region alignment

  void pretreatment_alignment_FFT(const Rest::Request &request,
                                  Net::Http::ResponseWriter response);

  void pretreatmetn_alignment_StaticAlignment(const Rest::Request &request,
                                              Net::Http::ResponseWriter response);


  void pretreatmetn_alignment_DTW(const Rest::Request &request,
                                  Net::Http::ResponseWriter response);

  void pretreatmetn_alignment_POC(const Rest::Request &request,
                                  Net::Http::ResponseWriter response);

  // endregion alignment

  Json::Value write3Dresult(const vector<vector<vector<double>>> &result);

  vector<int> middle_wrapper(const unsigned char ct);

  void attack_analysis_DPA(const Rest::Request &request,
                           Net::Http::ResponseWriter response);

  void test(const Rest::Request &request, Net::Http::ResponseWriter response);

  void kill(const Rest::Request &request, Net::Http::ResponseWriter response);

  // region tools

  bool checkHttpParams(Json::Value const &root, vector<string> const &params);

  vector<vector<double> > ReadTraces(const Json::Value &root);

  vector<double> ReadSignleTrace(const Json::Value &root);

  template<typename Iterable>
  void Iterable2Json(Json::Value &value, Iterable const &cont);

  // endregion tools end

  // region variable

  std::shared_ptr<Net::Http::Endpoint> httpEndpoint;
  Rest::Router router;

  Alignment_Factory alignmentFactory;

  Analysis_factory analysisFactory;

  // endregion variable
};

#endif //PROPROCESS_STATSENDPOINT_H
