#include "Framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	bg = new Quad(L"Textures/UI/Background.jpg");
	bg->Pos() = { CENTER_X, CENTER_Y };
	bg->UpdateWorld();

	logo = new Quad(L"Textures/UI/Logo.png");
	logo->SetTag("Logo");
	logo->Load();

	fadeout = new Quad(L"Textures/UI/Fadeout.png");
	fadeout->Pos() = { CENTER_X, CENTER_Y };
	fadeout->GetColor().w = 0.0f;
	fadeout->UpdateWorld();

	start = new Button(L"Textures/UI/Button.png");
	start->SetTag("Start_Button");
	start->Load();
	start->SetEvent(bind(&StartScene::FadeOut, this));

	exit = new Button(L"Textures/UI/Button.png");
	exit->SetTag("Exit_Button");
	exit->Load();
	exit->SetEvent(bind(&StartScene::ExitGame, this));

	cursor = new Cursor();
}

StartScene::~StartScene()
{
	delete bg;
	delete logo;
	delete fadeout;
	delete start;
	delete exit;
	delete cursor;
}

void StartScene::Update()
{
	LoopBgm();

	StartGame();

	logo->UpdateWorld();
	start->Update();
	exit->Update();
	cursor->Update();
}

void StartScene::PreRender()
{
}

void StartScene::Render()
{
}

void StartScene::PostRender()
{
	bg->Render();
	logo->Render();
	start->Render();
	exit->Render();
	fadeout->Render();
	cursor->Render();

	PrintText();
}

void StartScene::GUIRender()
{
	logo->GUIRender();
	start->GUIRender();
	exit->GUIRender();
}

void StartScene::PrintText()
{
	if (!isFadeOut)
	{
		Font::Get()->SetColor("Yellow");
		Font::Get()->SetStyle("50");

		Font::Get()->RenderText(NEW_GAME, { start->GlobalPos().x + 110.0f, start->GlobalPos().y + 10.0f });
		Font::Get()->RenderText(EXIT, { exit->GlobalPos().x + 90.0f, exit->GlobalPos().y + 10.0f });
	}
}

void StartScene::FadeOut()
{
	isFadeOut = true;
}

void StartScene::StartGame()
{
	if (isFadeOut)
	{
		fadeout->GetColor().w += DELTA * 1.5f;
	}

	if (fadeout->GetColor().w >= 1.0f)
	{
		Audio::Get()->Stop("Bgm " + to_string(curBgmIndex));
		SceneManager::Get()->Remove("Start");
		SceneManager::Get()->Add("Tavern");
		CAM->SetTavernScene(true);
	}
}

void StartScene::ExitGame()
{
	PostQuitMessage(0);
}

void StartScene::LoopBgm()
{
	if (!Audio::Get()->IsPlaySound("Bgm " + to_string(curBgmIndex)))
	{
		curBgmIndex = Random(1, 6);
		Audio::Get()->Play("Bgm " + to_string(curBgmIndex), 0.6f);
	}
}
