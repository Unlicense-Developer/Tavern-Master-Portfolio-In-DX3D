#include "Framework.h"
#include "Cursor.h"

Cursor::Cursor()
	:Quad(L"Textures/UI/Cursor.png")
{
	Scale() *= 0.5f;
}

Cursor::~Cursor()
{
}

void Cursor::Update()
{
	ShowCursor(NULL);
	Pos() = mousePos + Vector3(size.x * 0.2f , -size.y * 0.2f, 0.0f);

	UpdateWorld();
}

void Cursor::Render()
{
	Quad::Render();
}
