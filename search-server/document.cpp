#include "document.h"

Document::Document() = default;

Document::Document(int id_value, double relevance_value, int rating_value)
    : id(id_value)
    , relevance(relevance_value)
    , rating(rating_value)
{
}