#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS"s) {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }

    } else if (operation_code == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;
        is >> q.stop;

    } else if (operation_code == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;
        is >> q.bus;

    } else if (operation_code == "ALL_BUSES"s) {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop"s;
    } else {
        for (const string& bus : r.buses) {
            os << bus << " "s;
        }
    }
    return os;
}

struct StopsForBusResponse {
    vector<string> stops; // Порядок добавления
    map<string, vector<string>> buses_for_stop; //<остановка <автобусы>>
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus"s;
    } else {
        bool is_first = true;
        for (const string& stop : r.stops) {
            if (!is_first) {
                os << endl;
            }
            is_first = false;
            os << "Stop "s << stop << ": "s;
            if (r.buses_for_stop.find(stop) == r.buses_for_stop.end()) {
                os << "no interchange"s;
            } else {
                for (const string& bus : r.buses_for_stop.at(stop)) {
                    os << bus << " "s;
                }
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    set<string> buses; // В алфовитном порядке
    map<string, vector<string>> stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    if (r.buses.empty()) {
            os << "No buses"s;
    } else {
        bool is_first = true;
        for (const string& bus : r.buses) {
            if (!is_first) {
                os << endl;
            }
            is_first = false;
            os << "Bus "s << bus << ": "s;
            for (const string& stop : r.stops.at(bus)) {
                os << stop << " "s;
            }
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        for (const string& stop : stops) {
            buses_to_stops_[bus].push_back(stop);
            stops_to_buses_[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse buses_for_stop_response;
        if (stops_to_buses_.count(stop) == 0) {
            return buses_for_stop_response;
        }
        buses_for_stop_response.stop = stop;
        for (const string& bus : stops_to_buses_.at(stop)) {
            buses_for_stop_response.buses.push_back(bus);
        }
        return buses_for_stop_response;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse stops_for_bus_response;
        if (buses_to_stops_.count(bus) == 0) {
            return stops_for_bus_response;
        }
        for (const string& stop : buses_to_stops_.at(bus)) {
            stops_for_bus_response.stops.push_back(stop);
            for (const string& other_bus : stops_to_buses_.at(stop)) {
                if (other_bus != bus) {
                    stops_for_bus_response.buses_for_stop[stop].push_back(other_bus);
                }
            }
        }
        return stops_for_bus_response;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse all_buses_response;
        if (buses_to_stops_.empty()) {
            return all_buses_response;
        }
        for (const auto& [bus, stops] : buses_to_stops_) {
            all_buses_response.buses.insert(bus);
            all_buses_response.stops[bus] = buses_to_stops_.at(bus);
        }
        return all_buses_response;
    }

private:
    map<string, vector<string>> buses_to_stops_, stops_to_buses_;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}