# too-many-containers

`too-many-containers` or `tmc` is a work-in-progress library that implements all kinds of unusual containers, container adaptors and misc. library additions.

## Containers

## Container adaptors

## Utility

### Emplacement iterators

Emplacement iterators are a natural extension of traditional insertion iterators. While effectively equivalent in most cases, they provide a more general approach to constructing values with limited relocatability or assignment.

| `std::`                 | `tmc::`                 | Difference                                       |
| ----------------------- | ----------------------- | ------------------------------------------------ |
| `std::back_inserter()`  | `tmc::back_emplacer()`  | Uses `emplace_back()` instead of `push_back()`   |
| `std::front_inserter()` | `tmc::front_emplacer()` | Uses `emplace_front()` instead of `push_front()` |
| `std::inserter()`       | `tmc::emplacer()`       | Uses `emplace()` instead of `insert()`           |

An obvious limitation of emplacement iterators, is that `operator=()` can only accept a single argument, making arbitrary emplacement seemingly impossible to achieve with iterators. To circumvent this limitation we can forward constructor arguments as a tuple of references using `tmc::make_emplace_args()`. For example:

```cpp
std::vector<std::array<double, 3>> vector;

std::fill_n(tmc::back_emplacer(vector), 16, tmc::make_emplace_args(1.0, 2.0, 3.0));
```

Iterators returned by `tmc::back_emplacer()`, `tmc::front_emplacer()` and `tmc::emplacer()` provide the exact same API and guarantees as their standard counterparts. As always, everything is concept-constrained, `constexpr` and `noexcept` if possible.

### Approximate float comparator

`tmc::approx` is a wrapper for approximate comparison of floating-point values. Finite `approx` values compare equal when their absolute difference is below the comparison `tolerance`:

```cpp
if (tmc::approx{ value } == 0) throw std::runtime_error{ "Result is degenerate" };
```

The value of `tolerance` can be specified in template parameters (which became possible in C++20), by default `tolerance` is deduced to be `std::numeric_limits<T>::epsilon()` of the argument type.

```cpp
static_assert(tmc::approx<1e-3>{ 1e-4 } == 0); // explicit tolerance

static_assert(tmc::approx{ 0.0 } == 0); // deduced std::numeric_limits<double>::epsilon()
static_assert(tmc::approx{ 0.f } == 0); // deduced std::numeric_limits< float>::epsilon()
```

In general, due to their "special" states such as `inf` / `nan`, floating-point numbers form an `std::partial_ordering`, which can be evaluated with a spaceship operator `<=>` or `std::partial_order(lhs, rhs)`. In that sense, applying a "clamping equality" is entirely legal as it results in just another partial ordering. To evaluate it in general case with a given tolerance use `tmc::approx_order(lhs, rhs)`:

```cpp
constexpr auto tolerance = 1e-2;

static_assert(tmc::approx_order(1.0003, 1.0, tolerance) == std::partial_ordering::equivalent);
```

### Comparator closures

Numeric algorithms frequently require writing lambdas that boil down to a single comparison against some value.

This can be streamlined using comparator closures, for example:

```cpp
auto vector = std::vector{ 2, 5, 17, 3, 46, 1 };

auto count = std::ranges::count_if(vector, tmc::less_than{ 5 });
```

Below is a table of all present closures:

| Transparent closure            | Transparent comparator | Predicate    |
| ------------------------------ | ---------------------- | ------------ |
| `tmc::less_than{ x }`          | `tmc::less`            | `value < x`  |
| `tmc::less_equal_than{ x }`    | `tmc::less_equal`      | `value <= x` |
| `tmc::greater_than{ x }`       | `tmc::greater`         | `value > x`  |
| `tmc::greater_equal_then{ x }` | `tmc::greater_equal`   | `value >= x` |
| `tmc::equal_to{ x }`           | `tmc::equal`           | `value == x` |
| `tmc::not_equal_to{ x }`       | `tmc::not_equal`       | `value != x` |

## License

This project is licensed under the MIT License - see the [LICENSE.md](../LICENSE.md) for details.
