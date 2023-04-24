#pragma once
class Candle : public Structure
{
private:
	const Float4 CANDLELIGHT_COLOR = { 1.0f, 0.4f, 0.0f, 1.0f };
	const float LIGHT_RANGE = 10.0f;

public:
	Candle(string name);
	~Candle();

	void Update();
	void Render();
	void GUIRender();

	int GetCandleIndex() { return candleLightIndex; }

private:
	LightBuffer::Light* candleLight = nullptr;
	Sprite* candleFlame;
	Vector3 flamePos = {};
	float flameTime;
	int candleLightIndex;
};