#include <iostream>
#include <string>


int main() {
    std::string apiKey = "AZPUL0WUDJZ17T2S";
    std::string provider = "AlphaVantage";
    // Create an instance of MarketDataAccess
    MarketDataAccess marketDataAccess(provider,apiKey);

    // Retrieve historical data for a specific stock
    std::string interval = "daily";
    std::string dataType = "equityadjusted";
    std::string symbol = "ibm";
    Json::Value historicalData = marketDataAccess.fetchHistoricalData(symbol,interval,dataType);

    const Json::Value& timeSeriesData = historicalData;

//    for(const auto & it : timeSeriesData){
//        const std::string& date = it["date"].asString();
//        const std::string& value = it["value"].asString();
//
//        std::cout << date << " - Value: " << value<<std::endl;
//    }

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

    return 0;
}
