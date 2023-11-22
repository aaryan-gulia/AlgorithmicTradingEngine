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
    const Json::Value fetchMarketData(const std::string& instrumentSymbol,
                                      std::string& interval,
                                      std::string& dataType,
                                      const std::string& apiKey) override;

    const Json::Value currencyMarketData(const std::string& instrumentSymbol,
                                        std::string& interval,
                                        const std::string& apiKey,
                                        const std::string& functionBase);
    const Json::Value equityMarketData(const std::string& instrumentSymbol,
                                       const std::string& interval,
                                       const std::string& apiKey);
    const Json::Value commodityMarketData(const std::string& instrumentSymbol,
                                          const std::string& interval,
                                          const std::string& apiKey);
};


#endif //ALGORITHMICTRADINGENGINE_ALPHAVANTAGEPROVIDER_H
