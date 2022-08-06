#include <iostream>
#include <conio.h>

class Vehicle {
public:
	Vehicle() {}
	Vehicle(int speed, int wheels, int humanCapacity){
		_speed = speed;
		_wheels = wheels;
		_humanCapacity = humanCapacity;
		_distance = _speed / 2;
	}
	void move() {
		std::cout << "Press key on keyboard that vehicle will move\n";
		char key = _getch();
		std::cout << "\n\"Vehicle has moving " << getDistance() << " km\"\n";
		upDistance();
	}
	void setSpeed(int speed) {
		_speed = speed;
	}
	int getSpeed() {
		return _speed;
	}
	void setWheels(int wheels) {
		_wheels = wheels;
	}
	int getWheels() {
		return _wheels;
	}
	void setHumanCapacity(int humanCapacity) {
		_humanCapacity = humanCapacity;
	}
	int getHumanCapacity() {
		return _humanCapacity;
	}
	void upDistance() {
		_distance += 20;
	}
	int getDistance() {
		return _distance;
	}
private:
	int _speed = 0;
	int _wheels = 0;
	int _humanCapacity = 0;
	static int _distance;
};

int Vehicle::_distance = 0;

class Motorized : virtual public Vehicle {
public:
	Motorized(){}
	Motorized(int speed, int wheels, int humanCapacity, int fuel, int fuelConsumption): Vehicle(speed, wheels, humanCapacity) {
		_fuel = fuel;
		_fuelCapacity = _fuel;
		_fuelConsumption = fuelConsumption;
	}
	void move() {
		if (_fuel == 0)
			std::cout << "\"Fuel tank is empty\"\n";
		else {
			std::cout << "Press key on keyboard that vehicle will move\n";
			char key = _getch();
			std::cout << "\n\"Vehicle has moving " << getDistance() << " km\"\n";
			upDistance();
			consumeFuel(getFuelConsumption());
		}
	}
	void setFuel(int fuel) {
		fuel = _fuel;
	}
	int getFuel() {
		return _fuel;
	}
	void setFuelCapacity(int fuelCapacity) {
		fuelCapacity = _fuelCapacity;
	}
	int getFuelCapacity() {
		return _fuelCapacity;
	}
	void consumeFuel(int fuelConsumption) {
		_fuel -= fuelConsumption;
	}
	void setFuelConsumption(int fuelConsumption) {
		_fuelConsumption = fuelConsumption;
	}
	int getFuelConsumption() {
		return _fuelConsumption;
	}
	void reFuel(int value) {
		if (_fuel + value > _fuelCapacity)
			std::cout << "\"Error. You overflow fuel tank\"\n";
		else
			if (_fuel == _fuelCapacity)
				std::cout << "\"Fuel tank is full\"\n";
			else {
				_fuel += value;
				std::cout << "\"Fuel Tank has reFueled\"";
			}
	}
private:
	int _fuel = 0;
	int _fuelCapacity = 0;
	int _fuelConsumption = 0;
};

class ICE : virtual public Motorized {
public:
	ICE(){}
	ICE(int speed, int wheels, int humanCapacity, int fuel, int fuelConsumption) : 
	Motorized(speed, wheels, humanCapacity, fuel, fuelConsumption), Vehicle(speed, wheels, humanCapacity) {}
	void move() {
		if (getFuel() == 0)
			std::cout << "\"Fuel tank is empty\"\n";
		else
			if (_oil == false)
				std::cout << "\"You need change oil\"\n";
			else {
				std::cout << "Press key on keyboard that vehicle will move\n";
				char key = _getch();
				std::cout << "\n\"Vehicle has moving " << getDistance() << " km\"\n";
				upDistance();
				consumeFuel(getFuelConsumption());
				oilWear();
			}
	}
	void oilWear() {
		_oilCount--;
		if (_oilCount == 0)
			_oil = false;
	}
	void changeOil() {
		if (_oil == true)
			std::cout << "\"Oil change early\"\n";
		else {
			_oil = true;
			_oilCount = 5;
			std::cout << "Oil has changed";
		}
	}
private:
	bool _oil = true;
	int _oilCount = 5;
};

