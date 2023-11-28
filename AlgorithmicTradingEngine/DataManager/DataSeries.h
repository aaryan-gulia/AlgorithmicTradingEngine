//
// Created by Aaryan Gulia on 25/11/2023.
//

#ifndef ALGORITHMICTRADINGENGINE_DATASERIES_H
#define ALGORITHMICTRADINGENGINE_DATASERIES_H
#include <string>
#include "json/json.h"


template <typename T>
class DataSeries {
private:
    std::string m_seriesHeader;
    std::vector<T> m_seriesData;

public:
    DataSeries(std::string seriesHeader):m_seriesHeader(seriesHeader){}
    DataSeries(std::string seriesHeader, std::vector<T> seriesData);

    T& operator[](size_t index){
        return m_seriesData[index];
    }

    void addData(const T& data){
        m_seriesData.push_back(data);
    }
    std::string getHeader(){return m_seriesHeader;}
    int rows(){return m_seriesData.size();}
};



#endif //ALGORITHMICTRADINGENGINE_DATASERIES_H
