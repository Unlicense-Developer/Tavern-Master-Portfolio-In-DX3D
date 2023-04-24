#include "Framework.h"

UIManager::UIManager()
{
	structureEditor = new StructureEditor();
	structureEditor->Scale() *= 0.8f;

	floorEditor = new FloorEditor();
	floorEditor->Scale() *= 0.8f;

	grid = new Grid();

	menu = new Menu();

	cursor = new Cursor();
}

UIManager::~UIManager()
{
	delete structureEditor;
	delete floorEditor;
	delete grid;
	delete menu;
	delete cursor;
}

void UIManager::Update()
{
	structureEditor->Update();
	floorEditor->Update();

	if (structureEditor->Active() ||
		floorEditor->Active())
		grid->Update();

	menu->Update();
	cursor->Update();
}

void UIManager::Render()
{
	structureEditor->Render();
	floorEditor->Render();

	if (structureEditor->Active() ||
		floorEditor->Active())
		grid->Render();
}

void UIManager::PostRender()
{
	menu->PostRender();
	structureEditor->PostRender();
	floorEditor->PostRender();
	cursor->Render();
}

void UIManager::GUIRender()
{
	structureEditor->GUIRender();
	floorEditor->GUIRender();
}
