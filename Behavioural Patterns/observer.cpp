#include<iostream>

/*
	A lot of softwares are event driven. An event in one object might trigger other objects. Observer pattern
	is helpful in order to solve this requirement. In observer pattern, an object (called as subject xD) 
	maintains a list of objects (called as observers) which are dependent on subject. An event in subject
	can trigger the event. Then a method of observer is called thus observer gets notified about the
	event just occured in subject. It makes the most sense to use observers in threads running in background
	but we are not doing that here. 
	Observer pattern makes it easier to solve the one-to-many dependency making them loosely coupled. 

	IMPORTANT:
	Observer pattern is different that PubSub model and reactive programming.
	Reactive programming is out of the scope of this file but I am providing something very famous in this
	https://github.com/ReactiveX/RxCpp

	In observer pattern, subject is fully aware of the observers. It literally maintains the list of the
	observers. In PubSub, both subject and observer (subscribers) are independent. Both publishers and
	subscribers can be scaled on their own. Also, PubSub is more loosely coupled than observer. PubSub can
	be preferred easily over observer pattern if observer pattern makes your software components tightly
	coupled.
*/

int main()
{
	return 0;
}