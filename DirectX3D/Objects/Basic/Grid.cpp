#include "Framework.h"

Grid::Grid()
    : curWidth(MAX_VALUE), curHeight(MAX_VALUE),
    fixWidth(MAX_VALUE), fixHeight(MAX_VALUE)
{
    material = new Material(L"Basic/Grid.hlsl");

    mesh = new Mesh<VertexColor>();
    MakeMesh();
    mesh->CreateMesh();

    worldBuffer = new MatrixBuffer();
}

Grid::~Grid()
{
    delete material;
    delete mesh;
    delete worldBuffer;

}

void Grid::Update()
{
    ToggleGrid();

    bool check = false;
    check |= (curWidth != fixWidth || curHeight != fixHeight);
    check |= (baseGridColor != fixGridColor);

    if (!check) return;

    fixWidth = curWidth;
    fixHeight = curHeight;

    fixGridColor = baseGridColor;

    MakeMesh();
    mesh->UpdateVertex();
}

void Grid::PreRender()
{
}

void Grid::Render()
{
    if (!isActive) return;

    worldBuffer->SetVS(0);

    material->Set();
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void Grid::PostRender()
{
}

void Grid::GUIRender()
{
    if (ImGui::TreeNode("GridOption"))
    {
        ImGui::DragInt("Width", (int*)&curWidth, 1, 0, MAX_VALUE);
        ImGui::DragInt("Height", (int*)&curHeight, 1, 0, MAX_VALUE);

        ImGui::ColorEdit3("GridColor", (float*)&baseGridColor);

        ImGui::TreePop();
    }
}

void Grid::ToggleGrid()
{
    if (KEY_DOWN(VK_F3))
        isActive = !isActive;
}

void Grid::MakeMesh()
{
    vector<VertexColor>& vertices = mesh->GetVertices();
    vertices.clear();
    //Axis X
    vertices.emplace_back(-MAX_VALUE, BASE_HEIGHT, 0, 1, 0, 0);
    vertices.emplace_back(+MAX_VALUE, BASE_HEIGHT, 0, 1, 0, 0);

    //Axis Y
    vertices.emplace_back(0, -MAX_VALUE, 0, 0, 1, 1);
    vertices.emplace_back(0, +MAX_VALUE, 0, 0, 1, 1);

    //Axis Z
    vertices.emplace_back(0, BASE_HEIGHT, -MAX_VALUE, 0, 0, 1);
    vertices.emplace_back(0, BASE_HEIGHT, +MAX_VALUE, 0, 0, 1);

    int halfW = ( curWidth / 2 );
    int halfH = ( curHeight / 2 );

    for (int x = -halfW; x < halfW; x++)
    {
        if (x == 0) continue;

        if (x % 4 == 0)
        {
            vertices.emplace_back(x, BASE_HEIGHT, -halfH, fourBaseGridColor.x, fourBaseGridColor.y, fourBaseGridColor.z);
            vertices.emplace_back(x, BASE_HEIGHT, +halfH - 1, fourBaseGridColor.x, fourBaseGridColor.y, fourBaseGridColor.z);
        }
        else
        {
            vertices.emplace_back(x, BASE_HEIGHT, -halfH, baseGridColor.x, baseGridColor.y, baseGridColor.z);
            vertices.emplace_back(x, BASE_HEIGHT, +halfH - 1, baseGridColor.x, baseGridColor.y, baseGridColor.z);
        }
    }

    for (int z = -halfH; z < halfH; z++)
    {
        if (z == 0) continue;

        if (z % 4 == 0)
        {
            vertices.emplace_back(-halfW, BASE_HEIGHT, z, fourBaseGridColor.x, fourBaseGridColor.y, fourBaseGridColor.z);
            vertices.emplace_back(+halfW - 1, BASE_HEIGHT, z, fourBaseGridColor.x, fourBaseGridColor.y, fourBaseGridColor.z);
        }
        else
        {
            vertices.emplace_back(-halfW, BASE_HEIGHT, z, baseGridColor.x, baseGridColor.y, baseGridColor.z);
            vertices.emplace_back(+halfW - 1, BASE_HEIGHT, z, baseGridColor.x, baseGridColor.y, baseGridColor.z);
        }
    }
}