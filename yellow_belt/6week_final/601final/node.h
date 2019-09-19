#pragma once
#include "date.h"
#include "token.h"
#include <string>
#include <map>
#include <set>

template <typename T>
bool Compare(const T& lhs, const T& rhs, const Comparison& cmp);

class Node {
public:
	Node() {}
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode() {}
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& comparison, const Date& date);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& comparison, const std::string& event);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const Comparison cmp_;
	const std::string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& logical_opeartion, const std::shared_ptr <Node>& left, const std::shared_ptr <Node>& right);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const LogicalOperation logic_op_;
	const std::shared_ptr <Node> left_;
	const std::shared_ptr <Node> right_;
};