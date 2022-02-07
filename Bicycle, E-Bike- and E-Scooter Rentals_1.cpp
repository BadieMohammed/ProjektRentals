/**********************************************************************
Matr.-Nr:  3086452
Nachname/Surname: Mohammed
Vorname/Given name: Badie
Uni-Email:badie.mohammed@stud.uni-due.de
Studiengang/Course of studis: computer engineering ISE
**********************************************************************/
#include <iostream>
#include <string>
using namespace std;
class Dayofyear {
private:
	short unsigned int dayofyear;
	short unsigned int year;
	static const int days[13];
public:
	Dayofyear(int d = 1, int y = 365) : dayofyear(d), year(y) {};
	Dayofyear(int d, int m, int y) {
		dayofyear = days[m - 1] + d;
		year = y;
	};
	int get_dayOfYear() { return dayofyear; }
	Dayofyear operator++ () {
		if ( dayofyear == 365)
		{
			year++;
			dayofyear = 1;
		}
		else
		{
			dayofyear++;
		}
		return *this;
	}
	friend istream& operator>> (istream& , Dayofyear&);
	friend ostream& operator<< (ostream& , Dayofyear&);
};
const int Dayofyear::days[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365};
istream& operator>> (istream& input, Dayofyear& d) {
	int m, day;
	char c;
	input >> d.year >> c >> m >> c >> day;
	d.dayofyear = d.days[m - 1] + day;
	return input;
}

ostream& operator<< (ostream& out, Dayofyear& d) {

	char c = '-';
	out << d.year << c;
	for (int i = 0; i < 13 ; i++)
	{
		if (d.dayofyear <= d.days[i]) {
			out << i  << c << (d.dayofyear - d.days[i - 1]);
			return out;
		}
	}
}
class vehicle {
private:
	const int no;
	string model;
	float price24h;
public:
	vehicle(int n, string m, float p) : no(n), model(m), price24h(p) {};
	virtual ~vehicle() {};
	int get_no() { return no; }
	string get_model() { return model; }
	float get_price(int NumOfDays) {
		return NumOfDays * price24h;
	}
	virtual void print() = 0;
};

class Bike : public vehicle {
public:
	Bike(int n, string m) : vehicle(n, m, 9.99) {};
	virtual void print () {
		cout << get_no() << ": " << get_model() << " (Bike)";
	}
};
class EMotorVehicle : public vehicle {
public:
	EMotorVehicle(int n, string m, float p) : vehicle(n, m, p) {};
	virtual bool is_streetLegal() = 0;
	virtual void print() {
		if(is_streetLegal())
		cout << get_no() << ": " << get_model() ;
		else
		{

			cout << get_no() << ": " << get_model() << " (not street Legal)";
		}
	}
};

class Ebike : public EMotorVehicle {
public:
	Ebike(int n, string m, float p = 29.99) : EMotorVehicle(n, m, p) {};
	virtual bool is_streetLegal() { return true; }
	virtual void print() {
		EMotorVehicle::print();
		cout  << " (Ebike)";
	}
}; 
class Escooter : public EMotorVehicle {
private :
	bool streetLegal;
public :
	Escooter(int n, string m, float p = 19.99, bool sl = false) : EMotorVehicle(n, m, p) {
		streetLegal = sl;
	}
	virtual bool is_streetLegal() {
		return streetLegal;
	}
	virtual void print() {
		EMotorVehicle ::print();
		cout << " (Escooter)";
	}
};
class Rental {
private :
	const int no;  
	Dayofyear from;
	int days;
	string customer;
	static int last_no;
public:
	Rental(string c, Dayofyear d,  int n = 1 ) : customer(c), from(d), days(n) , no (last_no)
	{
		last_no++ ; 
	}
	int get_days() { return days; }
	Dayofyear get_from() { return from; }
	Dayofyear get_until() {
		Dayofyear until = from ;
		for (int i = 0; i <= days; i++) {
			++until;
		}
		return until;
	}
	void print() {
		Dayofyear until = get_until();
		cout << "to" << from << "from" << until << ", Rental no" << no << "for" << customer;
	}
};
int Rental::last_no = 1;
class Schedule {
private:
	vehicle* Vehicle ;
	Rental* year[365];
	Schedule* next ;
public:
	Schedule(vehicle* v) : Vehicle(v) , next(nullptr) {
		for (int i = 0; i < 365; i++) {
			year[i] = nullptr;
	}
	};
	vehicle* get_vehicle() { return Vehicle; }
	Schedule* get_next() { return next; }
	void set_next(Schedule* n) { next = n; }
	bool isFree(Dayofyear d, int nod) {
		bool isfree = true;
		for (int i = d.get_dayOfYear() - 1; i < (d.get_dayOfYear() + nod - 1); i++) {
			if (year[i] != nullptr)
			{
				isfree = false;
			}
		}

		return isfree;
	}
	float book(string person, Dayofyear date, int nod) {
		Rental* r = new Rental(person , date , nod);
		for (int i = date.get_dayOfYear()-1 ; i <date.get_dayOfYear()+nod-1 ; i++)
		{
			year[i] = r;
		}
		return Vehicle->get_price(nod);
	}

