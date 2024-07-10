#pragma once
#include "client_interface.hpp"
#include <thread>
#include <mutex>

class Client : IClient
{
public:
    Client(std::string endpoint, std::string identity);
    ~Client();
    void RequestToCreateChat(std::string& clients, std::string& chatId) override;
    void SendMessageToChat(const std::string& messageStr, const std::string& actionStr = "send_message") override;
    bool HasRequestToChat() const;
    void Reply(const std::string& reply);
    size_t GetChatId() const;

private:
    void _receiveMessage();
    zmq::context_t _context;
    zmq::socket_t _socket;
    std::string _identity;
    std::thread _receiver;
    size_t _chatId;
    bool _isInChat;
    bool _hasRequestToChat;
    std::mutex _mutex;
};
