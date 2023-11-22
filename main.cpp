
#include <iostream>
#include <string>
#include <json/json.h>
#include "MarketDataProviders/MarketDataAccess.h"


int main() {
    std::string apiKey = "JJV4T6R4GWVE3PP4";
    std::string provider = "AlphaVantage";
    // Create an instance of MarketDataAccess
    MarketDataAccess marketDataAccess(provider,apiKey);

    // Retrieve historical data for a specific stock
    std::string interval = "Daily";
    std::string dataType = "FX";
    Json::Value historicalData = marketDataAccess.fetchHistoricalData("EUR/USD",interval,dataType);



    const Json::Value& timeSeriesData = historicalData;
    for (Json::Value::const_iterator it = timeSeriesData.begin(); it != timeSeriesData.end(); ++it) {
        const std::string& date = it.key().asString();
        const Json::Value& values = *it;

        double open = stod(values["1. open"].asString());
        double high = stod(values["2. high"].asString());
        double low = stod(values["3. low"].asString());
        double close = stod(values["4. close"].asString());
        //double volume = stod(values["5. volume"].asString());

        std::cout << date << " - Open: " << open << ", High: " << high << ", Low: " << low << ", Close: " << close << std::endl;
    }

    return 0;
}
