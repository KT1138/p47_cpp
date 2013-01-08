/**
 *
 */

#ifndef auto_ptr_fix_h_
#define auto_ptr_fix_h_

#include <memory>

template <class _T>
inline void auto_ptr_copy (std::auto_ptr<_T>& lhs, std::auto_ptr<_T> rhs) {
	lhs = rhs;
}
template <class _T>
inline void auto_ptr_copy (std::auto_ptr<_T>& lhs, _T* rhs) {
	std::auto_ptr<_T> p(rhs);
	lhs = p;
}
template <class _T>
inline _T* auto_ptr_release(std::auto_ptr<_T>& p) {
	_T* ret = p.release();
	auto_ptr_copy(p, std::auto_ptr<_T>());
	return ret;
}

#endif // ! auto_ptr_fix_h_

