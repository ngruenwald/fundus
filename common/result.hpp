#pragma once

#include <exception>
#include <functional>
#include <type_traits>
#include <utility>
#include <variant>

namespace cmn {

class BadResultAccess : std::exception
{
public:
    explicit BadResultAccess(bool ok_or_error) noexcept
        : ok_or_error_(ok_or_error) {}

    BadResultAccess(const BadResultAccess& other) noexcept
        : ok_or_error_(other.ok_or_error_) {}

    BadResultAccess& operator=(const BadResultAccess& other) noexcept
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
class Result
{
public:
    using value_type = T;
    using error_type = E;

private:
    Result() {}

public:
    template<typename T1 = value_type, typename T2 = error_type>
    constexpr Result(const value_type& value, typename std::enable_if<!std::is_same<T1, T2>::value>::type* = nullptr)
        : ok_{true} { data_ = value; }

    template<typename T1 = value_type, typename T2 = error_type>
    constexpr Result(const error_type& error, typename std::enable_if<!std::is_same<T1, T2>::value, int>::type* = nullptr)
        : ok_{false} { data_ = error; }

    template<typename T1 = value_type, typename T2 = error_type>
    constexpr Result(bool is_ok, const value_type& value_or_error, typename std::enable_if<std::is_same<T1, T2>::value>::type* = nullptr)
        : ok_{is_ok} { data_ = value_or_error; }

    constexpr Result(const Result& rhs)
    {
        ok_ = rhs.ok_;
        data_ = rhs.data_;
    }

    constexpr Result(Result&& rhs)
    {
        ok_ = rhs.ok_;
        data_ = std::move(rhs.data_);
    }

    constexpr Result& operator=(const Result& rhs)
    {
        ok_ = rhs.ok_;
        data_ = rhs.data_;
        return *this;
    }

    constexpr Result& operator=(Result&& rhs)
    {
        ok_ = rhs.ok_;
        data_ = std::move(rhs.data_);
        return *this;
    }

    constexpr bool is_ok() const
    {
        return ok_;
    }

    constexpr const value_type& value() const
    {
        if (!ok_) throw BadResultAccess{true};
        return std::get<value_type>(data_);
    }

    constexpr const error_type& error() const
    {
        if (ok_) throw BadResultAccess{false};
        return std::get<error_type>(data_);
    }

public:
    Result then(
        std::function<Result<value_type, error_type>(value_type)> fn)
    {
        return is_ok() ? fn(value()) : *this;
    }

    Result on_error(
        std::function<Result<value_type, error_type>(error_type)> fn)
    {
        return is_ok() ? *this : fn(error());
    }

public:
    constexpr static Result ok(const value_type& value)
    {
        auto r = Result{};
        r.ok_ = true;
        r.data_ = value;
        return r;
    }

    constexpr static Result error(const error_type& error)
    {
        auto r = Result{};
        r.ok_ = false;
        r.data_ = error;
        return r;
    }

private:
    bool ok_;
    std::variant<value_type, error_type> data_;
};

template<typename E>
class Result<void, E>
{
public:
    using error_type = E;

public:
    constexpr Result()
        : ok_{true} {}

    constexpr Result(const error_type& error)
        : ok_{false}, error_{error} {}

    constexpr Result(const Result& rhs)
    {
        ok_ = rhs.ok_;
        if (!ok_) error_ = rhs.error;
    }

    constexpr Result(Result&& rhs)
    {
        ok_ = rhs.ok_;
        if (!ok_) error_ = std::move(rhs.error_);
    }

    constexpr Result& operator=(const Result& rhs)
    {
        ok_ = rhs.ok_;
        if (!ok_) error_ = rhs.error_;
        return *this;
    }

    constexpr Result& operator=(Result&& rhs)
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
        if (ok_) throw BadResultAccess{false};
        return error_;
    }

public:
    Result then(
        std::function<Result()> fn)
    {
        return is_ok() ? fn() : *this;
    }

    Result on_error(
        std::function<Result(error_type)> fn)
    {
        return is_ok() ? *this : fn(error());
    }

public:
    constexpr static Result ok()
    {
        auto r = Result{};
        r.ok_ = true;
        return r;
    }

    constexpr static Result error(const error_type& error)
    {
        auto r = Result{};
        r.ok_ = false;
        r.error_ = error;
        return r;
    }

private:
    bool ok_;
    error_type error_;
};

} // namespace cmn
