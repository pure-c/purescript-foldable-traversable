#include <purescript.h>

PURS_FFI_FUNC_3(Data_Foldable_foldrArray, f, init, _xs, {
  purs_any_t * acc = (purs_any_t *)init;
  const purs_vec_t * xs = purs_any_get_array(_xs);
  for (int i = xs->length - 1; i >= 0; i--) {
    acc = (purs_any_t *)purs_any_app(purs_any_app(f, xs->data[i]), (const purs_any_t *)acc);
  }
  return (const purs_any_t *)acc;
})

PURS_FFI_FUNC_3(Data_Foldable_foldlArray, f, init, _xs, {
  purs_any_t * acc = (purs_any_t *)init;
  const purs_vec_t * xs = purs_any_get_array(_xs);
  for (int i = 0; i < xs->length; i++) {
    acc = (purs_any_t *)purs_any_app(purs_any_app(f, (const purs_any_t *)acc), xs->data[i]);
  }
  return (const purs_any_t *)acc;
})
