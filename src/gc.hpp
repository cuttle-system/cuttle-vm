#pragma once

#include <vector>
#include <string>
#include <map>
#include <typeindex>
#include "value.hpp"
#include "gc_type_error.hpp"

namespace cuttle {
	namespace vm {
        template<typename... Ts>
        struct gc_item_destructor;

	    template <typename Head, typename ... Tail>
	    struct gc_item_destructor<Head, Tail...> {
            inline static void call(const std::type_index& type, void *ptr) {
                if (std::type_index(typeid(Head)) == type) {
                    auto typed_ptr = (Head *) ptr;
                    if (typed_ptr) delete typed_ptr;
                } else {
                    gc_item_destructor<Tail...>::call(type, ptr);
                }
            }
	    };
        template <>
        struct gc_item_destructor<> {
            inline static void call(const std::type_index& type, void *ptr) {
                throw gc_type_error(type);
            }
        };

	    template <typename ... Ts>
	    struct gc_item {
            std::type_index type = typeid(int);
	        void *ptr = nullptr;
	        template <typename T>
	        explicit gc_item(T *ptr) {
	            this->ptr = ptr;
	            type = typeid(T);
	        }
	        void clear() {
	            gc_item_destructor<Ts...>::call(type, ptr);
	        }
	    };

	    template <typename ... Ts>
		struct gc_without_types_t {
		    std::vector<gc_item<Ts...> > items;

			~gc_without_types_t() {
				clear();
			}

            void clear() {
			    for (auto item : items) {
			        item.clear();
			    }
            }

			template <typename T, typename R = any_t>
			R *add(T *ptr) {
                items.emplace_back(ptr);
			    return (R *) ptr;
			}

            template <typename T>
            T *add_r(T *ptr) {
                add(ptr);
                return ptr;
            }
		};

	    using gc_t = gc_without_types_t<VALUE_GCC_SUPPORTED_TYPES>;
	}
}
