#include <stdint.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "trace.hh"

typedef std::chrono::high_resolution_clock UrClock;
typedef std::chrono::time_point<UrClock> Instant;
typedef std::chrono::duration<UrClock::rep> Duration;
typedef std::chrono::microseconds Ms;
using std::chrono::duration_cast;

class Breather {
 public:
  virtual void Breathe(Instant ts) = 0;
};

class FooBreather : public Breather {
 public:
  void Breathe(Instant ts) {
    auto ins_ms =
        std::chrono::duration<double, std::milli>(ts.time_since_epoch());

    std::cout << "foo!\n";
  }
};

class BarBreather : public Breather {
 public:
  void Breathe(Instant ts) { std::cout << "bar!\n"; }
};

class UrestDrome {
 public:
  UrestDrome(Duration respire_time) : respire_time_(respire_time) {}

  void Respire() {
    for (;;) {
      RespireSingly();
    }
  }

  void RespireSingly() {
    // This is wrong, but simple and close enough for testing.
    frame_instant_ = UrClock::now();
    TRACE(URSPEAK_RESPIRE_START());
    for (const auto &breather : breathers_) {
      breather->Breathe(frame_instant_);
    }
    // We only want to measure the time spent *before* waiting.
    std::cout.flush();
    TRACE(URSPEAK_RESPIRE_DONE());
    const auto spent = UrClock::now() - frame_instant_;
    if (spent < respire_time_) {
      std::this_thread::sleep_for(respire_time_ - spent);
    }
  }

  void AppendBreather(std::shared_ptr<Breather> b) { breathers_.push_back(b); }

 private:
  std::vector<std::shared_ptr<Breather>> breathers_;
  Instant frame_instant_;
  Duration respire_time_;
};

int main() {
  // static_assert(UrClock::is_steady, "UrClock must be steady.");
  const auto respiration_delta =
      duration_cast<Duration>(std::chrono::seconds(1));
  auto drome = UrestDrome{respiration_delta};
  drome.AppendBreather(std::make_shared<FooBreather>());
  drome.AppendBreather(std::make_shared<BarBreather>());
  drome.Respire();
  return 0;
}
