#include<iostream>

/*
	Well, what is an adapter? An electric adapter is a device you connect to plug device with socket of some type
	to socket of another type. And that's what Adapter pattern is xD
	Adapter pattern allows us to use interface of existing class to be used in another class. It is very handy to
	use incompatible interfaces and classes together.
	What we actually do in Adapter is we wrap the interface in Adapter class. Consider this awesome scenario I
	found on Wikipedia page. (It was so nice that I could not think of other example) We have iPhone and Android 
	device. We need to charge them using Lightning and MicroUSB respectively. (This is before Type-C era)
	But what if we have to charge iPhone using MircoUSB? We write an adapter class. This adapter class wraps 
	Lightning adapter inside MicroUSB. An actual implementaion will make a lot more sense.
	More practical use of adapter patterns is used in providing support of new functions to legacy classes.
*/

class ILightningPort
{
public:
	virtual ~ILightningPort() {} 
	virtual	void charge() = 0;
	virtual void use_lightning() = 0;
};

class IMicroUSBPort
{
public:
	virtual ~IMicroUSBPort() {} 
	virtual	void charge() = 0;
	virtual void use_micro_usb() = 0;
};

class IPhone : public ILightningPort
{
private:
	bool is_connected;
public:
	void use_lightning()
	{
		is_connected = true;
		std::cout << "Lightning connected.\n";
	}

	void charge()
	{
		if(is_connected)
			std::cout << "Charging using Lightning Port\n";
		is_connected = false;
	}
};


class Android : public IMicroUSBPort
{
private:
	bool is_connected;
public:
	void use_micro_usb()
	{
		is_connected = true;
		std::cout << "Micro USB connected.\n";
	}

	void charge()
	{
		if(is_connected)
			std::cout << "Charging using Micro USB port\n";
		is_connected = false;
	}
};

// adapter
class MicroUSBToLightningAdapter : public IMicroUSBPort
{
private:
	ILightningPort* lightning_port;
	bool is_connected;
public:

	MicroUSBToLightningAdapter(ILightningPort *phone)
	{
		lightning_port = phone;
	}

	void use_micro_usb()
	{
		is_connected = true;
		std::cout << "Micro USB connected.\n";
		lightning_port->use_lightning();
	}

	void charge()
	{
		if(is_connected)
			lightning_port->charge();
		is_connected = false;
	}	
};

int main()
{
	// creating android phone and charging using micro usb
	IMicroUSBPort* android_phone = new Android();
	android_phone->use_micro_usb();
	android_phone->charge();

	// creating iphone and charging using lightning 
	ILightningPort* i_phone = new IPhone();
	i_phone->use_lightning();
	i_phone->charge();

	// charging i_phone using adapter i.e micro usb to lightning converter
	MicroUSBToLightningAdapter *adapter = new MicroUSBToLightningAdapter(i_phone);
	adapter->use_micro_usb();
	adapter->charge();
	// This produces results that iPhone is charging using lightning port, but we have
	// actually connected the adapter and micro usb.
	delete android_phone, i_phone, Adapter;	
}