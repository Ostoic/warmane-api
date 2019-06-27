#pragma once

#include <string_view>
#include <memory>
#include <optional>

#pragma warning(push, 0)
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#pragma warning(pop)

#include "target.hpp"
#include "../services.hpp"

#include <iostream>

namespace warmane::armory::http
{
	namespace system = boost::system;
	namespace asio = boost::asio;
	namespace beast = boost::beast;
	using tcp = asio::ip::tcp;

	// Synchronous interface for use with warmane's api services
	class connection
	{
	public:
		struct options;

		static constexpr const char* host = armory::hostname;

	public:
		connection();
		~connection() noexcept;

		connection(connection&& conn) noexcept;

		bool connected() const;

		void connect();

		beast::http::response<beast::http::string_body> get(const http::target& target);

		void shutdown();

		tcp::socket& socket() noexcept;

		const tcp::socket& socket() const noexcept;

	private:
		system::error_code noexcept_shutdown() noexcept;

	private:
		std::shared_ptr<asio::io_context> io_;
		tcp::resolver resolver_;
		tcp::socket socket_;
	};

	struct connection::options
	{
	public:
		std::string_view hostname
			= connection::host;

		std::string_view user_agent
			= "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0";

		std::string_view connection
			= "keep-alive";

		std::string_view accept
			= "text/html,application/json,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8";

		std::string_view accept_language
			= "en-US,en;q=0.5";

		std::string_view accept_encoding
			= "identity";

	public:
		template <class Body>
		static void fill_request(beast::http::request<Body>&, const options& options);
	};

	inline connection::connection()
		: io_{std::make_shared<asio::io_context>()}
		, resolver_{*io_}
		, socket_{*io_}
	{}

	inline connection::~connection() noexcept
	{
		this->shutdown();
	}

	inline connection::connection(connection&& conn) noexcept
		: io_{std::move(conn.io_)}
		, resolver_{std::move(conn.resolver_)}
		, socket_{std::move(conn.socket_)}
	{}

	inline bool connection::connected() const
	{
		return socket_.is_open();
	}

	inline beast::http::response<beast::http::string_body>
		connection::get(const http::target& target)
	{
		auto request = beast::http::request<beast::http::empty_body>{};

		request.method(beast::http::verb::get);
		request.target(target.path());
		options::fill_request(request, options{});

		beast::http::write(socket_, request);

		beast::flat_buffer buffer;
		beast::http::response<beast::http::string_body> response;

		system::error_code ec;
		beast::http::read(socket_, buffer, response, ec);
		return response;
	}

	inline void connection::connect()
	{
		const auto results = resolver_.resolve(connection::host, std::to_string(80));
		const auto result = asio::connect(socket_, results.begin(), results.end());
	}

	inline void connection::shutdown()
	{
		if (!socket_.is_open())
			return;

		const auto ec = this->noexcept_shutdown();

		if (ec && ec != boost::system::errc::not_connected)
			throw boost::system::system_error{ec};
	}

	inline system::error_code connection::noexcept_shutdown() noexcept
	{
		system::error_code ec;
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

	template <class Body>
	void connection::options::fill_request(beast::http::request<Body>& request, const connection::options& options)
	{
		request.set(beast::http::field::host, options.hostname);
		request.set(beast::http::field::user_agent, options.user_agent);
		request.set(beast::http::field::connection, options.connection);
		request.set(beast::http::field::accept, options.accept);
		request.set(beast::http::field::accept_language, options.accept_language);
		request.set(beast::http::field::accept_encoding, options.accept_encoding);
	}

	http::connection connect()
	{
		http::connection conn;
		conn.connect();
		return conn;
	}
}

namespace warmane::armory
{
	using http::connect;
}
