//
// Created by Aaryan Gulia on 21/11/2023.
//

#ifndef ALGORITHMICTRADINGENGINE_MARKETDATAACCESS_H
#define ALGORITHMICTRADINGENGINE_MARKETDATAACCESS_H
#include "MarketDataAccessor.h"

class MarketDataAccess: public MarketDataAccessor {
public:
    Json::Value fetchHistoricalData(const std::string& providerName,
                                            const std::string& instrumentSymbol,
                                            const std::string& interval,
                                            const std::string& dataType,
                                            const std::string& providerApiKey);
};


#endif //ALGORITHMICTRADINGENGINE_MARKETDATAACCESS_H
