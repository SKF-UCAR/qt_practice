#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using namespace boost::asio::ip;

void handle_request(tcp::socket& socket)
{
    try
    {
        char mybuffer[1024] = {0};
        socket.read_some(buffer(mybuffer));
        std::cout << "Request received:\n"
                  << mybuffer << std::endl;

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n\r\n"
            "Hello, World!";
        socket.write_some(buffer(response));
    }
    catch (std::exception& e)
    {
        std::cerr << "Error handling request: " << e.what() << std::endl;
    }
}

void handle_ssl_request(ssl::stream<tcp::socket>& stream)
{
    try
    {
        char mybuffer[1024] = {0};
        stream.read_some(buffer(mybuffer));
        std::cout << "Request received:\n"
                  << mybuffer << std::endl;

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n\r\n"
            "Hello, HTTPS!";
        stream.write_some(buffer(response));
    }
    catch (std::exception& e)
    {
        std::cerr << "Error handling request: " << e.what() << std::endl;
    }
}

void server_loop(io_context& context, tcp::acceptor& acceptor, std::atomic<bool>& running)
{
    while (running)
    {
        try
        {
            tcp::socket socket(context);
            acceptor.accept(socket);
            handle_request(socket);
        }
        catch (std::exception& e)
        {
            std::cerr << "Error in server loop: " << e.what() << std::endl;
        }
    }
}

void ssl_server_loop(io_context& context, ssl::context& ssl_context, tcp::acceptor& acceptor, std::atomic<bool>& running)
{
    while (running)
    {
        try
        {
            ssl::stream<tcp::socket> stream(context, ssl_context);
            acceptor.accept(stream.lowest_layer());
            stream.handshake(ssl::stream_base::server);
            handle_ssl_request(stream);
        }
        catch (std::exception& e)
        {
            std::cerr << "Error in ssl server loop: " << e.what() << std::endl;
        }
    }
}

int main()
{
    try
    {
        std::atomic<bool> running(true);
        io_context context;
        tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), 8080));
        std::thread serverThread(server_loop, std::ref(context), std::ref(acceptor), std::ref(running));
        std::cout << "HTTP Server is running on http://localhost:8080\n";

        ssl::context ssl_context(ssl::context::tlsv12_server);
        ssl_context.set_options(ssl::context::default_workarounds);
        ssl_context.use_certificate_chain_file("server.crt");
        ssl_context.use_private_key_file("server.key", ssl::context::pem);

        tcp::acceptor ssl_acceptor(context, tcp::endpoint(tcp::v4(), 8443));

        std::thread sslServerThread(ssl_server_loop, std::ref(context), std::ref(ssl_context), std::ref(acceptor), std::ref(running));
        std::cout << "HTTPS Server is running on https://localhost:8443\n";

        std::cin.get(); // Wait for user input to stop the server

        running = false;
        serverThread.join();
        sslServerThread.join();

        std::cout << "Server stopped.\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
