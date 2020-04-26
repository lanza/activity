#include <atomic>
#include <mutex>
#include <iostream>

class ProgressBar {
  std::mutex Mutex;

  float Progress = 0;

  int BarWidth = 60;

  std::string Fill = "#";
  std::string Remainder = " ";
  std::string StatusText = "";

public:
  void setProgress(float Value) {
    std::unique_lock lock{Mutex};
    Progress = Value;
  }

  void setBarWidth(size_t Width) {
    std::unique_lock Lock{Mutex};
    BarWidth = Width;
  }

  void fillBarProgressWith(const std::string& Chars) {
    std::unique_lock Lock{Mutex};
    Fill = Chars;
  }

  void fillBarRemainderWith(const std::string& Chars) {
    std::unique_lock Lock{Mutex};
    Remainder = Chars;
  }

  void setStatusText(const std::string& Status) {
    std::unique_lock Lock{Mutex};
    StatusText = Status;
  }

  void update(float Value, std::ostream &OS = std::cout) {
    setProgress(Value);
    writeProgress(OS);
  }

  void writeProgress(std::ostream &OS = std::cout) {
    std::unique_lock Lock{Mutex};

    if (Progress > 100.0f) return;

    OS << "\r" << std::flush;

    OS << "[";

    const auto Completed = static_cast<size_t>(Progress * static_cast<float>(BarWidth) / 100.0f);

    for (size_t I = 0; I < BarWidth; ++I) {
      if (I <= Completed)
        OS << Fill;
      else
        OS << Remainder;
    }

    OS << "]";

    OS << " " << std::min(static_cast<size_t>(Progress), size_t(100)) << "%";

    OS << " " << StatusText;
  }
};
