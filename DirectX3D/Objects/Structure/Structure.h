#pragma once

enum StructureType
{
	PILAR, WALL, CANDLE, TABLE, CHAIR1, CHAIR2, OTHER
};

class Structure : public Model
{
public:
	Structure(string name);
	~Structure();

	void Update();
	void Render();
	void GUIRender();

	void ReGenerate(string name);
	BoxCollider* GetCollider() { return collider; }
	StructureType GetType() { return type; }
	void SetType();

	int GetCost() { return cost; }
	void SetCost(int cost) { this->cost = cost; }

	//void RemoveNode();
	void ChangeNodeState();

protected:
	BoxCollider* collider;
	StructureType type;
	ColorBuffer* colorBuffer;

	int cost;
};