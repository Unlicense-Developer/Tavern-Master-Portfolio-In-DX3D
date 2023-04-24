#pragma once
class TavernScene : public Scene
{
public:
	TavernScene();
	~TavernScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	void CreateSounds();
	void LoopBgm();

private:
	Terrain* terrain;
	Skybox* skybox;
	Water* water;
	Tree* trees;
	Grass* grass;
	Rock* rock1;

	Model* bridge;
	Stonefence* stonefence;
	
	Waitress* waitress;
	Bartender* bartender;

	int curBgmIndex = 1;
};