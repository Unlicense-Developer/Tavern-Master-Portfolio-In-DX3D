#pragma once

class CustomerManager : public Singleton<CustomerManager>
{
private:
	const UINT SIZE = 10;
	const float SPAWN_TIME = 3.0f;
	friend class Singleton;

	CustomerManager();
	~CustomerManager();

public:
	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	void Spawn();

private:
	ModelAnimatorInstancing* blacksmithInstancing;
	ModelAnimatorInstancing* fortunetellerInstancing;
	ModelAnimatorInstancing* peasant_MaleInstancing;
	ModelAnimatorInstancing* peasant_FemaleInstancing;
	ModelAnimatorInstancing* riderInstancing;
	ModelAnimatorInstancing* wizardInstancing;

	vector<Customer*> customers;

	float time = 0.0f;
};