	void print(Dayofyear d) {
		Vehicle->print();
		int day = d.get_dayOfYear();
		if(year[day-1])
		year[day-1]->print();
	}
	void print() {
		Vehicle->print();
		for (int i = 0; i < 365; i++) {
			if (year[i]) {
				year[i]->print();
				i = i + year[i]->get_days()-1;
				cout << Vehicle->get_price(year[i]->get_days());
			}
		}

	}
}; 
class  Agency {
private:
	float profitpercent;
	float profit;
	Schedule* head, *last;
public:
	Agency() : profitpercent(0.2), profit(0.00), head(nullptr), last(nullptr) {};
	float get_profit() { return profit; }
	void set_profitpercentage(float pp)  {
		profitpercent = pp;
	}
	void add(vehicle* new_v) {
		Schedule* s = new Schedule(new_v);
		if (!last)
		{
			head = s;
			last= s;
		}
		else
		{
			last->set_next(s);
			last = s;
		}
	}
protected:
	Schedule* searchFor(int n) {
		vehicle *v ;
		Schedule* s = head;
		while (s)
		{ 
			v = s->get_vehicle();
			if (v->get_no()==n)
			{
				return s;
			}
			s = s->get_next();
		}

	}
public:
	bool isFree(int v_nom, Dayofyear date, int days) {
		Schedule* s = searchFor(v_nom);
		return s->isFree(date , days);
	}
    float book (int v_nom , string c , Dayofyear d ,int nod) {
		Schedule* s = searchFor(v_nom); 
		float price = s->book(c, d, nod);
		profit = profit + profitpercent*price;
		return price;
	}
	int chooseVehicle (){
		Schedule* s = head;
		vehicle* v;
		while (s)
		{
			v = s->get_vehicle();
			v->print();
			s = s->get_next();
		}
		cout << "choose vehicle no";
		int no;
		cin >> no;
		return no;
	
	}
	void print(Dayofyear d) {
		cout << "Schedule for " << d;
		Schedule* s = head;
		while(s)
		{
			s->print(d);
			s = s->get_next();
		}
	}
	void print() {
		Schedule* s = head;
		while(s)
		{
			cout << "Schedule for ";
			s->print();
			cout << endl;
			s = s->get_next();
		}
		cout << "profit: " << get_profit() << "  EUR" << endl ; 
	}

};

int enu = 1;
int main()
{
	char c;
	Agency ag;
	Dayofyear today(01,01,2021);
	Dayofyear tomorow = today;
	++tomorow;
	cout << "SIMPLIFIED SIMULATION OF A RENTAL AGENCY " << endl <<
		"======================================== " << endl;
	do
	{
		cout<< "________________________________________ " << endl << "MENUE " << endl;
		cout << "A end of simulation" << endl;
		cout << "B set new simulation date" << endl;
		cout << "C new rental manually " << endl;
		cout << "D print rental of today " << today << endl;
			cout <<"E print rental of tomorrow " << tomorow << endl ;
			cout << "F print all rentals " << endl;
			cout << "G print agency profit " << endl;
			cout << "H set agency profit percent " << endl;
			cout << "I add bikes " << endl;
			cout << "J add E - bikes " << endl;
			cout << "K add E - scooters" << endl;
			cout << " your choice : ";
			cin >> c;
			switch (toupper(c))
			{
			case 'B': {
				cout << "input date of today : ";
				Dayofyear t;
				cin >> t;
				today = t;
				tomorow = ++t;
			}
			case 'C': {

			}
			case 'D': {
				ag.print(today);
			}
			case 'E': {
				ag.print(tomorow);
			}
			case 'F': {
				ag.print();
				break;
			}
			case 'G': {
				cout << "agency profit: " << ag.get_profit() << " EUR";
			}
			case 'H': {
				float ppc;
				cout << "agency profit percent: ";
				cin >> ppc;
				ag.set_profitpercentage(ppc);
			}
			case 'I': {
				cout << "how many Bikes in this simulation?";
				int n; cin >> n;
				for (int i = 0; i < n; i++) {
					ag.add(new Bike(enu, "City"));
					enu++;
				}
				break;
			}
			case 'J': {
				cout << "how many EBikes in this simulation?";
				int n; cin >> n;
				for (int i = 0; i < n; i++) {
					ag.add(new Ebike(enu, "Trekky"));
					enu++;
				}
				break;
			}
			case 'K': {
				cout << "how many EScooters in this simulation?";
				int n; cin >> n;
				for (int i = 0; i < n; i++) {
					ag.add(new Escooter(enu, "Scooty"));
					enu++;
				}
				break;
			}
			default:
				break;
			}


	} while (c!='A' && c!='a');
	 

}
