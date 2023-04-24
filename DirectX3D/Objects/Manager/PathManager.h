#pragma once
class PathManager : public Singleton<PathManager>
{
private:
	friend class Singleton;

	PathManager();
	~PathManager();

public:
	void Update();
	void Render();

	AStar* GetAStar() { return aStar; }
	void SetPath(Terrain* terrain) { aStar->SetNode(terrain); }

private:
	AStar* aStar;
};