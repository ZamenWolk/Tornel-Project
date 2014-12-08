#ifndef VERSION_H
#define VERSION_H

#include "src/constants.hpp"
#include "communication.hpp"

namespace AutoVersion
{

    //Software Status
    static const char          STATUS[]             = "Alpha";
    static const long          MAJOR                = 1;
    static const long          MINOR                = 12;
    static const long          PATCH                = 2;
    static const VersionNumber VERSION(STATUS, MAJOR, MINOR, PATCH);
    static const char          FULLVERSION_STRING[] = "a1.12.2";


}
#endif //VERSION_H
