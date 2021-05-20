#include<string>
#include <iostream>
#include<map>
#include<vector>
#include<algorithm>
#include <chrono>
#include <ctime>
#include<list>
#include<cmath>

using namespace std;

enum PaymentState {
	pending,
	cancelled,
	payed
};



class PaymentResult {
public:
	PaymentState PayState;
	float AmoutOfTransaction;
	int id;
};

class PaymentSystem {
private:
	list<PaymentResult> storage;
public:
	void setStorage(PaymentResult PR);
	list<PaymentResult>getStorage();
	PaymentResult GetById();
	PaymentResult HandlePayment();
};

void PaymentSystem::setStorage(PaymentResult PR) {
	storage.push_back(PR);
}




enum DeliveryState
{
	rejected,
	pendingOfPayment,
	peyed,
	pendingOfSending,
	onTheWay,
	pendingOfRecieving,
	recieved
};

enum PackingType {
	simplePack = 100,
	glassPack = 375
};

enum VehicleType {
	plane = 3000,
	ship = 2600,
	truck = 1000
};



class location {
public:
	int x;
	int y;
};

class city {
public:
	string name;
	location location;
};

class DeliveryRequest {
private:
	int id;
	city cityFrom;
	city cityTo;
	string senderName;
	string recieverName;
	VehicleType vehicle;
	string Svehicle;
	float price;
	string SpackingType;
	DeliveryState deliveryState;
	bool isPacked;
	PackingType packingType;
public:
	int getid();
	string getCityFrom();
	string getCityTo();
	string getSender();
	string getReciever();
	VehicleType getVeh();
	float getPrice();
	DeliveryState getDel();
	bool getPacked();
	PackingType getPT();
	DeliveryRequest(city From, city To, string sender, string recieve, VehicleType veh, float prive, DeliveryState delState,bool ispacked ,PackingType PT);
	static int global_id;
};
int DeliveryRequest::getid() {
	return id;
}
string DeliveryRequest::getCityFrom() {
	return cityFrom.name;
}
string DeliveryRequest::getCityTo() {
	return cityTo.name;
}
string DeliveryRequest::getSender() {
	return senderName;
}
string DeliveryRequest::getReciever() {
	return recieverName;
}
VehicleType DeliveryRequest::getVeh() {
	return vehicle;
}
float DeliveryRequest::getPrice() {
	return price;
}
DeliveryState DeliveryRequest::getDel() {
	return deliveryState;
}
bool DeliveryRequest::getPacked() {
	return isPacked;
}
PackingType DeliveryRequest::getPT() {
	return packingType;
}

DeliveryRequest::DeliveryRequest(city From, city To,string sender,string recieve, VehicleType veh, float price, DeliveryState delState,bool ispacked ,PackingType PT) {
	id = 1;
	this->cityFrom = From;
	this->cityTo = To;
	this->senderName = sender;
	this->recieverName = recieve;
	this->vehicle = veh;
	this->price = price;
	this->deliveryState = delState;
	this->isPacked = false;
	this->packingType = PT;
}

class DeliverySystem {
public:
	void Deliver();
	location sendLocation(city from, city to);
private:
	
};

void DeliverySystem::Deliver() {
	cout << "the parcel arrived " << endl;
}
ostream& operator<<(ostream& stream, const location& loc) {
	stream << "parallel: " << loc.x << endl;
	stream << "meridian: " << loc.y << endl;
	return stream;
}

ostream& operator<<(ostream& stream, const city& city) {
	stream << city.name << endl << city.location;
	return stream;
}
ostream& operator<<(ostream& stream, DeliveryRequest DR) {
	stream << "Your order number: " << DR.getid() << "\n" << "City From: " << DR.getCityFrom() << endl;
	stream << "City to: " << DR.getCityTo() << "\n" << "Sender name: " << DR.getSender() << endl;
	stream << "Reciever name: " << DR.getReciever() << "\n" << "Vehicle: " << DR.getVeh() << endl;
	stream << "Price: " << DR.getPrice() << "\n" << "Packing Type: " << DR.getPT() << endl;
	return stream;
}
bool operator==(const location	&loc1,const location &loc2) {
	return (loc1.x == loc2.x && loc1.y == loc2.y);
}
bool operator!=(const location& loc1, const location& loc2) {
	return !(loc1==loc2);
}
class TrackingSystem {
public:
	location track(DeliverySystem del,city from,city to);
};

location TrackingSystem::track(DeliverySystem del, city from, city to) {
	del.sendLocation(from, to);
	return from.location;
}
class reciever {
private:
	string name;
public:
	void setName(string name);
	string getName();
	void tracking(TrackingSystem TrSys, DeliverySystem delSys, city from, city to);
	bool recive(DeliveryState DS);
	void askToUnpack();
};

void reciever::askToUnpack() {
	cout << "Unpack my package, please" << endl;
}

bool reciever::recive(DeliveryState DS) {
	if (DS == DeliveryState::pendingOfRecieving)
		return false;
	else if (DS == DeliveryState::recieved)
		return true;
}

void reciever::tracking(TrackingSystem TrSys, DeliverySystem delSys, city from, city to)
{
	TrSys.track(delSys, from, to);
}

