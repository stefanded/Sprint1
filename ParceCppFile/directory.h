#pragma once
#include <chrono>
#include <fstream>
#include <filesystem>
#include<vector>
#include<mutex>

#include "parseline.h"
using milliseconds = std::chrono::milliseconds;

namespace fs = std::filesystem;

class SyncOper
{
	std::mutex m_;
	Result result_;
public:
	void operator()(CppFile& file) noexcept;
	Result ResultOper()const noexcept;
};

class Directory
{
	void FileProcessing();
	void PushFile();
	
public:
	Directory(const std::string& way_file)noexcept;
	void Start();
	size_t GetNumberFiles()const noexcept;
	Result GetResult()const noexcept;
	size_t GetTime() const noexcept;
private:
	SyncOper syncOper_;
	std::vector<CppFile> file_;
	const fs::path path_;
	milliseconds time_;
};
std::ofstream& operator<<(std::ofstream& ofs, const Directory& d);