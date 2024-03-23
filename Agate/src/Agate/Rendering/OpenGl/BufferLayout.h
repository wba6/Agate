
#ifndef AGATE_BUFFERLAYOUT_H
#define AGATE_BUFFERLAYOUT_H
#include <utility>

#include "Agate/Core/Logger.h"
namespace Agate{
    //classify what data type the data is
    enum class vertexType {
        Float1,
        Float2,
        Float3,
        Float4,
    };

    //stores attribute data for a set of vertices
    struct vertexAttributes {
        std::string name;
        vertexType type;
        bool normalized;
        size_t offset{0};
    };


    //store each set of VertexData and calculate related information
    class BufferDataLayout {
    public:
        BufferDataLayout(std::initializer_list<vertexAttributes> attributes)
            : m_attribute(attributes){
                calculateOffsets();
              };

        //TODO: breaks rules for accessing private things
        const std::vector<vertexAttributes>& getAttributes(){
            return m_attribute;
        }

        size_t getStride() {
            return calculateStride();
        }

        int getSize(vertexType type) const {
            switch (type)
            {
                case vertexType::Float1:
                    return 1 * sizeof(float);
                case vertexType::Float2:
                    return 2 * sizeof(float);
                case vertexType::Float3:
                    return 3 * sizeof(float);
                case vertexType::Float4:
                    return 4 * sizeof(float);
            }
            PRINTCRIT("Error unknown vertexType BufferDataLayout::getSize()");
        }

        //get the size of given vertex
        int getVerticieCount(vertexType type) const {
            switch (type)
            {
                case vertexType::Float1:
                    return 1;
                case vertexType::Float2:
                    return 2;
                case vertexType::Float3:
                    return 3;
                case vertexType::Float4:
                    return 4;
            }
            PRINTCRIT("Error unknown vertexType BufferDataLayout::getVerticieCount()");
        }
    private:

        //calculate the stride between each vertex based on data type
        [[nodiscard]] size_t calculateStride() const {
            size_t stride = 0;

            //loop through all attributes in the data and add up the total size to the next piece of data
            for(const auto& item: m_attribute){
                stride += getSize(item.type);
            }
            return stride;
        }

        size_t calculateOffsets()  {
            size_t offset = 0;

            //loop through all attributes in the data and add up the total size to the next piece of data
            for(auto& item: m_attribute){
                item.offset = offset;
                offset += getSize(item.type);
            }
            return 1;
        }
    private:
        std::vector<vertexAttributes> m_attribute;
    };
}
#endif//AGATE_BUFFERLAYOUT_H
