#include "Framework.h"
#include "StructureDataManager.h"

StructureDataManager::StructureDataManager()
{
	LoadStructureButtonData();
}

StructureDataManager::~StructureDataManager()
{
}

void StructureDataManager::LoadStructureButtonData()
{
	fstream loadFile("TextData/StructureButtonData.csv");

	string temp;

	char text[256];

	bool isFirstLine = true;

	while (true)
	{
		loadFile >> temp;

		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> datas = SplitString(temp, ",");

		StructureButtonData data;
		data.key = datas[0];
		data.texturePath = ToWString(datas[1]);
		data.buttonPos.x = stof(datas[2]);
		data.buttonPos.y = stof(datas[3]);
		data.buttonPos.z = 0;
		data.StructureCost = stoi(datas[4]);

		structureButtonDatas[data.key].push_back(data);


		if (loadFile.eof())
			break;
	}
}

vector<StructureButtonData> StructureDataManager::GetStructureButtonDatas(string key)
{
	return structureButtonDatas.at(key);
}
