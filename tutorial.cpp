#include <thread>
#include <mach-o/dyld.h>

__attribute__((constructor)) void entry()
{
    printf("Custom printsploit loaded\n");
    std::thread([] {
        std::this_thread::sleep_for(std::chrono::seconds(13)); // give ample time to get into a game (you can modify this value based on your Mac's performance)
        uintptr_t offset = 0x1010adc10;
        void (*printfunction)(int, const char*, ...) = reinterpret_cast<void(*)(int, const char*, ...)>(_dyld_get_image_vmaddr_slide(0) + offset);
    
        auto output = [&](int type, const char* message) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            printfunction(type, message);
        };
    
        output(0, "print");
        output(1, "info");
        output(2, "warn");
        output(3, "error");
    }).detach();
}
