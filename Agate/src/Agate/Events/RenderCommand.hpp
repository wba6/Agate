/**
 * @brief Include file for render level events
 */

#ifndef AGATE_RENDERCOMMAND_HPP
#define AGATE_RENDERCOMMAND_HPP

#include "Core/Logger.h"
#include "ImGui-layer/imgui_interface.h"
#include "Rendering/Mesh.h"
#include "Rendering/mock/IndexBufferUser.hpp"
#include "Rendering/mock/VertexArrayUser.hpp"
#include  "imgui.h"

namespace Agate {

    /**
     * @brief Built-in command types for the engine
     */
    enum class API CommandTypes {
        DrawMesh,
        DrawUI,
        CreateVertexArray,
        CreateIndexBuffer
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

} // Namespace Agate

#endif // AGATE_RENDEREVENT_HPP
