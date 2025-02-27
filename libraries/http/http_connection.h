#pragma once

#include "http_common.h"
#include "http_parser.h"

namespace NetZ
{
namespace Http
{
  constexpr uint64_t socketTimeoutDuration = 15000;
  constexpr int buffer_size = 8192;
  class ResourceManager;
  class HttpServer;

  class HttpConnection
  {
    friend class HttpServer;
  public:
    HttpConnection(const HttpConnection&) = delete;
    HttpConnection& operator=(const HttpConnection&) = delete;

    HttpConnection(SocketService* _service, ResourceManager* rMgr);
    ~HttpConnection() { Stop(); }
    void Start();
    void Stop();

    TcpSocket socket;
  private:
    HttpMessageRequest request;
    HttpMessageResponse response;

    InputBuffer reply;
    ResourceManager* resource_mgr;
    SocketService* service;
    Util::TimerID socketTimeoutTimer = -1;
    char receiveBuffer[buffer_size];

    void Read(HttpParser::ParseState state);
    void Write();
    void WriteDefaultResponse();
  };
}
}
