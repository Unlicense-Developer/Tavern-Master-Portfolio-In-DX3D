#pragma once
class Bartender : public ModelAnimator
{
private:
	const Vector3 IDLE_POS = { 43.0f, 0.0f, 2.0f };
	const Vector3 BEER_POS = { 47.0f, 0.0f, 2.0f };
	const float MAKING_TIME = 2.0f;

private:
	enum State
	{
		WALK, IDLE, CARRY
	};
	
public:
	Bartender();
	~Bartender();

	void Update();
	void Render();
	void GUIRender();

	void MakeBeer();

private:
	void Move();
	void Rotate();
	void DeliverToCounter();
	void CheckMakeTime();
	
	void SetAnimation();

	void SetState(State state);
	void SetDestination();

private:
	Transform* tankardTransform;
	Model* tankard;

	float moveSpeed = 4.0f;
	float rotSpeed = 10.0f;
	float time = 0.0f;

	bool isCarry = false;

	Vector3 velocity = { 0, 0, 0 };
	Vector3 destPos;
	vector<Vector3> path;

	State curState;

};