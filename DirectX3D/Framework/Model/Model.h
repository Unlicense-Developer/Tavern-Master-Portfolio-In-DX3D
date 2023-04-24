#pragma once

class Model : public Transform
{
public:
    Model(string name);
    ~Model();

    void Render();
    void GUIRender();

    void SetShader(wstring file);

    string GetName() { return name; }
    Material* GetMaterial() { return materials[0]; }

protected:
    void ReadMaterial();
    void ReadMesh();

protected:
    string name;

    vector<Material*> materials;
    vector<ModelMesh*> meshes;
    vector<NodeData> nodes;
    vector<BoneData> bones;

    map<string, UINT> boneMap;

    WorldBuffer* worldBuffer;
};