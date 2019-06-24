#pragma once

#include <string_view>

#pragma warning(push, 0)    
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#pragma warning(pop)

#include "target.hpp"
#include "../services.hpp"

namespace warmane::api
{
	namespace asio = boost::asio;
	namespace beast = boost::beast;
	namespace http = beast::http;
	using tcp = asio::ip::tcp;

	constexpr std::string_view url()
	{ return "http://armory.warmane.com/api/"; }

	// Synchronous interface for use with warmane's api services
	class connection
	{
	public:
		connection();
		~connection() noexcept;

		connection(connection&& conn) noexcept;

		void connect();

		http::response<http::string_body> get(const api::target& target);

		void shutdown();

		tcp::socket& socket() noexcept;

		const tcp::socket& socket() const noexcept;

	private:
		beast::error_code noexcept_shutdown() noexcept;

	private:
		asio::io_context io_;
		tcp::resolver resolver_;
		tcp::socket socket_;
	};

	inline connection::connection()
		: io_{}
		, resolver_{io_}
		, socket_{io_}
	{}

	inline connection::~connection() noexcept
	{
		this->shutdown();
	}

	inline connection::connection(connection&& conn) noexcept
		: io_{}
		, resolver_{std::move(conn.resolver_)}
		, socket_{std::move(conn.socket_)}
	{}

	inline http::response<http::string_body> 
		connection::get(const api::target& target)
	{
		http::request<http::empty_body> req{http::verb::get, target.encode_url(), 11};

		req.set(http::field::host, warmane::hostname());
		req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

		http::write(socket_, req);

		beast::flat_buffer buffer;

		// Declare a container to hold the response
		http::response<http::string_body> res;

		http::read(socket_, buffer, res);
		return res;
	}

	inline void connection::connect()
	{
		const auto results = resolver_.resolve(warmane::hostname().data(), std::to_string(80));
		asio::connect(socket_, results.begin(), results.end());
	}

	inline void connection::shutdown()
	{
		const auto ec = this->noexcept_shutdown();

		if (ec && ec != beast::errc::not_connected)
			throw beast::system_error{ec};
	}

	inline beast::error_code connection::noexcept_shutdown() noexcept
	{
		beast::error_code ec;
		socket_.shutdown(tcp::socket::shutdown_both, ec);

		return ec;
	}

	inline tcp::socket& connection::socket() noexcept
	{
		return socket_;
	}

	inline const tcp::socket& connection::socket() const noexcept
	{
		return socket_;
	}

	connection connect()
	{
		connection conn;
		conn.connect();
		return conn;
	}
}
