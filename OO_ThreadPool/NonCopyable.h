#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

class NonCopyable
{
protected:
    NonCopyable() = default;
    NonCopyable(const NonCopyable &rhs) = delete;
    NonCopyable &operator=(const NonCopyable &rhs) = delete;
private:

};
#endif
