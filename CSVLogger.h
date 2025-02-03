//
// Created by krzys on 03.02.2025.
//

#ifndef CSVLOGGER_H
#define CSVLOGGER_H


#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

class CSVLogger {
public:
	CSVLogger();
	CSVLogger(const std::filesystem::path &filename, int n_columns);
	~CSVLogger();

	void commit_row();
	void add(int col, const std::string& content);
	void add(int col, const int& content);
	void add(int col, const float& content);

	void set_output_file(const std::filesystem::path &filename);
	void set_col_number(int n);

private:
	std::filesystem::path filepath;
	std::ofstream file;
	int n_columns;
	std::vector<std::string> row;

	int flush_counter;

	bool is_in_bounds(int col_index) const { return col_index < row.size(); }

};


#endif //CSVLOGGER_H
