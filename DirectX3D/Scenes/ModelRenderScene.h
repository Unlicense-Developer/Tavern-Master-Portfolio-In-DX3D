#pragma once

class ModelRenderScene : public Scene
{
public:
    ModelRenderScene();
    ~ModelRenderScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Model* test1;
    Model* test2;
    Candle* candle;
    Bartender* bartender;
    Waitress* waitress;
};