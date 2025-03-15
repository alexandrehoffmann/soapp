#ifndef SOAPP_DEMO_GENDER
#define SOAPP_DEMO_GENDER

#include <ostream>

enum class Gender
{
	MALE,
	FEMALE,
	NON_BINARY,
	GENDERQUEER,
	GENDERFLUID
};

std::ostream& operator<<(std::ostream& out, const Gender gender)
{
	switch (gender)
	{
	case Gender::MALE:
		out << "Male";
		break;
	case Gender::FEMALE:
		out << "Female";
		break;
	case Gender::NON_BINARY:
		out << "Non binary";
		break;
	case Gender::GENDERQUEER:
		out << "Genderqueer";
		break;
	case Gender::GENDERFLUID:
		out << "Genderfluid";
		break;
	default:
		out << "Unknown";
		break;
	}
	return out;
}

#endif // SOAPP_DEMO_GENDER
