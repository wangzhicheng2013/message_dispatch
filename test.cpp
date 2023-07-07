#include <unistd.h>
#include <mutex>
#include <thread>
#include "message_print.hpp"
#include "message_log.hpp"
static std::mutex global_lock;
void do_process(const char* key) {
    auto processor = FIND_MESSAGE_PROCESSOR(key);
    if (processor != nullptr) {
        std::lock_guard<std::mutex>lock(global_lock);
        processor->process();
    }
}
int main() {
    std::thread print_thread(do_process, "message_print");
    std::thread log_thread(do_process, "message_log");
    sleep(5);
    print_thread.join();
    log_thread.join();

    return 0;
}