#pragma once
#include<fstream>
#include<string>
struct Result

{

	size_t number_empty_lines_{ 0 };
	size_t number_comments_lines_{ 0 };
	size_t number_code_lines_{ 0 };
	Result operator+=(const Result& r);
	Result() = default;
};
class CppFile
{

	void Parce(std::ifstream& f);
public:
	CppFile(std::string&& file_name = "") :stream_(file_name) {}
	void Start();
	size_t GetEmptyLines() const noexcept;
	size_t GetCodeLines() const noexcept;
	size_t GetCommentsLines() const noexcept;
private:
	Result result_;

	std::ifstream stream_;

};

