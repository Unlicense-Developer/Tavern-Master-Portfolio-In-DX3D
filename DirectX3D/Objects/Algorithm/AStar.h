#pragma once

class AStar
{
private:
    const Vector3 NODE_STARTPOS = { -99.5f, 0.0f, -99.5f };
    const Vector3 TAVERN_NODE_STARTPOS = { 38.5f, 0.0f, 3.5f };
    const Vector3 DOOR_NODEPOS = { 49.5f, 0, -2.0f };
    const int TAVERN_BASEWIDTH = 12;
    const int TAVERN_BASEHEIGHT = 16;

public:
    AStar(UINT width = 20, UINT height = 20);
    ~AStar();

    void Update();
    void Render();

    void SetNode(class Terrain* terrain);

    int FindCloseNode(Vector3 pos);
    int FindRandomPos(Vector3 pos, float range);

    void GetPath(IN int start, IN int end, OUT vector<Vector3>& path);
    vector<Node*>& GetNode() { return nodes; }
    void MakeDirectPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path);

    bool IsCollisionObstacle(Vector3 start, Vector3 end);

    void AddObstacle(Collider* collider);    

    void SetEdge();

    void GUIRender();

private:
    void Reset();

    float GetDiagonalManhattanDistance(int start, int end);

    void Extend(int center, int end);
    int GetMinNode();

    void AddTavernNode();

private:
    UINT width, height;
    Vector2 interval;

    Texture* pathMap;

    Terrain* terrain;

    vector<Node*> nodes;    
    Heap* heap;

    vector<Collider*> obstacles;
};