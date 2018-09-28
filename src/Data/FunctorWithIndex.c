#include <purescript.h>

PURS_FFI_FUNC_2(Data_FunctorWithIndex_mapWithIndexArray, f, _xs, {
  const purs_vec_t * xs = purs_any_get_array(_xs);
  purs_vec_t * out = (purs_vec_t *) purs_vec_new();
  purs_vec_reserve(out, xs->length);

  for (int i = 0; i < xs->length; i++) {
    out->data[i] = (purs_any_t *)purs_any_app(purs_any_app(f, PURS_ANY_INT_NEW(i)), xs->data[i]);
  }
  out->length = xs->length;

  return PURS_ANY_ARRAY_NEW(out);
})
