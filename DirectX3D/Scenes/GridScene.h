#pragma once

class GridScene : public Scene
{
private:
    const int MAX_VALUE = 200;

public:
    GridScene();
    ~GridScene();
        
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

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

    Skybox* skybox;
};