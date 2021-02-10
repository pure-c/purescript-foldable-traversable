#include <purescript.h>

PURS_FFI_FUNC_1(Data_Traversable_array1, a) {
	return purs_any_array(purs_vec_new_va(1, a));
}

PURS_FFI_FUNC_2(Data_Traversable_array2, a, b) {
	return purs_any_array(purs_vec_new_va(2, a, b));
}

PURS_FFI_FUNC_3(Data_Traversable_array3, a, b, c) {
	return purs_any_array(purs_vec_new_va(3, a, b, c));
}

PURS_FFI_FUNC_2(Data_Traversable_concat2, xs, ys) {
	return purs_any_concat(xs, ys);
}

purs_any_t traversable_go(purs_any_t apply,
			  purs_any_t map,
			  purs_any_t pure,
			  purs_any_t f,
			  const purs_vec_t *array,
			  purs_int_t bot,
			  purs_int_t top) {
	purs_int_t pivot;
	purs_any_t ret = purs_any_null;
	purs_any_t tmp1 = purs_any_null;
	purs_any_t tmp2 = purs_any_null;
	purs_any_t tmp3 = purs_any_null;
	purs_any_t tmp4 = purs_any_null;
	purs_any_t tmp5 = purs_any_null;
	purs_any_t tmp6 = purs_any_null;
	purs_any_t tmp7 = purs_any_null;
	purs_any_t tmp8 = purs_any_null;
	purs_any_t tmp9 = purs_any_null;

	switch(top - bot) {
	case 0: {
		tmp1 = purs_any_array(purs_vec_new());
		ret = purs_any_app(pure, tmp1);
		goto end;
	}
	case 1: {
		tmp1 = purs_any_app(map, Data_Traversable_array1);
		tmp2 = purs_any_app(f, array->data[bot]);
		ret = purs_any_app(tmp1, tmp2);
		goto end;
	}
	case 2: {
		tmp1 = purs_any_app(map, Data_Traversable_array2);
		tmp2 = purs_any_app(f, array->data[bot]);
		tmp3 = purs_any_app(tmp1, tmp2);
		tmp4 = purs_any_app(apply, tmp3);
		tmp5 = purs_any_app(f, array->data[bot+1]);
		ret = purs_any_app(tmp4, tmp5);
		goto end;
	}
	case 3: {
		tmp1 = purs_any_app(map, Data_Traversable_array3);
		tmp2 = purs_any_app(f, array->data[bot]);
		tmp3 = purs_any_app(tmp1, tmp2);
		tmp4 = purs_any_app(apply, tmp3);
		tmp5 = purs_any_app(f, array->data[bot+1]);
		tmp6 = purs_any_app(tmp4, tmp5);
		tmp7 = purs_any_app(apply, tmp6);
		tmp8 = purs_any_app(f, array->data[bot+2]);
		ret = purs_any_app(tmp7, tmp8);
		goto end;
	}
	default: {
		// This slightly tricky pivot selection aims to produce two
		// even-length partitions where possible.
		pivot = (top - bot) / 4;
		pivot = bot + pivot * 2;
		tmp1 = purs_any_app(map, Data_Traversable_concat2);
		tmp5 = traversable_go(apply, map, pure, f, array, bot, pivot);
		tmp2 = purs_any_app(tmp1, tmp5);
		tmp3 = purs_any_app(apply, tmp2);
		tmp6 = traversable_go(apply, map, pure, f, array, pivot, top);
		ret  = purs_any_app(tmp3, tmp6);
		goto end;
	}
	}

 end:
	PURS_ANY_RELEASE(tmp9);
	PURS_ANY_RELEASE(tmp8);
	PURS_ANY_RELEASE(tmp7);
	PURS_ANY_RELEASE(tmp6);
	PURS_ANY_RELEASE(tmp5);
	PURS_ANY_RELEASE(tmp4);
	PURS_ANY_RELEASE(tmp3);
	PURS_ANY_RELEASE(tmp2);
	PURS_ANY_RELEASE(tmp1);

	return ret;
}

PURS_FFI_FUNC_5(Data_Traversable_traverseArrayImpl, apply, map, pure, f, _array) {
	const purs_vec_t *array;
	purs_any_t ret;
	array = purs_any_force_array(_array);
	if (array == NULL /* empty */) {
		return purs_any_array(NULL);
	}
	ret = traversable_go(apply, map, pure, f, array, 0, array->length);
	PURS_RC_RELEASE(array);
	return ret;
}
