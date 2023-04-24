#pragma once
class Grass : public ModelInstancing
{
	const UINT SIZE = 10;
public:
	Grass();
	~Grass();

	void Update();
	void Render();
	void GUIRender();

private:
	int instanceID = 0;
};