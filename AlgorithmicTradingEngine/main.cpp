
#include <iostream>
#include <string>
#include <json/json.h>
#include "MarketDataProviders/MarketDataAccess.h"
#include "DataManager/DataFrame.h"


int main() {
    std::string apiKey = "AZPUL0WUDJZ17T2S";
    std::string provider = "AlphaVantage";
    // Create an instance of MarketDataAccess
    MarketDataAccess marketDataAccess(provider,apiKey);

    // Retrieve historical data for a specific stock
    std::string interval = "daily";
    std::string dataType = "equity";
    std::string symbol = "ibm";
    Json::Value historicalData = marketDataAccess.fetchHistoricalData(symbol,interval,dataType);

    DataFrame<std::string> dataFrame(historicalData);
    std::cout<<dataFrame;

/*
    for (Json::Value::const_iterator it = timeSeriesData.begin(); it != timeSeriesData.end(); ++it) {
        const std::string& date = it.key().asString();
        const Json::Value& values = *it;

        double open = stod(values["1. open"].asString());
        double high = stod(values["2. high"].asString());
        double low = stod(values["3. low"].asString());
        double close = stod(values["4. close"].asString());
        double volume = stod(values["6. volume"].asString());

        std::cout << date << " - Open: " << open << ", High: " << high << ", Low: " << low << ", Close: " << close << ", Volume: "<<volume << std::endl;
    }
*/

    return 0;
}
