#include "Framework.h"

RectCollider::RectCollider(Vector2 size)
    : size(size)
{
    MakeMesh();
    mesh->CreateMesh();
}

bool RectCollider::IsPointCollision(Vector2 point)
{
    Matrix invWorld = XMMatrixInverse(nullptr, world);

    point *= invWorld;

    Vector2 half = size * 0.5f;

    return abs(point.x) < half.x && abs(point.y) < half.y;
}


//bool RectCollider::IsPointCollision(Vector2 point)
//{
//    ObbDesc obb = GetObb();
//
//    Vector2 direction = obb.position - point;
//
//    float d = abs(Dot(direction, obb.axis[0]));
//
//    if (d > obb.halfSize.x) return false;
//
//    d = abs(Dot(direction, obb.axis[1]));
//
//    if (d > obb.halfSize.y) return false;
//
//    return true;
//}

Vector2 RectCollider::LeftTop()
{
    Vector2 edge = Vector2(-size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 edge = Vector2(-size.x, -size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 edge = Vector2(+size.x, +size.y) * 0.5f;

    return edge * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 edge = Vector2(+size.x, -size.y) * 0.5f;

    return edge * world;
}

float RectCollider::L()
{
    float minLeft = min(LeftTop().x, LeftBottom().x);
    float minRight = min(RightTop().x, RightBottom().x);

    return min(minLeft, minRight);
}

float RectCollider::R()
{
    float maxLeft = max(LeftTop().x, LeftBottom().x);
    float maxRight = max(RightTop().x, RightBottom().x);

    return max(maxLeft, maxRight);
}

float RectCollider::T()
{
    float maxTop = max(LeftTop().y, RightTop().y);
    float maxBottom = max(LeftBottom().y, RightBottom().y);

    return max(maxTop, maxBottom);
}

float RectCollider::B()
{
    float minTop = min(LeftTop().y, RightTop().y);
    float minBottom = min(LeftBottom().y, RightBottom().y);

    return min(minTop, minBottom);
}

RectCollider::ObbDesc RectCollider::GetObb()
{
    obbDesc.position = Vector2(GlobalPos().x, GlobalPos().y);
    obbDesc.halfSize = Half();

    obbDesc.axis[0] = Vector2(Right().x, Right().y);
    obbDesc.axis[1] = Vector2(Up().x, Up().y);

    return obbDesc;
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    Vector2 halfSize = Size() * 0.5f;    

    float minRight = min(R(), rect->R());
    float maxLeft = max(L(), rect->L());
    float minTop = min(T(), rect->T());
    float maxBottom = max(B(), rect->B());

    overlap->x = minRight - maxLeft;
    overlap->y = minTop - maxBottom;

    if (overlap->x > 0 && overlap->y > 0)
        return true;

    return false;
}

bool RectCollider::IsOBB(RectCollider* rect)
{
    ObbDesc obbA = GetObb();
    ObbDesc obbB = rect->GetObb();

    if (IsSeperate(obbA.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbA.axis[1], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[1], obbA, obbB)) return false;

    return true;
}

bool RectCollider::IsSeperate(Vector2 sperateAxis, ObbDesc box1, ObbDesc box2)
{
    float d = abs(Dot(sperateAxis, box1.position - box2.position));

    Vector2 right = box1.axis[0] * box1.halfSize.x;
    Vector2 up = box1.axis[1] * box1.halfSize.y;

    float a = abs(Dot(sperateAxis, right)) + abs(Dot(sperateAxis, up));

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float b = abs(Dot(sperateAxis, right)) + abs(Dot(sperateAxis, up));

    return d > (a + b);
}

void RectCollider::MakeMesh()
{
    type = Type::RECT;

    Vector2 halfSize = size * 0.5f;

    vector<Vertex>& vertices = mesh->GetVertices();

    vertices.emplace_back(-halfSize.x, +halfSize.y, 0.0f);
    vertices.emplace_back(+halfSize.x, +halfSize.y, 0.0f);
    vertices.emplace_back(+halfSize.x, -halfSize.y, 0.0f);
    vertices.emplace_back(-halfSize.x, -halfSize.y, 0.0f);
    vertices.emplace_back(-halfSize.x, +halfSize.y, 0.0f);
}
