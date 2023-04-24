#pragma once
class StructureManager : public Singleton<StructureManager>
{
private:
	const int BASEFLOOR_WIDTH = 3;
	const int BASEFLOOR_HEIGHT = 4;

	friend class Singleton;

	StructureManager();
	~StructureManager();

	void LoadBaseStructureData();

public:
	void Update();
	void Render();
	void GUIRender();

	void AddStructure(Structure* structure);
	void AddFloor(Plane* plane);

	vector<Structure*>& GetMapStrctures() { return mapStructures; }
	vector<Plane*> GetFloors() { return floors; }

private:
	vector<Structure*> mapStructures; // ¼³Ä¡¹°
	vector<Plane*> floors; // ¹Ù´Ú
};