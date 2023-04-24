#include "Framework.h"
#include "FloorEditor.h"

FloorEditor::FloorEditor()
	:Quad(L"Textures/UI/UIBoard.png")
{
	Pos() = { WIN_WIDTH - GetMaterial()->GetDiffuseMap()->GetSize().x / 2 + 40, CENTER_Y, 0.0f };

	collider = new RectCollider(size);
	collider->SetParent(this);

	cancel = new Button(L"Textures/UI/Closebutton.png");
	cancel->Pos() = { size.x / 2 - 40.0f, size.y / 2 - 40.0f };
	cancel->Scale() *= 0.8f;
	cancel->SetParent(this);
	cancel->SetEvent(bind(&FloorEditor::CloseEditor, this));

	selectedFrame = new Quad(L"Textures/UI/Floorframe.png");
	selectedFrame->Scale() *= 0.46f;
	selectedFrame->SetActive(false);

	int buttonSize = StructureDataManager::Get()->GetStructureButtonDatas("Floor").size();

	FOR(buttonSize)
	{
		floorButtons.push_back(new StructureButton(StructureDataManager::Get()->GetStructureButtonDatas("Floor")[i].texturePath));
		floorButtons.back()->Pos() = StructureDataManager::Get()->GetStructureButtonDatas("Floor")[i].buttonPos;
		floorButtons.back()->SetCost(StructureDataManager::Get()->GetStructureButtonDatas("Floor")[i].StructureCost);
		floorButtons.back()->Scale() *= 0.55f;
		floorButtons.back()->SetParent(this);
	}

	UpdateWorld();
	SetActive(false);
}

FloorEditor::~FloorEditor()
{
	//delete selectedFloor;
	delete cancel;
	delete collider;

	for (StructureButton* floorButton : floorButtons)
		delete floorButton;
}

void FloorEditor::Update()
{
	if (!Active()) return;

	SelectFloorButton();
	ChangeFloor();

	cancel->Update();
	selectedFrame->UpdateWorld();

	UpdateWorld();
	collider->UpdateWorld();

	for (StructureButton* floorButton : floorButtons)
		floorButton->Update();
}

void FloorEditor::Render()
{
}

void FloorEditor::PostRender()
{
	if (!Active()) return;

	Quad::Render();

	cancel->Render();

	for (StructureButton* floorButton : floorButtons)
		floorButton->Render();

	selectedFrame->Render();

	PrintText();
}

void FloorEditor::CloseEditor()
{
	SetActive(false);
	Timer::Get()->SetDeltaScale(1.0f);
	Audio::Get()->Play("UI Click", 0.6f);
}

void FloorEditor::SelectFloorButton()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		for (StructureButton* floorButton : floorButtons)
		{
			if (floorButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
			{
				selectedFrame->Pos() = floorButton->GlobalPos();
				floorTexturePath = floorButton->GetMaterial()->GetDiffuseMap()->GetFile();
				selectedFrame->SetActive(true);

				return;
			}
		}
	}
}

void FloorEditor::ChangeFloor()
{
	if (collider->IsPointCollision({ mousePos.x, mousePos.y }) ||
		cancel->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
		return;

	if (!selectedFrame->Active())
		return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		Ray ray = CAM->ScreenPointToRay(mousePos);

		for (Plane* floor : FLOORS)
		{
			if (floor->GetCollider()->IsRayCollision(ray, nullptr))
			{
				floor->GetMaterial()->SetDiffuseMap(floorTexturePath);
				Audio::Get()->Play("Create_Floor", 0.6f);

				return;
			}
		}

		Vector3 floorPos;
		terrain->ComputePicking(floorPos);

		Plane* floor = new Plane();

		if( floorPos.x >= 0)
			floor->Pos().x = (int)((floorPos.x + 2) / FLOOR_SIZE) * FLOOR_SIZE;
		else
			floor->Pos().x = ((int)((floorPos.x - 2) / FLOOR_SIZE)) * FLOOR_SIZE;

		if(floorPos.z >= 0)
			floor->Pos().z = FLOOR_STARTPOS.z + (int)( floorPos.z / FLOOR_SIZE ) * FLOOR_SIZE;
		else
			floor->Pos().z = FLOOR_STARTPOS.z + ((int)(floorPos.z / FLOOR_SIZE ) - 1) * FLOOR_SIZE;

		floor->Pos().y = 0.01f;
		floor->Rot().y = -XM_PIDIV2;
		floor->GetMaterial()->SetDiffuseMap(floorTexturePath);
		floor->UpdateWorld();
		StructureManager::Get()->AddFloor(floor);
		Audio::Get()->Play("Create_Floor", 0.6f);
	}
}

void FloorEditor::PrintText()
{
	Font::Get()->SetStyle("40");
	Font::Get()->RenderText(FLOOR, { Pos().x + STRINGPOS_OFFSET.x, Pos().y + STRINGPOS_OFFSET.y });
}
