#include "wiz/cmd/cmd_list.hpp"
#include "wiz/type.hpp"

s32 main(s32 argc, c8 const **argv)
{
    wiz::cmd_list cmds(static_cast<u32>(argc), argv);

    return 0;
}
