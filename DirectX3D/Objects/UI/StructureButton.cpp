#include "Framework.h"

StructureButton::StructureButton(wstring textureFile)
	:Button(textureFile)
{
	frame = new Quad(L"Textures/UI/Iconframe.png");
	frame->Scale() *= 1.25f;
	frame->SetParent(this);

	coin = new Quad(L"Textures/UI/PayGold.png");
	coin->Pos() = { size.x / 2.6f, -size.y / 2.6f };
	coin->SetParent(this);

	structureName = ToString(textureFile);
	structureName = structureName.substr(structureName.rfind("/") + 1);
	structureName = structureName.substr(0, structureName.find("."));
}

StructureButton::~StructureButton()
{
	delete frame;
	delete coin;
}

void StructureButton::Update()
{
	Button::Update();
	frame->UpdateWorld();
	coin->UpdateWorld();
}

void StructureButton::Render()
{
	frame->Render();
	Button::Render();

	if (cost != 0)
	{
		coin->Render();

		Font::Get()->SetColor("Yellow");
		Font::Get()->SetStyle("30");

		Font::Get()->RenderText(to_string(cost), { coin->GlobalPos().x - 13, coin->GlobalPos().y + 2 });
	}
}