#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>


namespace ref {
    __attribute__((noinline))
    std::string get_search_string() {
        std::string rv = "50";
        benchmark::DoNotOptimize(rv);
        return rv;
    }

    using ID = std::uint32_t;
    using Phones = std::deque<std::string>;

    struct Filial {
        Filial() = default;

        Filial(ID id, Phones phones) : id(id), phones(phones) {}

        Filial(const Filial &rhs) : id(rhs.id), phones(rhs.phones) {}

        Filial &operator=(const Filial &rhs) {
            if (this != &rhs)
                std::tie(id, phones) = std::tie(rhs.id, rhs.phones);
            return *this;
        }

        ID id = 0;
        Phones phones;
    };

    using FilialPtr = std::shared_ptr<Filial>;
    using Filials = std::vector<FilialPtr>;

    struct Org {
        Org() = default;

        Org(ID id, std::string name, Filials filials) : id(id), name(name), filials(filials) {}

        Org(const Org &rhs) : id(rhs.id), name(rhs.name), filials(rhs.filials) {}

        Org &operator=(const Org &rhs) {
            if (this != &rhs)
                std::tie(id, name, filials) = std::tie(rhs.id, rhs.name, rhs.filials);
            return *this;
        }

        ID id = 0;
        std::string name;
        Filials filials;
    };

    using OrgPtr = std::shared_ptr<Org>;
    using Orgs = std::vector<OrgPtr>;

    __attribute__((noinline))
    Orgs gen_data() {
        return {
                OrgPtr(new Org(1, "Academpark", {
                        FilialPtr(new Filial(1, {"8--973--272--40--77", "8--959--638--2193", "8--975--027--80--76"})),
                        FilialPtr(new Filial(2, {"8--925--084--8449", "8  975  858  94  93"})),
                        FilialPtr(new Filial(3, {"8 (922) 871 6054", " 8  964  472  47  50"})),
                        FilialPtr(new Filial(4, {"8  921  685 6880", "45--46--328"})),
                })),
                OrgPtr(new Org(2, "Nobosibirsk State University", {
                        FilialPtr(new Filial(5, {"303--012--627", "8 (948) 955  07  27"})),
                        FilialPtr(new Filial(6, {"89391243637", "89417446859"})),
                })),
                OrgPtr(new Org(3, "Yandex LLC", {
                        FilialPtr(new Filial(7, {"8--988--586--75--04", "8-988--586--75--04"})),
                        FilialPtr(new Filial(8, {"8--800--888--8888"})),
                        FilialPtr(new Filial(9, {"89293682725", "8  954  252  69  58", " 8--927--210--40--30",
                                                 "8 (902) --502--6333", "89687848871"})),
                })),
                OrgPtr(new Org(4, "JetBrains LLC", {
                        FilialPtr(new Filial(10, {"89687845071", "8 (999) 007  75  08", "8--987--696--30--32",
                                                  "8  946  254  56  82", "8 (949) 263--7655"})),
                        FilialPtr(new Filial(11, {"8  949  2637655", "8 (986) 460   75  88", "8  979  616--50--45",
                                                  "8 (945) 601  39  67"})),
                        FilialPtr(new Filial(12, {"8--500--555  6555"})),
                })),
                OrgPtr(new Org(5, "Computer Science Center", {
                        FilialPtr(new Filial(13, {"8--959--930--53--58", "8  934  796  87  62", "89595664145"})),
                        FilialPtr(new Filial(14, {"8--999--888--77--66"})),
                        FilialPtr(new Filial(15, {"8 (962) 989  18  07", "8  949  851  74  12"})),
                }))};
    }

    bool is_phone_fit(std::string phone, std::string req) {
        std::string raw_phone;
        std::copy_if(phone.begin(),
                     phone.end(),
                     std::back_inserter(raw_phone),
                     isdigit);

        std::string raw_request;
        std::copy_if(req.begin(),
                     req.end(),
                     std::back_inserter(raw_request),
                     isdigit);

        return raw_phone.find(raw_request) != std::string::npos;
    }

    __attribute__((noinline))
    std::string search_by_phone(Orgs orgs, std::string request) {
        std::string rv;
        for (const auto &org: orgs) {
            std::string postfix;
            for (const auto &fil: org->filials)
                for (const auto &phone: fil->phones)
                    if (is_phone_fit(phone, request))
                        postfix += "    fil " + std::to_string(fil->id) + ": " + phone + "\n";

            if (!postfix.empty())
                rv += org->name + " (" + std::to_string(org->id) + ")\n" + postfix;
        }
        return rv;
    }

    __attribute__((noinline))
    std::string run() {
        const auto orgs = gen_data();
        benchmark::DoNotOptimize(orgs);
        const auto request = get_search_string();
        benchmark::DoNotOptimize(request);
        return search_by_phone(orgs, request);
    }

}  // namespace ref


namespace sol {
    __attribute__((noinline))
    std::string get_search_string() {
        std::string rv = "50";
        benchmark::DoNotOptimize(rv);
        return rv;
    }

    using ID = std::uint32_t;
    using Phones = std::vector<std::string>;

    struct Filial {
        Filial() = default;

        Filial(ID id, Phones phones) : id(id), phones(std::move(phones)) {}

        Filial(const Filial &rhs) : id(rhs.id), phones(std::move(rhs.phones)) {}

        Filial &operator=(const Filial &rhs) {
            if (this != &rhs)
                std::tie(id, phones) = std::tie(rhs.id, rhs.phones);
            return *this;
        }

