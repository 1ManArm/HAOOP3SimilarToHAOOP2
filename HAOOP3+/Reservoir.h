#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>
#include <fstream>

class Reservoir
{
	std::string reservoir_name;
	std::string reservoir_type;
	float width;
	float height;
	float max_depth;
	const static std::string filename_for_save;
public:

	bool SetName(std::string name);
	std::string GetName() const;

	bool SetType(std::string name);
	void SetType();
	std::string GetType() const;
	int GetTypeIndex() const;



	bool SetWidth(float param);
	float Width() const;

	bool SetHeight(float param);
	float Getheight() const;

	bool SetMaxDepth(float param);
	float GetMaxDepth() const;

	void ShowAllParams() const;

	static std::string GetFileName();
	void Save(std::ofstream& of);
	void Load(std::ifstream& load);

	float ReservoirVolume() const;
	float RevervoirSquare() const;
	bool GetType(std::string name) const;

	int CheckSquareReservoirOneType(Reservoir& src) const;

	explicit Reservoir(std::string name = "def", std::string type = "?????", float width = 1, float height = 1, float max_depth = 1);
	Reservoir(const Reservoir& src);
	Reservoir& operator =(const Reservoir& src);

};
