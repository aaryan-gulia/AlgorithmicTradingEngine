//
// Created by Aaryan Gulia on 21/11/2023.
//
#include "AlphaVantageProvider.h"
#include "MarketDataProvider.h"
#include "json/json.h"
#include "curl/curl.h"

using std::string;

const Json::Value AlphaVantageProvider::fetchMarketData(const std::string& function,
                                                        const std::string& instrumentSymbol,
                                                        const std::string& apiKey)
{
    std::string url = "https://www.alphavantage.co/query?function="+ function
            +"&symbol="+ instrumentSymbol +"&outputsize=full&apikey=" + apiKey;
    std::string response = connect(url);
    Json::Value root = parseJson(response);
    const Json::Value timeSeriesData = root["Time Series (Daily)"];
    return timeSeriesData;
}