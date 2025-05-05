#pragma once
#include <cstddef>
#include <type_traits>

namespace MdayS
{
    class script_local
    {
    private:
        std::size_t m_Index;
        void* m_StackPtr;

    public:
        constexpr script_local(std::size_t index) :
            m_Index(index),
            m_StackPtr(nullptr)
        {

        }

        constexpr script_local(void* stackPtr, std::size_t index) :
            m_Index(index),
            m_StackPtr(stackPtr)
        {

        }

        constexpr script_local at(std::ptrdiff_t offset) const
        {
            return { m_StackPtr, m_Index + offset };
        }

        constexpr script_local at(std::ptrdiff_t offset, std::size_t size) const
        {
            return { m_StackPtr, m_Index + 1 + offset * size };
        }

        constexpr script_local set(void* stackPtr)
        {
            return { stackPtr, m_Index };
        }

        template<typename T>
        std::enable_if_t<std::is_pointer_v<T>, T> as()
        {
            return static_cast<T>(get());
        }

        template<typename T>
        std::enable_if_t<std::is_lvalue_reference_v<T>, T> as()
        {
            return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
        }

    private:
        void* get() const;

    };
}