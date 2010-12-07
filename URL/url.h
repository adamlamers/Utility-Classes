#ifndef URL_HH_
#define URL_HH_
#include <string>
struct url {
    url(const std::string& url_s); // omitted copy, ==, accessors, ...
    std::string protocol();
    std::string host();
    std::string path();
    std::string query();
private:
    void parse(const std::string& url_s);
private:
    std::string protocol_, host_, path_, query_;
};
#endif /* URL_HH_ */
