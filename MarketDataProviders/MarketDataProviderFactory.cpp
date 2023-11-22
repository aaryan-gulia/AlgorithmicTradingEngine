//
// Created by Aaryan Gulia on 21/11/2023.
//

#include "MarketDataProviderFactory.h"
#include "MarketDataProvider.h"
#include "AlphaVantageProvider.h"
#include <string>
#include <iostream>

std::shared_ptr<MarketDataProvider> MarketDataProviderFactory::createProvider
(const std::string& providerName){
    if(providerName == "AlphaVantage"){
        return std::make_shared<AlphaVantageProvider>();
    }
    else{
        throw std::invalid_argument("Unknown provider name: " + providerName);
    }
}