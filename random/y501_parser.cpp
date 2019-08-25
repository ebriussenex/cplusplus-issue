#include <iostream>
#include <string>
#include <memory>

class Node {
public:
	virtual int Evaluate() const = 0;

};

class Digit : public Node {
public:
	Digit(int d) : d_(d) {}
	int Evaluate() const override {
		return d_;
	}
private:
	int d_;
};

class Variable : public Node {
public:
	Variable(const int& x) : x_(x) {}
	int Evaluate() const override {
		return x_;
	}
private:
	const int& x_;
};

class Operation : public Node {
public:
	Operation(char op, std::shared_ptr<Node> left, std::shared_ptr<Node> right) :
		op_(op), left_(left), right_(right) {}
	int Evaluate() const override {
		if (op_ == '*') {
			return left_->Evaluate() * right_->Evaluate();
		}else if (op_ == '+') {
			return left_->Evaluate() + right_->Evaluate();
		}
		else if (op_ == '-') {
			return left_->Evaluate() - right_->Evaluate();
		}
		else if (op_ == '/') {
			return left_->Evaluate() / right_->Evaluate();
		}
		return 0;
	}
private:
	const char op_;
	std::shared_ptr<Node> left_;
	std::shared_ptr<Node> right_;
};

//Node Parse(const std::string& tokens, int& x) {
//	
//}

int main() {
	std::string tokens = "5+7-x*x+x";
	/*std::cout << "Enter expr ";
	std::cin >> tokens;
	int x;
	auto expr = Parse(tokens, x);*/
	int x;
	std::cout << "Enter x ";
	std::shared_ptr<Node> var1 = std::make_shared<Variable>(x);
	std::shared_ptr<Node> var2 = std::make_shared<Variable>(x);
	std::shared_ptr<Node> mul1 = std::make_shared<Operation>('*', var1, var2);
	std::shared_ptr<Node> dig1 = std::make_shared<Digit>(5);
	std::shared_ptr<Node> dig2 = std::make_shared<Digit>(7);
	std::shared_ptr<Node> var3 = std::make_shared<Variable>(x);

	std::shared_ptr<Node> plus1 = std::make_shared<Operation>('+', dig1, dig2);
	std::shared_ptr<Node> minus1 = std::make_shared<Operation>('-', plus1, mul1);
	std::shared_ptr<Node> plus2 = std::make_shared<Operation>('+', minus1, var3);

	while (std::cin >> x) {
		std::cout << plus2->Evaluate() << std::endl;
	}
	return 0;
}