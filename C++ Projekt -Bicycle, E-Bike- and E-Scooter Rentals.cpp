/*********************************************************************
STORE THIS FILE WITH YOUR MATRICULATION NUMBER AS NAME AND ENDING .cpp
Nachname/Surname                   : Mohammed
Vorname/Given Name                 : Badie
Matrikelnummer/Matriculation number: 3086452
Uni-Email                          : badie.mohammed@stud.uni-due.de
Studiengang/Course of Studies      : Computer Engineering ISE
*********************************************************************/

#include <iostream>
#include <string>
using namespace std;
///// TASK 1.1 ///////////////////////////////////////
enum Vaccine
{
	astra, biontech, moderna, none
};

///// TASK 1.2 ///////////////////////////////////////
ostream& operator<< (ostream& output,Vaccine& v)
{
	if (v == astra)
	{
		output << "AstraZeneca";
	}
	if (v == biontech)
	{
		output << "BioNTech";
	}
	if (v == moderna)
	{
		output << "Moderna";
	}
	if (v == none)
	{
		output << "None";
	}

}
///// TASK 1.3 ///////////////////////////////////////
class SimError : public exception
{
public:
	string reason;
	SimError(string r) : reason(r){}
};
///// TASK 1.4 ///////////////////////////////////////
class Patient
{
private:
	int no;
	const int id;
	bool briefed;
	Vaccine vaccine;
public:
	Patient(int, bool, Vaccine);
	int get_id();
	bool is_briefed();
	void switch_briefed();
	void set_vaccinated(Vaccine);
	friend ostream& operator<< (ostream&, Patient&);
};
Patient::Patient(int n, bool b = false, Vaccine ) {
	no = n;
	briefed = b;
	vaccine = none;
	id++;
}
int Patient:: get_id() { return id; }
bool Patient::is_briefed() { return true; }
void Patient::switch_briefed() {
	if (briefed)
	{
		briefed = false;
	}
	else
	{
		briefed = true;
	}
}
void Patient::set_vaccinated(Vaccine v) {
	vaccine = v;
}
ostream& operator << (ostream& out, Patient& p) {
	out << "Patient" << p.get_id();
	if (p.is_briefed())
	{
		out << p.vaccine;
	}
	else
	{
		out << "briefed";
	}

}


///// TASK 2.0 ///////////////////////////////////////
class Station
{
protected: string station;
		 Patient* patient;
public:
	Station(string c, Patient* p) : station(c), patient(p){}
    virtual  ~Station(){}
	virtual void enter(Patient*) = 0;
	virtual Patient* leave(Patient*) = 0;
	virtual void print() = 0;


};
///// TASK 3.0 ///////////////////////////////////////
class WaitingArea : public Station {
private :
	class Waiting {
	public:
		Patient* patient;
		Waiting* next;
		Waiting(Patient* p = nullptr, Waiting* n = nullptr) {
			patient = p;
			next = n;
		}
		int count;
		Waiting* waiting;
	};
public:
	WaitingArea(string c, int co, Waiting* w = nullptr) {
		station = c;
		co = 0;
		Waiting = w;

	}
	virtual enter


};
///// TASK 4.0 ///////////////////////////////////////
class Single public : Station
{
private :
	int total;
public :

	Single(string c, int t=0) {
		station = c;
		total = t;
	}
	int get_total() { return total;  }
	virtual void enter(Patient* p) {

	}
	virtual Patient* leave(Patient*) {

	}


};
///// TASK 5.0 ///////////////////////////////////////
class Administrative : public Single
{
	Administrative(string c ) : station (c)
		virtual void print () {}
};
///// TASK 6.0 ///////////////////////////////////////
class Medical public : Single
{
private :
	string doctor;
	Medical (string s ,string d) : station (s) , doctor (d)
		virtual void enter (Patient* p) {}
};
///// TASK 7.0 ///////////////////////////////////////
class Center
{

private :
	Station* station[4];


};
///// TASK 8.0 ///////////////////////////////////////
int main(void)
{

	/*
	SIMULATION VACCINATION CENTER
	(a) end
	(b) new arrival at center
	(c) next vaccination
	(d) next debriefing
	*/

	return 0;
}
