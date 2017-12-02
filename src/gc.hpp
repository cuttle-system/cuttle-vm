#pragma once

#include <vector>

namespace cuttle {
	namespace vm {
		struct gc {
			~gc() {
				clear();
			}

			template <typename T>
			T *add(T *ptr) {
				ptrs.push_back((void *) ptr);
				return ptr;
			}

			void clear() {
				for (void *&ptr : ptrs) {
					delete ptr;
					ptr = NULL;
				}
				ptrs = std::vector<void *>();
			}

			std::vector<void *> ptrs;
		};
	}
}