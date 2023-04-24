#include "Framework.h"

#include "Scenes/GridScene.h"
#include "Scenes/ModelExportScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ModelAnimationScene.h"
#include "Scenes/StartScene.h"
#include "Scenes/TavernScene.h"
#include "Scenes/TerrainEditorScene.h"

GameManager::GameManager()
{
    srand(time(NULL));
    Create();
    CreateBgm();

    //SceneManager::Get()->Create("Grid", new GridScene());
    //SceneManager::Get()->Create("ModelExport", new ModelExportScene());
    //SceneManager::Get()->Create("Start", new ModelRenderScene());
    //SceneManager::Get()->Create("Start", new ModelAnimationScene());
    //SceneManager::Get()->Create("Start", new TerrainEditorScene());
    SceneManager::Get()->Create("Start", new StartScene());
    SceneManager::Get()->Create("Tavern", new TavernScene());


    //SceneManager::Get()->Add("Grid");    
    //SceneManager::Get()->Add("Tavern");
    SceneManager::Get()->Add("Start");
}

GameManager::~GameManager()
{
    Delete(); 
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();    
    Audio::Get()->Update();

    Environment::Get()->Update();

    SceneManager::Get()->Update();
}

void GameManager::Render()
{
    SceneManager::Get()->PreRender();
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();
    
    Environment::Get()->Set();    
    SceneManager::Get()->Render();
    
    Environment::Get()->PostSet();
    SceneManager::Get()->PostRender();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
   /* string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    Font::Get()->RenderText(fps, { 300, 20 });*/
    
    static bool isActive = false;

    if (isActive)
    {
        ImGui::Begin("Inspector", &isActive);
        Environment::Get()->GUIRender();
        SceneManager::Get()->GUIRender();
        ImGui::End();
    }    

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    
    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();
    Audio::Get();
    
    Font::Get()->AddColor("Gray", 0.68, 0.68, 0.68);
    Font::Get()->AddColor("White", 1.0, 1.0, 1.0);
    Font::Get()->AddColor("Yellow", 1.0, 0.81, 0.0);
    Font::Get()->AddColor("Brown", 0.21, 0.16, 0.11);
    Font::Get()->AddStyle("30", L"배달의민족 연성", 30.0f);
    Font::Get()->AddStyle("40", L"배달의민족 연성", 40.0f);
    Font::Get()->AddStyle("50", L"배달의민족 연성", 50.0f);
    
    Font::Get()->SetColor("Gray");
    Font::Get()->SetStyle("40");

    Texture::Add(L"Textures/Color/White.png");
    
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();
    Audio::Delete();
    SceneManager::Delete();
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    
    ImGui::DestroyContext();
}

void GameManager::CreateBgm()
{
    Audio::Get()->Add("Bgm 1", "Sounds/Bgm 1.wav", true, true);
    Audio::Get()->Add("Bgm 2", "Sounds/Bgm 2.wav", true, true);
    Audio::Get()->Add("Bgm 3", "Sounds/Bgm 3.wav", true, true);
    Audio::Get()->Add("Bgm 4", "Sounds/Bgm 4.wav", true, true);
    Audio::Get()->Add("Bgm 5", "Sounds/Bgm 5.wav", true, true);
}
