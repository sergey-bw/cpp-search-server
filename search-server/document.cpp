#include "document.h"

Document::Document() = default;

Document::Document(int id_value, double relevance_value, int rating_value)
    : id(id_value)
    , relevance(relevance_value)
    , rating(rating_value)
{
}

void PrintDocument(const Document& document) {
    std::cout << "{ "
         << "document_id = " << document.id << ", "
         << "relevance = " << document.relevance << ", "
         << "rating = " << document.rating << " }" << std::endl;
}

std::ostream& operator<<(std::ostream& output, const Document& document) {
    return output << "{ "
         << "document_id = " << document.id << ", "
         << "relevance = " << document.relevance << ", "
         << "rating = " << document.rating << " }";
}