class Electric : virtual public Motorized {
public:
	Electric(){}
	Electric(int speed, int wheels, int humanCapacity, int electricCharge, int energyConsumption): 
	Motorized(speed, wheels, humanCapacity, electricCharge, energyConsumption),Vehicle(speed, wheels, humanCapacity) {}
	void move() {
		if (getFuel() == 0)
			std::cout << "\"Battery is empty\"\n";
		else {
			std::cout << "Press key on keyboard that vehicle will move\n";
			char key = _getch();
			std::cout << "\n\"Vehicle has moving " << getDistance() << " km\"\n";
			upDistance();
			consumeFuel(getFuelConsumption());
		}
	}
	
	void reCharge(int value) {
		if (getFuel() + value > getFuelCapacity())
			std::cout << "\"Error. You overflow battery\"\n";
		else
			if (getFuel() == getFuelCapacity())
				std::cout << "\"Battery is full\"\n";
			else {
				int newElectricCharge = getFuel();
				setFuel(newElectricCharge += value);
				std::cout << "\"Battery has reCharged\"\n";
			}
	}
};

class Muscular : virtual public Vehicle {
public:
	Muscular(){}
	Muscular(int speed, int wheels, int humanCapacity): Vehicle(speed, wheels, humanCapacity){}
	
};

class KickScooter : virtual public Muscular {
public:
	KickScooter(){}
	KickScooter(int speed, int wheels, int humanCapacity): Muscular(speed, wheels, humanCapacity), Vehicle(speed, wheels, humanCapacity) {}
	
};

class Bike : virtual public Muscular {
public:
	Bike(){}
	Bike(int speed, int wheels, int humanCapacity) : Muscular(speed, wheels, humanCapacity), Vehicle(speed, wheels, humanCapacity) {}

};

class ElectroBike : public Electric, public Bike {
public:
	ElectroBike(){}
	ElectroBike(int speed, int wheels, int humanCapacity, int electricCharge, int energyConsumption) :
	Electric(speed, wheels, humanCapacity, electricCharge, energyConsumption), 
	Motorized(speed, wheels, humanCapacity, electricCharge, energyConsumption),
	Vehicle(speed, wheels, humanCapacity),Muscular(speed, wheels, humanCapacity),
	Bike(speed, wheels, humanCapacity) {}
	void move() {
		if (getFuel() == 0 && batteryIsFull == true) {
			batteryIsFull = false;
			lowSpeed();
			std::cout << "\"Battery is empty, but you still can drive(speed lowered half)\"\n";
			std::cout << "Press key on keyboard that vehicle will move\n";
			char key = _getch();
			std::cout << "\n\"Vehicle has moving " << getDistance() << " km\"\n";
			upDistance();
		}
		else
			if (getFuel() == 0 && batteryIsFull == false) {
				std::cout << "\"Battery is empty, but you still can drive\"\n";
				std::cout << "Press key on keyboard that vehicle will move\n";
				char key = _getch();
				std::cout << "\n\"Vehicle has moving " << getDistance() << " km\"\n";
				upDistance();
			}
			else {
				batteryIsFull = true;
				std::cout << "Press key on keyboard that vehicle will move\n";
				char key = _getch();
				std::cout << "\n\"Vehicle has moving " << getDistance() << " km\"\n";
				upDistance();
				consumeFuel(getFuelConsumption());
			}
	}
	void lowSpeed() {
		int speed2 = getSpeed();
		speed2 /= 2;
	}
	void upSpeed() {
		int speed2 = getSpeed();
		speed2 *= 2;
	}
private:
	bool batteryIsFull = true;
};


