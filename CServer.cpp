#include "CServer.h"
#include "HttpConnection.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port):
	_ioc(ioc),_acceptor(ioc,tcp::endpoint(tcp::v4(),port)),_socket(ioc)
{

}

void CServer::Start()
{
	//�ӳ�����
	auto self = shared_from_this();
	_acceptor.async_accept(_socket, [self](beast::error_code ec) {
		try
		{
			//��������������
			if (ec) {
				self->Start();
				return;
			}
			//���������ӣ�������HttpConnect����
			std::make_shared<HttpConnection>(std::move(self->_socket))->Start();
			//��������
			self->Start();
		}
		catch (const std::exception& exp)
		{

		}
	});
}
