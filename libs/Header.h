#pragma once

#include "primary_header.h"
#include "sock.h"
#include "keys.h"
#include "user.h"

#define CANDIDATE_CODE first
#define CANDIDATE_VOTES second


class Exeption {
private:
	string error;
public:
	Exeption(string err): error(err) {};
	string getErr() {return error;}
};
