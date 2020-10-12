#include "parseline.h"
#include <cwctype>
#include<algorithm>
void CppFile::Parce(std::ifstream& f)
{
	bool code = false;
	bool comment = false;
	bool is_comment = false;

	for (auto t = std::istreambuf_iterator<char>(f);; ) {
		t = std::find_if(t, std::istreambuf_iterator<char>(), [&code, is_comment, &f, &comment](char t)
			{
				if (t == '\n' || t == '/' || t == '*') { return true; }
				if (!std::iswspace(t))
				{
					if (is_comment) { comment = true; }
					else { code = true; }
				}
				return  t == '\"';
			});
		if (t == std::istreambuf_iterator<char>())
		{
			result_ += {(!code && !comment), comment || is_comment, code};
			break;
		}
		if (*(t++) == '\n')
		{

			result_ += {(!code && !comment), comment || is_comment, code};
			code = false;
			comment = false;

		}
		else if (*t == '/' || *t == '*')
		{
			char prev = *(t++);;
			if (t != std::istreambuf_iterator<char>())
			{
				if (prev == '*' && *t == '/')
				{
					comment = true;
					is_comment = false;
				}
				else if (*t == '/')
				{
					comment = true;
					t = std::find(std::next(t), std::istreambuf_iterator<char>(), '\n');
				}
				else if (*t == '*')
				{
					comment = true;
					is_comment = true;
				}
			}
		}
		else if (*t == '\"')
		{
			t = std::find_if(std::next(t), std::istreambuf_iterator<char>(), [](char t) {return t == '\"' || t == '\n'; });
		}

	}

}

void CppFile::Start()
{
	Parce(stream_);
}

size_t CppFile::GetEmptyLines() const noexcept
{
	return result_.number_empty_lines_;
}

size_t CppFile::GetCodeLines() const noexcept
{
	return result_.number_code_lines_;
}

size_t CppFile::GetCommentsLines() const noexcept
{
	return result_.number_comments_lines_;
}

Result Result::operator+=(const Result& r)
{
	number_empty_lines_ += r.number_empty_lines_;
	number_comments_lines_ += r.number_comments_lines_;
	number_code_lines_ += r.number_code_lines_;

	return *this;
}
