#pragma once
class Waitress : public ModelAnimator
{
private:
	const Vector3 IDLE_POS = { 41, 0, 1 };
private:
	enum State
	{
		WALK, IDLE, CARRY,
	};

public:
	Waitress();
	~Waitress();

	void Update();
	void Render();
	void GUIRender();

private:
	void Move();
	void Rotate();
	void Carry();
	void CheckBeer();
	void CompleteDeliver();
	void SetAnimation();

	void SetState(State state);
	void SetDestination();

private:
	Transform* plateTransform;
	Model* plate;
	Model* tankard;

	float moveSpeed = 4.0f;
	float rotSpeed = 10.0f;

	int deliverIndex = 0;
	bool isDelivering = false;

	Vector3 velocity = { 0, 0, 0 };
	Vector3 destPos;
	vector<Vector3> path;

	State curState;
};