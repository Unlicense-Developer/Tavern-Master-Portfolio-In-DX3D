#include "Framework.h"
#include "Menu.h"

Menu::Menu()
{
	make = new Button(L"Textures/UI/Make.png");
	make->Pos() = { CENTER_X - 60.0f, make->GetMaterial()->GetDiffuseMap()->GetSize().y / 4 };
	make->Scale() *= 0.6f;
	make->SetEvent(bind(&Menu::OpenFloorEditor, this));

	table = new Button(L"Textures/UI/Table.png");
	table->Pos() = { CENTER_X + 60.0f, table->GetMaterial()->GetDiffuseMap()->GetSize().y / 4 };
	table->Scale() *= 0.6f;
	table->SetEvent(bind(&Menu::OpenStructureEditor, this));

	pause = new Button(L"Textures/UI/Pause.png");
	pause->Pos() = { 50, WIN_HEIGHT - 40.0f };
	pause->Scale() *= 0.4f;
	pause->SetEvent(bind(&Menu::ToggleButton, this));

	play = new Button(L"Textures/UI/Play.png");
	play->Pos() = { 100, WIN_HEIGHT - 40.0f };
	play->Scale() *= 0.4f;
	play->SetEvent(bind(&Menu::ToggleButton, this));

	fastFoward = new Button(L"Textures/UI/FastFoward.png");
	fastFoward->Pos() = { 150, WIN_HEIGHT - 40.0f };
	fastFoward->Scale() *= 0.4f;
	fastFoward->SetEvent(bind(&Menu::ToggleButton, this));

	stat = new Button(L"Textures/UI/Stat.png");
	stat->Pos() = { 300, WIN_HEIGHT - 40.0f };
	stat->Scale() *= 0.6f;

	indicator = new Button(L"Textures/UI/Indicator.png");
	indicator->Pos() = { 380, WIN_HEIGHT - 40.0f };
	indicator->Scale() *= 0.6f;

	goldIcon = new Button(L"Textures/UI/Gold.png");
	goldIcon->Pos() = { 570, WIN_HEIGHT - 50.0f };
	goldIcon->Scale() *= 0.25f;
	goldIcon->UpdateWorld();

	fameIcon = new Button(L"Textures/UI/Fame.png");
	fameIcon->Pos() = { 725, WIN_HEIGHT - 52.0f };
	fameIcon->Scale() *= 0.15f;
	fameIcon->UpdateWorld();

	setting = new Button(L"Textures/UI/Setting.png");
	setting->Pos() = { WIN_WIDTH - 40.0f, WIN_HEIGHT - 40.0f };
	setting->Scale() *= 0.6f;

	statusBar = new Quad(L"Textures/UI/Status.png");
	statusBar->Pos() = { CENTER_X, WIN_HEIGHT - 40.0f };
	statusBar->Scale().x *= 1.5f;
	statusBar->Scale().y *= 0.9f;
	statusBar->UpdateWorld();

	pause->MakeToggleButton();
	fastFoward->MakeToggleButton();
}

Menu::~Menu()
{
	delete make;
	delete table;
	delete statusBar;
	delete pause;
	delete play;
	delete fastFoward;
	delete stat;
	delete indicator;
	delete goldIcon;
	delete fameIcon;
}

void Menu::Update()
{
	make->Update();
	table->Update();

	pause->Update();
	play->Update();
	fastFoward->Update();

	stat->Update();
	indicator->Update();

	setting->Update();
}

void Menu::Render()
{
}

void Menu::PostRender()
{
	make->Render();
	table->Render();
	statusBar->Render();

	pause->Render();
	play->Render();
	fastFoward->Render();

	goldIcon->Render();
	fameIcon->Render();

	stat->Render();
	indicator->Render();

	setting->Render();

	PrintText();
}

void Menu::GUIRender()
{

}

void Menu::OpenFloorEditor()
{
	if (UIManager::Get()->GetStructureEditor()->Active()) return;

	UIManager::Get()->GetFloorEditor()->SetActive(true);
	Timer::Get()->SetDeltaScale(0.0f);
	Audio::Get()->Play("UI Click");
}

void Menu::OpenStructureEditor()
{
	if (UIManager::Get()->GetFloorEditor()->Active()) return;

	UIManager::Get()->GetStructureEditor()->SetActive(true);
	Timer::Get()->SetDeltaScale(0.0f);
	Audio::Get()->Play("UI Click");
}

void Menu::PrintText()
{
	/*Font::Get()->SetStyle("40");
	Font::Get()->SetColor("White");

	if (Environment::Get()->GetDayTime() == 0)
		Font::Get()->RenderText(to_string(12) + "am", { 100, WIN_HEIGHT - 40.0f });
	else if (Environment::Get()->GetDayTime() == 12)
		Font::Get()->RenderText(to_string(12) + "pm", { 100, WIN_HEIGHT - 40.0f });
	else if (Environment::Get()->GetDayTime() < 12)
		Font::Get()->RenderText(to_string(Environment::Get()->GetDayTime()) + "am", { 100, WIN_HEIGHT - 40.0f });
	else if(Environment::Get()->GetDayTime() > 12)
		Font::Get()->RenderText(to_string(Environment::Get()->GetDayTime() - 12) + "pm", { 100, WIN_HEIGHT - 40.0f });*/

	Font::Get()->SetStyle("30");
	Font::Get()->SetColor("Gray");
	Font::Get()->RenderText(GOLD, { 500, WIN_HEIGHT - 15.0f });
	Font::Get()->RenderText(FAME, { 700, WIN_HEIGHT - 15.0f });

	Font::Get()->SetStyle("40");
	Font::Get()->RenderText(to_string(TavernManager::Get()->GetGold()), { 550, WIN_HEIGHT - 50.0f });
	Font::Get()->RenderText(to_string(TavernManager::Get()->GetFame()), { 700, WIN_HEIGHT - 50.0f });
}

void Menu::ToggleButton()
{
	if ( pause->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		//if (pause->GetToggleColor() == 1.0f) return;

		pause->MakeToggleButton();

		if (play->GetToggleColor() == 1.0f)
			play->MakeToggleButton();
		if (fastFoward->GetToggleColor() == 1.0f)
			fastFoward->MakeToggleButton();

		Timer::Get()->SetDeltaScale(0.0f);
		return;
	}
	else if (play->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		//if (play->GetToggleColor() == 1.0f) return;

		play->MakeToggleButton();

		if (pause->GetToggleColor() == 1.0f)
			pause->MakeToggleButton();
		if (fastFoward->GetToggleColor() == 1.0f)
			fastFoward->MakeToggleButton();

		Timer::Get()->SetDeltaScale(1.0f);
		return;
	}
	else if (fastFoward->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		//if (fastFoward->GetToggleColor() == 1.0f) return;

		fastFoward->MakeToggleButton();

		if (play->GetToggleColor() == 1.0f)
			play->MakeToggleButton();
		if (pause->GetToggleColor() == 1.0f)
			pause->MakeToggleButton();

		Timer::Get()->SetDeltaScale(2.0f);
		return;
	}
}