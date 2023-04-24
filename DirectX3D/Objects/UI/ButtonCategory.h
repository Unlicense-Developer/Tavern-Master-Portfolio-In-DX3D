#pragma once
class StructureEditor;

class ButtonCategory : public Quad
{
public:
	ButtonCategory(string key);
	~ButtonCategory();

	void Update();
	void PostRender();

	vector<StructureButton*> GetButtons() { return buttons; }

	void SetButtonEvent(StructureEditor* editor);

private:
	vector<StructureButton*> buttons;
};