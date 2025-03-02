#ifndef USCITY_H
#define USCITY_H

#include <string>

using std::string;

class USCity
{
public:
	// Constructors
	USCity();
	USCity(const string& newLatitude, const string& newLongitude, const string& newCityName,
		const string& newStateID, const string& newStateName, const string& newZCTA,
		const string& newParentZCTA, const string& newPopulation, const string& newPopulationDensity,
		const string& newCountyFIPS, const string& newCountyName, const string& newCountyWeights,
		const string& newCountyNamesAll, const string& newCountyFIPSAll, const string& newImprecise,
		const string& newMilitary, const string& newTimeZone);

	// Copy Constructor
	USCity(const USCity& original);

	// Destructor
	~USCity();

	// Copy Assignment
	USCity& operator=(const USCity& original);

	// Accessors
	string getLatitude() const;
	string getLongitude() const;
	string getCityName() const;
	string getStateID() const;
	string getStateName() const;
	string getZCTA() const;
	string getParentZCTA() const;
	string getPopulation() const;
	string getPopulationDensity() const;
	string getCountyFIPS() const;
	string getCountyName() const;
	string getCountyWeights() const;
	string getCountyNamesAll() const;
	string getCountyFIPSAll() const;
	string getImprecise() const;
	string getMilitary() const;
	string getTimeZone() const;

	// Mutators
	void setLatitude(const string& newLatitude);
	void setLongitude(const string& newLongitude);
	void setCityName(const string& newCityName);
	void setStateID(const string& newStateID);
	void setStateName(const string& newStateName);
	void setZCTA(const string& newZCTA);
	void setParentZCTA(const string& newParentZCTA);
	void setPopulation(const string& newPopulation);
	void setPopulationDensity(const string& newPopulationDensity);
	void setCountyFIPS(const string& newCountyFIPS);
	void setCountyName(const string& newCountyName);
	void setCountyWeights(const string& newCountyWeights);
	void setCountyNamesAll(const string& newCountyNamesAll);
	void setCountyFIPSAll(const string& newCountyFIPSAll);
	void setImprecise(const string& newImprecise);
	void setMilitary(const string& newMilitary);
	void setTimeZone(const string& newTimeZone);

private:
	string mLatitude;
	string mLongitude;
	string mCityName;
	string mStateID;
	string mStateName;
	string mZCTA;
	string mParentZCTA;
	string mPopulation;
	string mPopulationDensity;
	string mCountyFIPS;
	string mCountyName;
	string mCountyWeights;
	string mCountyNamesAll;
	string mCountyFIPSAll;
	string mImprecise;
	string mMilitary;
	string mTimeZone;
};

#endif