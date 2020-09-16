/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_OPTIONAL_H_
#define ARA_CORE_OPTIONAL_H_

#include "ara/core/utility.h"
#include <optional>

namespace ara::core {
    /**
     * @brief The class template Optional manages an optional contained value.
     * 
     * @tparam T the type of the value to manage initialization state for.
     * 
     * @req {SWS_CORE_01033}
     */
    template <class T>
    class Optional
    {
        public:
            typedef T value_type;

            /**
             * @brief Constructs an object that does not contain a value.
             * 
             */
            constexpr Optional() noexcept 
            {
                o_ = std::optional<T>();
            }

            /**
             * @brief Constructs an object that does not contain a value.
             * 
             */
            constexpr Optional(std::nullopt_t) noexcept
            {
                o_ = std::optional<T>(std::nullopt);
            }

            /**
             * @brief Copy constructor: If other contains a value, initializes the contained value as 
             * if direct-initializing (but not direct-list-initializing) an object of type T with the 
             * expression *other. If other does not contain a value, constructs an object that does not 
             * contain a value. 
             * 
             * @param other another optional object whose contained value is copied.
             * 
             */
            constexpr Optional(const Optional& other)
            {
                o_ = std::optional<T>(other.o_);
            }

            /**
             * @brief Move constructor: If other contains a value, initializes the contained value as if 
             * direct-initializing (but not direct-list-initializing) an object of type T with the expression 
             * std::move(*other) and does not make other empty: a moved-from optional still contains a value, 
             * but the value itself is moved from. If other does not contain a value, constructs an object that 
             * does not contain a value. 
             * 
             * @param other another optional object whose contained value is moved.
             * 
             */
            constexpr Optional(Optional&& other) noexcept
            {
                o_ = std::optional<T>(std::move(other.o_));
            }

            /**
             * @brief Converting copy constructor: If other doesn't contain a value, constructs an optional 
             * object that does not contain a value. Otherwise, constructs an optional object that contains a value, 
             * initialized as if direct-initializing (but not direct-list-initializing) an object of type T with 
             * the expression *other. 
             * 
             * @param other another optional object whose contained value is copied.
             * 
             */
            template <class U>
            Optional(const Optional<U>& other)
            {
                o_ = std::optional<U>(other.o_);
            }

            /**
             * @brief Converting move constructor: If other doesn't contain a value, constructs an optional object 
             * that does not contain a value. Otherwise, constructs an optional object that contains a value, 
             * initialized as if direct-initializing (but not direct-list-initializing) an object of type T with 
             * the expression std::move(*other).
             * 
             * @param other another optional object whose contained value is moved.
             * 
             */
            template <class U>
            Optional(Optional<U>&& other)
            {
                o_ = std::optional<U>(std::move(other.o_));
            }

            /**
             * @brief Constructs an optional object that contains a value, initialized as if direct-initializing 
             * (but not direct-list-initializing) an object of type T from the arguments std::forward<Args>(args)... . 
             * 
             * @param args arguments with which to initialize the contained value. 
             * 
             */
            template <class... Args>
            constexpr explicit Optional(in_place_t, Args&&... args)
            {
                o_ = std::optional<T>(in_place, std::forward<Args>(args)...);
            }

            /**
             * @brief Constructs an optional object that contains a value, initialized as if direct-initializing 
             * (but not direct-list-initializing) an object of type T from the arguments ilist, std::forward<Args>(args)... .
             * 
             * @tparam U initializer list type.
             * @tparam Args args class.
             * 
             * @param ilist initializer list with which to initialize the contained value.
             * @param args  	arguments with which to initialize the contained value.
             * 
             */
            template <class U, class... Args>
            constexpr explicit Optional(in_place_t, std::initializer_list<U> ilist, Args&&... args)
            {
                o_ = std::optional<T>(in_place, ilist, std::forward<Args>(args)...);
            }

