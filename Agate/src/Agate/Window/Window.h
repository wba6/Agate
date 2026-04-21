#include "Agate/Events/Event.h"

//TODO: Use a bridge and a factor to create this window so that there is only one instance so the api can be exposed to client

#ifndef AGATE_WINDOW_H
#define AGATE_WINDOW_H

#include "Agate/Events/Event.h"
#include <mutex>
#include <atomic>
#include <string>
#include <functional>

namespace Agate {
    class Context;

    class Window {

    public:
        using EventCallbackFn = std::function<void(Event &)>;

        Window(std::string WindowName, int size_x, int size_y, EventCallbackFn callback, bool vsync);

        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        void SwapBuffers(); 

        void PollEvents();

        double WindowOpenTime();

        int GetWidth();

        int GetHieght();

        void GrabCursor(bool cursor);

        void SetVSync(bool enable);

        bool GetVSyncState();

        void *GetInstanceWindow();

        /**
         * @brief Detaches any currently-bound OpenGL context from the calling thread.
         *
         * After calling this, there will be no current OpenGL context on the thread, so OpenGL calls
         * that require a current context will fail/produce undefined behavior until another context
         * is attached.
         */
        void DetachContext();

        /**
         * @brief Makes this window's OpenGL context the current context for the calling thread.
         *
         * After calling this, OpenGL commands issued on the current thread will affect this window's
         * context (until another context is made current or the context is detached).
         *
         * @note GLFW contexts are thread-local: a context can only be current on one thread at a time.
         */
        void AttachContext();

    private:
        void InitWindow();

        static void GlfwError(int error_code, const char *description);

        struct WindowProperies {
            std::string name;
            std::atomic<int> width;
            std::atomic<int> height;
            EventCallbackFn callback;
            std::atomic<bool> VSyncState;
            Context *context;

            WindowProperies(std::string n, int w, int h, EventCallbackFn cb, bool v)
                : name(std::move(n)), width(w), height(h), callback(std::move(cb)), VSyncState(v), context(nullptr) {}
        };
        void *m_Window;

        WindowProperies m_windowProps;
        std::recursive_mutex m_SyncMutex;
    };
}// namespace Agate

#endif // AGATE_WINDOW_H
