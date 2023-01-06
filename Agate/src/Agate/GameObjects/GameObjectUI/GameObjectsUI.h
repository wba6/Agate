//
// Created by William Aey on 12/20/2022.
//

#ifndef AGATE_GAMEOBJECTSUI_H
#define AGATE_GAMEOBJECTSUI_H
#include "Agate/Core/Layer.h"
namespace Agate
{
    class GameObject;
    class GameObjectsUI : public Layer {
    public:
        GameObjectsUI();
        static void AddObject(GameObject *go);
        void OnRender() override;

    private:
        static std::vector<GameObject *> m_gameobjects;
    };
}// namespace Agate

#endif//AGATE_GAMEOBJECTSUI_H
