//
// Created by Aaryan Gulia on 21/11/2023.
//

#ifndef ALGORITHMICTRADINGENGINE_MARKETDATAACCESSOR_H
#define ALGORITHMICTRADINGENGINE_MARKETDATAACCESSOR_H

#include "json/json.h"
#include <string>

class MarketDataAccessor{
public:
    virtual Json::Value fetchHistoricalData(const std::string& providerName,
                                            const std::string& instrumentSymbol,
                                            const std::string& interval,
                                            const std::string& dataType,
                                            const std::string& providerApiKey) = 0;
};
#endif //ALGORITHMICTRADINGENGINE_MARKETDATAACCESSOR_H
