#include <purescript.h>

PURS_FFI_FUNC_3(Data_Foldable_foldrArray, f, init, _xs) {
	purs_any_t acc;
	const purs_vec_t *xs;
	int acc_changed = 0;

	acc = init;
	xs = purs_any_force_array(_xs);

	if (xs == NULL /* empty */) {
		return acc;
	}

	for (int i = xs->length - 1; i >= 0; i--) {
		purs_any_t tmp1, tmp2;
		tmp1 = purs_any_app(f, xs->data[i]);
		tmp2 = purs_any_app(tmp1, acc);
		if (acc_changed) PURS_ANY_RELEASE(acc);
		acc = tmp2;
		acc_changed = 1;
		PURS_ANY_RELEASE(tmp1);
	}

	PURS_RC_RELEASE(xs);
	return acc;
}

PURS_FFI_FUNC_3(Data_Foldable_foldlArray, f, init, _xs) {
	purs_any_t acc;
	const purs_vec_t *xs;
	int acc_changed = 0;

	acc = init;
	xs = purs_any_force_array(_xs);

	if (xs == NULL /* empty */) {
		return acc;
	}

	for (int i = 0; i < xs->length; i++) {
		purs_any_t tmp1, tmp2;
		tmp1 = purs_any_app(f, acc);
		tmp2 = purs_any_app(tmp1, xs->data[i]);
		if (acc_changed) PURS_ANY_RELEASE(acc);
		acc = tmp2;
		acc_changed = 1;
		PURS_ANY_RELEASE(tmp1);
	}

	PURS_RC_RELEASE(xs);
	return acc;
}
