//
// Created by Aaryan Gulia on 21/11/2023.
//
#include "AlphaVantageProvider.h"
#include "json/json.h"
#include <cctype>

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
        return currencyMarketData(instrumentSymbol, const_cast<string &>(interval), apiKey, functionBase);
    }
    else if(dataType == "equity"){
        return equityMarketData(instrumentSymbol, interval, apiKey);
    }
    else if(dataType == "commodity"){
        return commodityMarketData(instrumentSymbol, interval, apiKey);
    }
    else{
        throw std::invalid_argument("Invalid dataType argument for AlphaVantage API: " + dataType);
    }
}

const Json::Value AlphaVantageProvider::currencyMarketData(const std::string& instrumentSymbol,
                                     std::string& interval,
                                     const std::string& apiKey,
                                     const std::string& functionBase){
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
        else
            url = "https://www.alphavantage.co/query?function="+function+"&symbol="+ toCurrency +"&market="+ fromCurrency +"&outputsize=full&apikey=d" + apiKey;
    }
    else{
        if(functionBase == "FX_")function = "FX_INTRADAY";
        else function = "CRYPTO_INTRADAY";

        if(interval == "1min" || interval == "5min" || interval == "15min" || interval == "30min" || interval == "60min"){
            if(functionBase == "FX_")
                url = "https://www.alphavantage.co/query?function="+function+"&from_symbol="+ fromCurrency +"&to_symbol="+ toCurrency + "&interval="+interval+"&outputsize=full&apikey=d" + apiKey;
            else
                url = "https://www.alphavantage.co/query?function="+function+"&symbol="+ toCurrency +"&market="+ fromCurrency + "&interval="+interval+"&outputsize=full&apikey=d" + apiKey;
        }
        else{
            throw std::invalid_argument("Invalid interval argument for AlphaVantage Currency APIs: " + interval);
        }
    }
    std::string response = connect(url);
    Json::Value root = parseJson(response);
    if(!isdigit(interval[0])){
        interval[0] = toupper(interval[0]);
    }
    if(functionBase == "FX_")
        return root["Time Series FX ("+interval+")"];
    else
        return root["Time Series Crypto ("+interval+")"];
}


const Json::Value AlphaVantageProvider::equityMarketData(const std::string& instrumentSymbol,
                                   const std::string& interval,
                                   const std::string& apiKey){
    throw std::runtime_error("EQUITY FUNCTIONALITY NOT READ");
}
const Json::Value AlphaVantageProvider::commodityMarketData(const std::string& instrumentSymbol,
                                      const std::string& interval,
                                      const std::string& apiKey){
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