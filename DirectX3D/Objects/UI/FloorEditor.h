#pragma once
class FloorEditor : public Quad
{
	const string FLOOR = "¹Ù´Ú";

	const Vector2 STRINGPOS_OFFSET = { 45.0f, 240.f };
	const Vector3 FLOOR_STARTPOS = { 0.0f, 0, 2.0f };
	const float FLOOR_SIZE = 4.0f;

public:
	FloorEditor();
	~FloorEditor();

	void Update();
	void Render();
	void PostRender();

	void SetTerrain(Terrain* terrain) { this->terrain = terrain; };

private:
	void CloseEditor();

	void SelectFloorButton();
	void ChangeFloor();

	void PrintText();

private:
	vector<StructureButton*> floorButtons;

	Quad* selectedFrame = nullptr;
	wstring floorTexturePath;
	Button* cancel;

	Terrain* terrain;
	RectCollider* collider;
};