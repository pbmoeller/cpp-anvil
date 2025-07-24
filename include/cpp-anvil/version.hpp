#ifndef CPP_ANVIL_VERSION_HPP
#define CPP_ANVIL_VERSION_HPP

namespace anvil {

unsigned int getCppAnvilVersionMajor();
unsigned int getCppAnvilVersionMinor();
unsigned int getCppAnvilVersionPatch();
unsigned int getCppAnvilVersionTweak();

const char* getCppAnvilVersion();

} // namespace anvil

#endif // CPP_ANVIL_VERSION_HPP
