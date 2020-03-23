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
#include "simple_vector.h"


template <typename Token>
using Sentence = std::vector<Token>;


template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens) {
	std::vector<Sentence<Token>> target;
	Sentence<Token> sentence;
	for (size_t i = 0; i < tokens.size(); i++) {
		if (sentence.empty()) {
				sentence.push_back(std::move(tokens[i]));
		}
		else if (!sentence.empty()) {
			if (sentence.back().IsEndSentencePunctuation()) {
				if (!tokens[i].IsEndSentencePunctuation()) {
					target.push_back(std::move(sentence));
					sentence.clear();
				}
			}
			sentence.push_back(std::move(tokens[i]));
		}
		if (i == tokens.size() - 1) {
			target.push_back(std::move(sentence));
		}
	}
	return target;
}


struct TestToken {
	std::string data;
	bool is_end_sentence_punctuation = false;

	bool IsEndSentencePunctuation() const {
		return is_end_sentence_punctuation;
	}
	bool operator==(const TestToken& other) const {
		return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
	}
};

std::ostream& operator<<(std::ostream& stream, const TestToken& token) {
	return stream << token.data;
}

void TestSplitting() {
	ASSERT_EQUAL(
		SplitIntoSentences(std::vector<TestToken>({ 
													{"Split"},
													{"into"},
													{"sentences"},
													{"!"} 
													})),
		std::vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!"}}
			})
	);

	ASSERT_EQUAL(
		SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
		std::vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}}
			})
	);

	ASSERT_EQUAL(
		SplitIntoSentences(std::vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true} })),
		std::vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
			{{"Without"}, {"copies"}, {".", true}},
			})
			);
}
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TestRunner tr;
	RUN_TEST(tr, TestSplitting);
	return 0;
}
