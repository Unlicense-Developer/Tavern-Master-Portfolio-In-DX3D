#pragma once
class Menu
{
private:
	const float TIME_INTERVAL = 2.0f;
	
	const string GOLD = "µ·:";
	const string FAME = "¸í¼º:";

public:
	Menu();
	~Menu();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

private:
	void OpenFloorEditor();
	void OpenStructureEditor();
	void PrintText();

	void ToggleButton();

private:
	Button* make;
	Button* table;

	Button* pause;
	Button* play;
	Button* fastFoward;

	Button* stat;
	Button* indicator;

	Quad* goldIcon;
	Quad* fameIcon;

	Button* setting;

	Quad* statusBar;
	int gold = 100;
	int fame = 0;
};