        ID id = 0;
        Phones phones;
    };

    using FilialPtr = std::shared_ptr<Filial>;
    using Filials = std::vector<FilialPtr>;

    struct Org {
        Org() = default;

        Org(ID id, std::string name, Filials filials) : id(id), name(std::move(name)), filials(std::move(filials)) {}

        Org(const Org &rhs) : id(rhs.id), name(std::move(rhs.name)), filials(std::move(rhs.filials)) {}

        Org &operator=(const Org &rhs) {
            if (this != &rhs)
                std::tie(id, name, filials) = std::tie(rhs.id, rhs.name, rhs.filials);
            return *this;
        }

        ID id = 0;
        std::string name;
        Filials filials;
    };

    using OrgPtr = std::shared_ptr<Org>;
    using Orgs = std::vector<OrgPtr>;

    __attribute__((noinline))
    Orgs gen_data() {
        return std::initializer_list<OrgPtr>{
                std::make_shared<Org>(1, "Academpark", std::initializer_list<FilialPtr>{
                        std::make_shared<Filial>(1, std::initializer_list<std::string>{"8--973--272--40--77", "8--959--638--2193", "8--975--027--80--76"}),
                        std::make_shared<Filial>(2, std::initializer_list<std::string>{"8--925--084--8449", "8  975  858  94  93"}),
                        std::make_shared<Filial>(3, std::initializer_list<std::string>{"8 (922) 871 6054", " 8  964  472  47  50"}),
                        std::make_shared<Filial>(4, std::initializer_list<std::string>{"8  921  685 6880", "45--46--328"}),
                }),
                std::make_shared<Org>(2, "Nobosibirsk State University", std::initializer_list<FilialPtr>{
                        std::make_shared<Filial>(5, std::initializer_list<std::string>{"303--012--627", "8 (948) 955  07  27"}),
                        std::make_shared<Filial>(6, std::initializer_list<std::string>{"89391243637", "89417446859"}),
                }),
                std::make_shared<Org>(3, "Yandex LLC", std::initializer_list<FilialPtr>{
                        std::make_shared<Filial>(7, std::initializer_list<std::string>{"8--988--586--75--04", "8-988--586--75--04"}),
                        std::make_shared<Filial>(8, std::initializer_list<std::string>{"8--800--888--8888"}),
                        std::make_shared<Filial>(9, std::initializer_list<std::string>{"89293682725", "8  954  252  69  58", " 8--927--210--40--30",
                                                                                       "8 (902) --502--6333", "89687848871"}),
                }),
                std::make_shared<Org>(4, "JetBrains LLC", std::initializer_list<FilialPtr>{
                        std::make_shared<Filial>(10, std::initializer_list<std::string>{"89687845071", "8 (999) 007  75  08", "8--987--696--30--32",
                                                                                        "8  946  254  56  82", "8 (949) 263--7655"}),
                        std::make_shared<Filial>(11, std::initializer_list<std::string>{"8  949  2637655", "8 (986) 460   75  88", "8  979  616--50--45",
                                                                                        "8 (945) 601  39  67"}),
                        std::make_shared<Filial>(12, std::initializer_list<std::string>{"8--500--555  6555"}),
                }),
                std::make_shared<Org>(5, "Computer Science Center", std::initializer_list<FilialPtr>{
                        std::make_shared<Filial>(13, std::initializer_list<std::string>{"8--959--930--53--58", "8  934  796  87  62", "89595664145"}),
                        std::make_shared<Filial>(14, std::initializer_list<std::string>{"8--999--888--77--66"}),
                        std::make_shared<Filial>(15, std::initializer_list<std::string>{"8 (962) 989  18  07", "8  949  851  74  12"}),
                })};
    }

    bool is_phone_fit(const std::string &phone, const std::string &raw_request) {
        std::string raw_phone;
        std::copy_if(phone.begin(),
                     phone.end(),
                     std::back_inserter(raw_phone),
                     isdigit);

        return raw_phone.find(raw_request) != std::string::npos;
    }

    __attribute__((noinline))
    std::string search_by_phone(const Orgs &orgs, const std::string &request) {
        std::string raw_request;
        std::copy_if(request.begin(),
                     request.end(),
                     std::back_inserter(raw_request),
                     isdigit);

        std::string rv;
        for (const auto &org: orgs) {
            bool is_first = true;
            for (const auto &fil: org->filials)
                for (const auto &phone: fil->phones)
                    if (is_phone_fit(phone, raw_request)) {
                        if (is_first) {
                            rv += org->name;
                            rv += " (";
                            rv += std::to_string(org->id);
                            rv += ")\n";
                            is_first = false;
                        }
                        rv += "    fil ";
                        rv += std::to_string(fil->id);
                        rv += ": ";
                        rv += phone;
                        rv += "\n";
                    }
        }
        return rv;
    }


    __attribute__((noinline))
    std::string run() {
        const auto orgs = gen_data();
        benchmark::DoNotOptimize(orgs);
        const auto request = get_search_string();
        benchmark::DoNotOptimize(request);
        return search_by_phone(orgs, request);
    }
}  // namespace sol



static void Reference(benchmark::State &state) {
    for (auto _ : state) {
        auto res = ref::run();
        benchmark::DoNotOptimize(res);
    }
}

BENCHMARK(Reference);


static void YourSolution(benchmark::State &state) {
    for (auto _ : state) {
        auto res = sol::run();
        benchmark::DoNotOptimize(res);
    }
}

BENCHMARK(YourSolution);