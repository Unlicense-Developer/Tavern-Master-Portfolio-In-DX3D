#include "Framework.h"

AStar::AStar(UINT width, UINT height)
    : width(width), height(height)
{
    heap = new Heap();

    pathMap = Texture::Add(L"Textures/AlphaMaps/TavernAlphaMap.png");
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;

    delete heap;
}

void AStar::Update()
{
    
}

void AStar::Render()
{
    for (Node* node : nodes)
    {
        node->Render();
    }
}

void AStar::SetNode(Terrain* terrain)
{
    this->terrain = terrain;

    vector<Float4> pixels;
    pathMap->ReadPixels(pixels);

    Vector2 size = terrain->GetSize();

    interval.x = size.x / width;
    interval.y = size.y / height;

    nodes.reserve((width + 1) * (height + 1));
    for (UINT z = 0; z < height; z++)
    {
        for (UINT x = 0; x < width; x++)
        {
            UINT index = width * z + x;

            Vector3 pos = Vector3(NODE_STARTPOS.x + x * interval.x, 0, -(NODE_STARTPOS.z + z * interval.y));

            if (pixels[index].x > 0)
            {
                nodes.push_back(new Node(pos, nodes.size()));
                nodes.back()->Scale() = { interval.x, 2.0f, interval.y };
                nodes.back()->UpdateWorld();
            }
        }
    }
    
    AddTavernNode();

    SetEdge();

}

int AStar::FindCloseNode(Vector3 pos)
{
    float minDist = FLT_MAX;

    int index = -1;

    for (UINT i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->state == Node::OBSTACLE)
            continue;

        float distance = Distance(pos, nodes[i]->GlobalPos());

        if (minDist > distance)
        {
            minDist = distance;
            index = i;
        }
    }

    return index;
}

int AStar::FindRandomPos(Vector3 pos, float range)
{
    vector<Node*> findNodes;

    for (Node* node : nodes)
    {
        float distance = Distance(pos, node->GlobalPos());

        if (distance < range)
        {
            findNodes.push_back(node);
        }
    }

    Node* findNode = findNodes[Random(0, findNodes.size())];

    return findNode->index;
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector3>& path)
{
    Reset();
    path.clear();

    //1. 시작노드 초기화하고 오픈노드에 추가
    float G = 0;
    float H = GetDiagonalManhattanDistance(start, end);

    nodes[start]->f = G + H;
    nodes[start]->g = G;
    nodes[start]->h = H;
    nodes[start]->via = start;

    nodes[start]->state = Node::OPEN;

    //openNodes.push_back(start);
    heap->Insert(nodes[start]);

    while (nodes[end]->state != Node::CLOSED)
    {
        //if (openNodes.empty())
        if(heap->Empty())
            return;

        //2. 오픈노드 중에서 효율이 가장 좋은 노드 찾기
        int curIndex = GetMinNode();
        //3. 찾은 노드와 연결된 노드의 정보 갱신후 오픈노드에 추가하고
        //확장이 끝난 노드는 닫기
        Extend(curIndex, end);
        nodes[curIndex]->state = Node::CLOSED;
    }

    //5. BackTracking
    int curIndex = end;

    while (curIndex != start)
    {
        nodes[curIndex]->state = Node::USING;
        path.push_back(nodes[curIndex]->GlobalPos());
        curIndex = nodes[curIndex]->via;
    }

    //path.push_back(nodes[start]->pos);
}

void AStar::MakeDirectPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path)
{
    int cutNodeNum = 0;
    Ray ray;
    ray.pos = start;

    FOR(path.size())
    {
        if (!IsCollisionObstacle(start, path[i]))
        {
            cutNodeNum = path.size() - i - 1;
            break;
        }
    }

    FOR(cutNodeNum)
        path.pop_back();

    cutNodeNum = 0;
    ray.pos = end;

    FOR(path.size())
    {
        if (!IsCollisionObstacle(end, path[path.size() - i - 1]))
        {
            cutNodeNum = path.size() - i - 1;
            break;
        }
    }

    FOR(cutNodeNum)
        path.erase(path.begin());
}

