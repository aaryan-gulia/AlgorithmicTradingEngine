//
// Created by Aaryan Gulia on 21/11/2023.
//


#include "MarketDataProvider.h"
#include<string>
#include<iostream>
#include <curl/curl.h>
#include <json/json.h>

using namespace std;
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string MarketDataProvider::connect(const string& url) {
    // Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a new curl easy handle
    CURL *curl = curl_easy_init();

    // Set the URL to fetch
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set the write callback function to capture the response
    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the HTTP request
    curl_easy_perform(curl);
    long responseCode;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    if (responseCode != 200) {
        cout << "Error: API returned HTTP code " << responseCode << endl;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return "";
    }
    // Cleanup curl resources
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    // Return the captured JSON response
    return response;
}

Json::Value MarketDataProvider::parseJson(const string& response){
    // Parse the JSON response
    Json::Value root;
    Json::Reader reader;
    bool success = reader.parse(response, root);
    if (!success) {
        cout << "Error: Could not parse JSON response" << endl;
        return "";
    }
    return root;
}