#include<iostream>

/*
	What is a proxy server? A server which is very much/less clone of actual real server. When you 
	request something over the internet, it is first checked in proxy server near you. If found, it is served,
	else the real server is called. So the proxy server is like a middle man between client (your browser) and
	the server.
	A proxy is an agent object to access the real required objects. Sometimes the objects cloning is expensive.
	These proxies can have their own functions as well.

	A quite simple example here I am using to demonstrate the need of proxy pattern.
	We have a stream interface used by FileStream. This FileStream is not changeable by us. We cannot customise
	it, we don;t want anything to go wrong with it. Thus, we put a proxy ProxyFileStream in front of FileStream
	which uses the same interface as FileStream. The benefit of doing so it, we don't create actual FileStream
	object until required. (Of course, that is same as lazy initialisation) But there are other benefits. As I
	said we can't change FileStream. What if we want to add some more functions to it, or it is a third party
	library we want to modify a bit? That is where we use Proxy. Using that, we never invoke real functions 
	directly.

*/

class Stream
{
public:
	virtual void send() = 0;
};

// we cannot change this class (assume)
class FileStream : public Stream
{
public:
	void send() override 
	{
		std::cout << "Sending something over stream...\n";
	}
};	

// proxy class
class ProxyFileStream : public Stream
{
private:
	Stream *stream;
public:
	ProxyFileStream()
	{
		stream = new FileStream();
	}
	void send() override
	{
		stream->send();
	}
	~ProxyFileStream()
	{
		delete stream;
	}
};

int main()
{
	Stream *stream = new ProxyFileStream();
	stream->send();
	delete stream;
	return 0;
}