bool AStar::IsCollisionObstacle(Vector3 start, Vector3 end)
{
    Ray ray(start, (end - start).GetNormalized());
    float distance = Distance(start, end);

    Contact contact;

    for (Collider* obstacle : obstacles)
    {        
        if (obstacle->IsRayCollision(ray, &contact))
        {
            if (contact.distance < distance)
            {
                return true;
            }
        }
    }

    return false;
}

void AStar::AddObstacle(Collider* collider)
{
    obstacles.push_back(collider);
}

void AStar::GUIRender()
{
    for (Node* node : nodes)
        node->GUIRender();
}

void AStar::Reset()
{
    for (Node* node : nodes)
    {
        if ( node->state == Node::OBSTACLE ) continue;

            node->state = Node::NONE;
    }

    heap->Clear();
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    Vector3 startPos = nodes[start]->GlobalPos();
    Vector3 endPos = nodes[end]->GlobalPos();

    Vector3 temp = endPos - startPos;

    float x = abs(temp.x);
    float z = abs(temp.z);

    float maxSize = max(x, z);
    float minSize = min(x, z);

    return (maxSize - minSize) + sqrt(minSize * minSize * 2);
}

void AStar::Extend(int center, int end)
{
    for (Node::Edge* edge : nodes[center]->edges)
    {
        int index = edge->index;

        if (nodes[index]->state == Node::CLOSED)
            continue;
        if (nodes[index]->state == Node::OBSTACLE)
            continue;

        float G = nodes[center]->g + edge->cost;
        float H = GetDiagonalManhattanDistance(index, end);
        float F = G + H;

        if (nodes[index]->state == Node::OPEN)
        {
            if (F < nodes[index]->f)
            {
                nodes[index]->g = G;
                nodes[index]->f = F;
                nodes[index]->via = center;
            }
        }
        else if(nodes[index]->state == Node:: NONE)
        {
            nodes[index]->g = G;
            nodes[index]->h = H;
            nodes[index]->f = F;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN;

            //openNodes.push_back(index);
            heap->Insert(nodes[index]);
        }
    }
}

int AStar::GetMinNode()
{
    return heap->DeleteRoot()->index;
}

void AStar::AddTavernNode() // 주점 안 노드 설치
{
    Vector2 size = terrain->GetSize();

    interval.x = size.x / width;
    interval.y = size.y / height;

    nodes.reserve( TAVERN_BASEWIDTH * TAVERN_BASEHEIGHT);
    for (UINT z = 0; z < TAVERN_BASEHEIGHT; z++)
    {
        for (UINT x = 0; x < TAVERN_BASEWIDTH; x++)
        {
            Vector3 pos = Vector3(TAVERN_NODE_STARTPOS.x + x * interval.x, 0, TAVERN_NODE_STARTPOS.z - z * interval.y);

            if (pos.x == DOOR_NODEPOS.x && pos.z <= -0.5f && pos.z >= -3.5f) continue;

            nodes.push_back(new Node(pos, nodes.size()));
            nodes.back()->Scale() = { interval.x, 2.0f, interval.y };
            nodes.back()->UpdateWorld();
            
        }
    }

    Vector3 pos = DOOR_NODEPOS; // 문 노드

    nodes.push_back(new Node(pos, nodes.size()));
    nodes.back()->Scale() = { interval.x, 2.0f, interval.y };
    nodes.back()->UpdateWorld();
}

void AStar::SetEdge() // 노드 연결
{
    for (UINT i = 0; i < nodes.size(); i++)
    {
        for (Node* node : nodes)
        {
            if (nodes[i] == node) continue;

            if (abs(node->Pos().x - nodes[i]->Pos().x) == node->GetSize().x &&
                abs(node->Pos().z - nodes[i]->Pos().z) <= node->GetSize().z) // 좌 우 노드 연결 && 대각선 노드 연결
            {
                node->AddEdge(nodes[i]);
                continue;
            }

            if (abs(node->Pos().x - nodes[i]->Pos().x) < node->GetSize().x &&
                abs(node->Pos().z - nodes[i]->Pos().z) == node->GetSize().z) // 위 아래 노드 연결
            {
                node->AddEdge(nodes[i]);
                continue;
            }
        }
    }
}
