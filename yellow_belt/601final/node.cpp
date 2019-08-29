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
	switch (cmp_) {
	case Comparison::Less:
		return date < date_;
	case Comparison::Equal:
		return date == date_;
	case Comparison::Greater:
		return date > date_;
	case Comparison::GreaterOrEqual:
		return date >= date_;
	case Comparison::LessOrEqual:
		return date <= date_;
	case Comparison::NotEqual:
		return date != date_;
	}

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
	switch (cmp_) {
	case Comparison::Less:
		return event < event_;
	case Comparison::Equal:
		return event == event_;
	case Comparison::Greater:
		return event > event_;
	case Comparison::GreaterOrEqual:
		return event >= event_;
	case Comparison::LessOrEqual:
		return event <= event_;
	case Comparison::NotEqual:
		return event != event_;
	}
}
