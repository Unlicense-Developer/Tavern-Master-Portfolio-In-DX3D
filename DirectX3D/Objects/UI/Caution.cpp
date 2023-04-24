#include "Framework.h"

Caution::Caution()
	:Quad(L"Textures/UI/UIBoard_Wide.png")
{
	cancel = new Button(L"Textures/UI/Closebutton.png");
	cancel->Pos() = Pos() + CANCEL_POS;
	cancel->Scale() *= 0.7f;
	cancel->SetParent(this);
	cancel->SetEvent(bind(&Caution::Close, this));

	title = new Quad(L"Textures/UI/UITitle.png");
	title->Pos() = Pos() + TITLE_POS;
	title->Scale() *= 0.55f;
	title->SetParent(this);

	shadow = new Quad(L"Textures/UI/Fadeout.png");
	shadow->GetColor().w = 0.5f;
	shadow->SetParent(this);

	UpdateWorld();
}

Caution::~Caution()
{
	delete cancel;
	delete title;
	delete shadow;
}

void Caution::Update()
{
	cancel->Update();
	title->UpdateWorld();
	shadow->UpdateWorld();
}

void Caution::Render()
{
	shadow->Render();
	Quad::Render();
	cancel->Render();
	title->Render();

	PrintText();
}

void Caution::GUIRender()
{
}

void Caution::Show()
{
	isActive = true;
	CAM->SetTavernScene(false);
}

void Caution::Close()
{
	isActive = false;
	CAM->SetTavernScene(true);
	Audio::Get()->Play("UI Click");
}

void Caution::PrintText()
{
	if (!Active()) return;

 	Font::Get()->SetColor("Brown");
	Font::Get()->SetStyle("40");

	Font::Get()->RenderText(CAUTION, { title->GlobalPos().x + 70.0f, title->GlobalPos().y + 5.0f });

	Font::Get()->SetColor("Gray");

	Font::Get()->RenderText("골드가 부족합니다.", { GlobalPos().x + 250.0f, GlobalPos().y + 10.0f });
}
