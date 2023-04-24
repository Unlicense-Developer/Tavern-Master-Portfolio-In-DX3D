#include "Framework.h"
#include "ButtonCategory.h"

ButtonCategory::ButtonCategory(string key)
	:Quad(Vector2(474, 707))
{
	int buttonSize = StructureDataManager::Get()->GetStructureButtonDatas(key).size();

	FOR( buttonSize )
	{
		buttons.push_back(new StructureButton(StructureDataManager::Get()->GetStructureButtonDatas(key)[i].texturePath));
		buttons.back()->Pos() = StructureDataManager::Get()->GetStructureButtonDatas(key)[i].buttonPos;
		buttons.back()->SetCost(StructureDataManager::Get()->GetStructureButtonDatas(key)[i].StructureCost);
		buttons.back()->Scale() *= 0.55f;
		buttons.back()->SetParent(this);
	}
}

ButtonCategory::~ButtonCategory()
{
	for (StructureButton* button : buttons)
		delete button;
}

void ButtonCategory::Update()
{
	Quad::UpdateWorld();

	for (StructureButton* button : buttons)
		button->Update();
}

void ButtonCategory::PostRender()
{
	for (StructureButton* button : buttons)
	{
		if(isActive)
			button->Render();
	}
}

void ButtonCategory::SetButtonEvent(StructureEditor* editor)
{
	for (StructureButton* button : buttons)
		button->SetEvent(bind(&StructureEditor::SetClickedModel, editor));
}

