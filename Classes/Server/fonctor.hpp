#include "Subserver.hpp"

class InputFonctor
{
public:

    /**
    * \param[in] subservers Subservers concerned by the commands typed
    * \param[in] stopServer Reference to the main thread's stopServer variable
    */

    InputFonctor(std::vector<FightSubserver *> *subservers, bool &stopServer);

    /**
    * \brief Function of the functor
    */

    void operator()();

private:

    std::vector<FightSubserver *> *subservers; ///< Subservers concerned by the commands typed
    bool                          &stopServer; ///< Reference to the main thread's stopping server variable
};