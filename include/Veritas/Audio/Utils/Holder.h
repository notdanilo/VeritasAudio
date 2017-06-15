#pragma once

#include <cassert>
#include <iostream>

namespace Veritas {
    namespace Audio {
        namespace Utils {
            template <class T>
            class Holder {
                public:
                    Holder() : value(0), moved(false) {}
                    Holder(T*  pvalue) : value(pvalue), moved(false) {}
                    Holder(T&  lvalue) : value(&lvalue), moved(false) {}
                    Holder(T&& rvalue) : value(new T(std::move(rvalue))), moved(true) {}

                    Holder(Holder&&) = delete;
                    Holder(const Holder&) = delete;
                    Holder& operator=(Holder&&) = delete;
                    Holder& operator=(const Holder&) = delete;
                    ~Holder() { if (moved) delete value; }

                    void operator=(T* pvalue) {
                        if (moved) {
                            delete value;
                            moved = false;
                        }
                        value = pvalue;
                    }
                    void operator=(T& lvalue) { operator=(&lvalue); }
                    template <class U>
                    void operator=(const U&& rvalue) {
                        if (moved) delete value;
                        value = new U(std::move(rvalue));
                        moved = true;
                    }

                    operator T*() { return value; }
                    T* operator->() { return value; }
                    T** operator&() { return &value; }
                private:
                    bool moved;
                    T* value;
            };
        }
    }
}
