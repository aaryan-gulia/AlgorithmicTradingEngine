//
// Created by Aaryan Gulia on 21/11/2023.
//
#include <string>
#include "MarketDataAccessor.h"
#include "MarketDataAccess.h"
#include "MarketDataProviderFactory.h"
#include "MarketDataProvider.h"
#include "AlphaVantageProvider.h"
#include "json/json.h"

Json::Value MarketDataAccess::fetchHistoricalData(const std::string& providerName,
                                const std::string& instrumentSymbol,
                                const std::string& interval,
                                const std::string& dataType,
                                const std::string& providerApiKey){
    std::shared_ptr<MarketDataProvider> marketDataProvider =
            MarketDataProviderFactory::createProvider(providerName);
    Json::Value marketData = marketDataProvider->fetchMarketData("TIME_SERIES_DAILY", instrumentSymbol, providerApiKey);
    return marketData;
}