#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <cstdint>

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
#include <regex>
#include <iterator>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
public:
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
		return db_.at(person);
	}
	void AddNewTask(const std::string& person) {
		db_[person][TaskStatus::NEW]++;
	}
	void RemoveZeroStatus(TasksInfo& ti) {
		std::vector <TaskStatus> v;
		for (const auto& item : ti) {
			if (item.second == 0)	v.push_back(item.first);
		}
		for (const auto status : v) {
			ti.erase(status);
		}
	}
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const std::string& person, int task_count) {
		TasksInfo updated, untouched;
		for (size_t i = 0; i < 3; i++) {
			TaskStatus current = static_cast<TaskStatus>(i);
			TaskStatus next = static_cast<TaskStatus>(i + 1);
			updated[next] = std::min(task_count, db_[person][current]);
			task_count -= updated[next];
		}
		for (size_t i = 0; i < 3; i++) {
			TaskStatus current = static_cast<TaskStatus>(i);
			TaskStatus next = static_cast<TaskStatus>(i + 1);
			untouched[current] = db_[person][current] - updated[next];
			db_[person][current] += updated[current] - updated[next];
		}
		db_[person][TaskStatus::DONE] += updated[TaskStatus::DONE];
		RemoveZeroStatus(updated);
		RemoveZeroStatus(untouched);
		return { updated, untouched };
	}
private:
	std::map <std::string, TasksInfo> db_;
};


void PrintTasksInfo(const TasksInfo& tasks_info) {
	if (tasks_info.count(TaskStatus::NEW)) {
		std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
	}
	if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
		std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
	}
	if (tasks_info.count(TaskStatus::TESTING)) {
		std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
	}
	if (tasks_info.count(TaskStatus::DONE)) {
		std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
	}
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
	std::cout << "Updated: [";
	PrintTasksInfo(updated_tasks);
	std::cout << "] ";

	std::cout << "Untouched: [";
	PrintTasksInfo(untouched_tasks);
	std::cout << "] ";

	std::cout << std::endl;
}

int main() {
	TeamTasks tasks;
	TasksInfo updated_tasks;
	TasksInfo untouched_tasks;

	///* TEST 1 */
	std::cout << "Alice" << std::endl;

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
		2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
	PrintTasksInfo(updated_tasks, untouched_tasks);

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	std::cout << std::endl;
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	std::cout << std::endl;

	///* TEST 2 */
	std::cout << "\nJack" << std::endl;

	tasks.AddNewTask("Jack");

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	//tasks.AddNewTask("Jack");

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

	//tasks.AddNewTask("Jack");

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
	//std::cout << std::endl;

	///* TEST 3 */
	//std::cout << "\nLisa" << std::endl;

	//for (auto i = 0; i < 5; ++i) {
	//	tasks.AddNewTask("Lisa");
	//}

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	//for (auto i = 0; i < 5; ++i) {
	//	tasks.AddNewTask("Lisa");
	//}

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": 2}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
	//std::cout << std::endl;

	//tasks.AddNewTask("Lisa");

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	//PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
	//std::cout << std::endl;

	//tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
	//PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

	return 0;
}
