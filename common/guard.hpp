#pragma once

//
// Execute a function when Guard is destroyed
//  e.g.   auto guard = Guard{[]() { std::cout << "... done ..." << std::endl; }};
//

#include <functional>

namespace cmn {

class Guard final
{
public:
    typedef std::function<void(void)> fn_t;

    Guard() : fn_{nullptr} {}
    explicit Guard(fn_t fn) : fn_{fn} {}

    Guard(const Guard&) = delete;
    Guard(Guard&&) = default;

    Guard& operator=(const Guard&) = delete;
    Guard& operator=(Guard&&) = default;

    ~Guard() { if (fn_) fn_(); }

    void set(fn_t fn) { fn_ = fn; }

private:
    fn_t fn_;
};

} // namespace cmn
