#include <internal/utils.hpp>

#include <cstdarg>
#include <functional>
#include <string>

namespace hocon {

std::string string_format(const char* fmt, ...) {
    size_t sizet = strlen(fmt) * 2 + 50;   // Use a rubric appropriate for your code
    if (sizet > std::numeric_limits<int>::max()) {
        return "[INVALID FORMAT SPECIFIED]";
    }
    int size = static_cast<int>(sizet);
    std::string str;
    va_list ap;
    while (1) {     // Maximum two passes on a POSIX system...
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char*) str.data(), size, fmt, ap);
        va_end(ap);
        if (n > -1 && n < size) {  // Everything worked
            str.resize(n);
            return str;
        }
        if (n > -1)  // Needed size returned
            size = n + 1;   // For null char
        else
            size *= 2;      // Guess at a larger size (OS specific)
    }
    return str;
}


/**
 * Moves the given scope_exit into this scope_exit.
 * @param other The scope_exit to move into this scope_exit.
 */
scope_exit::scope_exit(scope_exit&& other) {
    *this = std::move(other);
}

/**
 * Moves the given scoped_resource into this scoped_resource.
 * @param other The scoped_resource to move into this scoped_resource.
 * @return Returns this scope_exit.
 */
scope_exit& scope_exit::operator=(scope_exit&& other) {
    _callback = std::move(other._callback);

    // Ensure the callback is in a known "empty" state; we can't rely on default move semantics for that
    other._callback = nullptr;
    return *this;
}

/**
 * Destructs a scope_exit.
 */
scope_exit::~scope_exit() {
    invoke();
}

/**
 * Invokes the callback.
 * If called, the callback will not be called upon destruction.
 */
void scope_exit::invoke() {
    if (_callback) {
        _callback();
        _callback = nullptr;
    }
}


} //namespace hocon
