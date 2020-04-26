#include <iostream>
#include <thread>

#include <Person.hpp>
#include <Utility.hpp>
#include <ProgressBar.hpp>

#include <dbg.h>
#include <termcolor/termcolor.hpp>

#include <llvm/Support/CommandLine.h>

static llvm::cl::OptionCategory MuffinCategory("muffin");
llvm::cl::opt<bool> MuffinIsCool("muffin-is-cool",
                                 llvm::cl::desc("Muffin is a cool dog."),
                                 llvm::cl::init(true));

int main(int argc, char **argv) {
  if (!llvm::cl::ParseCommandLineOptions(argc, argv)) {
    llvm::cl::PrintOptionValues();
  }

  std::cout << termcolor::bold << termcolor::yellow;
  ProgressBar Bar;
  Bar.setBarWidth(50);
  Bar.fillBarProgressWith("■");
  Bar.fillBarRemainderWith(" ");

  for (size_t I = 1; I <= 100; ++I) {
    Bar.update(I);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  std::cout << termcolor::reset;
  return 0;
}
