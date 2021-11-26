#pragma once

#include <exception>
#include <type_traits>
#include <utility>

namespace cmn {

class bad_result_access : std::exception
{
public:
    explicit bad_result_access(bool ok_or_error) noexcept
        : ok_or_error_(ok_or_error) {}

    bad_result_access(const bad_result_access& other) noexcept
        : ok_or_error_(other.ok_or_error_) {}

    bad_result_access& operator=(const bad_result_access& other) noexcept
    {
        ok_or_error_ = other.ok_or_error_;
        return *this;
    }

    virtual const char* what() const noexcept override
    {
        return ok_or_error_ ? "bad value access" : "bad error access";
    }

private:
    bool ok_or_error_;
};

template<typename T, typename E>
class result
{
public:
    using value_type = T;
    using error_type = E;

private:
    result() {}

public:
    template<typename T1 = value_type, typename T2 = error_type>
    constexpr result(const value_type& value, typename std::enable_if<!std::is_same<T1, T2>::value>::type* = nullptr)
        : ok_{true} {data_.value = value; }

    template<typename T1 = value_type, typename T2 = error_type>
    constexpr result(const error_type& error, typename std::enable_if<!std::is_same<T1, T2>::value, int>::type* = nullptr)
        : ok_{false} { data_.error = error; }

    template<typename T1 = value_type, typename T2 = error_type>
    constexpr result(bool is_ok, const value_type& value_or_error, typename std::enable_if<std::is_same<T1, T2>::value>::type* = nullptr)
        : ok_{is_ok} { ok_ ? data_.value = value_or_error : data_.error = value_or_error; }

    constexpr result(const result& rhs)
    {
        ok_ = rhs.ok_;
        ok_ ? data_.value = rhs.data_.value
            : data_.error = rhs.data_.error;
    }

    constexpr result(result&& rhs)
    {
        ok_ = rhs.ok_;
        ok_ ? data_.value = std::move(rhs.data_.value)
            : data_.error = std::move(rhs.data_.error);
    }

    constexpr result& operator=(const result& rhs)
    {
        ok_ = rhs.ok_;
        ok_ ? data_.value = rhs.data_.value
            : data_.error = rhs.data_.error;
        return *this;
    }

    constexpr result& operator=(result&& rhs)
    {
        ok_ = rhs.ok_;
        ok_ ? data_.value = std::move(rhs.data_.value)
            : data_.error = std::move(rhs.data_.error);
        return *this;
    }

    constexpr bool is_ok() const
    {
        return ok_;
    }

    constexpr const value_type& value() const
    {
        if (!ok_) throw bad_result_access{true};
        return data_.value;
    }

    constexpr const error_type& error() const
    {
        if (ok_) throw bad_result_access{false};
        return data_.error;
    }

public:
    constexpr static result ok(const value_type& value)
    {
        auto r = result{};
        r.ok_ = true;
        r.data_.value = value;
        return r;
    }

    constexpr static result error(const error_type& error)
    {
        auto r = result{};
        r.ok_ = false;
        r.data_.error = error;
        return r;
    }

private:
    bool ok_;

    union
    {
        value_type value;
        error_type error;

    } data_;
};

template<typename E>
class result<void, E>
{
public:
    using error_type = E;

public:
    constexpr result()
        : ok_{true} {}

    constexpr result(const error_type& error)
        : ok_{false}, error_{error} {}

    constexpr result(const result& rhs)
    {
        ok_ = rhs.ok_;
        if (!ok_) error_ = rhs.error;
    }

    constexpr result(result&& rhs)
    {
        ok_ = rhs.ok_;
        if (!ok_) error_ = std::move(rhs.error_);
    }

    constexpr result& operator=(const result& rhs)
    {
        ok_ = rhs.ok_;
        if (!ok_) error_ = rhs.error_;
        return *this;
    }

    constexpr result& operator=(result&& rhs)
    {
        ok_ = rhs.ok_;
        if (!ok_) error_ = std::move(rhs.error_);
        return *this;
    }

    constexpr bool is_ok() const
    {
        return ok_;
    }

    constexpr const error_type& error() const
    {
        if (ok_) throw bad_result_access{false};
        return error_;
    }

public:
    constexpr static result ok()
    {
        auto r = result{};
        r.ok_ = true;
        return r;
    }

    constexpr static result error(const error_type& error)
    {
        auto r = result{};
        r.ok_ = false;
        r.error_ = error;
        return r;
    }

private:
    bool ok_;
    error_type error_;
};

} // namespace cmn
