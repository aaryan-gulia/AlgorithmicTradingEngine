#include "AlphaVantageProvider.h"
#include "json/json.h"
#include <cctype>
#include "iostream"

using std::string;

const Json::Value AlphaVantageProvider::fetchMarketData(const std::string& instrumentSymbol,
                                                        std::string& interval,
                                                        std::string& dataType,
                                                        const std::string& apiKey){
    string function;
    std::transform(dataType.begin(), dataType.end(), dataType.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if(dataType == "fx"){
        string functionBase = "FX_";
        return currencyMarketData(instrumentSymbol, interval, apiKey, functionBase);
    }
    else if(dataType == "crypto"){
        string functionBase = "DIGITAL_CURRENCY_";
        return currencyMarketData(instrumentSymbol, interval, apiKey, functionBase);
    }
    else if(dataType == "equity"){
        string functionBase = "";
        return equityMarketData(instrumentSymbol, interval, apiKey, functionBase);
    }
    else if(dataType == "equityadjusted"){
        string functionBase = "_ADJUSTED";
        return equityMarketData(instrumentSymbol, interval, apiKey, functionBase);
    }
    else if(dataType == "commodity"){
        string functionBase;
        return commodityMarketData(instrumentSymbol, interval, apiKey, functionBase);
    }
    else{
        throw std::invalid_argument("Invalid dataType argument for AlphaVantage API: " + dataType);
    }
}

const Json::Value AlphaVantageProvider::currencyMarketData(const std::string& instrumentSymbol,
                                     std::string& interval,
                                     const std::string& apiKey,
                                     std::string& functionBase){
    string url,function;
    auto split = instrumentSymbol.find('/');
    if(split >= instrumentSymbol.size()){
        throw std::invalid_argument("Invalid instrumentSymbol argument for AlphaVantage Currency APIs: " + instrumentSymbol);
    }
    string fromCurrency = instrumentSymbol.substr(split + 1);
    string toCurrency = instrumentSymbol.substr(0, split);
    std::transform(interval.begin(), interval.end(), interval.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if(interval == "daily" || interval == "weekly" || interval == "monthly"){
        function = functionBase + interval;
        if (functionBase == "FX_")
            url = "https://www.alphavantage.co/query?function="+function+"&from_symbol="+ fromCurrency +"&to_symbol="+ toCurrency +"&outputsize=full&apikey=d" + apiKey;
        else if (functionBase == "DIGITAL_CURRENCY_")
            url = "https://www.alphavantage.co/query?function="+function+"&symbol="+ toCurrency +"&market="+ fromCurrency +"&outputsize=full&apikey=d" + apiKey;
    }
    else if(interval == "1min" || interval == "5min" || interval == "15min" || interval == "30min" || interval == "60min") {
        if (functionBase == "FX_") {
            function = "FX_INTRADAY";
            url = "https://www.alphavantage.co/query?function=" + function + "&from_symbol=" + fromCurrency +
                  "&to_symbol=" + toCurrency + "&interval=" + interval + "&outputsize=full&apikey=d" + apiKey;
        }
        else if (functionBase == "DIGITAL_CURRENCY_") {
            function = "CRYPTO_INTRADAY";
            url = "https://www.alphavantage.co/query?function=" + function + "&symbol=" + toCurrency + "&market=" +
                  fromCurrency + "&interval=" + interval + "&outputsize=full&apikey=d" + apiKey;
        }
    }
    else{
        throw std::invalid_argument("Invalid interval argument for AlphaVantage Currency APIs: " + interval);
    }
    std::string response = connect(url);
    Json::Value root = parseJson(response);
    if(!isdigit(interval[0])){
        interval[0] = toupper(interval[0]);
    }
    return root[(functionBase == "FX_" ? "Time Series FX (" : "Time Series Crypto (") + interval + ")"];
}


const Json::Value AlphaVantageProvider::equityMarketData(const std::string& instrumentSymbol,
                                                         std::string& interval,
                                                         const std::string& apiKey,
                                                         std::string& functionBase){
    string url,function;

    if(interval == "daily" || interval == "weekly" || interval == "monthly") {
        function = "TIME_SERIES_" + interval + functionBase;
        url = "https://www.alphavantage.co/query?function=" + function + "&symbol=" + instrumentSymbol +
              "&outputsize=full&apikey=" + apiKey;
    }
    else if(interval == "1min" || interval == "5min" || interval == "15min" || interval == "30min" || interval == "60min") {
        function="TIME_SERIES_INTRADAY";
        if (functionBase == "_ADJUSTED") {
            url = "https://www.alphavantage.co/query?function=" + function + "&symbol=" + instrumentSymbol + "&interval=" + interval +
                  "&adjusted=true&outputsize=full&apikey=" + apiKey;
        } else {
            url = "https://www.alphavantage.co/query?function=" + function + "&symbol=" + instrumentSymbol +
                  "&interval=" + interval +
                  "&adjusted=false&outputsize=full&apikey=" + apiKey;
        }
    }
    else{
        throw std::invalid_argument("Invalid interval argument for AlphaVantage Equity Market APIs: " + interval);
    }
    std::string response = connect(url);
    Json::Value root = parseJson(response);
    if(!isdigit(interval[0])){
        interval[0] = toupper(interval[0]);
    }
    if(functionBase.size()>0)
        functionBase = "Adjusted";
    return root[(interval == "Daily" || interval == "1min" || interval == "5min" || interval == "15min" || interval == "30min" || interval == "60min" ?
                 "Time Series (" + interval + ")" : interval +" "+ functionBase +" Time Series")];
}

const Json::Value AlphaVantageProvider::commodityMarketData(const std::string& instrumentSymbol,
                                                            std::string& interval,
                                                            const std::string& apiKey,
                                                            std::string& functionBase){
    std::string url = "https://www.alphavantage.co/query?function="+instrumentSymbol+"&interval="+interval+"&apikey="+apiKey;
    std::string response = connect(url);
    Json::Value root = parseJson(response);
    std::cout<<url<<std::endl;
    return root["data"];
    throw std::runtime_error("COMMODITY FUNCTIONALITY NOT READ");
}



//{
//    std::string url = "https://www.alphavantage.co/query?function="+ function
//            +"&symbol="+ instrumentSymbol +"&outputsize=full&apikey=" + apiKey;
//    std::string response = connect(url);
//    Json::Value root = parseJson(response);
//    const Json::Value timeSeriesData = root["Time Series (Daily)"];
//    return timeSeriesData;
//}