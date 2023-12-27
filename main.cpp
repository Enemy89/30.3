#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>

int main() {
    std::map<std::string, std::string> arguments_map;
    std::vector<cpr::Pair> arguments_pair;

    std::string key, value;
    std::cout << "Enter the name of the argument ('post' or 'get' to send the request): ";
    while (std::cin >> key && key != "post" && key != "get") {
        std::cout << "Enter a value for the argument '" << key << "': ";
        std::cin >> value;

        arguments_map[key] = value;
        arguments_pair.emplace_back(cpr::Pair(key, value));

        std::cout << "Enter the name of the argument ('post' or 'get' to send the request): ";
    }

    if (key == "post") {
        cpr::Payload payload(arguments_pair.begin(), arguments_pair.end());
        cpr::Response r = cpr::Post(cpr::Url("http://httpbin.org/post"), payload);
        std::cout << "The server's response to the POST request:\n" << r.text << std::endl;
    } else if (key == "get") {
        std::string url = "https://httpbin.org/get?";
        for (std::map<std::string, std::string>::iterator it = arguments_map.begin(); it != arguments_map.end(); ++it) {
            url += it->first + "=" + it->second + "&";
        }
        url.pop_back();

        cpr::Response r = cpr::Get(cpr::Url(url));
        std::cout << "The server's response to the GET request:\n" << r.text << std::endl;
    }
}
