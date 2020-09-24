/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_OPTIONAL_H_
#define ARA_CORE_OPTIONAL_H_

#include "ara/core/utility.h"
#include "ara/core/exception.h"
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
            using value_type = T;

            /**
             * @brief Constructs an object that does not contain a value.
             */
            constexpr Optional() noexcept : o_() {}

            /**
             * @brief Constructs an object that does not contain a value.
             */
            constexpr Optional(nullopt_t) noexcept : o_(nullopt) {}

            /**
             * @brief Copy constructor: If other contains a value, 
             * initializes the contained value as if direct-initializing 
             * (but not direct-list-initializing) an object of type T 
             * with the expression *other. If other does not contain a value, 
             * constructs an object that does not contain a value. 
             * 
             * @param other another optional object whose contained value is copied.
             */
            constexpr Optional(const Optional& other) : o_(other) {}

            /**
             * @brief Move constructor: If other contains a value, 
             * initializes the contained value as if direct-initializing 
             * (but not direct-list-initializing) an object of type T 
             * with the expression std::move(*other) and does not make other empty: 
             * a moved-from optional still contains a value, but the value itself is moved from. 
             * If other does not contain a value, constructs an object that does not contain a value. 
             * 
             * @param other another optional object whose contained value is moved.
             */
            constexpr Optional(Optional&& other) noexcept : o_(std::move(other.o_)) {}

            /**
             * @brief Constructs an optional object that contains a value,
             * initialized as if direct-initializing (but not direct-list-initializing) 
             * an object of type T from the arguments std::forward<Args>(args)... .
             * 
             * @tparam Args args type.
             * 
             * @param args arguments with which to initialize the contained value.
             */
            template <class... Args>
            constexpr explicit Optional(in_place_t, Args&&... args) : o_(in_place, std::forward<Args>(args)...) {}

            /**
             * @brief Constructs an optional object that contains a value, 
             * initialized as if direct-initializing (but not direct-list-initializing) 
             * an object of type T from the arguments ilist, std::forward<Args>(args).... 
             * 
             * @tparam U initializer list type.
             * @tparam Args args type.
             * 
             * @param ilist initializer list with which to initialize the contained value.
             * @param args arguments with which to initialize the contained value.
             */
            template <class U, class... Args>
            constexpr explicit Optional(in_place_t, initializer_list<U> ilist, Args&&... args) : o_(in_place, ilist, std::forward<Args>(args)...) {}

            /**
             * @brief Constructs an optional object that contains a value, 
             * initialized as if direct-initializing (but not direct-list-initializing) 
             * an object of type T (where T = value_type) with the expression std::forward<U>(value). 
             * 
             * @tparam U value type.
             * 
             * @param value value with which to initialize the contained value.
             */
            template <class U = T>
            explicit constexpr Optional(U&& value) : o_(std::move(value)) {}

            /**
             * @brief Converting copy constructor: If other doesn't contain a value, 
             * constructs an optional object that does not contain a value. Otherwise,
             * constructs an optional object that contains a value, 
             * initialized as if direct-initializing (but not direct-list-initializing) 
             * an object of type T with the expression *other. 
             * 
             * @tparam U other value type.
             * 
             * @param another optional object whose contained value is copied.
             */
            template <class U>
            explicit Optional(const Optional<U>& other) : o_(other.o_) {}

            /**
             * @brief Converting move constructor: If other doesn't contain a value, 
             * constructs an optional object that does not contain a value. Otherwise, 
             * constructs an optional object that contains a value, 
             * initialized as if direct-initializing (but not direct-list-initializing) 
             * an object of type T with the expression std::move(*other). 
             * 
             * @tparam U other value type.
             * 
             * @param other optional object whose contained value is moved.
             */
            template <class U>
            explicit Optional(Optional<U>&& other) : o_(std::move(other.o_)) {}

            /**
             * @brief Replaces contents of *this with the nullopt.
             * 
             * @return reference to this.
             */
            Optional& operator=(nullopt_t) noexcept
            {
                o_ = nullopt;
                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return reference to this.
             */
            Optional& operator=(const Optional& other)
            {
                o_ = other.o_;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return reference to this.
             */
            Optional& operator=(Optional&& other) noexcept
            {
                if (this != other)
                    o_ = other.o_;
                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @tparam U value type.
             * 
             * @param value value to assign to the contained value.
             * 
             * @return reference to this.
             */
            template <class U = T> 
            Optional& operator=(U&& value)
            {
                o_ = value;
                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @tparam U other value type.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return reference to this.
             */
            template <class U> 
            Optional& operator=(const Optional<U>& other)
            {
                o_ = other.o_;
                return *this;
            }

            /**
             * @brief Replaces contents of *this with the contents of other.
             * 
             * @tparam U other value type.
             * 
             * @param other another optional object whose contained value to assign.
             * 
             * @return reference to this.
             */
            template <class U> 
            Optional& operator=(Optional<U>&& other)
            {
                o_ = other.o_;
                return *this;
            }

            /**
             * @brief Constructs the contained value in-place.
             * 
             * @tparam Args args type.
             * 
             * @param args the arguments to pass to the constructor.
             * 
             * @return A reference to the new contained value. 
             */
            template <class... Args> 
            T& emplace(Args&&... args)
            {
                return o_.emplace(std::forward<Args>(args)...);
            }

            /**
             * @brief Constructs the contained value in-place.
             * 
             * @tparam U initializer list type.
             * @tparam Args args type.
             * 
             * @param args the arguments to pass to the constructor.
             * @param initializer_list initializer list to pass to the constructor.
             * 
             * @return A reference to the new contained value. 
             */
            template <class U, class... Args> 
            T& emplace(initializer_list<U> ilist, Args&&... args)
            {
                return o_.emplace(ilist, std::forward<Args>(args)...);
            }

            /**
             * @brief Exchanges the content.
             */
            void swap(Optional& other) noexcept
            {
                o_.swap(other.o_);
            }

            /**
             * @brief Returns a pointer to the contained value.
             * 
             * @return pointer to the contained value. 
             */
            constexpr const T* operator->() const
            {
                return o_.value();
            }

            /**
             * @brief Returns a pointer to the contained value.
             * 
             * @return pointer to the contained value. 
             */
            constexpr T* operator->()
            {
                return o_.value();
            }

            /**
             * @brief Returns a reference to the contained value.
             * 
             * @return reference to the contained value. 
             */
            constexpr const T& operator*() const&
            {
                return *o_.value;
            }

            /**
             * @brief Returns a reference to the contained value.
             * 
             * @return reference to the contained value. 
             */
            constexpr T& operator*() &
            {
                return *o.value;
            }

            /**
             * @brief Returns a reference to the contained value.
             * 
             * @return reference to the contained value. 
             */
            constexpr T&& operator*() &&
            {
                return std::move(*o_.value());
            }

            /**
             * @brief Returns a reference to the contained value.
             * 
             * @return reference to the contained value. 
             */
            constexpr const T&& operator*() const&&
            {
                return std::move(*o_.value());
            }

            /**
             * @brief Checks whether *this contains a value.
             * 
             * @return true if *this contains a value, false if *this does not contain a value.
             */
            constexpr explicit operator bool() const noexcept
            {
                return has_value();
            }

            /**
             * @brief Checks whether *this contains a value.
             * 
             * @return true if *this contains a value, false if *this does not contain a value.
             */
            constexpr bool has_value() const noexcept
            {
                return o_.has_value();
            }

            /**
             * @brief Returns the contained value if *this has a value, otherwise returns default_value.
             * 
             * @tparam U default_value type.
             * 
             * @param default_value the value to use in case *this is empty.
             * 
             * @return The current value if *this has a value, or default_value otherwise.
             */
            template <class U> 
            constexpr T value_or(U&& default_value) const&
            {
                return o_.value_or(default_value);
            }

            /**
             * @brief Returns the contained value if *this has a value, otherwise returns default_value.
             * 
             * @tparam U default_value type.
             * 
             * @param default_value the value to use in case *this is empty.
             * 
             * @return The current value if *this has a value, or default_value otherwise.
             */
            template <class U>
            constexpr T value_or(U&& default_value) &&
            {
                return std::move(o_.value_or(default_value));
            }

            /**
             * @brief Destroys any contained value.
             */
            void reset() noexcept
            {
                o_.reset();
            }
        private:
            std::optional<T> o_;
    };

    /**
     * @brief indicator of optional type with uninitialized state.
     */
    struct nullopt_t
    {
        explicit constexpr nullopt_t(int) {}
    }

    /**
     * @brief an object of type nullopt_t.
     */
    constexpr nullopt_t nullopt{};

    /**
     * @brief exception indicating checked access to an optional that doesn't contain a value.
     */
    class bad_optional_access : public Exception 
    {
        public:
            bad_optional_access();
    };

    /**
     * @brief Compares two optional objects.
     * 
     * @tparam T an optional object type.
     * @tparam U an optional object type.
     * 
     * @param lhs an optional object to compare.
     * @param rhs an optional object to compare.
     *
     * @return If bool(lhs) != bool(rhs), returns false. 
     * Otherwise, if bool(lhs) == false (and so bool(rhs) == false as well), returns true. 
     * Otherwise, returns *lhs == *rhs.
     */
    template <class T, class U>
    constexpr bool operator==(const Optional<T>& lhs, const Optional<U>& rhs)
    {
        if (bool(lhs) != bool(rhs)) return false;
        if (!bool(lhs) && !bool(rhs)) return true;
        return (*lhs == *rhs);
    }

    /**
     * @brief Compares two optional objects.
     * 
     * @tparam T an optional object type.
     * @tparam U an optional object type.
     * 
     * @param lhs an optional object to compare.
     * @param rhs an optional object to compare.
     *
     * @return If bool(lhs) != bool(rhs), returns true. 
     * Otherwise, if bool(lhs) == false (and so bool(rhs) == false as well), returns false. 
     * Otherwise, returns *lhs != *rhs.
     */
    template <class T, class U>
    constexpr bool operator!=(const Optional<T>& lhs, const Optional<U>& rhs)
    {
        if (bool(lhs) != bool(rhs)) return true;
        if (!bool(lhs) && !bool(rhs)) return false;
        return (*lhs != *rhs);
    }

    /**
     * @brief Compares two optional objects.
     * 
     * @tparam T an optional object type.
     * @tparam U an optional object type.
     * 
     * @param lhs an optional object to compare.
     * @param rhs an optional object to compare.
     *
     * @return If bool(rhs) == false returns false. 
     * Otherwise, if bool(lhs) == false, returns true. 
     * Otherwise returns *lhs < *rhs.
     */
    template <class T, class U>
    constexpr bool operator<(const Optional<T>& lhs, const Optional<U>& rhs)
    {
        if (!bool(rhs)) return false;
        if (!bool(lhs)) return true;
        return (*lhs < *rhs);
    }

    /**
     * @brief Compares two optional objects.
     * 
     * @tparam T an optional object type.
     * @tparam U an optional object type.
     * 
     * @param lhs an optional object to compare.
     * @param rhs an optional object to compare.
     *
     * @return If bool(lhs) == false returns false. 
     * Otherwise, if bool(rhs) == false, returns true.
     * Otherwise returns *lhs > *rhs.
     */
    template <class T, class U>
    constexpr bool operator>(const Optional<T>& lhs, const Optional<U>& rhs)
    {
        if (!bool(lhs)) return false;
        if (!bool(rhs)) return true;
        return (*lhs > *rhs);
    }

    /**
     * @brief Compares two optional objects.
     * 
     * @tparam T an optional object type.
     * @tparam U an optional object type.
     * 
     * @param lhs an optional object to compare.
     * @param rhs an optional object to compare.
     *
     * @return If bool(lhs) == false returns true.
     * Otherwise, if bool(rhs) == false, returns false.
     * Otherwise returns *lhs <= *rhs.
     */
    template <class T, class U>
    constexpr bool operator<=(const Optional<T>& lhs, const Optional<U>& rhs)
    {
        if (!bool(lhs)) return true;
        if (!bool(rhs)) return false;
        return (*lhs <= *rhs);
    }

    /**
     * @brief Compares two optional objects.
     * 
     * @tparam T an optional object type.
     * @tparam U an optional object type.
     * 
     * @param lhs an optional object to compare.
     * @param rhs an optional object to compare.
     *
     * @return If bool(rhs) == false returns true. 
     * Otherwise, if bool(lhs) == false, returns false. 
     * Otherwise returns *lhs >= *rhs.
     */
    template <class T, class U>
    constexpr bool operator>=(const Optional<T>& lhs, const Optional<U>& rhs)
    {
        if (!bool(rhs)) return true;
        if (!bool(lhs)) return false;
        return (*lhs >= *rhs);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns !opt.
     */
    template <class T>
    constexpr bool operator==(const optional<T>& opt, nullopt_t) noexcept
    {
        return !bool(opt);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns !opt.
     */
    template <class T>
    constexpr bool operator==(nullopt_t, const optional<T>& opt) noexcept
    {
        return !bool(opt);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns bool(opt).
     */
    template <class T>
    constexpr bool operator!=(const optional<T>& opt, nullopt_t) noexcept
    {
        return bool(opt);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns bool(opt).
     */
    template <class T>
    constexpr bool operator!=(nullopt_t, const optional<T>& opt) noexcept
    {
        return bool(opt);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns false.
     */
    template <class T>
    constexpr bool operator<(const optional<T>& opt, nullopt_t) noexcept
    {
        return false;
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns bool(opt).
     */
    template <class T>
    constexpr bool operator<(nullopt_t, const optional<T>& opt) noexcept
    {
        return bool(opt);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns !opt.
     */
    template <class T>
    constexpr bool operator<=(const optional<T>& opt, nullopt_t) noexcept
    {
        return !bool(opt);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns true.
     */
    template <class T>
    constexpr bool operator<=(nullopt_t, const optional<T>& opt) noexcept
    {
        return true;
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns bool(opt).
     */
    template <class T>
    constexpr bool operator>(const optional<T>& opt, nullopt_t) noexcept
    {
        return bool(opt);
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns false.
     */
    template <class T>
    constexpr bool operator>(nullopt_t, const optional<T>& opt) noexcept
    {
        return false;
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns true.
     */
    template <class T>
    constexpr bool operator>=(const optional<T>& opt, nullopt_t) noexcept
    {
        return true;
    }

    /**
     * @brief Compares an optional object with a nullopt.
     * 
     * @tparam T an optional object type.
     * 
     * @param opt an optional object to compare.
     * 
     * @return Returns !opt.
     */
    template <class T>
    constexpr bool operator>=(nullopt_t, const optional<T>& opt) noexcept
    {
        return !bool(opt);
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? *opt == value : false.
     */
    template <class T, class U>
    constexpr bool operator==(const optional<T>& opt, const U& value)
    {
        return bool(opt) ? *opt == value : false;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? value == *opt : false.
     */
    template <class T, class U>
    constexpr bool operator==(const U& value, const optional<T>& opt)
    {
        return bool(opt) ? value == *opt : false;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? *opt != value : true.
     */
    template <class T, class U>
    constexpr bool operator!=(const optional<T>& opt, const U& value)
    {
        return bool(opt) ? *opt != value : true;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? value != *opt : true.
     */
    template <class T, class U>
    constexpr bool operator!=(const U& value, const optional<T>& opt)
    {
        return bool(opt) ? value != *opt : true;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? *opt < value  : true.
     */
    template <class T, class U>
    constexpr bool operator<(const optional<T>& opt, const U& value)
    {
        return bool(opt) ? *opt < value  : true;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? value < *opt  : false.
     */
    template <class T, class U>
    constexpr bool operator<(const U& value, const optional<T>& opt)
    {
        return bool(opt) ? value < *opt  : false;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? *opt <= value : true.
     */
    template <class T, class U>
    constexpr bool operator<=(const optional<T>& opt, const U& value)
    {
        return bool(opt) ? *opt <= value : true;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? value <= *opt : false.
     */
    template <class T, class U>
    constexpr bool operator<=(const U& value, const optional<T>& opt)
    {
        return bool(opt) ? value <= *opt : false;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? *opt > value  : false.
     */
    template <class T, class U>
    constexpr bool operator>(const optional<T>& opt, const U& value)
    {
        return bool(opt) ? *opt > value  : false;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? value > *opt  : true.
     */
    template <class T, class U>
    constexpr bool operator>(const U& value, const optional<T>& opt)
    {
        return bool(opt) ? value > *opt  : true;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? *opt >= value : false.
     */
    template <class T, class U>
    constexpr bool operator>=(const optional<T>& opt, const U& value)
    {
        return bool(opt) ? *opt >= value : false;
    }

    /**
     * @brief Compares an optional object with a value.
     * 
     * @tparam T an optional object type.
     * @tparam U an value type.
     * 
     * @param opt an optional object to compare.
     * @param value an value to compare.
     * 
     * @return Returns bool(opt) ? value >= *opt : true.
     */
    template <class T, class U>
    constexpr bool operator>=(const U& value, const optional<T>& opt)
    {
        return bool(opt) ? value >= *opt : true;
    }

    /**
     * @brief Swaps content between optional objects.
     * 
     * @tparam T an optional object type.
     * 
     * @param lhs an optional object to swap.
     * @param rhs an optional object to swap.
     */
    template <class T>
    void swap(Optional<T>& lhs, Optional<T>& rhs) noexcept
    {
        lhs.swap(rhs);
    }

    /**
     * @brief Creates an optional object from value.
     * 
     * @tparam T value type.
     * 
     * @param value the value to construct object with.
     * 
     * @return the constructed optional object.
     */
    template <class T>
    constexpr Optional<std::decay_t<T>> make_optional(T&& value)
    {
        return Optional<T>(std::move(value));
    }

    /**
     * @brief Creates an optional object from argument list.
     * 
     * @tparam T an optional type.
     * @tparam Args argument list type.
     * 
     * @param args arguments to be passed to the constructor of optional.
     * 
     * @return the constructed optional object.
     */
    template <class T, class... Args>
    constexpr Optional<T> make_optional(Args&&... args)
    {
        return Optional<T>(in_place, std::forward<Args>(args)...);
    }

    /**
     * @brief Creates an optional object from argument list.
     * 
     * @tparam T an optional type.
     * @tparam U an initializer list type.
     * @tparam Args argument list type.
     * 
     * @param il initializer list to be passed to the constructor of optional.
     * @param args arguments to be passed to the constructor of optional.
     * 
     * @return the constructed optional object.
     */
    template <class T, class U, class... Args>
    constexpr Optional<T> make_optional(initializer_list<U> il, Args&&... args)
    {
        return Optional<T>(in_place, il, std::forward<Args>(args)...);
    }
}  // namespace ara::core

#endif  // ARA_CORE_OPTIONAL_H_
