//Code by willhelmtell
// http://stackoverflow.com/questions/2616011/easy-way-to-parse-a-url-in-c-cross-platform

#include "url.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <functional>
using namespace std;

// ctors, copy, equality, ...

url::url(const std::string& url_s)
{
    parse(url_s);
}

void url::parse(const string& url_s)
{
    const string prot_end("://");
    string::const_iterator prot_i = search(url_s.begin(), url_s.end(),
                                           prot_end.begin(), prot_end.end());
    protocol_.reserve(distance(url_s.begin(), prot_i));
    transform(url_s.begin(), prot_i,
              back_inserter(protocol_),
              ptr_fun<int,int>(tolower)); // protocol is icase
    if( prot_i == url_s.end() )
        return;
    advance(prot_i, prot_end.length());
    string::const_iterator path_i = find(prot_i, url_s.end(), '/');
    host_.reserve(distance(prot_i, path_i));
    transform(prot_i, path_i,
              back_inserter(host_),
              ptr_fun<int,int>(tolower)); // host is icase
    string::const_iterator query_i = find(path_i, url_s.end(), '?');
    path_.assign(path_i, query_i);
    if( query_i != url_s.end() )
        ++query_i;
    query_.assign(query_i, url_s.end());
}

std::string url::protocol()
{
    return protocol_;
}

std::string url::host()
{
    return host_;
}

std::string url::path()
{
    return path_;
}

std::string url::query()
{
    return query_;
}
