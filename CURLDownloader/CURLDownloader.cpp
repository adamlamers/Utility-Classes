/**
 * Adam Lamers
 * December 6th, 2010
 * CURL HTTP Downloader class
 */

#include "CURLDownloader.h"
#include <iostream>
#include <stdlib.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, dataBuffer *buffer)
{
    if(buffer->size == 0)
    {
        int dataLength = size * nmemb;
        buffer->size = dataLength;
        buffer->data = (byte*)malloc(buffer->size);
        if(!buffer->data) return 0;
        memcpy(buffer->data, ptr, dataLength);
        buffer->pos = dataLength;
        return dataLength;
    }
    else
    {
        int dataLength = size * nmemb;
        if(buffer->data)
        {
            buffer->size += dataLength;
            buffer->data = (byte*)realloc(buffer->data, buffer->size);
            if(!buffer->data) return 0;
            memcpy((char*)buffer->data + buffer->pos, ptr, dataLength);
            buffer->pos += dataLength;
        }
        else
            return 0;
        return dataLength;
    }
}

size_t write_data_file(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

CURLDownloader::CURLDownloader()
{
}

int CURLDownloader::downloadToFile(const char *URL, const char *localFilename)
{
    CURL *curl = curl_easy_init();
    if(curl)
    {
        FILE *localFile = fopen(localFilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_file);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, localFile);
        m_curlRes = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_lastHTTPResponseCode);
        curl_easy_cleanup(curl);
        fclose(localFile);
    }
    return m_curlRes;
}

int CURLDownloader::downloadToBuffer(const char *URL, dataBuffer *buffer)
{
    CURL *curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
        m_curlRes = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &m_lastHTTPResponseCode);
        curl_easy_cleanup(curl);
    }
    return m_curlRes;
}

long CURLDownloader::lastHTTPResponseCode()
{
    return m_lastHTTPResponseCode;
}

CURLDownloader::~CURLDownloader()
{
}
