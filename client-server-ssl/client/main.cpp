#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;
using namespace boost::asio::ip;

int main()
{
    try
    {
        io_context context;
        tcp::resolver resolver(context);
        auto endpoints = resolver.resolve("127.0.0.1", "8080");
        tcp::socket socket(context);

        connect(socket, endpoints);

        ssl::context ssl_context(ssl::context::tlsv12_client);
        ssl_context.set_default_verify_paths();

        ssl::stream<tcp::socket> stream(context, ssl_context);
        auto ssl_endpoints = resolver.resolve("127.0.0.1", "8443");

        std::string request =
            "GET / HTTP/1.1\r\n"
            "Host: localhost\r\n"
            "Connection: close\r\n\r\n";
        socket.write_some(buffer(request));

        std::string response;
        char mybuffer[1024] = {0};
        int res             = 0;
        do
        {
            res = socket.read_some(buffer(mybuffer));
            response.append(mybuffer);
        } while (res >= 1023);

        std::cout << "Response received:\n"
                  << response << std::endl;

        connect(stream.lowest_layer(), endpoints);
        stream.handshake(ssl::stream_base::client);
        stream.write_some(buffer(request));

        response.clear();
        do
        {
            res = stream.read_some(buffer(mybuffer));
            response.append(mybuffer);
        } while (res >= 1023);

        std::cout << "SSL Response received:\n"
                  << response << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Client error: " << e.what() << std::endl;
    }

    return 0;
}
