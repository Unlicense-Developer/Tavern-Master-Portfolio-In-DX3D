#include "Framework.h"

Plane::Plane(Vector3 size)
    : GameObject(L"Basic/Texture.hlsl"), size(size)
{
    tag = "Plane";

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();

    collider = new BoxCollider(size);
    collider->SetParent(this);
    collider->UpdateWorld();

    material->SetDiffuseMap(L"Textures/Floor/Wood.png");;
}

Plane::~Plane()
{
    delete mesh;
    delete collider;
}

void Plane::Update()
{
    if (!Active()) return;

    UpdateWorld();
    collider->UpdateWorld();
}

void Plane::Render()
{
    if (!Active()) return;

    SetRender();

    mesh->Draw();

    //collider->Render();
}

void Plane::MakeMesh()
{
    Vector3 halfSize = size * 0.5f;

    vector<VertexType>& vertices = mesh->GetVertices();
    //Front
    vertices.emplace_back(-halfSize.x, PLANE_YPOS, -halfSize.z, 0, 1);
    vertices.emplace_back(-halfSize.x, PLANE_YPOS, +halfSize.z, 0, 0);
    vertices.emplace_back(+halfSize.x, PLANE_YPOS, -halfSize.z, 1, 1);
    vertices.emplace_back(+halfSize.x, PLANE_YPOS, +halfSize.z, 1, 0);

    vector<UINT>& indices = mesh->GetIndices();
    indices = {
        //Front
        0, 1, 2, 2, 1, 3,
    };
}