int main() {
	using namespace std;
	setlocale(LC_ALL, "Russian");
	
	int speed = 0, wheels = 0, humanCapacity = 0, fuel = 0, batteryCapacity = 0, fuelConsumption = 0, energyConsumption = 0;
	cout << "Choose the type of Vehicle: \n";
	cout << "1 - Motorized\t2 - Muscular\t3 - ElectroBike ";
	char choose = 0;
	int value = 0;
	cin >> choose;
	switch (choose) {
	case '1':
		cout << "\n1 - ICE\t2 - Electric ";
		cin >> choose;
		switch (choose) {
		case '1': {
			cout << "Choose the type of ICE:\n";
			cout << "1 - Car\t2 - MotorBike ";
			cin >> choose;
			if (choose == '1') {
				wheels = 4;
				humanCapacity = 5;
			}
			if (choose == '2') {
				wheels = 2;
				humanCapacity = 2;
			}
			cout << "\nEnter speed( km/h ): ";
			cin >> value;
			speed = value;
			cout << "\nEnter fuel capacity( Liters ): ";
			cin >> value;
			fuel = value;
			cout << "\nEnter fuel consumption for 1 move: ";
			cin >> value;
			fuelConsumption = value;
			ICE ice(speed, wheels, humanCapacity, fuel, fuelConsumption);
		Mark1:
			cout << "\nChoose the option:\n";
			cout << "1 - move\t2 - reFuel\t3 - change oil\t4 - check Fuel\t5 - End program\n\n";
			cin >> choose;
			switch (choose) {
				case '1': {
					ice.move();
					goto Mark1;
					break;
				}
				case '2': {
					cout << "\nEnter the fuel: ";
					cin >> value;
					ice.reFuel(value);
					goto Mark1;
					break;
				}
				case '3': {
					ice.changeOil();
					goto Mark1;
					break;
				}
				case '4': {
					std::cout << "\"" << ice.getFuel() << " / " << ice.getFuelCapacity() << " fuel\"\n";
					goto Mark1;
				}
				case '5': {
					goto EndMark;
				}
			}
			break;
		}
		case '2': {
			cout << "\nEnter speed( km/h ): ";
			cin >> value;
			speed = value;
			cout << "\nEnter battery capacity( Kilowatt-hour ): ";
			cin >> value;
			batteryCapacity = value;
			cout << "\nEnter energy consumption on 1 move: ";
			cin >> value;
			energyConsumption = value;
			Electric electric(speed, 4, 5, batteryCapacity, energyConsumption);
		Mark2:
			cout << "\nChoose the option:\n";
			cout << "1 - move\t2 - reCharge\t3 - check Energy\t4 - End program\n\n";
			cin >> choose;
			switch (choose) {
				case '1': {
					electric.move();
					goto Mark2;
					break;
				}
				case '2': {
					cout << "\nEnter the energy: ";
					cin >> value;
					electric.reCharge(value);
					goto Mark2;
					break;
				}
				case '3': {
					std::cout << "\"" << electric.getFuel() << " / " << electric.getFuelCapacity() << " energy\"\n";
					goto Mark2;
				}
				case '4': {
					goto EndMark;
				}
			}
			break;
		}
		}break;
	case '2':
		cout << "\n1 - KickScooter\t2 - Bike";
		cin >> choose;
		switch (choose) {
			case '1': {
				cout << "\nEnter speed( km/h ): ";
				cin >> value;
				speed = value;
				KickScooter kickScooter(speed, 2, 1);
			Mark3:
				cout << "\nChoose the option:\n";
				cout << "1 - move\t2 - End program\n\n";
				cin >> choose;
				switch (choose) {
					case '1': {
						kickScooter.move();
						goto Mark3;
					}
					case '2': {
						goto EndMark;
					}
				}
				break;
			}
			case '2': {
				cout << "\nEnter speed( km/h ): ";
				cin >> value;
				speed = value;
				Bike bike(speed, 2, 1);
			Mark4:
				cout << "\nChoose the option:\n";
				cout << "1 - move\t2 - End program\n\n";
				cin >> choose;
				switch (choose) {
					case '1': {
						bike.move();
						goto Mark4;
					}
					case '2': {
						goto EndMark;
					}
				}
				break;
			}
		}break;
	case '3':
		cout << "\nEnter speed( km/h ): ";
		cin >> value;
		speed = value;
		cout << "\nEnter battery capacity( Kilowatt-hour ): ";
		cin >> value;
		batteryCapacity = value;
		cout << "\nEnter energy consumption on 1 move: ";
		cin >> value;
		energyConsumption = value;
		ElectroBike electroBike(speed, 2, 1, batteryCapacity, energyConsumption);
	Mark5:
		cout << "\nChoose the option:\n";
		cout << "1 - move\t2 - reCharge\t3 - check energy\t4 - End program\n\n";
		cin >> choose;
		switch (choose) {
			case '1': {
				electroBike.move();
				goto Mark5;
				break;
			}
			case '2': {
				cout << "\nEnter the energy: ";
				cin >> value;
				electroBike.reCharge(value);
				goto Mark5;
				break;
			}
			case '3': {
				std::cout << "\"" << electroBike.getFuel() << " / " << electroBike.getFuelCapacity() << " energy\"\n";
				goto Mark5;
			}
			case '4': {
				goto EndMark;
			}
			break;
		}
	}
	
	EndMark:
	return 0;
}