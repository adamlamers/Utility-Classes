/**
 * Adam Lamers
 * December 4th, 2010
 * HTML link crawler.
 */

#include "file_get_contents.h"
#include "ParserDom.h"
#include "LinkExtractor.h"

#include <iostream>
#include <stdlib.h>

using namespace htmlcxx;

LinkExtractor::LinkExtractor()
:
m_numLinks(0),
m_linksExtracted(false),
m_filename(0),
m_source(0)
{

}

void LinkExtractor::setSource(const char *source, int sourceLength)
{
    if(m_linksExtracted == true)
    {
        m_linksExtracted = false;
        m_numLinks = 0;
        m_links.clear();
    }
    m_source = (char*)malloc(sourceLength);
    memcpy(m_source, source, sourceLength);
}

void LinkExtractor::setFile(const char *file)
{
    if(m_linksExtracted == true)
    {
        m_linksExtracted = false;
        m_numLinks = 0;
        m_links.clear();
    }
    m_filename = (char*)malloc(strlen(file));
    strcpy(m_filename, file);
}

int LinkExtractor::linkCount()
{
    return m_numLinks;
}

std::list<std::string> LinkExtractor::links()
{
    if(m_linksExtracted == false)
    {
        std::list<std::string> links(64);
        char *htmlContents = NULL;
        unsigned long htmlLength = 0;

        if(m_source)
            htmlContents = m_source;
        else if(m_filename)
            file_get_contents(m_filename, &htmlContents, &htmlLength);
        else
            return std::list<std::string>();

        HTML::ParserDom parser;
        tree<HTML::Node> dom = parser.parseTree(htmlContents);
        tree<HTML::Node>::iterator it = dom.begin();
        tree<HTML::Node>::iterator end = dom.end();
        for(; it != end; ++it)
        {
            if(it->tagName() == "a")
            {
                it->parseAttributes();
                std::pair<bool, std::string> linkPair = it->attribute("href");
                links.push_back(linkPair.second);
                m_links.push_back(linkPair.second);
                m_numLinks++;
            }
        }
        m_linksExtracted = true;
        return links;
    }
    else
    {
        return m_links;
    }
}

LinkExtractor::~LinkExtractor()
{
    if(m_source) free(m_source);
    if(m_filename) free(m_filename);
}
