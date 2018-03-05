#include "stdafx.h"
#include "individu.h"
#include <string>
#include <iostream>

using namespace std;

individu::individu(string a_socialNumber, string a_name, string a_firstName, int a_birthDay, int a_birthMounth, int a_birthYear, string a_job) 
		: socialNumber(a_socialNumber), name(a_name), firstName(a_firstName), birthDay(a_birthDay), birthMounth(a_birthMounth), birthYear(a_birthYear), job(a_job)
{
}


individu::~individu()
{
}
