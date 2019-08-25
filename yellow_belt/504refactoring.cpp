#include <iostream>
#include <string>
#include <vector>

class Person {
public:
	Person(const std::string& name, const std::string& type) :
		name_(name), type_(type) {}

	std::string GetName() const {
		return name_;
	}
	std::string GetType() const {
		return type_;
	}

	virtual void Walk(const std::string& destination) const = 0;

private:
	const std::string name_;
	const std::string type_;
};


class Student : public Person {
public:
	Student(const std::string& name, const std::string& favourite_song) :
		Person(name, "Student"), favourite_song_(favourite_song) {}

	void Learn() const {
		std::cout << "Student: " << GetName() << " learns" << std::endl;
	}
	void Walk(const std::string& destination) const override {
		std::cout << "Student: " << GetName() << " walks to: " << destination << std::endl;
		std::cout << "Student: " << GetName() << " sings a song: " << favourite_song_ << std::endl;
	}
	void SingSong() const {
		std::cout << "Student: " << GetName() << " sings a song: " << favourite_song_ << std::endl;
	}

public:
	const std::string favourite_song_;
};


class Teacher : public Person {
public:
	Teacher(const std::string& name, const std::string& subj) :
		Person(name, "Teacher"), subj_(subj) {}

	void Teach() const {
		std::cout << "Teacher: " << GetName() << " teaches: " << subj_ << std::endl;
	}
	void Walk(const std::string& destination) const override {
		std::cout << "Teacher: " << GetName() << " walks to: " << destination << std::endl;
	}

public:
	const std::string subj_;
};


class Policeman : public Person {
public:
	Policeman(const std::string& name) : Person(name, "Policeman") {}

	void Check(Person& p) const {
		std::cout << "Policeman: " << GetName() << " checks " << p.GetType() << ". " << p.GetType()
			<< "'s name is: " << p.GetName() << std::endl;
	}
	void Walk(const std::string& destination) const override {
		std::cout << "Policeman: " << GetName() << " walks to: " << destination << std::endl;
	}
};


void VisitPlaces(const Person& p, std::vector<std::string> places) {
	for (auto place : places) {
		p.Walk(place);
	}
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}