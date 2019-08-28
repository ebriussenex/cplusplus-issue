#pragma once
#include "date.h"
#include "token.h"
#include <string>

class Node {
public:
	Node() {}
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& comparison, const Date& date);
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	Comparison cmp_;
	Date date_;
};

class EventComparisonNode : public Node {
	bool Evaluate(const Date& date, const std::string& event) const override;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& logical_opeartion, const std::shared_ptr <Node>& left, const std::shared_ptr <Node>& right) :
		logic_op_(logical_opeartion), left_(left), right_(right) {}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const LogicalOperation logic_op_;
	std::shared_ptr <Node> left_;
	std::shared_ptr <Node> right_;
};