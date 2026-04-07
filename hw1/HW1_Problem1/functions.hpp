#include <map>
#include <string>
#include <vector>

void ParseCSV(const std::string& filename,
              std::map<int, std::string>& header_cols,
              std::map<std::string, std::vector<std::string>>& data_map);

int SumColumn(const std::string& column_name,
              std::map<std::string, std::vector<std::string>>& data_map);

double FilterMostFrequentAvg(
    const std::string& key_col, std::string& value_col,
    std::map<std::string, std::vector<std::string>>& data_map);

void SumTwoColumns(std::string& value_col1, std::string& value_col2,
                   const std::string& out_filename,
                   std::map<int, std::string>& header_cols,
                   std::map<std::string, std::vector<std::string>>& data_map);
