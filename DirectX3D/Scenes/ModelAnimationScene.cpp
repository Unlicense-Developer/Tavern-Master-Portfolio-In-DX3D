#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
    modelAnimator = new ModelAnimator("Wizard");
    //modelAnimator->ReadClip("Walk");
    //modelAnimator->ReadClip("Standing_Idle");
    //modelAnimator->ReadClip("Carry");

}

ModelAnimationScene::~ModelAnimationScene()
{
    delete modelAnimator;
}

void ModelAnimationScene::Update()
{
    if (KEY_DOWN('1'))
        modelAnimator->PlayClip(0);
    if (KEY_DOWN('2'))
        modelAnimator->PlayClip(1);
    if (KEY_DOWN('3'))
        modelAnimator->PlayClip(2);
    if (KEY_DOWN('4'))
        modelAnimator->PlayClip(3);
    if (KEY_DOWN('5'))
        modelAnimator->PlayClip(4);
    if (KEY_DOWN('6'))
        modelAnimator->PlayClip(5);

    modelAnimator->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
    modelAnimator->Render();
}

void ModelAnimationScene::PostRender()
{
}

void ModelAnimationScene::GUIRender()
{
    modelAnimator->GUIRender();
}

void ModelAnimationScene::SetIdle()
{
    modelAnimator->PlayClip(0, 1.0f, 0.1f);
}
