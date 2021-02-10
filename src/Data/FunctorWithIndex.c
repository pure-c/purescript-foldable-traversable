#include <purescript.h>

PURS_FFI_FUNC_2(Data_FunctorWithIndex_mapWithIndexArray, f, _xs) {
	purs_any_t tmp1;
	const purs_vec_t *xs = purs_any_force_array(_xs);
	if (xs == NULL /* empty */) {
		return purs_any_array(NULL);
	}

	purs_vec_t *out = (purs_vec_t *) purs_vec_new();
	purs_vec_reserve(out, xs->length);
	for (int i = 0; i < xs->length; i++) {
		tmp1 = purs_any_app(f, purs_any_int(i));
		out->data[i] = purs_any_app(tmp1, xs->data[i]);
		PURS_ANY_RELEASE(tmp1);
	}
	out->length = xs->length;
	PURS_RC_RELEASE(xs);
	return purs_any_array(out);
}
