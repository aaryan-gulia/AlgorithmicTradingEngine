//
// Created by Aaryan Gulia on 21/11/2023.
//

#ifndef ALGORITHMICTRADINGENGINE_ALPHAVANTAGEPROVIDER_H
#define ALGORITHMICTRADINGENGINE_ALPHAVANTAGEPROVIDER_H
#include <json/json.h>
#include <curl/curl.h>
#include <string>
#include "MarketDataProvider.h"

class AlphaVantageProvider : public MarketDataProvider{
private:
    static std::unordered_map<std::string,std::unordered_map<std::string, std::string>> functionMap;
public:
    const Json::Value fetchMarketData(const std::string& function,
                                                            const std::string& instrumentSymbol,
                                                            const std::string& apiKey);
};


#endif //ALGORITHMICTRADINGENGINE_ALPHAVANTAGEPROVIDER_H
