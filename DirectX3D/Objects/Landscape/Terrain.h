#pragma once

class Terrain : public GameObject
{
private:
    class RayBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Float3 pos;
            UINT triangleSize;

            Float3 dir;
            float padding;
        };

    public:
        RayBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }

        Data& Get() { return data; }

    private:
        Data data;
    };

    struct InputDesc
    {
        Float3 v0, v1, v2;
    };

    struct OutputDesc
    {
        int picked;
        float distance;
    };

    typedef VertexUVNormalTangent VertexType;
    const float MAX_HEIGHT = -20.0f;
    const UINT TERRAIN_WIDTH = 200;
    const UINT TERRAIN_HEIGHT = 200;
    const Vector3 TERRAIN_STARTPOS = { -100.0f, 0.0f, -100.0f };

public:
    Terrain();
    //Terrain(string mapFile);
    ~Terrain();

    void Render();
    void RenderInstanced(UINT instanceCount);

    float GetHeight(const Vector3& pos, Vector3* normal = nullptr);

    Vector3 Picking();
    bool ComputePicking(Vector3& pos);

    Vector2 GetSize() { return Vector2(width, height); }

private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();
    void MakeComputeData();

private:
    UINT width, height;

    Mesh<VertexType>* mesh;

    Texture* heightMap;
    Texture* alphaMap;
    Texture* secondMap;
    Texture* thirdMap;

    RayBuffer* rayBuffer;

    vector<InputDesc> inputs;
    vector<OutputDesc> outputs;

    UINT triangleSize;
    StructuredBuffer* structuredBuffer;
    ComputeShader* computeShader;
};