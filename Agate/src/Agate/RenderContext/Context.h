//
// Created by TANK1_41 on 9/6/2022.
//

#ifndef AGATE_CONTEXT_H
#define AGATE_CONTEXT_H

namespace Agate
{

    class Context {
    public:
        virtual ~Context(){};
        virtual void CreateContext() = 0;
        virtual void EndContext() = 0;
        virtual void NewFrame() = 0;
    };

    class OpenGL: public Context{
    public:
        void CreateContext() override;
        void EndContext() override;
        void NewFrame() override;
    };
}// namespace Agate

#endif//AGATE_CONTEXT_H
