#include "directory.h"
#include<execution>
#include<algorithm>

#include<chrono>
void SyncOper::operator()(CppFile& file) noexcept
{
	file.Start();
	std::unique_lock<std::mutex> lock{ m_ };
	result_ += {file.GetEmptyLines(), file.GetCommentsLines(), file.GetCodeLines()};
}

Result SyncOper::ResultOper() const noexcept
{
	return result_;
}

void Directory::FileProcessing()
{
	auto begin_ = std::chrono::high_resolution_clock::now();
	std::for_each(std::execution::par, begin(file_), end(file_), std::ref(syncOper_));///*std::execution::par,*/
	auto end_ = std::chrono::high_resolution_clock::now();
	time_ = std::chrono::duration_cast<milliseconds>(end_ - begin_);

}

void Directory::PushFile()
{
	for (const auto& pr : fs::recursive_directory_iterator(path_))
	{
		auto extension = pr.path().extension();
		if (extension == ".cpp" || extension == ".hpp" || extension == ".h" || extension == ".c")
		{
			file_.emplace_back(std::move(pr.path().string()));
		}
	}
	FileProcessing();
}

Directory::Directory(const std::string& way_file) noexcept :path_(way_file), time_(0) {}

void Directory::Start()
{
	if (!fs::exists(path_))
	{
		throw std::runtime_error("file not found");
	}
	PushFile();
}

size_t Directory::GetNumberFiles() const noexcept
{
	return file_.size();
}

Result Directory::GetResult() const noexcept
{
	return syncOper_.ResultOper();
}

size_t Directory::GetTime() const noexcept
{
	return time_.count();
}

std::ofstream& operator<<(std::ofstream& ofs, const Directory& d)
{
	ofs << "total number of processed files: " << d.GetNumberFiles() << '\n';
	ofs << "total number of blank lines: " << d.GetResult().number_empty_lines_ << '\n';
	ofs << "total number of comments lines: " << d.GetResult().number_comments_lines_ << '\n';
	ofs << "total number of code lines: " << d.GetResult().number_code_lines_ << '\n';
	ofs << "total time of time files: " << d.GetTime() << " ms" << '\n';
	return ofs;
}

// Line 68-71 Consider creating a reference to avoid using the 'd.GetResult()' expression repeatedly
