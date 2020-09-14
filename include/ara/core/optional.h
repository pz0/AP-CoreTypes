/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_OPTIONAL_H_
#define ARA_CORE_OPTIONAL_H_

#include <optional>
#include "ara/core/utility.h"

namespace ara::core {
    template <class T>
    class Optional
    {
        public:
            typedef T value_type;

            constexpr Optional() noexcept 
            {
                o_ = std::optional<T>();
            }

            constexpr Optional(std::nullopt_t) noexcept
            {
                o_ = std::optional<T>(std::nullopt);
            }

            constexpr Optional(const Optional& other)
            {
                o_ = std::optional<T>(other.o_);
            }

            constexpr Optional(Optional&& other) noexcept
            {
                o_ = std::optional<T>(std::move(other.o_));
            }

            template <class U>
            Optional(const Optional<U>& other)
            {
                o_ = std::optional<U>(other.o_);
            }

            template <class U>
            Optional(Optional<U>&& other)
            {
                o_ = std::optional<U>(std::move(other.o_));
            }

            template <class... Args>
            constexpr explicit Optional(in_place_t, Args&&... args)
            {
                o_ = std::optional<T>(in_place, std::forward<Args>(args)...);
            }

            template <class U, class... Args>
            constexpr explicit Optional(in_place_t, std::initializer_list<U> ilist, Args&&... args)
            {
                o_ = std::optional<T>(in_place, ilist, std::forward<Args>(args)...);
            }

            template <class U  = value_type>
            constexpr Optional(U&& value)
            {
                // todo
            }

            Optional& operator=(std::nullopt_t) noexcept
            {
                o_ = std::nullopt;

                return *this;
            }

            constexpr Optional& operator=(const Optional& other)
            {
                o_ = other.o_;

                return *this;
            }

            constexpr Optional& operator=(Optional&& other) noexcept
            {
                if (this != other)
                {
                    o_ = other.o_;
                }
                return *this;
            }

            template<class U>
            Optional& operator=(U&& value)
            {
                o_ = value;

                return *this;
            }

            template<class U>
            Optional& operator=(const Optional<U>& other)
            {
                o_ = other.o_;

                return *this;
            }

            template<class U>
            Optional& operator=(Optional<U>&& other)
            {
                o_ = other.o_;

                return *this;
            }

            constexpr const T* operator->() const
            {
                return o_.value();
            }

            constexpr T* operator->()
            {
                return o_.value();
            }

            constexpr const T& operator*() const&
            {
                return *o_.value();
            }

            constexpr T& operator*() &
            {
                return *o_.value();
            }

            constexpr const T&& operator*() const&&
            {
                return std::move(*o_.value());
            }

            constexpr T&& operator*() &&
            {
                return std::move(*o_.value());
            }

            constexpr explicit operator bool() const noexcept
            {
                return has_value();
            }

            constexpr bool has_value() const noexcept
            {
                return o_.has_value();
            }

            constexpr T& value() &
            {
                return o_.value();
            }

            constexpr const T& value() const &
            {
                return o_.value();
            }

            constexpr T&& value() &&
            {
                return std::move(o_.value());
            }

            constexpr const T&& value() const &&
            {
                return std::move(o_.value());
            }

            template<class U>
            constexpr T value_or(U&& default_value) const&
            {
                return o_.value_or(default_value);
            }

            template<class U>
            constexpr T value_or(U&& default_value) &&
            {
                return std::move(o_.value_or(default_value));
            }

            void swap(Optional& other) noexcept
            {
                o_.swap(other.o_);
            }

            void reset() noexcept
            {
                o_.reset();
            }

            template<class... Args>
            T& emplace(Args&&... args)
            {
                return o_.emplace(std::forward<Args>(args)...);
            }

            template<class U, class... Args>
            T& emplace(std::initializer_list<U> ilist, Args&&... args)
            {
                return o_.emplace(ilist, std::forward<Args>(args)...);
            }

            template<class X, class Y>
            friend constexpr bool operator==(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ == rhs.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator!=(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ != rhs.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator<(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ < rhs.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator<=(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ <= rhs.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator>(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ > rhs.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator>=(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ >= rhs.o_;
            }

            template<class X, std::three_way_comparable_with<X> Y>
            friend constexpr std::compare_three_way_result_t<X, Y> operator<=>(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ <=> rhs.o_;
            }

            template<class X>
            friend constexpr bool operator==(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ == std::nullopt;
            }

            template<class X>
            friend constexpr bool operator==(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt == opt.o_;
            }

            template<class X>
            friend constexpr bool operator!=(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ != std::nullopt;
            }

            template<class X>
            friend constexpr bool operator!=(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt != opt.o_;
            }

            template<class X>
            friend constexpr bool operator<(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ < std::nullopt;
            }

            template<class X>
            friend constexpr bool operator<(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt < opt.o_;
            }

            template<class X>
            friend constexpr bool operator<=(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ <= std::nullopt;
            }

            template<class X>
            friend constexpr bool operator<=(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt <= opt.o_;
            }

            template<class X>
            friend constexpr bool operator>(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ > std::nullopt;
            }

            template<class X>
            friend constexpr bool operator>(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt > opt.o_;
            }

            template<class X>
            friend constexpr bool operator>=(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ >= std::nullopt;
            }

            template<class X>
            friend constexpr bool operator>=(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt >= opt.o_;
            }

            template<class X>
            friend constexpr std::strong_ordering operator<=>(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ <=> std::nullopt;
            }

            template<class X, class Y>
            friend constexpr bool operator==(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ == value;
            }

            template<class X, class Y>
            friend constexpr bool operator==(const X& value, const Optional<Y>& opt)
            {
                return value == opt.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator!=(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ != value;
            }

            template<class X, class Y>
            friend constexpr bool operator!=(const X& value, const Optional<Y>& opt)
            {
                return value != opt.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator<(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ < value;
            }

            template<class X, class Y>
            friend constexpr bool operator<(const X& value, const Optional<Y>& opt)
            {
                return value < opt.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator<=(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ <= value;
            }

            template<class X, class Y>
            friend constexpr bool operator<=(const X& value, const Optional<Y>& opt)
            {
                return value <= opt.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator>(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ > value;
            }

            template<class X, class Y>
            friend constexpr bool operator>(const X& value, const Optional<Y>& opt)
            {
                return value > opt.o_;
            }

            template<class X, class Y>
            friend constexpr bool operator>=(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ >= value;
            }

            template<class X, class Y>
            friend constexpr bool operator>=(const X& value, const Optional<Y>& opt)
            {
                return value >= opt.o_;
            }

            template<class X, std::three_way_comparable_with<X> Y>
            friend constexpr std::compare_three_way_result_t<X, Y> operator<=>(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ <=> value;
            }

            template<class X>
            friend constexpr Optional<std::decay_t<X>> make_optional(X&& value)
            {
                return Optional<std::decay_t<T>>(std::forward<T>(value));
            }

            template<class X, class... Args>
            friend constexpr Optional<X> make_optional(Args&&... args)
            {
                return Optional<X>(in_place, std::forward<Args>(args)...);
            }

            template<class X, class Y, class... Args>
            friend constexpr Optional<X> make_optional(std::initializer_list<Y> il, Args&&... args)
            {
                return Optional<X>(in_place, il, std::forward<Args>(args)...);
            }
        private:
            std::optional<T> o_;
    };

    template<class T>
    void swap(Optional<T>& lhs, Optional<T>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}  // namespace ara::core

#endif  // ARA_CORE_OPTIONAL_H_
