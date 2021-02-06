#include <purescript.h>

PURS_FFI_FUNC_3(Data_Foldable_foldrArray, f, init, _xs) {
	purs_any_t acc = init;
	const purs_vec_t *xs = purs_any_force_array(_xs);
	for (int i = xs->length - 1; i >= 0; i--) {
		acc = purs_any_app(purs_any_app(f, xs->data[i]), acc);
	}
	PURS_RC_RELEASE(xs);
	return acc;
}

PURS_FFI_FUNC_3(Data_Foldable_foldlArray, f, init, _xs) {
	purs_any_t acc = init;
	const purs_vec_t *xs = purs_any_force_array(_xs);
	for (int i = 0; i < xs->length; i++) {
		acc = purs_any_app(purs_any_app(f, acc), xs->data[i]);
	}
	PURS_RC_RELEASE(xs);
	return acc;
}
