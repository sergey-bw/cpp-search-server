#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server)
    : search_server_(search_server)
{
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    const auto result = search_server_.FindTopDocuments(raw_query, status);
    AddRequestResult(result);
    return result;
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    const auto result = search_server_.FindTopDocuments(raw_query);
    AddRequestResult(result);
    return result;
}

int RequestQueue::GetNoResultRequests() const {
    return count_query_not_result_;
}

void RequestQueue::ClearOldRequest() {
    if (current_time_ <= min_in_day_) {
        return;
    }
    if (!requests_.empty() && requests_.front().query_time == (current_time_ - min_in_day_)) {
        requests_.pop_front();
    } else {
        --count_query_not_result_;
    }
}

void RequestQueue::AddRequestResult(const std::vector<Document>& result) {
    ++current_time_;
    ClearOldRequest();
    if (!result.empty()) {
        requests_.push_back({result, current_time_});
    } else {
        ++count_query_not_result_;
    }
}