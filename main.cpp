#include <iostream>
#include <string>
#include <thread>

#include <MultiProgress.h>
#include <Person.hpp>
#include <ProgressBar.hpp>
#include <Utility.hpp>

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

  std::cout << "Muffin\n";

  std::cout << termcolor::bold << termcolor::green << "\n\n" << std::endl;
  ProgressBar Bar1;
  ProgressBar Bar2;
  ProgressBar Bar3;
  MultiProgress<ProgressBar, 3> Bars(Bar1, Bar2, Bar3);

  auto Job1 = [&Bars]() {
    for (size_t I = 0; I <= 100; ++I) {
      Bars.update<0>(I);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  };

  auto Job2 = [&Bars]() {
    for (size_t I = 0; I <= 100; ++I) {
      Bars.update<1>(I);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  };

  auto Job3 = [&Bars]() {
    for (size_t I = 0; I <= 100; ++I) {
      Bars.update<2>(I);
      std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
  };

  std::thread FirstJob{Job1};
  std::thread SecondJob{Job2};
  std::thread ThirdJob{Job3};

  FirstJob.join();
  SecondJob.join();
  ThirdJob.join();

  std::cout << termcolor::reset << std::endl;
  return 0;
}
