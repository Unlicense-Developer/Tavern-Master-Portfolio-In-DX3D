#pragma once
class UIManager : public Singleton<UIManager>
{
private:
    friend class Singleton;

    UIManager();
    ~UIManager();

public:
    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    void SetTerrain(Terrain* terrain)
    {
        structureEditor->SetTerrain(terrain);
        floorEditor->SetTerrain(terrain);
    }

    StructureEditor* GetStructureEditor() { return structureEditor; }
    FloorEditor* GetFloorEditor() { return floorEditor; }

private:
    StructureEditor* structureEditor;
    FloorEditor* floorEditor;
    Grid* grid;
    Menu* menu;
    Cursor* cursor;
};