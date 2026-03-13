/**
 * @brief Include file for render level events
 */

#ifndef AGATE_RENDERCOMMAND_HPP
#define AGATE_RENDERCOMMAND_HPP

#include "Core/Logger.h"
#include <glm/glm.hpp>
#include "ImGui-layer/imgui_interface.h"
#include "Rendering/Mesh.h"
#include "Rendering/mock/IndexBufferUser.hpp"
#include "Rendering/mock/VertexArrayUser.hpp"
#include "Rendering/mock/ShaderUser.hpp"
#include "Rendering/mock/TextureUser.hpp"
#include  "imgui.h"

namespace Agate {

    /**
     * @brief Built-in command types for the engine
     */
    enum class API CommandTypes {
        DrawMesh,
        DrawUI,
        CreateVertexArray,
        CreateIndexBuffer,
        CreateShader,
        CreateTexture,
        UpdateShaderUniform4f,
        UpdateShaderUniform3f,
        UpdateShaderUniformMat4,
        UpdateShaderUniform1i,
        UpdateShaderUniform1f
    };

    /**
     * @brief a pure virtual class for all render commands to derive from
     *
     * */
    class RenderCommand {
    public:
         /**
         * @brief Execute the render operation.
         *
         * Implementations should perform the necessary rendering work without
         * modifying the command object itself.
         */
        virtual void Execute() = 0;
        virtual ~RenderCommand() = default;
        /**
         * @brief Command Type of this event
         */
        virtual CommandTypes GetCommandType() = 0;
    };


    /**
     * @brief Wrapper for event handlers. Consumes a generic
     *        `Event` and narrows it to a specialization of
     *        `Event` if possible to bind it to a callback
     *        that is then invoked
     */
    class CommandNotifier {
        template<typename T>
        using EventFn = std::function<void(T &)>;

    public:

        /**
         * @brief Constructor; Creates a notifier for an event
         * 
         * @param e Event to handle
         */
        explicit CommandNotifier(RenderCommand &e)
                : m_RenderCommand(e) {};

        /**
         * @brief Template that conditionally handles the underlying
         *        event if its event type matches that of the template
         *        argument
         * 
         * @param ev Handler for the event, given it is of the
         *           appropriate type
         * 
         * @return Whether the event has been handled by this invocation
         * @retval true The event has been handled
         * @retval false The event has not been handled
         */
        template<typename T>
        bool NotifyCommand(EventFn<T> ev) {
            if (m_RenderCommand.GetCommandType() == T::s_GetCommandType()) {
                ev(*(T *) &m_RenderCommand);
                return true;
            }
            return false;
        }

    private:
        RenderCommand &m_RenderCommand;
    };

    /**
     * @brief Emitted when the application window is resized.
     *        Has the new window size
     */
    class DrawMesh: public RenderCommand{
    public:
        /**
         * @brief Constructor - takes in the mesh to cummicate to the render
         *  
         * @param mesh : currently an int for testing purposes a real mesh in future 
         */
        DrawMesh(int mesh): m_mesh(mesh) {};

         /**
         * @brief Execute the render operation.
         *
         * Implementations should perform the necessary rendering work without
         * modifying the command object itself.
         */
        virtual void Execute() override { PRINTWARN("Excute in draw mesh not implimented");}

        /**
         * @brief Command Type of this event
         */
        virtual CommandTypes GetCommandType() override {
            return CommandTypes::DrawMesh;
        };

        /**
         * @brief Type of this command
         */
        static CommandTypes s_GetCommandType() {
            return CommandTypes::DrawMesh;
        }



        virtual ~DrawMesh() = default;

    private:
        int m_mesh;
    };

    /**
    * @brief Render command for drawing UI data across threads.
    */
    class DrawUI : public RenderCommand {
    public:
        DrawUI(const ImDrawData* data) {
            // Shallow copy scalar fields
            m_data = *data;

            // Deep copy command lists into ImVector (matches ImDrawData::CmdLists type)
            m_data.CmdLists.clear();
            m_data.CmdLists.reserve(data->CmdListsCount);

            for (int i = 0; i < data->CmdListsCount; i++) {
                ImDrawList* cloned = data->CmdLists[i]->CloneOutput();
                m_data.CmdLists.push_back(cloned);
            }

            m_data.CmdListsCount = m_data.CmdLists.Size;
        }

        void Execute() override {
            imgui_interface::DrawFrame(&m_data);
        }

        /**
        * @brief Command Type of this event
        */
        virtual CommandTypes GetCommandType() override {
            return CommandTypes::DrawUI;
        };

        /**
         * @brief Type of this command
         */
        static CommandTypes s_GetCommandType() {
            return CommandTypes::DrawUI;
        }

        ~DrawUI() override {
            // Free cloned lists
            for (int i = 0; i < m_data.CmdLists.Size; i++) {
                IM_DELETE(m_data.CmdLists[i]);
            }
            m_data.CmdLists.clear();
            m_data.CmdListsCount = 0;
        }

    private:
        ImDrawData m_data{};
    }; 

    class CreateVertexArray : public RenderCommand {
    public:
        CreateVertexArray(VertexArrayUser VAU)
        : m_VAU(std::move(VAU)){}

        void Execute() override {PRINTMSG("Creating Vertex Array");};

        /**
        * @brief Command Type of this event
        */
        virtual CommandTypes GetCommandType() override {
            return CommandTypes::CreateVertexArray;
        };

