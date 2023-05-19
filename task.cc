#include <iostream>
#include <atomic>
#include <thread>
#include <condition_variable>

class PingPong
{
public:
    static constexpr std::size_t MAX = 3;

    void ping()
    {
        std::unique_lock<std::mutex> lock(m_);
        for (size_t i = 0; i < MAX; ++i) {
            cv_.wait(lock, [this] { return !pause_; });
            std::cout << "Ping" << std::endl;
            pause_ = !pause_;
            cv_.notify_one();
        }
    }

    void pong()
    {
        std::unique_lock<std::mutex> lock(m_);
        for (size_t i = 0; i < MAX; ++i) {
            cv_.wait(lock, [this] { return pause_; });
            std::cout << "Pong" << std::endl;
            pause_ = !pause_;
            cv_.notify_one();
        }
    }

private:
    bool pause_ = false;
    std::mutex m_;
    std::condition_variable cv_;
};

int main()
{
	PingPong p;
	std::thread pingThread(&PingPong::ping, &p);
	std::thread pongThread(&PingPong::pong, &p);

	pingThread.join();
	pongThread.join();
}
