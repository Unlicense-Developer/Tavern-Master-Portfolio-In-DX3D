#include "Framework.h"

StructureEditor::StructureEditor()
	:Quad(L"Textures/UI/UIBoard.png")
{
	Pos() = {WIN_WIDTH - GetMaterial()->GetDiffuseMap()->GetSize().x / 2 + 40, CENTER_Y, 0.0f};

	collider = new RectCollider(size);
	collider->SetParent(this);

	cancel = new Button(L"Textures/UI/Closebutton.png");
	cancel->Pos() = { size.x / 2 - 40.0f, size.y / 2 - 40.0f };
	cancel->Scale() *= 0.8f;
	cancel->SetParent(this);
	cancel->SetEvent(bind(&StructureEditor::CloseEditor, this));

	caution = new Caution();
	caution->Pos() = { CENTER_X, CENTER_Y };
	caution->SetActive(false);
	caution->UpdateWorld();

	selectedFrame = new Quad(L"Textures/UI/Floorframe.png");
	selectedFrame->Scale() *= 0.46f;
	selectedFrame->SetActive(false);

	//카테고리 버튼
	exteriorButton = new Button(L"Textures/UI/SubButton.png");
	exteriorButton->Pos() = { -260, 200 };
	exteriorButton->Scale() *= 0.5f;
	exteriorButton->SetParent(this);

	tableButton = new Button(L"Textures/UI/SubButton.png");
	tableButton->Pos() = { -260, 135 };
	tableButton->Scale() *= 0.5f;
	tableButton->SetParent(this);

	chairButton = new Button(L"Textures/UI/SubButton.png");
	chairButton->Pos() = { -260, 70 };
	chairButton->Scale() *= 0.5f;
	chairButton->SetParent(this);

	decorationButton = new Button(L"Textures/UI/SubButton.png");
	decorationButton->Pos() = { -260, 5 };
	decorationButton->Scale() *= 0.5f;
	decorationButton->SetParent(this);

	lightButton = new Button(L"Textures/UI/SubButton.png");
	lightButton->Pos() = { -260, -60 };
	lightButton->Scale() *= 0.5f;
	lightButton->SetParent(this);

	exteriorButton->SetEvent(bind(&StructureEditor::ChangeCategory, this));
	tableButton->SetEvent(bind(&StructureEditor::ChangeCategory, this));
	chairButton->SetEvent(bind(&StructureEditor::ChangeCategory, this));
	decorationButton->SetEvent(bind(&StructureEditor::ChangeCategory, this));
	lightButton->SetEvent(bind(&StructureEditor::ChangeCategory, this));

	// 카테고리 내 모델 버튼
	exteriors = new ButtonCategory("Exterior");
	exteriors->SetParent(this);
	exteriors->SetButtonEvent(this);

	tables = new ButtonCategory("Table");
	tables->SetParent(this);
	tables->SetActive(false);
	tables->SetButtonEvent(this);

	chairs = new ButtonCategory("Chair");
	chairs->SetParent(this);
	chairs->SetActive(false);
	chairs->SetButtonEvent(this);

	decorations = new ButtonCategory("Decoration");
	decorations->SetParent(this);
	decorations->SetActive(false);
	decorations->SetButtonEvent(this);

	lights = new ButtonCategory("Light");
	lights->SetParent(this);
	lights->SetActive(false);
	lights->SetButtonEvent(this);

	ByteAddress();
	UpdateWorld();
	SetActive(false);
}

StructureEditor::~StructureEditor()
{
	delete caution;

	delete sampleModel;
	delete cancel;
	delete selectedFrame;
	delete collider;

	delete exteriors;
	delete tables;
	delete chairs;
	delete decorations;
	delete lights;

	delete exteriorButton;
	delete tableButton;
	delete chairButton;
	delete decorationButton;
	delete lightButton;
}

void StructureEditor::Update()
{
	if (!Active()) return;

	cancel->Update();
	caution->Update();
	selectedFrame->UpdateWorld();

	exteriors->Update();
	tables->Update();
	chairs->Update();
	decorations->Update();
	lights->Update();

	exteriorButton->Update();
	tableButton->Update();
	chairButton->Update();
	decorationButton->Update();
	lightButton->Update();

	SampleControl();
	DeleteStructure();

	UpdateWorld();
	collider->UpdateWorld();

	if (sampleModel)
	{
		if(sampleModel->GetType() == CANDLE)
			((Candle*)sampleModel)->Update();
		else
			sampleModel->Update();
	}
}

void StructureEditor::Render()
{
	if (!Active()) return;

	if (sampleModel && !caution->Active())
	{
		sampleModel->Render();
	}
}

