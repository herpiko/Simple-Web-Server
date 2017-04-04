#include "server_http.hpp"
#include "client_http.hpp"
#include "/usr/local/opt/openssl/include/openssl/opensslv.h"
#include <uWS/uWS.h>

using namespace std;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

int main() {

	HttpServer server;
	server.config.port=8000;

	server.resource["^/ok$"]["GET"]=[](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
		string ok = "ok";
		*response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << ok.length() << "\r\n\r\n" << ok;
	};
	
	server.resource["^/ok$"]["POST"]=[](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
		auto foo=request->content.string();
		*response <<  "HTTP/1.1 200 OK\r\nContent-Length: " << foo.length() << "\r\n\r\n" << foo;
	};
    
	server.start();

  // Socket

  uWS::Hub h;
  hub.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
    ws->send(message, length, opCode);
  });
    
	return 0;

}