string reciever::getName() {
	return name;
}

void reciever::setName(string name) {
	this->name = name;
}
class sender {
private:
	string name;
	float amountOfMoney = 3550;
public:
	void Pay();
	void setName(string name);
	string getName();
	float getMoney();
	void Reject(float price);
	void tracking(TrackingSystem TrSys,DeliverySystem delSys,city from,city to);
};



void sender::Pay() {
	cout << "I paid for the order" << endl;
}

string sender::getName() {
	return name;
}

void sender::setName(string name) {
	this->name = name;
}

float sender::getMoney() {
	return amountOfMoney;
}

void sender::Reject(float price) {
	if (price > getMoney()) {
		cout << "I haven`t so much money" << endl;
	}
}

void sender::tracking(TrackingSystem TrSys,DeliverySystem delSys,city from,city to)
{
	TrSys.track(delSys,from,to);
}

int norm(int i) {
	if (i > 0)
		return -1;
	else if (i < 0) {
		return 1;
	}
	return 0;
}

location DeliverySystem::sendLocation(city from,city to) {

	while (from.location.x != to.location.x || from.location.y != to.location.y) {
		int dirx = 0;
		int diry = 0;
		dirx = norm(from.location.x - to.location.x);
		diry = norm(from.location.y - to.location.y);
		from.location.x += dirx;
		from.location.y += diry;
	}
	cout << from.location<<endl;
	return from.location;
}

city addCity(vector<city> cities, string name) {
	location loc;
	city City;
	loc.x = rand();
	loc.y = rand();
	City.name = name;
	City.location = loc;
	return City;
}

class LogisticSystem {
public:
	bool FindVehicle();
	void setCorrectWay(city from, city to);
};

void LogisticSystem::setCorrectWay(city from, city to) {
	cout << "The way between citis is: " << endl;
	cout << "by parallels: " << from.location.x << " - " << to.location.x << endl;
	cout << "by meridians: " << from.location.y << " - " << to.location.y << endl;
}

bool LogisticSystem::FindVehicle() {
	return true;
}
class PackingSystem {
public:
	void Pack(PackingType PT);
	void Unpack();
};

void PackingSystem::Unpack() {
	cout << "baggage is unpacked" << endl;
}

void PackingSystem::Pack(PackingType PT) {
	if (PT == PackingType::glassPack) {
		cout << "Your package packed in glass pack" << endl;
	}
	else if (PT == PackingType::simplePack) {
		cout << "Your package packed in simple pack" << endl;
	}
}

class PostOfficeOperator {
public:
	float calculatePrice(VehicleType vh, PackingType PT);
	bool isPayed(PaymentResult PR);
	void pack();
	void findVehicle(bool log);
	void send();
	bool isDelivered();
	void takePackage(DeliveryState DS);
	void unpack();
};

void PostOfficeOperator::unpack() {
	PackingSystem P;
	P.Unpack();
}

void PostOfficeOperator::takePackage(DeliveryState DS) {
	DS = DeliveryState::recieved;
}

bool PostOfficeOperator::isDelivered() {
	return true;
}

void PostOfficeOperator::send() {
	cout << "Your package is sent" << endl;
}

void PostOfficeOperator::findVehicle(bool log) {
	LogisticSystem LS;
	if (LS.FindVehicle() == true) {
		cout << "We find a vehicle" << endl;
	}
}


bool PostOfficeOperator::isPayed(PaymentResult PR) {
	if (PR.PayState == PaymentState::payed) {
		return true;
	}
	else if (PR.PayState == PaymentState::cancelled) {
		cout << "U can transport your baggage by the other type of vehicle" << endl;
		return false;
	}
}

void PostOfficeOperator::pack() {
	cout << "Your baggage is going packing" << endl;
}




float PostOfficeOperator::calculatePrice(VehicleType vh, PackingType PT){
	if (vh == VehicleType::plane && PT == PackingType::simplePack) {
		return vh + PT + ((vh + PT) / 10);
	}
	else if (vh == VehicleType::plane && PT == PackingType::glassPack) {
		return vh + PT + ((vh + PT) / 5);
	}
	else if (vh == VehicleType::ship && PT == PackingType::simplePack) {
		return vh + PT + ((vh + PT) / 10);
	}
	else if (vh == VehicleType::ship && PT == PackingType::glassPack) {
		return vh + PT + ((vh + PT) / 5);
	}
	else if (vh == VehicleType::truck && PT == PackingType::glassPack) {
		return vh + PT + ((vh + PT) / 5);
	}
	else if (vh == VehicleType::truck && PT == PackingType::simplePack) {
		return vh + PT + ((vh + PT) / 10);
	}
	else {
		cout << "Can`t calculate" << endl;
	}

}

