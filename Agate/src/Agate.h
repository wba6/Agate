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
#include "Agate/Rendering/OpenGl/IndexBuffer.h"
#include "Agate/Rendering/OpenGl/Render.h"
#include "Agate/Rendering/OpenGl/VertexArray.h"
#include "Agate/Rendering/OpenGl/VertexBuffer.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include "Agate/Rendering/ModelLoader.h"
#include "Agate/Rendering/Camera.h"

