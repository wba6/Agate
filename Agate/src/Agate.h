#pragma once

#include "Agate/Core/EntryPoint.h"
#include "Agate/Core/Logger.h"

#include "Agate/Events/ApplicationEvents.h"
#include "Agate/Events/Event.h"
#include "Agate/Events/MouseEvent.h"

#include "Agate/Core/Layer.h"

//------------main-------------
#include "../vender/imgui/imgui.h"
#include "Agate/Core/Main.h"

//-----------------------------

//-----------keycodes------------
#include "Agate/Core/keyCodes.h"

//--------glm------------------
#include <../vender/glm/glm/glm.hpp>
#include <../vender/glm/glm/gtc/matrix_transform.hpp>
#include <../vender/glm/glm/gtc/type_ptr.hpp>

//-----------Rendering---------
#include "Agate/Rendering/mock/IndexBufferUser.hpp"
#include "Agate/Rendering/mock/VertexArrayUser.hpp"
#include "Agate/Rendering/mock/ShaderUser.hpp"
#include "Agate/Rendering/mock/TextureUser.hpp"
#include "Agate/Rendering/ModelLoader.h"
#include "Agate/Rendering/Camera.h"

namespace Agate {
    using Shader = ShaderUser;
    using VertexArray = VertexArrayUser;
    using IndexBuffer = IndexBufferUser;
    using Texture = TextureUser;
}

//-----------Async-------------
#include "Agate/Async/TaskPool.h"
