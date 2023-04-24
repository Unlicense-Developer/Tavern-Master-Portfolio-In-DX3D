#pragma once
class StartScene : public Scene
{
private:
	const Vector3 LOGO_POS = { 400, 500 };
	const string NEW_GAME = "새 게임";
	const string EXIT = "나가기";
public:
	StartScene();
	~StartScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	void PrintText();

	void FadeOut();
	void StartGame();
	void ExitGame();

	void LoopBgm();

private:
	Quad* bg;
	Quad* logo;
	Quad* fadeout;
	Button* start;
	Button* exit;
	Cursor* cursor;

	bool isFadeOut = false;

	int curBgmIndex = 1;
};