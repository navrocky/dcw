#include <exception>
#include <iostream>

#include <args-parser/all.hpp>
#include <termcolor/termcolor.hpp>

using namespace std;
using namespace Args;
namespace tc = termcolor;

int main(int argc, char** argv)
{
    try {
        CmdLine cmd(argc, argv, CmdLine::CommandIsRequired);
        cmd.addCommand("add").end()
            .addCommand("list").end()
            .addCommand("remove").end()
            .addCommand("switch").end()
            .addCommand("stop").end()
            .addCommand("down").end()
            .addHelp(true, argv[0], "Docker Compose Workspace Manager");

        cmd.parse();

        return 0;
    } catch (const HelpHasBeenPrintedException& e) {
        return 0;
    } catch (const BaseException& e) {
        cerr << tc::red << "Call error: " << e.desc() << tc::reset << endl;
        return 1;
    } catch (const exception& e) {
        cerr << tc::red << "Error: " << e.what() << tc::reset << endl;
        return 1;
    }
}
