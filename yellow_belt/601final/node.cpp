#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const
{
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) :
	cmp_(cmp), date_(date)
{}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const
{

}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const
{
	switch (logic_op_) {
	case(LogicalOperation::Or):
		return left_ || right_;
	case(LogicalOperation::And):
		return left_ && right_;
	}
}