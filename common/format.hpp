#pragma once

//
// Stream based formatter
//   Example:  auto str = cmn::Format{} << "Hello " << "World " << 3;
//

#include <sstream>

namespace cmn {

class Format
{
public:
    template<typename T>
    Format& operator<<(const T& v)
    {
        stream_ << v;
        return *this;
    }

    operator std::string() const
    {
        return ToString();
    }

    std::string ToString() const
    {
        return stream_.str();
    }

private:
    std::ostringstream stream_;
};

} // namespace cmn
