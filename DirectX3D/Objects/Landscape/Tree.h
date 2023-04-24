#pragma once
class Tree : public ModelInstancing
{
	const UINT SIZE = 500;
public:
	Tree();
	~Tree();

    void Update();
    void Render();
	void GUIRender();

private:
	int instanceID = 0;
};