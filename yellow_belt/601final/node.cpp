#include "node.h"

template <typename T>
bool Compare(const T& lhs, const T& rhs, const Comparison& cmp) {
	switch (cmp) {
	case Comparison::Less:
		return lhs < rhs;
	case Comparison::Equal:
		return lhs == rhs;
	case Comparison::Greater:
		return lhs > rhs;
	case Comparison::GreaterOrEqual:
		return lhs >= rhs;
	case Comparison::LessOrEqual:
		return lhs <= rhs;
	case Comparison::NotEqual:
		return lhs != rhs;
	}
}

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const
{
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) :
	cmp_(cmp), date_(date)
{}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const
{
	return Compare(date, date_, cmp_);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_opeartion, const std::shared_ptr <Node>& left, const std::shared_ptr <Node>& right) :
	logic_op_(logical_opeartion), left_(left), right_(right) 
{}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const
{
	switch (logic_op_) {
	case(LogicalOperation::Or):
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
	case(LogicalOperation::And):
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& comparison, const std::string& event) :
	cmp_(comparison), event_(event)
{}

bool EventComparisonNode::Evaluate(const Date & date, const std::string & event) const
{
	return Compare(event, event_, cmp_);
}
