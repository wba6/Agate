
#include "Agate.h"

#include <iostream>
#include <string>
class app : public Agate::EntryPoint {

public:
};


Agate::EntryPoint *Agate::CreateEntryPoint()
{
    return new app();
}
