/**
 * Adam Lamers
 * December 6th, 2010
 * CURL HTTP Downloader class
 */

#ifndef CURLDOWNLOADER_H
#define CURLDOWNLOADER_H

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/types.h>

#ifndef byte
    typedef unsigned char byte;
#endif

struct dataBuffer
{
    dataBuffer()
    {
        this->size = 0;
        this->pos = 0;
        this->data = 0;
    }

    long size;
    long pos;
    byte *data;
};

class CURLDownloader
{
    public:
        CURLDownloader();
        int downloadToFile(const char *URL, const char *localFilename);
        int downloadToBuffer(const char *URL, dataBuffer *buffer);;
        long lastHTTPResponseCode();
        virtual ~CURLDownloader();

    protected:
    long m_lastHTTPResponseCode;
    CURLcode m_curlRes;

    private:
};

#endif // CURLDOWNLOADER_H
