#include <purescript.h>

PURS_FFI_FUNC_1(Test_Main_arrayFrom1UpTo, _n) {
	purs_int_t n = purs_any_force_int(_n);
	purs_vec_t *result = (purs_vec_t *) purs_vec_new();
	for (purs_int_t i = 1; i <= n; i++) {
		purs_vec_push_mut(result, purs_any_int(i));
	}
	return purs_any_array(result);
}

PURS_FFI_FUNC_2(Test_Main_arrayReplicate, _n, x) {
	purs_int_t n = purs_any_force_int(_n);
	purs_vec_t *result = (purs_vec_t *) purs_vec_new();
	for (purs_int_t i = 1; i <= n; i++) {
		PURS_ANY_RETAIN(x);
		purs_vec_push_mut(result, x);
	}
	return purs_any_array(result);
}
