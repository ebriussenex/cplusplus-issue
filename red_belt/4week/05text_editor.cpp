#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <cstdint>
#include <memory>
#include <random>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cfenv>
#include <iomanip>

#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <vector>
#include <tuple>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include <forward_list>
#include <bitset>
#include <algorithm>
#include <string>
#include <string_view>
#include <regex>
#include <iterator>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

#include "test_runner.h"
#include "profile.h"


class Editor {
public:
	// –еализуйте конструктор по умолчанию и объ€вленные методы
	Editor() : cursor_(text_.begin()) {
	}
	void Left() {
		if (cursor_ != text_.begin())	cursor_--;
	}
	void Right() {
		if (cursor_ != text_.end())	  cursor_++;
	}
	void Insert(char token) {
		text_.insert(cursor_, token);
	}
	void Cut(size_t tokens = 1) {
		buffer_.clear();
		auto temp_it = cursor_;
		if (std::distance(cursor_, text_.end()) < tokens) {
			tokens = std::distance(cursor_, text_.end());
		}
		std::advance(cursor_, tokens);
		buffer_.splice(buffer_.begin(), text_, temp_it, cursor_);
	}
	void Copy(size_t tokens = 1) {
		buffer_.clear();
		auto temp_it = cursor_;
		if (std::distance(cursor_, text_.end()) < tokens) {
			tokens = std::distance(cursor_, text_.end());
		}
		std::advance(temp_it, tokens);
		buffer_.assign(cursor_, temp_it);
	}
	void Paste() {
		text_.insert(cursor_, buffer_.begin(), buffer_.end());
	}
	std::string GetText() const {
		std::string text;
		text.reserve(text_.size());
		for (auto item : text_) {
			text.push_back(item);
		}
		return text;
	}
private:
	std::list<char> text_;
	std::list<char> buffer_;
	std::list<char>::iterator cursor_;
};

void TypeText(Editor& editor, const std::string& text) {
	for (char c : text) {
		editor.Insert(c);
	}
}

void TestEditing() {
	{
		Editor editor;

		const size_t text_len = 12;
		const size_t first_part_len = 7;
		TypeText(editor, "hello, world");
		for (size_t i = 0; i < text_len; ++i) {
			editor.Left();
		}
		editor.Cut(first_part_len);
		for (size_t i = 0; i < text_len - first_part_len; ++i) {
			editor.Right();
		}
		TypeText(editor, ", ");
		editor.Paste();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "world, hello");
	}
	{
		Editor editor;

		TypeText(editor, "misprnit");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Right();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "misprint");
	}
}

void TestReverse() {
	Editor editor;

	const std::string text = "esreveR";
	for (char c : text) {
		editor.Insert(c);
		editor.Left();
	}

	ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
	Editor editor;
	ASSERT_EQUAL(editor.GetText(), "");

	editor.Left();
	editor.Left();
	editor.Right();
	editor.Right();
	editor.Copy(0);
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
	Editor editor;

	editor.Paste();
	TypeText(editor, "example");
	editor.Left();
	editor.Left();
	editor.Paste();
	editor.Right();
	editor.Paste();
	editor.Copy(0);
	editor.Paste();
	editor.Left();
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "example");
}

void TestCut()
{
	Editor editor;
	//1
	editor.Cut(10);
	editor.Insert('a');
	editor.Left();
	//2
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	//3
	editor.Cut(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	TypeText(editor, "bcde");
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcde");
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	//5
	editor.Cut(5);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	//6
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bcde");
	editor.Right();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bde");
	editor.Cut(1);
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
	Editor editor;
	//1
	editor.Copy(10);
	editor.Insert('a');
	editor.Paste();
	editor.Left();
	ASSERT_EQUAL(editor.GetText(), "a");
	//2
	editor.Copy(1);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");//between a
	////3
	editor.Copy(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");
	TypeText(editor, "bcde");
	editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
	////4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcdea");
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	LOG_DURATION("Total tests duration");
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	RUN_TEST(tr, TestCut);
	RUN_TEST(tr, TestCopy);
	return 0;
}
