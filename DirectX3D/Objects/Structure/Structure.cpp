#include "Framework.h"
#include "Structure.h"

Structure::Structure(string name)
	:Model(name)
{
    collider = new BoxCollider();
    collider->SetTag(name + "_Collider");
    collider->SetParent(this);
    collider->Load();

    SetType();

    colorBuffer = new ColorBuffer();
}

Structure::~Structure()
{
    delete collider;
    delete colorBuffer;
}

void Structure::Update()
{
    if (!Active()) return;

    UpdateWorld();
    collider->UpdateWorld();
}

void Structure::Render()
{
    colorBuffer->SetPS(1);

    Model::Render();
    //collider->Render();
}

void Structure::GUIRender()
{
    Model::GUIRender();
    collider->GUIRender();
}

void Structure::ReGenerate(string name)
{ 
    this->name = name;
    SetTag(name);

    materials.clear();
    meshes.clear();

    ReadMaterial();
    ReadMesh();

    collider->SetTag(name + "_Collider");
    collider->Load();

    SetType();
}

void Structure::SetType() // 구조물 타입 세팅
{
    if (name == "Pilar")
        type == PILAR;
    else if (name.substr(name.rfind("_") + 1) == "Candle")
        type = CANDLE;
    else if (name.substr(0, name.find("_")) == "Wall")
        type = WALL;
    else if (name.rfind("_") == string::npos)
        type = OTHER;
    else if (name.substr(name.rfind("_") + 1) == "Chair1")
        type = CHAIR1;
    else if (name.substr(name.rfind("_") + 1) == "Chair2")
        type = CHAIR2;
    else if (name.substr(0, name.find("_")) == "Table")
        type = TABLE;
    else
        type = OTHER;
}

void Structure::ChangeNodeState()
{
    collider->UpdateWorld();

    vector<Node*>& nodes = PathManager::Get()->GetAStar()->GetNode();

    for (vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
    {
        if (collider->IsBoxCollision(*iter))
        {
            Node* node = *iter;

            if(type == TABLE)
                node->SetState(Node::OBSTACLE);
        }
    }
}