            /**
             * @brief Constructs an optional object that contains a value, initialized as if direct-initializing 
             * (but not direct-list-initializing) an object of type T (where T = value_type) with the expression std::forward<U>(value).
             * 
             * @tparam U value type.
             * 
             * @param value value with which to initialize the contained value.
             * 
             */
            template <class U  = value_type>
            constexpr Optional(U&& value)
            {
                // todo
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @return Reference to data.
             * 
             */
            Optional& operator=(std::nullopt_t) noexcept
            {
                o_ = std::nullopt;

                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return Reference to data.
             * 
             */
            constexpr Optional& operator=(const Optional& other)
            {
                o_ = other.o_;

                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return Reference to data.
             * 
             */
            constexpr Optional& operator=(Optional&& other) noexcept
            {
                if (this != other)
                {
                    o_ = other.o_;
                }
                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @tparam U value type.
             * 
             * @param value value to assign to the contained value.
             * 
             * @return Reference to data.
             * 
             */
            template<class U>
            Optional& operator=(U&& value)
            {
                o_ = value;

                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return Reference to data.
             * 
             */
            template<class U>
            Optional& operator=(const Optional<U>& other)
            {
                o_ = other.o_;

                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @tparam U other type.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return Reference to data.
             * 
             */
            template<class U>
            Optional& operator=(Optional<U>&& other)
            {
                o_ = other.o_;

                return *this;
            }

            /**
             * @brief Accesses the contained value.
             * 
             * @return Returns a pointer to the contained value.
             * 
             */
            constexpr const T* operator->() const
            {
                return o_.value();
            }

            /**
             * @brief Accesses the contained value.
             * 
             * @return Returns a pointer to the contained value.
             * 
             */
            constexpr T* operator->()
            {
                return o_.value();
            }

            /**
             * @brief Accesses the contained value.
             * 
             * @return Returns a reference to the contained value.
             * 
             */
            constexpr const T& operator*() const&
            {
                return *o_.value();
            }

            /**
             * @brief Accesses the contained value.
             * 
             * @return Returns a reference to the contained value.
             * 
             */
            constexpr T& operator*() &
            {
                return *o_.value();
            }

            /**
             * @brief Accesses the contained value.
             * 
             * @return Returns a reference to the contained value.
             * 
             */
            constexpr const T&& operator*() const&&
            {
                return std::move(*o_.value());
            }

            /**
             * @brief Accesses the contained value.
             * 
             * @return Returns a reference to the contained value.
             * 
             */
            constexpr T&& operator*() &&
            {
                return std::move(*o_.value());
            }

            /**
             * @brief Checks whether *this contains a value.
             * 
             * @return true if *this contains a value, false if *this does not contain a value.
             * 
             */
            constexpr explicit operator bool() const noexcept
            {
                return has_value();
            }

            /**
             * @brief Checks whether *this contains a value.
             * 
             * @return true if *this contains a value, false if *this does not contain a value.
             * 
             */
            constexpr bool has_value() const noexcept
            {
                return o_.has_value();
            }

            /**
             * @brief If *this contains a value, returns a reference to the contained value. 
             * 
             * @return A reference to the contained value.
             * 
             * @req {SWS_CORE_01030}
             */
            constexpr T& value() &
            {
                return o_.value();
            }

            /**
             * @brief If *this contains a value, returns a reference to the contained value. 
             * 
             * @return A reference to the contained value.
             * 
             * @req {SWS_CORE_01030}
             */
            constexpr const T& value() const &
            {
                return o_.value();
            }

            /**
             * @brief If *this contains a value, returns a reference to the contained value. 
             * 
             * @return A reference to the contained value.
             * 
             * @req {SWS_CORE_01030}
             */
            constexpr T&& value() &&
            {
                return std::move(o_.value());
            }

            /**
             * @brief If *this contains a value, returns a reference to the contained value. 
             * 
             * @return A reference to the contained value.
             * 
             * @req {SWS_CORE_01030}
             */
            constexpr const T&& value() const &&
            {
                return std::move(o_.value());
            }

            /**
             * @brief Returns the contained value if *this has a value, otherwise returns default_value.
             * 
             * @tparam U type of default value.
             * 
             * @param default_value the value to use in case *this is empty.
             * 
             * @return The current value if *this has a value, or default_value otherwise.
             * 
             */
            template<class U>
            constexpr T value_or(U&& default_value) const&
            {
                return o_.value_or(default_value);
            }

            /**
             * @brief Returns the contained value if *this has a value, otherwise returns default_value.
             * 
             * @tparam U type of default value.
             * 
             * @param default_value the value to use in case *this is empty.
             * 
             * @return The current value if *this has a value, or default_value otherwise.
             * 
             */
            template<class U>
            constexpr T value_or(U&& default_value) &&
            {
                return std::move(o_.value_or(default_value));
            }

            /**
             * @brief Swaps the contents with those of other.
             * 
             */
            void swap(Optional& other) noexcept
            {
                o_.swap(other.o_);
            }

            /**
             * @brief If *this contains a value, destroy that value as if by value().T::~T(). Otherwise, there are no effects.
             * 
             */
            void reset() noexcept
            {
                o_.reset();
            }

            /**
             * @brief Constructs the contained value in-place. If *this already contains a value before the call, the contained value is destroyed by calling its destructor. 
             * 
             * @tparam Args arguments type.
             * 
             * @param args the arguments to pass to the constructor.
             * 
             * @return A reference to the new contained value. 
             * 
             */
            template<class... Args>
            T& emplace(Args&&... args)
            {
                return o_.emplace(std::forward<Args>(args)...);
            }

            /**
             * @brief Constructs the contained value in-place. If *this already contains a value before the call, the contained value is destroyed by calling its destructor. 
             * 
             * @tparam U initializer list type.
             * @tparam Args arguments type.
             * 
             * @param ilist the initializer list to pass to the constructor.
             * @param args the arguments to pass to the constructor.
             * 
             * @return A reference to the new contained value. 
             * 
             */
            template<class U, class... Args>
            T& emplace(std::initializer_list<U> ilist, Args&&... args)
            {
                return o_.emplace(ilist, std::forward<Args>(args)...);
            }

            /**
             * @brief Compares two optional objects, lhs and rhs. The contained values are compared (using the corresponding operator of T) only if both lhs and rhs contain values.
             * 
             * @tparam X lhs optional type.
             * @tparam Y rhs optional type.
             * 
             * @param lhs optional object to compare.
             * @param rhs optional object to compare.
             * 
             * @return If bool(lhs) != bool(rhs), returns false. Otherwise, if bool(lhs) == false (and so bool(rhs) == false as well), returns true. Otherwise, returns *lhs == *rhs.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator==(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ == rhs.o_;
            }

            /**
             * @brief Compares two optional objects, lhs and rhs. The contained values are compared (using the corresponding operator of T) only if both lhs and rhs contain values.
             * 
             * @tparam X lhs optional type.
             * @tparam Y rhs optional type.
             * 
             * @param lhs optional object to compare.
             * @param rhs optional object to compare.
             * 
             * @return If bool(lhs) != bool(rhs), returns true. Otherwise, if bool(lhs) == false (and so bool(rhs) == false as well), returns false. Otherwise, returns *lhs != *rhs.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator!=(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ != rhs.o_;
            }

            /**
             * @brief Compares two optional objects, lhs and rhs. The contained values are compared (using the corresponding operator of T) only if both lhs and rhs contain values.
             * 
             * @tparam X lhs optional type.
             * @tparam Y rhs optional type.
             * 
             * @param lhs optional object to compare.
             * @param rhs optional object to compare.
             * 
             * @return If bool(rhs) == false returns false. Otherwise, if bool(lhs) == false, returns true. Otherwise returns *lhs < *rhs.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator<(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ < rhs.o_;
            }

            /**
             * @brief Compares two optional objects, lhs and rhs. The contained values are compared (using the corresponding operator of T) only if both lhs and rhs contain values.
             * 
             * @tparam X lhs optional type.
             * @tparam Y rhs optional type.
             * 
             * @param lhs optional object to compare.
             * @param rhs optional object to compare.
             * 
             * @return If bool(lhs) == false returns true. Otherwise, if bool(rhs) == false, returns false. Otherwise returns *lhs <= *rhs.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator<=(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ <= rhs.o_;
            }

            /**
             * @brief Compares two optional objects, lhs and rhs. The contained values are compared (using the corresponding operator of T) only if both lhs and rhs contain values.
             * 
             * @tparam X lhs optional type.
             * @tparam Y rhs optional type.
             * 
             * @param lhs optional object to compare.
             * @param rhs optional object to compare.
             * 
             * @return If bool(lhs) == false returns false. Otherwise, if bool(rhs) == false, returns true. Otherwise returns *lhs > *rhs.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator>(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ > rhs.o_;
            }

            /**
             * @brief Compares two optional objects, lhs and rhs. The contained values are compared (using the corresponding operator of T) only if both lhs and rhs contain values.
             * 
             * @tparam X lhs optional type.
             * @tparam Y rhs optional type.
             * 
             * @param lhs optional object to compare.
             * @param rhs optional object to compare.
             * 
             * @return If bool(rhs) == false returns true. Otherwise, if bool(lhs) == false, returns false. Otherwise returns *lhs >= *rhs.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator>=(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ >= rhs.o_;
            }

            /**
             * @brief Compares two optional objects, lhs and rhs. The contained values are compared (using the corresponding operator of T) only if both lhs and rhs contain values.
             * 
             * @tparam X lhs optional type.
             * @tparam Y rhs optional type.
             * 
             * @param lhs optional object to compare.
             * @param rhs optional object to compare.
             * 
             * @return If bool(lhs) && bool(rhs) is true returns *x <=> *y. Otherwise, returns bool(lhs) <=> bool(rhs).
             * 
             */
            template<class X, std::three_way_comparable_with<X> Y>
            friend constexpr std::compare_three_way_result_t<X, Y> operator<=>(const Optional<X>& lhs, const Optional<Y>& rhs)
            {
                return lhs.o_ <=> rhs.o_;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns !opt.
             * 
             */
            template<class X>
            friend constexpr bool operator==(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ == std::nullopt;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns !opt.
             * 
             */
            template<class X>
            friend constexpr bool operator==(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt == opt.o_;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns bool(opt).
             * 
             */
            template<class X>
            friend constexpr bool operator!=(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ != std::nullopt;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns bool(opt).
             * 
             */
            template<class X>
            friend constexpr bool operator!=(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt != opt.o_;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns false.
             * 
             */
            template<class X>
            friend constexpr bool operator<(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ < std::nullopt;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns bool(opt).
             * 
             */
            template<class X>
            friend constexpr bool operator<(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt < opt.o_;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns !opt.
             * 
             */
            template<class X>
            friend constexpr bool operator<=(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ <= std::nullopt;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns true.
             * 
             */
            template<class X>
            friend constexpr bool operator<=(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt <= opt.o_;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns bool(opt).
             * 
             */
            template<class X>
            friend constexpr bool operator>(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ > std::nullopt;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns false.
             * 
             */
            template<class X>
            friend constexpr bool operator>(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt > opt.o_;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns true.
             * 
             */
            template<class X>
            friend constexpr bool operator>=(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ >= std::nullopt;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns !opt.
             * 
             */
            template<class X>
            friend constexpr bool operator>=(std::nullopt_t, const Optional<X>& opt) noexcept
            {
                return std::nullopt >= opt.o_;
            }

            /**
             * @brief Compares opt with a nullopt.
             * 
             * @tparam X opt optional type.
             * 
             * @param opt an optional object to compare.
             * 
             * @return Returns bool(opt) <=> false.
             * 
             */
            template<class X>
            friend constexpr std::strong_ordering operator<=>(const Optional<X>& opt, std::nullopt_t) noexcept
            {
                return opt.o_ <=> std::nullopt;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X optional type.
             * @tparam Y value type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? *opt == value : false.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator==(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ == value;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X value type.
             * @tparam Y optional type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? value == *opt : false.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator==(const X& value, const Optional<Y>& opt)
            {
                return value == opt.o_;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X optional type.
             * @tparam Y value type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? *opt != value : true.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator!=(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ != value;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X value type.
             * @tparam Y optional type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? value != *opt : true.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator!=(const X& value, const Optional<Y>& opt)
            {
                return value != opt.o_;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X optional type.
             * @tparam Y value type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? *opt < value  : true.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator<(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ < value;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X value type.
             * @tparam Y optional type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? value < *opt  : false.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator<(const X& value, const Optional<Y>& opt)
            {
                return value < opt.o_;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X optional type.
             * @tparam Y value type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? *opt <= value : true.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator<=(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ <= value;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X value type.
             * @tparam Y optional type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? value <= *opt : false.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator<=(const X& value, const Optional<Y>& opt)
            {
                return value <= opt.o_;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X optional type.
             * @tparam Y value type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? *opt > value  : false.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator>(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ > value;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X value type.
             * @tparam Y optional type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? value > *opt  : true.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator>(const X& value, const Optional<Y>& opt)
            {
                return value > opt.o_;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X optional type.
             * @tparam Y value type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? *opt >= value : false.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator>=(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ >= value;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X value type.
             * @tparam Y optional type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? value >= *opt : true.
             * 
             */
            template<class X, class Y>
            friend constexpr bool operator>=(const X& value, const Optional<Y>& opt)
            {
                return value >= opt.o_;
            }

            /**
             * @brief Compares opt with a value.
             * 
             * @tparam X optional type.
             * @tparam Y value type.
             * 
             * @param opt optional object to compare. 
             * @param value value to compare to contained value.
             * 
             * @return Returns bool(opt) ? *opt <=> value : std::strong_ordering::less.
             * 
             */
            template<class X, std::three_way_comparable_with<X> Y>
            friend constexpr std::compare_three_way_result_t<X, Y> operator<=>(const Optional<X>& opt, const Y& value)
            {
                return opt.o_ <=> value;
            }

            /**
             * @brief Creates an optional object from value.
             * 
             * @tparam X optional type.
             * 
             * @param value value to construct object with.
             * 
             */
            template<class X>
            friend constexpr Optional<std::decay_t<X>> make_optional(X&& value)
            {
                return Optional<std::decay_t<T>>(std::forward<T>(value));
            }

            /**
             * @brief Creates an optional object from value.
             * 
             * @tparam X optional type.
             * @tparam Args args type.
             * 
             * @param args arguments to be passed to the constructor.
             * 
             */
            template<class X, class... Args>
            friend constexpr Optional<X> make_optional(Args&&... args)
            {
                return Optional<X>(in_place, std::forward<Args>(args)...);
            }

            /**
             * @brief Creates an optional object from value.
             * 
             * @tparam X optional type.
             * @tparam Y initializer list type.
             * @tparam Args args type.
             * 
             * @param il initializer list to be passed to the constructor.
             * @param args arguments to be passed to the constructor.
             * 
             */
            template<class X, class Y, class... Args>
            friend constexpr Optional<X> make_optional(std::initializer_list<Y> il, Args&&... args)
            {
                return Optional<X>(in_place, il, std::forward<Args>(args)...);
            }
        private:
            std::optional<T> o_;
    };

    /**
     * @brief Exchanges the state of lhs with that of rhs.
     * 
     * @tparam T optional type.
     * 
     * @param lhs optional object to swap.
     * @param rhs optional object to swap.
     * 
     * @req {SWS_CORE_01096}
     */
    template<class T>
    void swap(Optional<T>& lhs, Optional<T>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}  // namespace ara::core

#endif  // ARA_CORE_OPTIONAL_H_
