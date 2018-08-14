
# type_finder

 same type finder from variadic template parameters



## functions

### `type_finder :: same <Target, Args... > :: type`

find `Target` type from `Args...`. `type` returned `Target` if found, 
otherwise returned `same<Target, Args... > :: not_found`, it is a alias to `type_finder :: not_found`.


### `type_finder :: same_base <Target, Args... > :: type`

find `Target` or `Target` based inherit type from `Args`. `type` returned `Target` if found.
otherwise returned `same_base<Target, Args...> :: not_found`, it is a alias to `type_finder :: not_found`

### `type_finder :: is_same <Target, Args... > :: value`

find `Target` type from `Args...`. `value` returned `true` if found, otherwise returned `false`.


### `type_finder :: is_same_base <Target, Args... > :: value`

find `Target` or `Target` based inherit type from `Args`. `value` returned `true` if found. otherwise returned `false`.
