#include "USCity.h"

// Constructs a USCity object and initializes all string data members to an empty string
USCity::USCity()
{
	mLatitude = "";
	mLongitude = "";
	mCityName = "";
	mStateID = "";
	mStateName = "";
	mZCTA = "";
	mParentZCTA = "";
	mPopulation = "";
	mPopulationDensity = "";
	mCountyFIPS = "";
	mCountyName = "";
	mCountyWeights = "";
	mCountyNamesAll = "";
	mCountyFIPSAll = "";
	mImprecise = "";
	mMilitary = "";
	mTimeZone = "";
}

// Constructs a USCity object and initializes all string data members to the corresponding input parameters
USCity::USCity(const string& newLatitude, const string& newLongitude, const string& newCityName, const string& newStateID, const string& newStateName, const string& newZCTA, const string& newParentZCTA, const string& newPopulation, const string& newPopulationDensity, const string& newCountyFIPS, const string& newCountyName, const string& newCountyWeights, const string& newCountyNamesAll, const string& newCountyFIPSAll, const string& newImprecise, const string& newMilitary, const string& newTimeZone)
{
	mLatitude = newLatitude;
	mLongitude = newLongitude;
	mCityName = newCityName;
	mStateID = newStateID;
	mStateName = newStateName;
	mZCTA = newZCTA;
	mParentZCTA = newParentZCTA;
	mPopulation = newPopulation;
	mPopulationDensity = newPopulationDensity;
	mCountyFIPS = newCountyFIPS;
	mCountyName = newCountyName;
	mCountyWeights = newCountyWeights;
	mCountyNamesAll = newCountyNamesAll;
	mCountyFIPSAll = newCountyFIPSAll;
	mImprecise = newImprecise;
	mMilitary = newMilitary;
	mTimeZone = newTimeZone;
}

// Constructs a USCity object, and initializes all string data members to copies of the string data members of another USCity
USCity::USCity(const USCity& original)
{
	if (this != &original) {
		mLatitude = original.getLatitude();
		mLongitude = original.getLongitude();
		mCityName = original.getCityName();
		mStateID = original.getStateID();
		mStateName = original.getStateName();
		mZCTA = original.getZCTA();
		mParentZCTA = original.getParentZCTA();
		mPopulation = original.getPopulation();
		mPopulationDensity = original.getPopulationDensity();
		mCountyFIPS = original.getCountyFIPS();
		mCountyName = original.getCountyName();
		mCountyWeights = original.getCountyWeights();
		mCountyNamesAll = original.getCountyNamesAll();
		mCountyFIPSAll = original.getCountyFIPSAll();
		mImprecise = original.getImprecise();
		mMilitary = original.getMilitary();
		mTimeZone = original.getTimeZone();
	}
}

// Empty destructor
USCity::~USCity()
{
	// nothing to do here
}

// Overloaded assignment operator for USCity which assigns a new USCity's data members to copies from another USCity object
USCity& USCity::operator=(const USCity& original)
{
	if (this != &original) {
		this->mLatitude = original.getLatitude();
		this->mLongitude = original.getLongitude();
		this->mCityName = original.getCityName();
		this->mStateID = original.getStateID();
		this->mStateName = original.getStateName();
		this->mZCTA = original.getZCTA();
		this->mParentZCTA = original.getParentZCTA();
		this->mPopulation = original.getPopulation();
		this->mPopulationDensity = original.getPopulationDensity();
		this->mCountyFIPS = original.getCountyFIPS();
		this->mCountyName = original.getCountyName();
		this->mCountyWeights = original.getCountyWeights();
		this->mCountyNamesAll = original.getCountyNamesAll();
		this->mCountyFIPSAll = original.getCountyFIPSAll();
		this->mImprecise = original.getImprecise();
		this->mMilitary = original.getMilitary();
		this->mTimeZone = original.getTimeZone();
	}
	return *this;
}

// Below are simple accessor and mutator functions which either return a copy of the data member being accessed or
// set the value of a data member to the value of a constant reference input parameter
string USCity::getLatitude() const
{
	return mLatitude;
}

string USCity::getLongitude() const
{
	return mLongitude;
}

string USCity::getCityName() const
{
	return mCityName;
}

string USCity::getStateID() const
{
	return mStateID;
}

string USCity::getStateName() const
{
	return mStateName;
}

string USCity::getZCTA() const
{
	return mZCTA;
}

string USCity::getParentZCTA() const
{
	return mParentZCTA;
}

string USCity::getPopulation() const
{
	return mPopulation;
}

string USCity::getPopulationDensity() const
{
	return mPopulationDensity;
}

string USCity::getCountyFIPS() const
{
	return mCountyFIPS;
}

string USCity::getCountyName() const
{
	return mCountyName;
}

string USCity::getCountyWeights() const
{
	return mCountyWeights;
}

string USCity::getCountyNamesAll() const
{
	return mCountyNamesAll;
}

string USCity::getCountyFIPSAll() const
{
	return mCountyFIPSAll;
}

string USCity::getImprecise() const
{
	return mImprecise;
}

string USCity::getMilitary() const
{
	return mMilitary;
}

string USCity::getTimeZone() const
{
	return mTimeZone;
}

void USCity::setLatitude(const string& newLatitude)
{
	mLatitude = newLatitude;
}

void USCity::setLongitude(const string& newLongitude)
{
	mLongitude = newLongitude;
}

void USCity::setCityName(const string& newCityName)
{
	mCityName = newCityName;
}

void USCity::setStateID(const string& newStateID)
{
	mStateID = newStateID;
}

void USCity::setStateName(const string& newStateName)
{
	mStateName = newStateName;
}

void USCity::setZCTA(const string& newZCTA)
{
	mZCTA = newZCTA;
}

void USCity::setParentZCTA(const string& newParentZCTA)
{
	mParentZCTA = newParentZCTA;
}

void USCity::setPopulation(const string& newPopulation)
{
	mPopulation = newPopulation;
}

void USCity::setPopulationDensity(const string& newPopulationDensity)
{
	mPopulationDensity = newPopulationDensity;
}

void USCity::setCountyFIPS(const string& newCountyFIPS)
{
	mCountyFIPS = newCountyFIPS;
}

void USCity::setCountyName(const string& newCountyName) 
{
	mCountyName = newCountyName;
}

void USCity::setCountyWeights(const string& newCountyWeights)
{
	mCountyWeights = newCountyWeights;
}

void USCity::setCountyNamesAll(const string& newCountyNamesAll)
{
	mCountyNamesAll = newCountyNamesAll;
}

void USCity::setCountyFIPSAll(const string& newCountyFIPSAll)
{
	mCountyFIPSAll = newCountyFIPSAll;
}

void USCity::setImprecise(const string& newImprecise)
{
	mImprecise = newImprecise;
}

void USCity::setMilitary(const string& newMilitary)
{
	mMilitary = newMilitary;
}

void USCity::setTimeZone(const string& newTimeZone)
{
	mTimeZone = newTimeZone;
}
