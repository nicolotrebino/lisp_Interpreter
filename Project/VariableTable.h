#ifndef VARIABLETABLE_H
#define VARIABLETABLE_H

#include <map>
#include <string>
#include <vector>

class VariableTable {
public:
	VariableTable() = default;
	~VariableTable() = default;

	VariableTable(const VariableTable& other) = delete;
	VariableTable& operator=(const VariableTable& other) = delete;

	// If the variable is already present in the map its value will be changed
	// If the variable is not already present it will be created
	void setVar(const std::string& name, int64_t value) {
		variable_table[name] = value;
	}

	// Method to find the value of a variable knowing the name
	int64_t getVar(const std::string& varName) const {
		auto it = variable_table.find(varName);
		if (it != variable_table.end()) {
			// Returns the value associated with the variable 
			// whose name is the string passed as a parameter
			return it->second;
		}
		else {
			std::stringstream tmp{};
			tmp << "variable '" << varName << "' not found in the Variable Table";
			throw EvaluationError(tmp.str());
		}
	}

private:
	std::map<std::string, int64_t> variable_table;
};
#endif
