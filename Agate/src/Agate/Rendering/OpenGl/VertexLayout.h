//
// Created by brade on 12/26/2023.
//

#ifndef AGATE_VERTEXLAYOUT_H
#define AGATE_VERTEXLAYOUT_H
namespace Agate
{
    enum vertexType {
        Float,
        Float2,
        Float3,
        Int,
        Int2,
        Int3,
    };

    struct ElementLayout{
        std::string m_name;
        vertexType m_dataType;
        bool m_normalized;

        //constructor
        ElementLayout(std::string name, vertexType dataType, bool normalize = false)
        :m_name(name), m_dataType(dataType), m_normalized(normalize){

        }

        int getElementsPerVertex(vertexType t){
            switch (t)
            {
                case Float:     return 1;
                case Float2:    return 2;
                case Float3:    return 3;
                case Int:       return 1;
                case Int2:      return 2;
                case Int3:      return 3;
            }

            PRINTCRIT("Unknown vertex type ElementLayout::getElementsPerVertex");
            return -1;
        }
    };

    class VertexLayOut {
    public:
        VertexLayOut(std::initializer_list<ElementLayout> l)
            :m_elementLayouts(l){
              CalcStrideAndOffset();
              };

        void CalcStrideAndOffset(){
            m_stride = 0;
            m_offset = 0;
            for (int i = 0; i < m_elementLayouts.size(); i++)
            {
                
            }
        };

    private:
        std::vector<ElementLayout> m_elementLayouts;
        unsigned int layoutNum;
        unsigned int vertexSize;
        bool Normilized;
        unsigned int m_stride;
        unsigned int m_offset;
    };

}
#endif//AGATE_VERTEXLAYOUT_H
