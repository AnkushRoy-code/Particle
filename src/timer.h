#include <chrono>

template<typename Fn> class Timer
{
  public:
    Timer(const char *name, Fn &&func) :
        m_Name(name), m_Stopped(false), m_Func(func)
    {
        start = std::chrono::steady_clock::now();
    }

    ~Timer()
    {
        if (!m_Stopped) Stop();
    }

    void Stop()
    {
        m_Stopped = true;

        using namespace std::chrono;

        // Duration in milliseconds
        end = steady_clock::now();
        auto duration =
            float(duration_cast<microseconds>(end - start).count()) * 0.001f;

        m_Func({m_Name, duration});
    }

  private:
    Fn m_Func;
    const char *m_Name;
    std::chrono::time_point<std::chrono::steady_clock> start {}, end {};
    bool m_Stopped;
};
