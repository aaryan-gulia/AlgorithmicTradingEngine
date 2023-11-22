
#include <iostream>
#include <string>
#include <vector>
#include <json/json.h>
#include "MarketDataProviders/MarketDataAccessor.h"
#include "MarketDataProviders/MarketDataAccess.h"


int main() {
    const std::string apiKey = "JJV4T6R4GWVE3PP4";
    const std::string symbol = "IBM";
    // Create an instance of MarketDataAccess
    MarketDataAccess marketDataAccess;

    // Retrieve historical data for a specific stock
    std::string instrumentSymbol = "AAPL";
    Json::Value historicalData = marketDataAccess.fetchHistoricalData("AlphaVantage","IBM","Daily","Stock","JJV4T6R4GWVE3PP4");



    const Json::Value& timeSeriesData = historicalData;
    for (Json::Value::const_iterator it = timeSeriesData.begin(); it != timeSeriesData.end(); ++it) {
        const std::string& date = it.key().asString();
        const Json::Value& values = *it;

        double open = stod(values["1. open"].asString());
        double high = stod(values["2. high"].asString());
        double low = stod(values["3. low"].asString());
        double close = stod(values["4. close"].asString());
        double volume = stod(values["5. volume"].asString());

        std::cout << date << " - Open: " << open << ", High: " << high << ", Low: " << low << ", Close: " << close << ", Volume: " << volume << std::endl;
    }

    return 0;
}
