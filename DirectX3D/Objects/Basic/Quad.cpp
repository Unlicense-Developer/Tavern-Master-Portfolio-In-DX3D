#include "Framework.h"

Quad::Quad(Vector2 size)
    : GameObject(L"Basic/Texture.hlsl"), size(size)
{
    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();

    colorBuffer = new ColorBuffer();
}

Quad::Quad(wstring file)
    : GameObject(L"Basic/Texture.hlsl")
{
    Texture* texture = Texture::Add(file);
    material->SetDiffuseMap(file);
    size = texture->GetSize();

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();

    colorBuffer = new ColorBuffer();
}


Quad::~Quad()
{    
    delete mesh;
    delete colorBuffer;
}

void Quad::Render()
{
    if (!Active()) return;

    SetRender();
    colorBuffer->SetPS(1);
    mesh->Draw();
}

void Quad::MakeMesh()
{
    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.emplace_back(left, top, 0, 0, 0);
    vertices.emplace_back(right, top, 0, 1, 0);
    vertices.emplace_back(left, bottom, 0, 0, 1);
    vertices.emplace_back(right, bottom, 0, 1, 1);

    vector<UINT>& indices = mesh->GetIndices();
    indices = { 0, 1, 2, 2, 1, 3 };
}