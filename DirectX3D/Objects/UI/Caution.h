#pragma once
class Caution : public Quad
{
private:
	const Vector3 TITLE_POS = { 0, 150, 0 };
	const Vector3 CANCEL_POS = { -220, 100, 0 };
	const string CAUTION = "ºÎÁ·!";

public:
	Caution();
	~Caution();

	void Update();
	void Render();
	void GUIRender();

	void Show();
	RectCollider* GetCancelCollider() { return cancel->GetCollider(); }

private:
	void Close();
	void PrintText();

private:
	Button* cancel;
	Quad* title;
	Quad* shadow;
};