/**
 * @brief Include file for render level events
 */

#ifndef AGATE_RENDERCOMMAND_HPP
#define AGATE_RENDERCOMMAND_HPP

#include "Core/Logger.h"
#include "ImGui-layer/imgui_interface.h"
#include "Rendering/Mesh.h"
#include  "imgui.h"

namespace Agate {

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

    /**
    * @brief Render command for drawing UI data across threads.
    */
    class PrepareMesh : public RenderCommand {
    public:
        PrepareMesh(const Mesh data): m_data(data) {}

        void Execute() override {
            /*
                This seems to block for quite a while after the model
                loads, but I think a fix should be deferred until this
                is running on the render thread
            */
            PRINTMSG("Loading textures - This may take a minute");
            for (auto& texture: m_data.m_textures) {
                texture.initialize();
            }
            m_data.setupMesh();
        }


        ~PrepareMesh() override {}

    private:
        Mesh m_data;
    };
} // Namespace Agate

#endif // AGATE_RENDEREVENT_HPP
