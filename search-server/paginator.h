#pragma once

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange<Iterator> (Iterator range_begin, Iterator range_end)
        : it_begin_(range_begin)
        , it_end_(range_end)
    {
    }

    Iterator begin() const {
        return it_begin_;
    }

    Iterator end() const {
        return it_end_;
    }

    size_t size() const {
        return distance(it_begin_, it_end_);
    }

private:
    Iterator it_begin_;
    Iterator it_end_;
};

template <typename Iterator>
class Paginator {
public:
    Paginator<Iterator> (Iterator range_begin, Iterator range_end, size_t page_size) {
        Iterator it_begin = range_begin;
        while (distance(it_begin, range_end) > 0) {
            if (distance(it_begin, range_end) > page_size) {
                Iterator it_end = it_begin;
                advance(it_end, page_size);
                pages_.push_back(IteratorRange(it_begin, it_end));
                advance(it_begin, page_size);
            } else {
                pages_.push_back(IteratorRange(it_begin, range_end));
                it_begin = range_end;
            }
        }
    }

    auto begin() const {
        return pages_.begin();
    }

    auto end() const {
        return pages_.end();
    }

    auto size() const {
        return pages_.size();
    }
 
private:
    std::vector<IteratorRange<Iterator>> pages_;
};

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

template <typename Iterator>
std::ostream& operator<<(std::ostream& output, IteratorRange<Iterator> range) {
    for (auto it = range.begin(); it != range.end(); ++it) {
        output << *it; // *it - Document
    }
    return output;
}