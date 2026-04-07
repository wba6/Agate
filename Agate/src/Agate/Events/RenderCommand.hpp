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
        BindVertexArray,
        UnBindVertexArray,
        BindIndexBuffer,
        UnBindIndexBuffer,
        BindShader,
        UnBindShader,
        BindTexture,
        UpdateShaderUniform4f,
        UpdateShaderUniform3f,
        UpdateShaderUniformMat4,
        UpdateShaderUniform1i,
        UpdateShaderUniform1f,
        SetViewport,
        DeleteVertexArray,
        DeleteIndexBuffer,
        DeleteShader,
        DeleteTexture
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
         * @param vaoUUID : UUID of the Vertex Array
         * @param shaderUUID : UUID of the Shader
         * @param indexCount : Number of indices to draw
         */
        DrawMesh(UUID vaoUUID, UUID shaderUUID, uint32_t indexCount)
            : m_VaoUUID(vaoUUID), m_ShaderUUID(shaderUUID), m_IndexCount(indexCount) {};

         /**
         * @brief Execute the render operation.
         */
        virtual void Execute() override {}

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

    public:
        UUID m_VaoUUID;
        UUID m_ShaderUUID;
        uint32_t m_IndexCount;
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
        struct VertexArrayData {
            UUID m_UUID;
            BufferDataLayout m_bufferInformation;
            std::shared_ptr<void> m_data;
            size_t m_dataSize;

            UUID getUUID() const { return m_UUID; }
            BufferDataLayout getBufferData() const { return m_bufferInformation; }
            std::shared_ptr<void> getData() const { return m_data; }
            size_t getDataSize() const { return m_dataSize; }
        };

        CreateVertexArray(const VertexArrayUser& VAU)
        : m_VAU{VAU.getUUID(), 
                VAU.getBufferData(), 
                VAU.getData(), 
                VAU.getDataSize()}{}

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
        VertexArrayData m_VAU;
    };

    class CreateIndexBuffer : public RenderCommand {
    public:
        struct IndexBufferData {
            std::vector<unsigned int> m_indinces;
            UUID m_UUID;
            UUID m_VAUUID;

            const std::vector<unsigned int>& getIndinces() const { return m_indinces; }
            UUID getUUID() const { return m_UUID; }
            UUID getAttachedVAOUUID() const { return m_VAUUID; }
        };

        CreateIndexBuffer(const IndexBufferUser& IBU, UUID VAUUID)
        : m_IBU{IBU.getIndinces(), 
                IBU.getUUID(), 
                IBU.getAttachedVAOUUID()}, 
          m_VAUUID(std::move(VAUUID)){}

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
        IndexBufferData m_IBU;
        UUID m_VAUUID;
    };

    class CreateShader : public RenderCommand {
    public:
        struct ShaderData {
            std::string m_vertexShaderPath;
            std::string m_fragmentShaderPath;
            UUID m_UUID;

            const std::string& getVertexShaderPath() const { return m_vertexShaderPath; }
            const std::string& getFragmentShaderPath() const { return m_fragmentShaderPath; }
            UUID getUUID() const { return m_UUID; }
        };

        CreateShader(const ShaderUser& SU)
        : m_SU{SU.getVertexShaderPath(), 
               SU.getFragmentShaderPath(), 
               SU.getUUID()}{}

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
        ShaderData m_SU;
    };

    class CreateTexture : public RenderCommand {
    public:
        struct TextureData {
            std::string m_path;
            std::string m_directory;
            std::string m_type;
            UUID m_UUID;

            const std::string& getPath() const { return m_path; }
            const std::string& getDirectory() const { return m_directory; }
            const std::string& getType() const { return m_type; }
            UUID getUUID() const { return m_UUID; }
        };

        CreateTexture(const TextureUser& TU)
        : m_TU{TU.getPath(), 
               TU.getDirectory(), 
               TU.getType(), 
               TU.getUUID()}{}

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
        TextureData m_TU;
    };

    class BindVertexArray : public RenderCommand {
    public:
        BindVertexArray(UUID uuid) : m_UUID(uuid) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::BindVertexArray; }
        static CommandTypes s_GetCommandType() { return CommandTypes::BindVertexArray; }
        UUID m_UUID;
    };

    class UnBindVertexArray : public RenderCommand {
    public:
        UnBindVertexArray() = default;
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::UnBindVertexArray; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UnBindVertexArray; }
    };

    class BindIndexBuffer : public RenderCommand {
    public:
        BindIndexBuffer(UUID uuid) : m_UUID(uuid) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::BindIndexBuffer; }
        static CommandTypes s_GetCommandType() { return CommandTypes::BindIndexBuffer; }
        UUID m_UUID;
    };

    class UnBindIndexBuffer : public RenderCommand {
    public:
        UnBindIndexBuffer() = default;
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::UnBindIndexBuffer; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UnBindIndexBuffer; }
    };

    class BindShader : public RenderCommand {
    public:
        BindShader(UUID uuid) : m_UUID(uuid) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::BindShader; }
        static CommandTypes s_GetCommandType() { return CommandTypes::BindShader; }
        UUID m_UUID;
    };

    class UnBindShader : public RenderCommand {
    public:
        UnBindShader() = default;
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::UnBindShader; }
        static CommandTypes s_GetCommandType() { return CommandTypes::UnBindShader; }
    };

    class BindTexture : public RenderCommand {
    public:
        BindTexture(UUID uuid, uint32_t slot) : m_UUID(uuid), m_Slot(slot) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::BindTexture; }
        static CommandTypes s_GetCommandType() { return CommandTypes::BindTexture; }
        UUID m_UUID;
        uint32_t m_Slot;
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

    class SetViewport : public RenderCommand {
    public:
        SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        : m_X(x), m_Y(y), m_Width(width), m_Height(height) {}

        void Execute() override {}

        virtual CommandTypes GetCommandType() override { return CommandTypes::SetViewport; }
        static CommandTypes s_GetCommandType() { return CommandTypes::SetViewport; }

        virtual ~SetViewport() = default;
    public:
        uint32_t m_X, m_Y, m_Width, m_Height;
    };

    class DeleteVertexArray : public RenderCommand {
    public:
        DeleteVertexArray(UUID uuid) : m_UUID(uuid) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::DeleteVertexArray; }
        static CommandTypes s_GetCommandType() { return CommandTypes::DeleteVertexArray; }
        UUID m_UUID;
    };

    class DeleteIndexBuffer : public RenderCommand {
    public:
        DeleteIndexBuffer(UUID uuid) : m_UUID(uuid) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::DeleteIndexBuffer; }
        static CommandTypes s_GetCommandType() { return CommandTypes::DeleteIndexBuffer; }
        UUID m_UUID;
    };

    class DeleteShader : public RenderCommand {
    public:
        DeleteShader(UUID uuid) : m_UUID(uuid) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::DeleteShader; }
        static CommandTypes s_GetCommandType() { return CommandTypes::DeleteShader; }
        UUID m_UUID;
    };

    class DeleteTexture : public RenderCommand {
    public:
        DeleteTexture(UUID uuid) : m_UUID(uuid) {}
        void Execute() override {}
        virtual CommandTypes GetCommandType() override { return CommandTypes::DeleteTexture; }
        static CommandTypes s_GetCommandType() { return CommandTypes::DeleteTexture; }
        UUID m_UUID;
    };


} // Namespace Agate

#endif // AGATE_RENDEREVENT_HPP
