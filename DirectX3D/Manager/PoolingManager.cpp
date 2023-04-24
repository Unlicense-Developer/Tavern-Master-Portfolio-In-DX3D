#include "Framework.h"

PoolingManager::PoolingManager()
{
}

PoolingManager::~PoolingManager()
{
    for (pair<string, Objects> objects : totalObjects)
    {
        for (ModelAnimator* object : objects.second)
        {
            delete object;
        }

        objects.second.clear();
    }

    totalObjects.clear();
}

ModelAnimator* PoolingManager::Pop(string key)
{
    if (totalObjects.count(key) == 0)
        return nullptr;

    for (ModelAnimator* object : totalObjects[key])
    {
        if (!object->Active())
        {
            return object;
        }
    }

    return nullptr;
}

void PoolingManager::ClearObjects(string key)
{
    if (totalObjects.count(key) == 0)
        return;

    for (ModelAnimator* object : totalObjects[key])
    {
        delete object;
    }
    totalObjects[key].clear();

    totalObjects.erase(key);

}
