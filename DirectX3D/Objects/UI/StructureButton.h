#pragma once

class StructureButton : public Button
{
public:
	StructureButton(wstring textureFile);
	~StructureButton();

	void Update();
	void Render();

	string GetStructureName() { return structureName;}
	void SetStructureName(string name) { this->structureName = name; }

	void SetCost(int cost) { this->cost = cost; } 
	int GetCost() { return cost; }

private:
	string structureName;

	Quad* frame;
	Quad* coin;
	
	int cost;
};