void StructureEditor::PostRender()
{
	if (!Active()) return;

	Quad::Render();

	exteriors->PostRender();
	tables->PostRender();
	chairs->PostRender();
	decorations->PostRender();
	lights->PostRender();

	exteriorButton->Render();
	tableButton->Render();
	chairButton->Render();
	decorationButton->Render();
	lightButton->Render();

	cancel->Render();
	selectedFrame->Render();
	caution->Render();

	PrintText();
}

void StructureEditor::GUIRender()
{
	StructureManager::Get()->GUIRender();
}

bool StructureEditor::IsUICollision()
{
	if (collider->IsPointCollision({ mousePos.x, mousePos.y }) ||
		exteriorButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }) ||
		tableButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }) ||
		chairButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }) ||
		decorationButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }) ||
		lightButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }) ||
		cancel->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
		return true;
	else
		return false;
}

void StructureEditor::SetClickedModel()
{
	vector<StructureButton*> tempButtons;

	if (exteriors->Active())
		tempButtons = exteriors->GetButtons();
	else if (tables->Active())
		tempButtons = tables->GetButtons();
	else if (chairs->Active())
		tempButtons = chairs->GetButtons();
	else if (decorations->Active())
		tempButtons = decorations->GetButtons();
	else if (lights->Active())
		tempButtons = lights->GetButtons();

	for (StructureButton* button : tempButtons)
	{
		if (button->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
		{
			if (!sampleModel) // 샘플 모델 없을때
			{
				selectedFrame->Pos() = button->GlobalPos();
				selectedFrame->SetActive(true);
				selectedFrame->UpdateWorld();

				if (button->GetStructureName() == "DeleteStructure")
				{
					isDeleteMode = true;
					return;
				}

				isDeleteMode = false;

				if (GetStructureCategory(button->GetStructureName()) == "Candle")
					sampleModel = new Candle(button->GetStructureName());
				else
					sampleModel = new Structure(button->GetStructureName());

				sampleModel->SetCost(button->GetCost());

			}
			else // 샘플 모델 있을때 다른 모델로 교체
			{
				selectedFrame->Pos() = button->GlobalPos();
				selectedFrame->SetActive(true);
				selectedFrame->UpdateWorld();

				if (button->GetStructureName() == "DeleteStructure")
				{
					sampleModel = nullptr;
					isDeleteMode = true;
					return;
				}

				isDeleteMode = false;

				if (sampleModel->GetType() == CANDLE)
				{
					sampleModel = nullptr;
					sampleModel = new Candle(button->GetStructureName());
				}
				else
					sampleModel->ReGenerate(button->GetStructureName());

				sampleModel->Rot().y = 0.0f;

				sampleModel->SetCost(button->GetCost());
			}

			break;
		}
	}
}

Vector3 StructureEditor::DefineStructurePos(Vector3 pos)
{
	if (sampleModel->GetType() == StructureType::TABLE)
	{
		return { round(pos.x), pos.y, round(pos.z) };
	}
	else if (sampleModel->GetType() == StructureType::CHAIR1)
	{
		return { floor(pos.x) + 0.5f, pos.y, floor(pos.z) + 0.5f };
	}
	else if (sampleModel->GetType() == StructureType::CHAIR2)
	{
		if (abs((int)(sampleModel->Rot().y / XM_PIDIV2)) % 2 == 0) // 가로
		{
			return { round(pos.x), pos.y, floor(pos.z) + 0.5f };
		}
		else if (abs((int)(sampleModel->Rot().y / XM_PIDIV2)) % 2 == 1) // 세로
		{
			return { floor(pos.x) + 0.5f, pos.y,  round(pos.z) };
		}
	}
	else
		return { PosCorrect(pos.x), pos.y, PosCorrect(pos.z) };
}

float StructureEditor::PosCorrect(float pos)
{
	if (pos < 0) // 기타 구조물 0.5 단위로 위치 조정
	{
		if (fmod(pos, 1.0f) >= -CORRECT_VALUE)
			return ceil(pos);
		else if (fmod(pos, 1.0f) < -CORRECT_VALUE &&
			fmod(pos, 1.0f) > -CORRECT_VALUE * 3.0f)
			return ceil(pos) + -CORRECT_VALUE * 2.0f;
		else if (fmod(pos, 1.0f) <= -CORRECT_VALUE * 3.0f)
			return floor(pos);
	}
	else
	{
		if (fmod(pos, 1.0f) <= CORRECT_VALUE)
			return floor(pos);
		else if (fmod(pos, 1.0f) > CORRECT_VALUE &&
			fmod(pos, 1.0f) < CORRECT_VALUE * 3.0f)
			return floor(pos) + CORRECT_VALUE * 2.0f;
		else if (fmod(pos, 1.0f) >= CORRECT_VALUE * 3.0f)
			return ceil(pos);
	}
}

void StructureEditor::PrintText()
{	
	Font::Get()->SetStyle("40");
	Font::Get()->SetColor("Gray");

	Font::Get()->RenderText(SHOP, {Pos().x + 20.0f, Pos().y + 240.0f });

	Font::Get()->SetStyle("30");
	Font::Get()->RenderText(WALL, {Pos().x - 190.0f, Pos().y + 165.0f });
	Font::Get()->RenderText(TABLE, { Pos().x - 175.0f, Pos().y + 112.0f });
	Font::Get()->RenderText(CHAIR, { Pos().x - 175.0f, Pos().y + 59.0f });
	Font::Get()->RenderText(DECORATION, { Pos().x - 175.0f, Pos().y + 6.0f });
	Font::Get()->RenderText(LIGHT, { Pos().x - 177.0f, Pos().y - 45.0f });
}

void StructureEditor::SampleControl() // 샘플모델 pos 조절
{ 
	if (!sampleModel) return;

	terrain->ComputePicking(sampleModel->Pos());

	sampleModel->Pos() = DefineStructurePos(sampleModel->Pos());
	
	if (sampleModel->GetType() == CANDLE && 
		sampleModel->GetName() != "Stick_Candle")
	{
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;

		for (Structure* mapModel : STRUCTURES)
		{
			if ( mapModel->GetType() == PILAR &&
				mapModel->GetCollider()->IsRayCollision(ray, &contact))
			{
				Vector3 direction = (contact.hitPoint - mapModel->GetCollider()->GlobalPos());

				if (direction.x > 0 && direction.z > 0)
				{
					if (direction.x > direction.z) // 우
					{
						sampleModel->Pos().x = contact.hitPoint.x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = mapModel->GetCollider()->GlobalPos().z;
						sampleModel->Rot().y = -XM_PIDIV2;
					}
					else if (direction.x < direction.z) // 상
					{
						sampleModel->Pos().x = mapModel->GetCollider()->GlobalPos().x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = contact.hitPoint.z;
						sampleModel->Rot().y = XM_PIDIV2 * 2.0f; 
					}

				}
				else if (direction.x > 0 && direction.z < 0)
				{
					if (direction.x > abs(direction.z)) // 우
					{
						sampleModel->Pos().x = contact.hitPoint.x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = mapModel->GetCollider()->GlobalPos().z;
						sampleModel->Rot().y = -XM_PIDIV2;
					}
					else if (direction.x < abs(direction.z)) // 하
					{
						sampleModel->Pos().x = mapModel->GetCollider()->GlobalPos().x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = contact.hitPoint.z;
					}
				}
				else if (direction.x < 0 && direction.z > 0)
				{
					if (abs(direction.x) > direction.z) // 좌
					{
						sampleModel->Pos().x = contact.hitPoint.x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = mapModel->GetCollider()->GlobalPos().z;
						sampleModel->Rot().y = XM_PIDIV2;
					}
					else if (abs(direction.x) < direction.z) // 상
					{
						sampleModel->Pos().x = mapModel->GetCollider()->GlobalPos().x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = contact.hitPoint.z;
						sampleModel->Rot().y = XM_PIDIV2 * 2.0f;
					}
				}
				else if (direction.x < 0 && direction.z < 0)
				{
					if (direction.x > direction.z) // 하
					{
						sampleModel->Pos().x = mapModel->GetCollider()->GlobalPos().x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = contact.hitPoint.z;
					}
					else if (direction.x < direction.z) // 좌
					{
						sampleModel->Pos().x = contact.hitPoint.x;
						sampleModel->Pos().y = WALL_YPOS;
						sampleModel->Pos().z = mapModel->GetCollider()->GlobalPos().z;
						sampleModel->Rot().y = XM_PIDIV2;
					}
				}

				break;
			}
			else
			{
				sampleModel->Pos().y = 2.5f;
				sampleModel->Rot().y = 0.0f;
			}
		}
	}

	if (KEY_DOWN('Q'))
	{
		sampleModel->Rot().y += XM_PIDIV2;
	}
	else if (KEY_DOWN('E'))
	{
		sampleModel->Rot().y -= XM_PIDIV2;
	}

	if (KEY_DOWN(VK_LBUTTON) && !IsUICollision()) // 모델 설치
	{
		if (!sampleModel) return;

		if (sampleModel->Active())
		{
			{
				if (sampleModel->GetCost() > TavernManager::Get()->GetGold())
				{
					caution->Show();
					return;
				}
				else
					TavernManager::Get()->GetGold() -= sampleModel->GetCost();
			}

			PlayCreateSound();

			Structure* structure;

			if(sampleModel->GetType() == CANDLE) // Candle 종류의 구조물
				structure = new Candle(sampleModel->GetName());
			else
				structure = new Structure(sampleModel->GetName());

			structure->Pos() = sampleModel->Pos();
			structure->Rot() = sampleModel->Rot();
			structure->UpdateWorld();
			StructureManager::Get()->AddStructure(structure);

			TavernManager::Get()->AddChairData(structure);

			//기존 노드 타입 변경
			structure->ChangeNodeState();
		}
	}
}

void StructureEditor::PlayCreateSound()
{
	if (sampleModel->GetType() == StructureType::WALL || StructureType::PILAR)
	{
		Audio::Get()->Play("Create_Wall", 0.6f);
	}
	else
	{
		Audio::Get()->Play("Create_Structure", 0.6f);
	}
}

void StructureEditor::DeleteStructure()
{
	if (isDeleteMode)
	{
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;
		Structure* ClosestStructure = nullptr;

		for (Structure* structure : STRUCTURES) // 삭제 대상 구조물 색 변경
		{
			if (structure->GetCollider()->IsRayCollision(ray, &contact))
			{
				if (ClosestStructure == nullptr ||
					(ClosestStructure->GlobalPos() - contact.hitPoint).Length() >
					(structure->GlobalPos() - contact.hitPoint).Length())
					ClosestStructure = structure;
			}
			structure->GetMaterial()->GetData().emissive = ORIGINAL_COLOR;
		}
		
		if (ClosestStructure)
			ClosestStructure->GetMaterial()->GetData().emissive = DELETE_COLOR;

		if (!ClosestStructure) return;

		if (KEY_DOWN(VK_LBUTTON))
		{
			vector<Structure*>& structures = STRUCTURES;

			for (vector<Structure*>::iterator iter = structures.begin(); iter != structures.end();)
			{
				Structure* structure = *iter;

				if (structure == ClosestStructure)
				{
					iter = structures.erase(iter);
					Audio::Get()->Play("Delete_Structure", 0.6f);
				}
				else
					iter++;

			}
		}
	}
}

void StructureEditor::ChangeCategory()
{
	selectedFrame->SetActive(false);
	exteriors->SetActive(false);
	tables->SetActive(false);
	chairs->SetActive(false);
	decorations->SetActive(false);
	lights->SetActive(false);

	isDeleteMode = false;
	Audio::Get()->Play("UI Click", 0.6f);

	if (exteriorButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		exteriors->SetActive(true);
	}
	else if (tableButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		tables->SetActive(true);
	}
	else if (chairButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		chairs->SetActive(true);
	}
	else if (decorationButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		decorations->SetActive(true);
	}
	else if (lightButton->GetCollider()->IsPointCollision({ mousePos.x, mousePos.y }))
	{
		lights->SetActive(true);
	}
}

void StructureEditor::CloseEditor()
{
	SetActive(false);

	exteriors->SetActive(true);
	tables->SetActive(false);
	chairs->SetActive(false);
	decorations->SetActive(false);
	lights->SetActive(false);

	sampleModel = nullptr;
	isDeleteMode = false;

	Timer::Get()->SetDeltaScale(1.0f);
	Audio::Get()->Play("UI Click", 0.6f);
}

void StructureEditor::ByteAddress()
{
	ComputeShader* shader = Shader::AddCS(L"Compute/ByteAddress.hlsl");

	struct Output
	{
		UINT groupID[3];
		UINT groupThreadID[3];
		UINT dispatchThreadID[3];
		UINT groupIndex;
	};

	UINT groupX = 2;
	UINT size = 10 * 8 * 3 * groupX;

	Output* output = new Output[size];
	RawBuffer* buffer = new RawBuffer(sizeof(Output) * size);

	DC->CSSetUnorderedAccessViews(0, 1, &buffer->GetUAV(), nullptr);

	shader->Set();

	DC->Dispatch(groupX, 1, 1);

	buffer->Copy(output, sizeof(Output) * size);

	FILE* file;
	fopen_s(&file, "TextData/RawTest.csv", "w");

	for (UINT i = 0; i < size; i++)
	{
		Output temp = output[i];

		fprintf
		(
			file,
			"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			i,
			temp.groupID[0], temp.groupID[1], temp.groupID[2],
			temp.groupThreadID[0], temp.groupThreadID[1], temp.groupThreadID[2],
			temp.dispatchThreadID[0], temp.dispatchThreadID[1], temp.dispatchThreadID[2],
			temp.groupIndex
		);
	}
}
