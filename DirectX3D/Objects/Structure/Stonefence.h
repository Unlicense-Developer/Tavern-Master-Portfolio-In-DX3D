#pragma once
class Stonefence
{
	const Vector3 OFFSET_LEFTFIRE = {1.0f, 1.6f, -0.1f};
	const Vector3 OFFSET_RIGHTFIRE = {1.0f, 1.6f, 0.6f};
public:
	Stonefence();
	~Stonefence();

	void Update();
	void Render();
	void GUIRender();

private:
	Model* leftFence;
	Model* rightFence;

	Sprite* leftFire;
	Sprite* rightFire;
};