#pragma once
class Grid
{
private:
    const int MAX_VALUE = 200;
    const float BASE_HEIGHT = 0.02;

public:
    Grid();
    ~Grid();

    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

    void ToggleGrid();

private:
    void MakeMesh();

private:
    Material* material;
    Mesh<VertexColor>* mesh;

    bool isActive = true;

    UINT curWidth, curHeight;
    UINT fixWidth, fixHeight;

    MatrixBuffer* worldBuffer;

    Vector3 baseGridColor = { 0.7f, 0.7f, 0.7f };
    Vector3 fourBaseGridColor = { 1.0f, 1.0f, 1.0f };
    Vector3 fixGridColor = { 0.5f, 0.5f, 0.5f };
};