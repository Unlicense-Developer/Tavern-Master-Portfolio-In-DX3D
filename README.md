# 🍺 Tavern Master
[![image](https://github.com/user-attachments/assets/cfecebdb-d354-4037-85e1-e4a62f6bcac6)](https://youtu.be/vMxOww6r8Fg?si=9fadFGcezjWTjN3U)
* **개발 기간** : 2023. 03. 17 ~ 2023. 04. 13 / 28일
* **게임 장르** : 주점 운영 시뮬레이션
* **개발 인원** : 1인
* **핵심 기술** : DirectX11, FMOD, ImGui, Assimp, DXTex
* **Notion** : https://www.notion.so/unlicense-developer/Tavern-Master-0334d8f27eff43088a3c552df1c47f27?pvs=4
<br/>

# 📕 Content
* Assimp를 사용하여 fbx, obj파일의 material, mesh, animation 정보를 추출하여 Binary 데이터 입출력 사용
* 마우스 Picking으로 얻은 좌표를 Texture로 저장하여 게임맵의 Save, Load 구현
* 주점을 커스텀할 수 있는 Structure Editor 구현
* 캐릭터의 이동은 A* 알고리즘 사용
* Shader 코딩을 통해 Candle에 Point Light를 구현
* 주점을 방문하는 손님이나 나무, 돌, 풀 등등 여러개를 출력해야하는 클래스는 Instancing 기법을 사용하여 최적화
* Rasterizer State에서 Skybox 텍스처로 맵을 둘러싸는 Skybox를 구현
* 반사, 굴절을 이용해 물에 반사되는 오브젝트를 바라보는 카메라를 추가하여 Water 구현
