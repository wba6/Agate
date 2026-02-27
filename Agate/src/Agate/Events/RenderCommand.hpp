/**
 * @brief Include file for render level events
 */

#ifndef AGATE_RENDERCOMMAND_HPP
#define AGATE_RENDERCOMMAND_HPP

#include "Core/Logger.h"
#include "ImGui-layer/imgui_interface.h"
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
     * @brief Emitted when the application window is resized.
     *        Has the new window size
     */
    class DrawUI: public RenderCommand{
    public:
        /**
         * @brief Constructor - takes in the mesh to cummicate to the render
         *  
         * @param mesh : currently an int for testing purposes a real mesh in future 
         */
        DrawUI(ImDrawData data): m_data(data) {};

         /**
         * @brief Execute the render operation.
         *
         * Implementations should perform the necessary rendering work without
         * modifying the command object itself.
         */
        virtual void Execute() override { imgui_interface::DrawFrame(&m_data);}

        virtual ~DrawUI() = default;

    private:
        ImDrawData m_data;
    };

} // Namespace Agate

#endif // AGATE_RENDEREVENT_HPP
