#pragma once

#include <vector>

namespace cuttle {
	namespace vm {
		struct gc_t {
			~gc_t() {
				clear();
			}

			template <typename T>
			T *add(T *ptr) {
				ptrs.push_back((void *) ptr);
				return ptr;
			}

			void clear() {
				for (void *&ptr : ptrs) {
					free(ptr);
					ptr = nullptr;
				}
				ptrs.clear();
			}

			std::vector<void *> ptrs;
		};
	}
}
