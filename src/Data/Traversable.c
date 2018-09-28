#include <purescript.h>

PURS_FFI_FUNC_1(Data_Traversable_array1, a, {
  return PURS_ANY_ARRAY_NEW(purs_vec_new_from_array(1, a));
})

PURS_FFI_FUNC_2(Data_Traversable_array2, a, b, {
  return PURS_ANY_ARRAY_NEW(purs_vec_new_from_array(2, a, b));
})

PURS_FFI_FUNC_3(Data_Traversable_array3, a, b, c, {
  return PURS_ANY_ARRAY_NEW(purs_vec_new_from_array(3, a, b, c));
})

PURS_FFI_FUNC_2(Data_Traversable_concat2, xs, ys, {
  return purs_any_concat(xs, ys);
})

const purs_any_t * traversable_go(
    const purs_any_t * apply,
    const purs_any_t * map,
    const purs_any_t * pure,
    const purs_any_t * f,
    const purs_vec_t * array,
    purs_any_int_t bot,
    purs_any_int_t top) {

  purs_any_int_t pivot;

  switch(top - bot) {
    case 0:
      return purs_any_app(pure, PURS_ANY_ARRAY_NEW(purs_vec_new()));
    case 1:
      return purs_any_app(
               purs_any_app(map, Data_Traversable_array1$),
               purs_any_app(f, array->data[bot]));
    case 2:
      return purs_any_app(
               purs_any_app(apply,
                 purs_any_app(
                   purs_any_app(map, Data_Traversable_array2$),
                   purs_any_app(f, array->data[bot])
                 )
               ),
               purs_any_app(f, array->data[bot+1]));
    case 3:
      return purs_any_app(
               purs_any_app(apply,
                 purs_any_app(
                   purs_any_app(apply,
                     purs_any_app(
                       purs_any_app(map, Data_Traversable_array3$),
                       purs_any_app(f, array->data[bot])
                     )
                   ),
                   purs_any_app(f, array->data[bot+1])
                 )
               ),
               purs_any_app(f, array->data[bot+2]));
    default:
      // This slightly tricky pivot selection aims to produce two
      // even-length partitions where possible.
      pivot = (top - bot) / 4;
      pivot = bot + pivot * 2;

      return purs_any_app(
               purs_any_app(apply,
                 purs_any_app(
                   purs_any_app(map, Data_Traversable_concat2$),
                   traversable_go(apply, map, pure, f, array, bot, pivot)
                 )
               ),
               traversable_go(apply, map, pure, f, array, pivot, top));

  }
}

PURS_FFI_FUNC_5(Data_Traversable_traverseArrayImpl, apply, map, pure, f, _array, {
  const purs_vec_t * array = purs_any_get_array(_array);
  return traversable_go(apply, map, pure, f, array, 0, array->length);
})