int main()
{
	vector<city> cities;
	cities.push_back(addCity(cities, "Kyiv"));
	cities.push_back(addCity(cities, "Kharkiv"));
	cities.push_back(addCity(cities, "Odesa"));
	cities.push_back(addCity(cities, "Donetsk"));
	cities.push_back(addCity(cities, "Lviv"));
	cities.push_back(addCity(cities, "Uzhhorod"));
	cities.push_back(addCity(cities, "Mykolaiv"));
	/*for (int i = 0; i < cities.size(); i++) {
		cout << cities[i] << endl;
	}*/
	cout << "Hello! You are greeted by the carrier \"Happy Way\"."<<endl;
	cout << "Where Do you want to send the goods?"<<endl;
	city chosen;
	city from = cities[0];
		cout << "We can send the parcel to the cities: " << endl;
		for (int i = 0; i < cities.size(); i++) {
			cout << cities[i].name << endl;
		}
			cout << "Let's fill in all the necessary data to send" << endl;
			cout << "Which city are you planning to send to?" << endl;
			string nameOfcity;
			cin >> nameOfcity;
			for (int i = 0; i < cities.size(); ++i) {
					if (nameOfcity == cities[i].name) {
					cout << "OK" << endl;
					chosen.name = nameOfcity;
					chosen.location = cities[i].location;
					break;
					}
					else if (nameOfcity != cities[i].name && i == cities.size()-1) {
					cout << "We can`t sent in this city" << endl;
					exit(1);
					}
				
			}			
			cout << chosen;
			cout << "Enter your name"<<endl;
			string sendname;
			cin >> sendname;
			sender sender;
			sender.setName(sendname);
			cout << "Enter the recipient's name"<<endl;
			string reciename;
			cin >> reciename;
			reciever reciever;
			reciever.setName(reciename);
			cout << "Choose the type of transport for transportation, the time of transportation depends on it" << endl;
			cout << "Press 1 if you want a plane 2 - a ship, 3 - a car" << endl;
			int choice_veh;
			cin >> choice_veh;
			VehicleType veh;
			PackingType PT;
			string vehicleType;
			if (choice_veh == 1) {
					veh = VehicleType::plane;
					vehicleType = "plane";
				}
			else if (choice_veh == 2) {
					veh = VehicleType::ship;
					vehicleType = "ship";
				}
			else if (choice_veh == 3) {
					veh = VehicleType::truck;
					vehicleType = "truck";
				}
			else {
					cout << "You pressed the wrong button, please repeat again" << endl;
					return 1;
				}
			cout << "Indicate whether your cargo is fragile" << endl;
			cout << "1 - yes, 2 - no" << endl;
			int choice_pack;
			cin >> choice_pack;
			string packingType;
			if (choice_pack == 1) {
				PT = PackingType::glassPack;
			}
			else if (choice_pack == 2) {
				PT = PackingType::simplePack;
			}
			else {
				cout << "You pressed the wrong button, please repeat again" << endl;
				return 1;
			}
			DeliveryState del;
			PostOfficeOperator Oper;

			float price = Oper.calculatePrice(veh, PT);
			cout << "Okay, go to the operator, he will calculate the cost of shipping\n \n \n";
			cout << "\"going\"" << endl;
			cout << "\"Post Office Opertor say\"" << endl;
			cout << "Hi, your shipping will cost - "<< price <<endl;
			cout << "You can pay your goods through the terminal" << endl;
			PaymentState PS;
			PaymentResult payResult;
			PackingSystem packSys;
			LogisticSystem log;
			DeliverySystem delSys;
			TrackingSystem trackSys;
			PostOfficeOperator Oper2;
			if (price > sender.getMoney()) {
				sender.Reject(price);
				del = DeliveryState::rejected;
				PS = PaymentState::cancelled;
				payResult.PayState = PS;
				Oper.isPayed(payResult);
			}
			else {
				cout << "OK" << endl;
				del = DeliveryState::pendingOfPayment;
				PS = PaymentState::pending;
				payResult.PayState = PS;
				sender.Pay();
				payResult.PayState = PaymentState::payed;
				payResult.AmoutOfTransaction = price;
				Oper.isPayed(payResult);
				DeliveryRequest DR(from, chosen, sendname, reciename, veh, price, del, false, PT);
				payResult.id = DR.getid();
				cout << "\"Post Office Operator say\"" << endl;
				Oper.pack();
				packSys.Pack(PT);
				Oper.findVehicle(log.FindVehicle());
				log.setCorrectWay(from, chosen);
				del = DeliveryState::onTheWay;
			
				location New = delSys.sendLocation(from, chosen);
				cout << "\n \n \n";
				string unpack;
				cout << "1 day later" << endl;
				if ( chosen.location == New) {
					delSys.Deliver();
					Oper2.isDelivered();
					del = DeliveryState::pendingOfRecieving;
					cout << "Post office operator 2 said to reciever that his/her package delivered and reciever arrived" << endl;
					if (Oper2.isDelivered()) {
						Oper2.takePackage(del);
						reciever.recive(del);
						cin >> unpack;
						if (unpack == "unpack") {
							reciever.askToUnpack();
							Oper2.unpack();
							cout << "Have a nice day";
						}
						else {
							cout << "Have a nice day" << endl;
						}
					}
					else {
						cout << "Ehhhh, waiting...." << endl;
					}
				}
				else {
					cout << "Maybe later" << endl;
				}
				
				
				
			}
	
}

