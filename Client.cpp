#include "Client.hpp"

Client::Client() : numberMyChannel(0), checkPing(0), flagCheckPingPong(0) {}

Client::Client(int _socket_fd) : socket_fd(_socket_fd), id(++numberClient), passCheck(0), userCheck(0), nickCheck(0), nickname(""), Registed(0), offlineOnline(0)
{
	std::cout << "Client №" << id << " connected\n";
}
void Client::setRegisted() { ++this->Registed; }
void Client::setuserCheckPlus() { ++this->userCheck; }
void Client::setnickCheckPlus() { ++this->nickCheck; }
void Client::setpassCheckPlus() { ++this->passCheck; }
void Client::setuserCheckMinus() { --this->userCheck; }
void Client::setnickCheckMinus() { --this->nickCheck; }
void Client::setpassCheckMinus() { --this->passCheck; }
int Client::getRegisted() { return this->Registed; }
int Client::getnickCheck() { return (this->nickCheck); }
int Client::getpassCheck() { return (this->passCheck); }
int Client::getuserCheck() { return (this->userCheck); }
std::string Client::getNickName() { return (this->nickname); }
void Client::setzvezda(std::string str) { this->zvezda = str; }
void Client::setRealname(std::string str) { this->Realname = str; }
void Client::setUserName(std::string str) { this->UserName = str; }
std::string Client::getUserName() { return (this->UserName); }
void Client::setHostName(std::string str) { this->HostName = str; }
void Client::setNickName(std::string nick) { this->nickname = nick; }
void Client::setOfflineOnlinePlus() { ++this->offlineOnline; }
int Client::getOffineOnline() { return (this->offlineOnline); }
void Client::setOfflineOnlineMinus() { --this->offlineOnline; }
int Client::getId() { return (this->id); }
void Client::setIP(std::string _ip) { this->ip = _ip; }
std::string Client::getIP() { return this->ip; }
int Client::getCheckPing() { return (this->checkPing); }
void Client::setCheckPing() { this->checkPing++; }
void Client::nullCheckPing() { this->checkPing = 0; }

void Client::setRealNamePlus(std::string str)
{
	this->Realname += ' ';
	this->Realname += str;
}
void Client::setMyChannel(std::string nameChannel)
{
	this->myChannels[numberMyChannel] = nameChannel;
	numberMyChannel++;
}

void Client::plusFlagCheckPingPong() { this->flagCheckPingPong = 1; }
void Client::minusFlagCheckPingPong() { this->flagCheckPingPong = 0; }
int Client::getflagCheckPingPong() { return (this->flagCheckPingPong); }
int Client::getSocket() { return (this->socket_fd); }
Client::~Client() {}
