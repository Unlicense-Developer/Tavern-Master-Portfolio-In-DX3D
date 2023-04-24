#pragma once

struct StructureButtonData
{
	string key;
	wstring texturePath;
	Vector3 buttonPos;
	int StructureCost;
};

class StructureDataManager : public Singleton<StructureDataManager>
{
private:
	friend class Singleton;

	StructureDataManager();
	~StructureDataManager();

	void LoadStructureButtonData();

public:
	vector<StructureButtonData> GetStructureButtonDatas(string key);

private:
	map<string, vector<StructureButtonData>> structureButtonDatas;

};