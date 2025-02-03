//
// Created by krzys on 03.02.2025.
//

#include "CSVLogger.h"

#include "Config.h"
#include <iostream>
#include <sstream>

CSVLogger::CSVLogger()
	: n_columns(0),
	  flush_counter(0) {}

CSVLogger::CSVLogger(const std::filesystem::path &filename, int n_columns)
	: filepath(PROJECT_ROOT / filename),
	  n_columns(n_columns),
	  flush_counter(0)
{
	set_col_number(n_columns);
	set_output_file(filename);
}

CSVLogger::~CSVLogger() {
	file.flush();
	file.close();
}

void CSVLogger::set_output_file(const std::filesystem::path &filepath) {
	std::filesystem::path abs_filepath(PROJECT_ROOT);
	abs_filepath /= filepath;
	file = std::ofstream(abs_filepath, std::ios_base::app);
	if ( ! file.is_open() )
		std::cout << "Error while trying to open the file: "
				  << "'" << filepath << "': " << file.bad() << std::endl;
}

void CSVLogger::set_col_number(int n) {
	n_columns = n;
	row.resize(n_columns, "");
}

void CSVLogger::commit_row() {
	std::ostringstream full_row {};
	for ( const auto& el : row ) {
		full_row << el << ';';
	}
	full_row << '\n';
	file << full_row.str();
	row.clear();
	row.resize(n_columns, "");

	if ( file.bad() )
		printf("File error occured!\n");

	if ( flush_counter > 100 ) {
		file.flush();
		flush_counter = 0;
	}
	++flush_counter;
}

void CSVLogger::add(int col, const std::string& content) {
	if ( ! is_in_bounds(col) )
		return;

	row.at(col) = content;
}

void CSVLogger::add(int col, const int& content) {
	if ( ! is_in_bounds(col) )
		return;

	row.at(col) = std::to_string(content);
}

void CSVLogger::add(int col, const float& content) {
	if ( ! is_in_bounds(col) )
		return;

	row.at(col) = std::to_string(content);
}
