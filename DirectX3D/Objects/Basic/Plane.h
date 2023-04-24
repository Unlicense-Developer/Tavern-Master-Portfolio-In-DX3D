#pragma once
class Plane : public GameObject
{
private:
    typedef VertexUV VertexType;

    const float PLANE_YPOS = 0.01f;

public:
    Plane(Vector3 size = Vector3(4, 0, 4));
    ~Plane();

    void Update();
    void Render();

    BoxCollider* GetCollider() { return collider; }

private:
    void MakeMesh();

private:
    Vector3 size;

    Mesh<VertexType>* mesh;
    BoxCollider* collider;
};