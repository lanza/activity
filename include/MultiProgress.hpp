#include <array>
#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>

template <typename Indicator, size_t Count> class MultiProgress {
  std::array<std::reference_wrapper<Indicator>, Count> Bars;

  std::mutex Mutex;
  std::atomic<bool> Started = false;

public:
  template <typename... Indicators, typename = typename std::enable_if_t<
                                        (sizeof...(Indicators) == Count)>>
  explicit MultiProgress(Indicators &... Bars) : Bars({Bars...}) {}

  template <size_t Index>
  typename std::enable_if_t<(Index >= 0 && Index < Count), void>
  update(float Value, std::ostream &OS = std::cout) {
    Bars[Index].get().setProgress(Value);
    writeProgress(OS);
  }

  void writeProgress(std::ostream &OS = std::cout) {
    std::unique_lock Lock{Mutex};

    if (Started)
      for (size_t I = 0; I < Count; ++I)
        OS << "\x1b[A";

    for (auto &Bar : Bars) {
      Bar.get().writeProgress();
      OS << "\n";
    }

    if (!Started)
      Started = true;
  }
};
