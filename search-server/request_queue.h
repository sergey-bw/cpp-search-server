#pragma once

#include <cstdint>
#include <deque>
#include <string>
#include <vector>

#include "document.h"
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);

    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);

    std::vector<Document> AddFindRequest(const std::string& raw_query);

    int GetNoResultRequests() const;

private:
    struct QueryResult {
        std::vector<Document> query_result;
        uint64_t query_time;
    };

    const SearchServer& search_server_;
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    int count_query_not_result_ = 0;
    uint64_t current_time_ = 0;

    void ClearOldRequest();

    void AddRequestResult(const std::vector<Document>& result);
};