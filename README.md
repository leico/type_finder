
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


## 簡単な解説

### finder_template

```cpp
template <
    template < typename, typename > class Conditioner
  , typename    Target
  , typename... Args
>
class finder_template {
...
};
```

`Conditioner`
: `Func<A, B> :: value` のようなテンプレート型を比較処理に用いる。
  `same` の場合、`std :: is_same` を, `same_base` の場合、`std :: is_base_of` をそれぞれ渡している。
  内部で型同士の判定に利用している。

`Target`
: 対象となる型を指定する

`Args...`
: 対象を検索するテンプレートパラメータたち

```cpp
public:
  using type = typename impl< Conditioner, Target, Args... > :: type;
```

返り値の導出開始部分。テンプレートパラメータを内部処理のメタ関数に渡している。

```cpp
private:

template <
    template < typename, typename > class Cond
  , typename    InTarget
  , typename... NoArgs
>
struct impl {
  using type = not_found;
};
```

内部処理。検索範囲が何もない状態の時は `not_found` を返す。

```cpp
template <
    template < typename, typename > class Cond
  , typename    InTarget
  , typename    Head
  , typename... Tail
>
struct impl < Cond, InTarget, Head, Tail... > {
  using type = typename std :: conditional<
      Cond< InTarget, Head > :: value
    , InTarget
    , typename impl< Cond, InTarget, Tail... > :: type
  > :: type;
};
```

検索範囲が1つ以上ある場合の内部処理。
先頭の型とターゲットの型を `Cond` = `Conditioal` で比較、`true` が返れば`Target` を返す。
`false` の場合、 `impl< Cond, InTarget, Tail... > :: type` と先頭を削って再帰処理に入る。


## example

```cpp

 // same returned not_found
  std :: cout << typeid( type_finder :: same< A, B, C > :: type ).name() << std :: endl ;

  // same returned type B
  std :: cout << typeid( type_finder :: same< B, A, int, double, char, B > :: type ).name() << std :: endl;

  // same_base returned type A
  std :: cout << typeid( type_finder :: same_base< A, B, C, AA > :: type ).name() << std :: endl;

  // same_base returned not_found
  std :: cout << typeid( type_finder :: same_base< AA, int, char, AB, C, B > :: type ).name() << std :: endl;

  // is_same returned false
  std :: cout << std :: boolalpha << type_finder :: is_same< A, B, C > :: value << std :: endl; 
  
  // is_same returned true
  std :: cout << std :: boolalpha << type_finder :: is_same< int, long, double, int > :: value << std :: endl; 

  // is_same_base returned true
  std :: cout << std :: boolalpha << type_finder :: is_same_base< A, B, C, AA > :: value << std :: endl; 

  // is_same_base returned false
  std :: cout << std :: boolalpha << type_finder :: is_same_base< A, int, B, C> :: value << std :: endl; 
```
