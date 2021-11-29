#pragma once

#include <exception>
#include <optional>
#include <string_view>

#include <string.h>

namespace cmn {

class Error final
{
public:
    Error() = default;
    ~Error() = default;

    Error(const Error&) = default;
    Error(Error&&) = default;

    explicit Error(int code)
        : code_{code} {}
    explicit Error(const std::string_view& message)
        : message_{message} {}
    explicit Error(std::string_view&& message)
        : message_{std::move(message)} {}
    Error(int code, const std::string_view& message)
        : code_{code}, message_{message} {}
    Error(int code, std::string_view&& message)
        : code_{code}, message_{std::move(message)} {}

    Error& operator=(const Error&) = default;
    Error& operator=(Error&&) = default;

    int get_code() const { return code_; }
    const std::string_view& get_message() const { return message_; }

public:
    static Error from_errno(int errno) { return Error{errno, strerror(errno)}; }
    static Error from_exception(const std::exception& ex) { return Error{ex.what()}; }

private:
    int code_{0};
    std::string_view message_;

}; // Error

template<typename T>
class ErrorOr final
{
public:
    ErrorOr(const ErrorOr<T>&) = default;
    ErrorOr(ErrorOr<T>&&) = default;

    ErrorOr(const T& result)
        : result_{result} {}
    ErrorOr(T&& result)
        : result_{std::move(result)} {}
    ErrorOr(const Error& error)
        : error_{error} {}
    ErrorOr(Error&& error)
        : error_{std::move(error)} {}

    ErrorOr operator=(const ErrorOr<T>& other) {
        result_ = other.result_;
        error_ = other.error_;
        return *this;
    }

    ErrorOr operator=(ErrorOr<T>&& other) {
        result_ = std::move(other.result_);
        error_ = std::move(other.error_);
        return *this;
    }

    ErrorOr operator=(const T& value) { result_ = value; return *this; }
    ErrorOr operator=(T&& value) { result_ = std::move(value); return *this; }

    bool is_ok() const { return result_.has_value(); }
    bool is_error() const { return error_.has_value(); }

    const T& get_result() const { return result_.value(); }
    const Error& get_error() const { return error_.value(); }

    T&& release_result() { return *std::move(result_); }
    Error&& release_error() { return *std::move(error_); }

    operator bool() const { return is_ok(); }

private:
    std::optional<T> result_;
    std::optional<Error> error_;
};

template<>
class ErrorOr<void>
{
public:
    ErrorOr(const ErrorOr&) = default;
    ErrorOr(ErrorOr&&) = default;

    explicit ErrorOr(const Error& error)
        : error_{error} {}

    explicit ErrorOr(Error&& error)
        : error_{std::move(error)} {}

    ErrorOr operator=(const ErrorOr& other) {
        error_ = other.error_;
        return *this;
    }

    ErrorOr operator=(ErrorOr&& other) {
        error_ = std::move(other.error_);
        return *this;
    }

    bool is_ok() const { return !error_.has_value(); }
    bool is_error() const { return error_.has_value(); }

    const Error& get_error() const { return error_.value(); }

    Error&& release_error() { return *std::move(error_); }

    operator bool() const { return is_ok(); }

private:
    std::optional<Error> error_;
};

} // namespace cmn
