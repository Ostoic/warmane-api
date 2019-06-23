#pragma once

#include <string_view>
//#include <boost/beast/core.hpp>
//#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>

//#include "target.hpp"
//#include "../services.hpp"

namespace warmane::api
{
	//namespace asio = boost::asio;
	//namespace beast = boost::beast;
	//namespace http = beast::http;
	//using tcp = asio::ip::tcp;

	//constexpr std::string_view url()
	//{ return "http://armory.warmane.com/api/"; }

	//class connection
	//{
	//public:
	//	connection();
	//	~connection() noexcept;

	//	connection(connection&& conn);

	//	void connect();

	//	http::response<http::string_body> get(const api::target& target);

	//	void shutdown();

	//	beast::tcp_stream& stream() noexcept;

	//private:
	//	beast::error_code noexcept_shutdown() noexcept;

	//private:
	//	asio::io_context io_;
	//	tcp::resolver resolver_;
	//	beast::tcp_stream stream_;
	//};

	//inline connection::connection()
	//	: io_{}
	//	, resolver_{io_}
	//	, stream_{io_}
	//{}

	//inline connection::~connection() noexcept
	//{
	//	this->shutdown();
	//}

	//inline connection::connection(connection&& conn)
	//	: io_{}
	//	, resolver_{std::move(conn.resolver_)}
	//	, stream_{std::move(conn.stream_)}
	//{}

	//inline http::response<http::string_body> connection::get(const api::target& target)
	//{
	//	http::request<http::empty_body> req{http::verb::get, target.encode_url(), 11};

	//	//req.set(http::field::host, warmane::hostname());
	//	//req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

	//	//http::write(stream_, req);

	//	beast::flat_buffer buffer;

	//	// Declare a container to hold the response
	//	http::response<http::string_body> res;

	//	//http::read(stream_, buffer, res);
	//	return res;
	//}

	//inline void connection::connect()
	//{
	//	const auto results = resolver_.resolve(warmane::hostname().data(), std::to_string(80));
	//	stream_.connect(results);
	//}

	//inline void connection::shutdown()
	//{
	//	const auto ec = this->noexcept_shutdown();

	//	if (ec && ec != beast::errc::not_connected)
	//		throw beast::system_error{ec};
	//}

	//inline beast::error_code connection::noexcept_shutdown() noexcept
	//{
	//	beast::error_code ec;
	//	stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

	//	return ec;
	//}

	//inline beast::tcp_stream& connection::stream() noexcept
	//{
	//	return stream_;
	//}

	//connection connect()
	//{
	//	connection conn;
	//	conn.connect();
	//	return conn;
	//}
}