        /**
         * @brief Type of this command
         */
        static CommandTypes s_GetCommandType() {
            return CommandTypes::CreateVertexArray;
        }

        virtual ~CreateVertexArray() = default;
    public:
        VertexArrayUser m_VAU;
    };

    class CreateIndexBuffer : public RenderCommand {
    public:
        CreateIndexBuffer(IndexBufferUser IBU, UUID VAUUID)
        : m_IBU(std::move(IBU)), m_VAUUID(std::move(VAUUID)){}

        void Execute() override {PRINTMSG("Createing Index Buffer"); };

        /**
        * @brief Command Type of this event
        */
        virtual CommandTypes GetCommandType() override {
            return CommandTypes::CreateIndexBuffer;
        };

        /**
         * @brief Type of this command
         */
        static CommandTypes s_GetCommandType() {
            return CommandTypes::CreateIndexBuffer;
        }

        virtual ~CreateIndexBuffer() = default;
    public:
        IndexBufferUser m_IBU;
        UUID m_VAUUID;
    };

    class CreateShader : public RenderCommand {
    public:
        CreateShader(ShaderUser SU)
        : m_SU(std::move(SU)){}

        void Execute() override {PRINTMSG("Creating Shader");};

        /**
        * @brief Command Type of this event
        */
        virtual CommandTypes GetCommandType() override {
            return CommandTypes::CreateShader;
        };

        /**
         * @brief Type of this command
         */
        static CommandTypes s_GetCommandType() {
            return CommandTypes::CreateShader;
        }

        virtual ~CreateShader() = default;
    public:
        ShaderUser m_SU;
    };

    class CreateTexture : public RenderCommand {
    public:
        CreateTexture(TextureUser TU)
        : m_TU(std::move(TU)){}

        void Execute() override {PRINTMSG("Creating Texture");};

        /**
        * @brief Command Type of this event
        */
        virtual CommandTypes GetCommandType() override {
            return CommandTypes::CreateTexture;
        };

        /**
         * @brief Type of this command
         */
        static CommandTypes s_GetCommandType() {
            return CommandTypes::CreateTexture;
        }

        virtual ~CreateTexture() = default;
    public:
        TextureUser m_TU;
    };

    class UpdateShaderUniform4f : public RenderCommand {
    public:
        UpdateShaderUniform4f(UUID shaderUUID, std::string uniform, float x, float y, float z, float w)
        : m_ShaderUUID(shaderUUID), m_Uniform(std::move(uniform)), m_X(x), m_Y(y), m_Z(z), m_W(w) {}

        void Execute() override {}

        virtual CommandTypes GetCommandType() override { return CommandTypes::UpdateShaderUniform4f; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UpdateShaderUniform4f; }

        virtual ~UpdateShaderUniform4f() = default;
    public:
        UUID m_ShaderUUID;
        std::string m_Uniform;
        float m_X, m_Y, m_Z, m_W;
    };

    class UpdateShaderUniform3f : public RenderCommand {
    public:
        UpdateShaderUniform3f(UUID shaderUUID, std::string uniform, float x, float y, float z)
        : m_ShaderUUID(shaderUUID), m_Uniform(std::move(uniform)), m_X(x), m_Y(y), m_Z(z) {}

        void Execute() override {}

        virtual CommandTypes GetCommandType() override { return CommandTypes::UpdateShaderUniform3f; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UpdateShaderUniform3f; }

        virtual ~UpdateShaderUniform3f() = default;
    public:
        UUID m_ShaderUUID;
        std::string m_Uniform;
        float m_X, m_Y, m_Z;
    };

    class UpdateShaderUniformMat4 : public RenderCommand {
    public:
        UpdateShaderUniformMat4(UUID shaderUUID, std::string uniform, glm::mat4 trans)
        : m_ShaderUUID(shaderUUID), m_Uniform(std::move(uniform)), m_Trans(trans) {}

        void Execute() override {}

        virtual CommandTypes GetCommandType() override { return CommandTypes::UpdateShaderUniformMat4; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UpdateShaderUniformMat4; }

        virtual ~UpdateShaderUniformMat4() = default;
    public:
        UUID m_ShaderUUID;
        std::string m_Uniform;
        glm::mat4 m_Trans;
    };

    class UpdateShaderUniform1i : public RenderCommand {
    public:
        UpdateShaderUniform1i(UUID shaderUUID, std::string uniform, int value)
        : m_ShaderUUID(shaderUUID), m_Uniform(std::move(uniform)), m_Value(value) {}

        void Execute() override {}

        virtual CommandTypes GetCommandType() override { return CommandTypes::UpdateShaderUniform1i; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UpdateShaderUniform1i; }

        virtual ~UpdateShaderUniform1i() = default;
    public:
        UUID m_ShaderUUID;
        std::string m_Uniform;
        int m_Value;
    };

    class UpdateShaderUniform1f : public RenderCommand {
    public:
        UpdateShaderUniform1f(UUID shaderUUID, std::string uniform, float x)
        : m_ShaderUUID(shaderUUID), m_Uniform(std::move(uniform)), m_X(x) {}

        void Execute() override {}

        virtual CommandTypes GetCommandType() override { return CommandTypes::UpdateShaderUniform1f; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UpdateShaderUniform1f; }

        virtual ~UpdateShaderUniform1f() = default;
    public:
        UUID m_ShaderUUID;
        std::string m_Uniform;
        float m_X;
    };

} // Namespace Agate

#endif // AGATE_RENDEREVENT_HPP
