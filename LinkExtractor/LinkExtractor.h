#ifndef LINKEXTRACTOR_H_INCLUDED
#define LINKEXTRACTOR_H_INCLUDED

#include <list>
#include <string>

class LinkExtractor
{

    public:
        LinkExtractor();
        std::list<std::string> links();
        void setSource(const char *source, int sourceLength);
        void setFile(const char *filename);
        int linkCount();
        ~LinkExtractor();

    protected:
        int m_numLinks;
        bool m_linksExtracted;
        char *m_filename;
        char *m_source;
        std::list<std::string> m_links;

};

#endif // LINKEXTRACTOR_H_INCLUDED
