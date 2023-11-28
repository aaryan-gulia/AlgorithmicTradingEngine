//
// Created by Aaryan Gulia on 25/11/2023.
//

#ifndef ALGORITHMICTRADINGENGINE_DATAFRAME_H
#define ALGORITHMICTRADINGENGINE_DATAFRAME_H
#include <iostream>
#include <iomanip>
#include <string>
#include "DataSeries.h"
#include "json/json.h"

template <typename T>
class DataFrame {
private:
    std::vector<DataSeries<T>> m_columns;
    DataSeries<std::string> timestamp = DataSeries<std::string> ("timestamp");

public:

    DataFrame() = default;

    explicit DataFrame(Json::Value jsonData){
        for(const auto& key:(jsonData[(jsonData.getMemberNames())[0]].getMemberNames())){
            DataSeries<T> valueSeries(key);
            m_columns.push_back(valueSeries);
        }
        for(const auto& date : jsonData.getMemberNames()){
            int valueNum = 0;
            const Json::Value& values = jsonData[date];
            timestamp.addData(date);
            for(const auto& key : values.getMemberNames()){
                m_columns[valueNum++].addData((values[key].asString()));
            }
        }
    }
    std::vector<std::string> getColumnHeaders(){
        std::vector<std::string> headers;
        for (auto column : m_columns)
            headers.push_back(column.getHeader());
        return headers;
    }

    std::vector<T> getColumn(std::string & columnHeader);

    void addColumn(std::string, std::vector<T>);

    void addColumn(DataSeries<T>);

    void addRow(std::string time, std::vector<T> data);

    friend std::ostream& operator<<(std::ostream& os, DataFrame<T>& df) {
        df.printToStream(os);
        return os;
    }

private:
    void printToStream(std::ostream& os){
        // Print column names
        os << std::setw(10) << "Columns: " << timestamp.getHeader() << " ";
        for (const auto& column : getColumnHeaders()) {
            os << std::setw(20) << column;
        }
        os << "\n";

        // Print data
        size_t rows = timestamp.rows();
        for (size_t i = 0; i < rows; ++i) {
            os << std::setw(5) << "Row " << std::setw(2) << i + 1 << " : " << timestamp[i];
            std::for_each(m_columns.begin(),m_columns.end(),[&os, i](auto column){os << std::setw(20)<< column[i];});
            os << "\n";
        }
    }
};


#endif //ALGORITHMICTRADINGENGINE_DATAFRAME_H
