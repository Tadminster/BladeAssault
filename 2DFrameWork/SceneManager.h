#pragma once
class SceneManager :public Singleton<SceneManager>
{
private:
    bool                    isChanging = false;
    Scene *                 nextScene = nullptr;
    Scene *                 currentScene = nullptr;
    map<string, Scene*>    scenes;

    float changingTime = 0.0f;

    string                  currentSceneKey = "";
public:
    ~SceneManager();

    //�� �߰�
    bool    AddScene(string key, Scene * value);
    //�� ����
    bool    DeleteScene(string key);
    //�� ����
    Scene * ChangeScene(string key, float changingTime = 0.0f);
    //�� ��������
    Scene * GetScene(string key);
    //���� �� ��������
    Scene * GetCurrentScene();
    //���� �� key ����
    string&  GetCurrentSceneKey() { return currentSceneKey; };

    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    ResizeScreen();
};

