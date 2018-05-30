#include <iostream>

using namespace std;

class Patient{
	public:
		Patient();
		Patient(string n,int p,int t);
		string name;
		int priority;
		int treatment;
};

Patient::Patient() {

}

Patient::Patient(string n,int p,int t) {
	name = n;
	priority = p;
	treatment = t;
}

template <class Patient> struct compare {
  bool operator() (Patient one, Patient two) {
  	return (one->priority == two->priority)?one->treatment > two->treatment:one->priority <= two->priority;
  }
  typedef Patient* first_argument_type;
  typedef Patient* second_argument_type;
  typedef bool result_type;
};