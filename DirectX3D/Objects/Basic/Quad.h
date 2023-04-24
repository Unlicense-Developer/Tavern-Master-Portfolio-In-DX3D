#pragma once

class Quad : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    Quad(Vector2 size);    
    Quad(wstring file);
    ~Quad();

    void Render();

    Float4& GetColor() { return colorBuffer->Get(); }

private:
    void MakeMesh();

protected:
    Vector2 size;

    Mesh<VertexType>* mesh;    

    ColorBuffer* colorBuffer = nullptr;
};