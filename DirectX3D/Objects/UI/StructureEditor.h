#pragma once
class StructureEditor : public Quad
{
private:
	const string WALL = "º®";
	const string SHOP = "¼¥";
	const string TABLE = "Å¹ÀÚ";
	const string CHAIR = "ÁÂ¼®";
	const string DECORATION = "Àå½Ä";
	const string LIGHT = "Á¶¸í";
	const string CARPET = "Ä«Æê";

	const float CORRECT_VALUE = 0.25f;
	const float WALL_YPOS = 2.5f;
	const Float4 ORIGINAL_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
	const Float4 DELETE_COLOR = { 0.47f, 0.0f, 0.0f, 1.0f };

public:
	StructureEditor();
	~StructureEditor();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	bool IsUICollision();

	Structure* GetSampleModel() { return sampleModel; }
	string GetSampleName() { return sampleName; }
	void SetTerrain(Terrain* terrain) { this->terrain = terrain; };

	void SetClickedModel();

private:
	Vector3 DefineStructurePos(Vector3 pos);
	float PosCorrect(float pos);

	void PrintText();
	void SampleControl();
	void PlayCreateSound();
	void DeleteStructure();
	void ChangeCategory();
	void CloseEditor();

	void ByteAddress();

private:
	Caution* caution;

	//Ä«Å×°í¸® ¹öÆ°
	Button* exteriorButton;
	Button* tableButton;
	Button* chairButton;
	Button* decorationButton;
	Button* lightButton;

	//Button* carpet;

	ButtonCategory* exteriors;
	ButtonCategory* tables;
	ButtonCategory* chairs;
	ButtonCategory* decorations;
	ButtonCategory* lights;

	Button* cancel;

	//vector<StructureButton*> carpets;

	Quad* selectedFrame = nullptr;
	Structure* sampleModel = nullptr;
	string sampleName = "Wall";

	bool isDeleteMode = false;

	Terrain* terrain;
	RectCollider* collider;
};