#pragma once
class Rock : public ModelInstancing
{
	const UINT SIZE = 10;
public:
	Rock(string name);
	~Rock();

	void Update();
	void Render();
	void GUIRender();

private:
	int instanceID = 0;
};