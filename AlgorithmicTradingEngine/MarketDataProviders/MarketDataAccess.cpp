//
// Created by Aaryan Gulia on 21/11/2023.
//
#include <string>
#include "MarketDataAccess.h"
#include "MarketDataProviderFactory.h"
#include "MarketDataProvider.h"
#include "json/json.h"

Json::Value MarketDataAccess::fetchHistoricalData(std::string& instrumentSymbol,
                                                  std::string& interval,
                                                  std::string& dataType){
    std::shared_ptr<MarketDataProvider> marketDataProvider =
            MarketDataProviderFactory::createProvider(providerName);
    Json::Value marketData = marketDataProvider->fetchMarketData(instrumentSymbol, interval, dataType, providerApiKey);
    return marketData;
}