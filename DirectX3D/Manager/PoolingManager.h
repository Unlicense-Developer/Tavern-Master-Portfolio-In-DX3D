#pragma once

class PoolingManager
{
public:
    PoolingManager();
    ~PoolingManager();

    virtual void Update() {};
    virtual void Render() {};

    ModelAnimator* Pop(string key);

    virtual void CreateObjects(string key, UINT poolSize) {};

    void ClearObjects(string key);

protected:
    typedef vector<ModelAnimator*> Objects;
    map<string, Objects> totalObjects;
};