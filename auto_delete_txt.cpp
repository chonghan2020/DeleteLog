#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

// 删除指定文件夹中的所有 .txt 文件
void deleteTxtFiles(const std::vector<std::string>& folderPaths) {
    for (const auto& folder : folderPaths) {
        try {
            for (const auto& entry : fs::directory_iterator(folder)) {
                if (entry.path().extension() == ".txt") {
                    std::string filePath = entry.path().string();
                    std::cout << "Deleting: " << filePath << std::endl;
                    fs::remove(filePath);  // 删除文件
                }
            }
        } catch (const fs::filesystem_error& err) {
            std::cerr << "Filesystem error in folder " << folder << ": " << err.what() << std::endl;
        }
    }
}

int main() {
    // 指定要遍历的文件夹路径列表
    std::vector<std::string> folderPaths = {
        "/data/code/Trackor/log",
        
    };

    // 无限循环，每4小时删除一次 .txt 文件
    while(true)
    {
        deleteTxtFiles(folderPaths);
        std::this_thread::sleep_for(std::chrono::hours(2));
    }
    return 0;
}
