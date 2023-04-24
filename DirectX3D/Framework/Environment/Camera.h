#pragma once

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void GUIRender();

    void SetView();  

    Vector3 ScreenToWorld(Vector3 screenPos);
    Vector3 WorldToScreen(Vector3 worldPos);

    Ray ScreenPointToRay(Vector3 screenPoint);

    void TargetOptionSave(string file);
    void TargetOptionLoad(string file);

    bool ContainPoint(Vector3 point, float containValue);

    ViewBuffer* GetViewBuffer() { return viewBuffer; }
    void SetTavernScene(bool show) { isTavernScene = show; }

private:
    void FreeMode();

    void Frustum();

private:
    ViewBuffer* viewBuffer;
    Matrix view;
    Matrix projection;

    Vector3 planes[6];
    float a, b, c, d;

    float moveSpeed = 30.0f;
    float rotSpeed = 3.0f;

    Vector3 prevMousePos; 

    bool isTavernScene = true;

    float distance = 20.0f;
    float height = 20.0f;
    float moveDamping = 5.0f;
    float rotDamping = 1.0f;

    float rotY = 0;

    float destRot = 0.0f;
    Vector3 destPos;
    Vector3 focusOffset;

    bool isLookAtTargetX = true;
    bool isLookAtTargetY = true;

    Matrix rotMatrix;

    char file[128] = {};
};