#pragma once

#include <string>
#include <filesystem>
#include <fileapi.h>
#include <direct.h>
#include <shlobj.h> 
#include <shellapi.h>
#include <Windows.h>

#include "xor_.hpp"

// 定义一个宏来获取 Roaming 文件夹的 CSIDL 值
#define CSIDL_ROAMING   CSIDL_APPDATA

namespace MdayS
{
	class filesystem {
	public:
		// 函数定义
		const bool open_folder(const std::string& path) {
			// 检查路径是否为空
			if (path.empty()) {
				return false;
			}

			// 根据操作系统选择命令
#ifdef _WIN32
	// Windows 系统使用 explorer
			std::string command = "explorer \"" + path + "\"";
#elif __APPLE__
	// macOS 系统使用 open
			std::string command = "open \"" + path + "\"";
#elif __linux__
	// Linux 系统使用 xdg-open
			std::string command = "xdg-open \"" + path + "\"";
#else
			std::cerr << "Error: Unsupported operating system." << std::endl;
			return false;
#endif

			// 执行命令
			int result = system(command.c_str());

			// 检查返回值
			if (result == 0) {
				return true;
			}
			else {
				return false;
			}
		}

		const bool create_folder(std::string name, std::string path = "") {

			std::error_code err;

			if (path.empty() && !std::filesystem::exists(get_main_folder() + "\\" + name)) {
				std::filesystem::create_directory(get_main_folder() + "\\" + name, err);
			}
			else if (!std::filesystem::exists(get_main_folder() + "\\" + name)) {
				std::filesystem::create_directory(path + "\\" + name, err);
			}

			return !err;
		}

		const bool delete_folder(std::string name, std::string path = "") {

			BOOL status = false;

			if (path.empty()) {
				status = RemoveDirectoryA(std::string(get_main_folder() + "\\" + name).c_str());
			}
			else {
				status = RemoveDirectoryA(std::string(path + "\\" + name).c_str());
			}

			return status;
		}

		const bool delete_file(std::string name, std::string path = "") {

			int result;

			if (path.empty()) {
				result = std::remove(std::string(get_main_folder() + "\\" + name).c_str());
			}
			else {
				result = std::remove(std::string(path + "\\" + name).c_str());
			}

			return (result == 0);
		}

		const std::string get_main_folder() {
			std::string path = std::string(MENU_PATH);
			if (std::filesystem::exists(path))
				return path;

			std::filesystem::create_directory(path);

			return path;
		}

		const std::string get_self_path()
		{
			char buffer[128] = { 0 };
			if (_getcwd(buffer, sizeof(buffer)) == buffer) {

				return buffer;
			}
			else
			{
				return "";
			}
		}

		const std::string get_roaming_path()
		{
			char path[MAX_PATH];
			// 使用 SHGetFolderPathA 获取 Roaming 文件夹路径
			HRESULT hr = SHGetFolderPathA(NULL, CSIDL_ROAMING, NULL, SHGFP_TYPE_CURRENT, path);
			if (SUCCEEDED(hr))
			{
				return std::string(path);
			}
			else
			{
				return "";
			}
		}

		const bool exists(std::string name, std::string path = "") {

			if (path.empty()) {
				return std::filesystem::exists(get_main_folder() + "\\" + name);
			}

			return std::filesystem::exists(path + "\\" + name);
		}

		const bool move_file(std::string old_path, std::string new_path) {

			int result = std::rename(old_path.c_str(), new_path.c_str());

			return (result == 0);
		}

		const std::string get_file(std::string name) {
			return get_main_folder() + "\\" + name;
		}

		const std::string get_timestamp() {
			std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::tm time_info;
			localtime_s(&time_info, &now);
			std::stringstream ss;
			ss << std::put_time(&time_info, "%Y-%m-%d-%H-%M-%S");
			std::string formatted_date = ss.str();

			return formatted_date;
		}

		const std::string get_timestamp_narrow() {
			std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::tm time_info;
			localtime_s(&time_info, &now);
			std::stringstream ss;
			ss << std::put_time(&time_info, "%Y-%m-%d-%H-%M-%S");
			std::string formatted_date = ss.str();

			return formatted_date;
		}

	}; inline filesystem file;
}
