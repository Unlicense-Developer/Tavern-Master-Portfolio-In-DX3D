#pragma once

class TavernManager : public Singleton<TavernManager> // 가게 관리 매니저
{
private:
	struct ChairData // 의자들의 정보
	{
		bool isAvailable = true;
		bool isDelivered = false;
		Vector3 chairPos;
		float sitAngle;
	};

	const int BEER_PRICE = 6;
	const int MAX_COUNTERBEER = 5;

	friend class Singleton;

	TavernManager();
	~TavernManager();

public:
	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	int& GetGold() { return gold; }
	int GetFame() { return fame; }

	void MakeBeverage(int chairIndex);
	void StartDeliver(int& deliverIndex);

	void ServeCounterBeer();
	void PayBeer(int deliverIndex);

	void AddChairData(Structure* chair);
	Vector3 GetFrontOrderPos();
	Vector3 GetRandomChairPos(int& chairIndex);
	float GetChairAngle(int chairIndex);
	void ClearChairSeat(int chairIndex);
	bool GetIsDelivered(int chairIndex);
	int GetCounterBeerNum() { return counterBeerNum; }
	int GetOrderSize() { return orderPriority.size(); }

private:
	LightBuffer::Light* lanternLight = nullptr;
	vector<ChairData> chairDatas;
	vector<Model*> counterTankards;
	Bartender* bartender;
	Waitress* waitress;

	Model* waterBarrel;
	Model* beerBarrel;

	queue<int> orderPriority;
	int counterBeerNum = 0;

	Vector3 lanternLight_Pos = { 43.1f, 2.3f, 1.1f };

	int lanternLightIndex;
	int gold = 1000;
	int fame = 0;
};