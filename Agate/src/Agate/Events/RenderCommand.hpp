/**
 * @brief Include file for render level events
 */

#ifndef AGATE_RENDERCOMMAND_HPP
#define AGATE_RENDERCOMMAND_HPP

#include "Core/Logger.h"

namespace Agate {

    class RenderCommand {
    public:
        virtual void Execute() const = 0;
    };

    /**
     * @brief Emitted when the application window is resized.
     *        Has the new window size
     */
    class DrawMesh: public RenderCommand{
    public:
        /**
         * @brief Constructor - takes the new dimensions of
         *        the window
         * 
         * @param x New width of the window
         * @param y New height of the window
         */
        DrawMesh(int mesh): m_mesh(mesh) {};

        virtual void Execute() const override { PRINTWARN("Excute in draw mesh not implimented");}

    private:
        int m_mesh;
    };

} // Namespace Agate

#endif // AGATE_RENDEREVENT_HPP
