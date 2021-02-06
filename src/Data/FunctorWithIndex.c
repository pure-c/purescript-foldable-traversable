#include <purescript.h>

PURS_FFI_FUNC_2(Data_FunctorWithIndex_mapWithIndexArray, f, _xs) {
	const purs_vec_t *xs = purs_any_force_array(_xs);
	purs_vec_t *out = (purs_vec_t *) purs_vec_new();
	purs_vec_reserve(out, xs->length);
	for (int i = 0; i < xs->length; i++) {
		out->data[i] = purs_any_app(purs_any_app(f, purs_any_int(i)), xs->data[i]);
	}
	out->length = xs->length;
	PURS_RC_RELEASE(xs);
	return purs_any_array(out);
}
