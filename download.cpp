#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

// you need to download and link this library to run the program https://curl.haxx.se/libcurl/

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <URL> <file>" << endl;
        return 1;
    }

    CURL *curl;
    FILE *fp;
    CURLcode res;
    string url = argv[1];
    string file = argv[2];

    curl = curl_easy_init();
    fp = fopen(file.c_str(), "wb");
    if (!curl || !fp) {
        cerr << "Error: could not initialize CURL or open the file." << endl;
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "Error: " << curl_easy_strerror(res) << endl;
        return 1;
    }
    curl_easy_cleanup(curl);
    fclose(fp);

    cout << "File " << file << " has been downloaded successfully." << endl;

    return 0;
}
