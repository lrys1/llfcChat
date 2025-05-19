#pragma once
#include "const.h"
class HttpConnection:public std::enable_shared_from_this<HttpConnection>
{
	friend class LogicSystem;
public:

	HttpConnection(boost::asio::io_context & ioc);
	void Start();
	tcp::socket& GetSocket() {
		return _socket;
	}
private:

	void WriteResponse();
	void HandleReq();
	void CheckDeadline();
	void PreParseGetParam();
	tcp::socket _socket;
	beast::flat_buffer _buffer{ 8192 };
	http::request<http::dynamic_body> _request;
	http::response<http::dynamic_body> _response;
	//花括号初始化列表，防止括号语义歧义
	net::steady_timer deadline_{
		//获得调度器
		_socket.get_executor(),std::chrono::seconds(60)
	};

	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;
};

