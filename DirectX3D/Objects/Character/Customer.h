#pragma once

enum Way
{
	UP, DOWN, TAVERN
};

class Customer
{
private:

	enum State
	{
		WALK, SIT, ORDER, DRINK, SITTING_IDLE, STAND,
	};

	const Vector3 UP_START = { -96.0f, 0, -24.0f };
	const Vector3 DOWN_START = { 85.0f, 0, -98.0f };
	const Vector3 TEST_CHAIR = { 45.5f, 0, -8.5f };
	const float WAIT_TIME = 5.0f;

public:
	Customer(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~Customer();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	void Spawn();

	void SetWay(Way way) { this->way = way; }

	Transform* GetTransform() { return transform; }

private:
	void SetDestination();
	void UpdatePayGold();

	void SetEvent(int clip, Event event, float timeRatio = 1.0f);
	void ExcuteEvent();

	void PlayEndEvent();

	void SetState(State state);

	void Move();
	void Rotate();

	void Sit();
	void Order();
	void Drink();
	void Stand();

	void Remove();
	void PrintPayGold();

private:
	Transform* transform;
	Transform* rightHand;
	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Model* tankard;
	Quad* payGold;

	Vector3 payGoldPos;
	float payGold_YValue = 0.0f;

	Way way;
	float moveSpeed = 4.0f;
	float rotSpeed = 10.0f;

	Vector3 velocity;
	Vector3 destPos;
	vector<Vector3> path;

	UINT index;
	State curState = WALK;

	int chairIndex = 0;

	float waitTime = 0.0f;
	bool isSit = false;
	bool isOrdered = false;
	bool isDrink = false;

	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;
};