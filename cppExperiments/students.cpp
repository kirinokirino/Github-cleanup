#include <iostream>
#include <vector>
#include <string>

using namespace std; 

enum class mark {
	two = 2,
	three,
	four,
	five
};

std::ostream& operator<<(std::ostream& os, mark c) {
    switch(c) {
        case mark::two   : os << "2";    break;
        case mark::three : os << "3";    break;
        case mark::four  : os << "4";    break;
        case mark::five  : os << "5";    break;
        default          : os.setstate(std::ios_base::failbit);
    }
    return os;
}

class Student {
	public:
		Student(string tempName){ name = tempName; };
		virtual ~Student(){};
		
		int countExams(){ return marks.size(); };
		vector<mark> getMarks(){ return marks; };
		void addMark(mark m){ marks.emplace_back(m); };
		void studentInfo(){ 
			cout << "Student " << name << " have these marks: ";
			for (auto m : marks){ cout << m << " "; }
			cout << endl; 
			};
		bool isFine(){ 
			for (auto m : marks){ if (m == mark::two || m == mark::three) return false; }
			return true;
			};
	private:
		string name;
		vector<mark> marks;
		
};

class Group {
	public:
		Group(string tempName){ groupName = tempName; };
		virtual ~Group(){};
		
		void addStudent(Student student){ students.emplace_back(student); };
		vector<Student> getStudents(){ return students; };
		int countStudents(){ return students.size(); };
		int countFine(){ 
			int counter = 0;
			for (auto s : students) if (s.isFine()) counter++;
			return counter;
			};
		double performance(){
			int everyone = countStudents();
			if (everyone == 0) return 100;
			else return ((double)countFine() / everyone) * 100;
		};
		void groupInfo(){
			cout << "Group " << groupName << ":" << endl;
			for (auto s : students) s.studentInfo();
			cout << endl; 
		}
	private:
		string groupName;
		vector<Student> students;
};

int main() {
	
	Student test1("Владимир");
	test1.addMark(mark::five);
	test1.addMark(mark::five);
	test1.addMark(mark::four);
	Student test2("Петр");
	test2.addMark(mark::three);
	test2.addMark(mark::two);
	test2.addMark(mark::four);
	
	Group MP21("Мп-21");
	MP21.addStudent(test1);
	MP21.addStudent(test2);
	
	cout << MP21.performance() << endl;
	cout << MP21.countFine() << endl;
	MP21.groupInfo();
	return 0;
}
