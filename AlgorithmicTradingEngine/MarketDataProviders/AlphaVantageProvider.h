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

public:
    const Json::Value fetchMarketData(std::string& instrumentSymbol,
                                      std::string& interval,
                                      std::string& dataType,
                                      const std::string& apiKey) override;

    const Json::Value currencyMarketData(std::string& instrumentSymbol,
                                         std::string& interval,
                                         const std::string& apiKey,
                                         std::string& functionBase);
    const Json::Value equityMarketData(std::string& instrumentSymbol,
                                       std::string& interval,
                                       const std::string& apiKey,
                                       std::string& functionBase);
    const Json::Value commodityMarketData(std::string& instrumentSymbol,
                                          std::string& interval,
                                          const std::string& apiKey,
                                          std::string& functionBase);
};


#endif //ALGORITHMICTRADINGENGINE_ALPHAVANTAGEPROVIDER_H
