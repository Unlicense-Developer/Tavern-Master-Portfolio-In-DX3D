#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    test1 = new Model("Sofa_Chair2");
    //test2 = new Model("Chair2");

    //candle = new Candle();

    //waitress = new Waitress();
    //bartender = new Bartender();
}

ModelRenderScene::~ModelRenderScene()
{
    delete test1;
    //delete test2;
    //delete candle;
    //delete waitress;
    //delete bartender;
}

void ModelRenderScene::Update()
{
    test1->UpdateWorld();
    //test1->GetCollider()->UpdateWorld();
    //test2->UpdateWorld();
    //waitress->Update();
    //bartender->Update();

    //candle->Update();
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    test1->Render();
    //test2->Render();
    //candle->Render();
    //waitress->Render();
    //bartender->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    test1->GUIRender();
   // test2->GUIRender();
   // waitress->GUIRender();
    //bartender->GUIRender();
}
