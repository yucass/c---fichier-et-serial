#pragma once
#include <string>
#include <iostream>
#include <D:/boost/boost/archive/text_oarchive.hpp>
#include <D:/boost/boost/archive/text_iarchive.hpp>


using namespace std;


class individu
{

private:



	string socialNumber;
	string name;
	string firstName;
	int birthDay;
	int birthMounth;
	int birthYear;
	string job;


	// Allow serialization to access non-public data
	friend class boost::serialization::access;

	// Serialize the data members of BoostObject
	template <typename Archive>
	void serialize(Archive& ia, const unsigned version)
	{
		ia& socialNumber;
		ia& name;
		ia& firstName;
		ia& birthDay;
		ia& birthMounth;
		ia& birthYear;
		ia& job;
	}

public:


	individu(string a_socialNumber ="", string a_name = "", string a_firstName = "", int a_birthDay = 0, int a_birthMounth = 0, int a_birthYear = 0, string a_job = "" );
	~individu();

	void setSocialNumber(const string a_socialNumber) { socialNumber = a_socialNumber; };
	void setName(const string a_name) { name = a_name; };
	void setFirstName(const string a_firstName) { firstName = a_firstName; };
	void setBirthday(const int a_birthDay) { birthDay = a_birthDay; };
	void setBirthMounth(const int a_birthMounth) { birthMounth = a_birthMounth; };
	void setBirthYear(const int a_birthYear) { birthYear = a_birthYear; };
	void setJob(const string a_job) { job = a_job; };


	string getSocialNumber()const { return socialNumber; };
	string getName() const { return name; };
	string getFirstName() const { return firstName; };
	int getBirthday() const { return birthDay; };
	int getBirthMounth() const { return birthMounth; };
	int getBirthYear() const { return birthYear; };
	string getJob() const { return job; };


};

