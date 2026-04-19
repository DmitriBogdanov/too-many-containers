# too-many-containers

`too-many-containers` or `tmc` is a comprehensive library of containers, adapters and memory resources for performance-sensitive code.

It wraps some of the best (performance-wise) container implementations into a uniform API with sane modern defaults.

> [!Important]
> Current documentation **does not** reflect the actual feature set, it serves merely as a specification.

## Design choices

- Containers don't pay the performance penalty of having stable pointers unless `stable_` version is explicitly specified
- All containers support heterogeneous lookup by default (by using transparent `tmc::hash`, `tmc::less`, `tmc::equal_to` and etc.)
- All containers support C++23 `std::from_range` construction
- All containers with heap allocation provide `pmr::` versions for polymorphic allocator support
- All templates are be concept-constrained to fail early and with readable messages
- Additional functionality (such as `tmc::try_fetch()`, `tmc::try_pop()`, `tmc::grow_by_factor()` and etc.) is implemented unintrusively in terms of free functions

## Adapters

| Type                     | Summary                                                      |
| ------------------------ | ------------------------------------------------------------ |
| `tmc::flat_map<K, V, C>` | Associative wrapper around sorted container `C` of `std::pair<K, V>` |
| `tmc::flat_set<K, V, C>` | Associative wrapper around sorted container `C` of `K`       |
| `tmc::queue<T, C>`       | FIFO wrapper around push / pop container `C`                 |
| `tmc::stack<T, C>`       | LIFO wrapper around push / pop container `C`                 |

## Containers

| Type                      | Summary                                     |
| ------------------------- | ------------------------------------------- |
| **vector** |  |
| `tmc::vector<T>`        | `std::vector<T>` without `bool` specialization |
| `tmc::small_vector<T, N>` | `std::vector<T>` with allocation-free storage below `N` elements |
| `tmc::static_vector<T, N>` | `std::vector<T>`  with allocation-free storage for at most `N` elements |
| `tmc::stable_vector<T, N>` | `std::vector<T>` with pointer-stable elements |
| **unordered_map** |  |
| `tmc::unordered_map<K, V>` | Faster `std::unordered_map<K, V>` without pointer stability & bucket API |
| `tmc::small_unordered_map<K, V, N>` | `std::unordered_map<K, V>` with allocation-free storage below `N` elements |
| `tmc::static_unordered_map<K, V, N>` | `std::unordered_map<K, V>` with allocation-free storage for at most `N` elements |
| `tmc::stable_unordered_map<K, V>` | Faster `std::unordered_map<K, V>` without bucket API |
| **map** |  |
| `tmc::map<K, V>` | Faster `std::map<K, V>` without pointer stability |
| `tmc::small_map<K, V, N>` | `std::map<K, V>` with allocation-free storage below `N` elements |
| `tmc::static_map<K, V, N>` | `std::map<K, V>` with allocation-free storage for at most `N` elements |
| `tmc::stable_map<K, V>` | `std::map<K, V>` |
| **unordered_set** |  |
| `tmc::unordered_set<K, V>` | Faster `std::unordered_set<K, V>` without pointer stability & bucket API |
| `tmc::small_unordered_set<K, V, N>` | `std::unordered_set<K, V>` with allocation-free storage below `N` elements |
| `tmc::static_unordered_set<K, V, N>` | `std::unordered_set<K, V>` with allocation-free storage for at most `N` elements |
| `tmc::stable_unordered_set<K, V>` | Faster `std::unordered_set<K, V>` without bucket API |
| **set** |  |
| `tmc::set<K, V>` | Faster `std::set<K, V>` without pointer stability |
| `tmc::small_set<K, V, N>` | `std::set<K, V>` with allocation-free storage below `N` elements |
| `tmc::static_set<K, V, N>` | `std::set<K, V>` with allocation-free storage for at most `N` elements |
| `tmc::stable_set<K, V>` | `std::set<K, V>` |
| **deque** |  |
| `tmc::deque<T>` | Faster `std::deque<T>` without pointer stability |
| `tmc::small_deque<T, N>` | `std::deque<T>` with allocation-free storage below `N` elements |
| `tmc::static_deque<T, N>` | `std::deque<T>` with allocation-free storage for at most `N` elements |
| `tmc::stable_deque<T>` | `std::deque<T>` without MSVC block size defects |
| **string_view** |  |
| `tmc::string_view` | `std::string_view` |
| `tmc::zstring_view` | `std::string_view` which guarantees zero termination |
| **span** |  |
| `tmc::span<T>` | `std::span<T>` |
| **optional** |  |
| `tmc::optional<T>` | `std::optional<T>` with reference type & range support |

## Data-structures

| Type                            | Summary                                            |
| ------------------------------- | -------------------------------------------------- |
| `tmc::allocation_ptr<T, Alloc>` | `std::unique_ptr<T>` with custom allocator support |
| `tmc::dynamic_array<T, Alloc>`  | `std::unique_ptr<T[]>` with vector-like API        |

## Building

`tmc` and all of its dependencies are header-only and bundled into the repo, to use bundled dependencies just add their directories to the include path:

```bash
clang++ -I/include/ -I/external/boost/include main.cpp
```

Using CMake, all deps are included into the default target:

```cmake
# Link TMC with all its dependencies embedded
target_link_libraries(target too-many-containers::with_dependencies)
```

When vendoring your own versions of dependencies, simply link `too-many-containers::without_dependencies` instead.

```cmake
# Use your own Boost installation
find_package(Boost REQUIRED)

# Link TMC without 
target_link_libraries(target too-many-containers::without_dependencies)
```

### Why depend on Boost.Unordered

[Boost.Unordered]() contains multiple bleeding-edge unordered container implementations whose performance characteristics are well-tested and proven to be consistently among the best options available (see benchmarks [[1]](), [[2]]() and [[3]]()). In particular:

- `boost::unordered_flat_map<K, V>` is a solid contender for being the overall fastest unordered map
- `boost::unordered_node_map<K, V>` is a solid contender for being the overall fastest pointer-stable unordered map
- `boost::unordered_multimap<K, V>` is a solid contender for being the overall fastest pointer-stable unordered multi-map

As such, there is little point in re-inventing the wheel, which is why most `tmc` unordered containers are simply thin wrappers around the `boost::unordered` implementations.

### Why depend on Boost.Container

[Boost.Container]() contains multiple well-tested implementations of standard containers and adaptors, which in many ways use saner defaults than the standard library implementations susceptible to the ABI lockdown, in particular:

- `boost::container::deque<T>` is an excellent implementation of pointer-stable deque, which has similar performance characteristics to `libc++` implementation of `std::deque<T>`. It avoids horribly small block size choice used by `STL` (which was ossified due to the ABI stability) and doesn't perform allocation in default constructor that's present on `libstdc++`. Since version 1.90 it's also the smallest deque available in terms of its `sizeof` (`32` bytes) and has `noexcept` move (which `STL` and `libstdc++` do not provide)
- `boost::container::vector<T>` is for all practical purposes the same as `std::vector<T>`, but without the bitset specialization for `std::vector<bool>` (which in hindsight turned out to be a terrible optimization due to breaking standard container semantics)
- `boost::container::small_vector<T, N>` and `boost::container::static_vector<T, N>` are solid implementations of small-buffer optimization and static capacity vectors
- `boost::container::flat_map<K, V, C>` is a sane battle-tested implementation of a sorted associative wrapper

In summary, using this library as a backend avoids a whole lot of wheel re-invention that would otherwise be required to re-implement all of its containers with no particular benefit in terms of performance.

### Links

- [Comprehensive C++ Hashmap Benchmarks 2022 by Martin Ankerl](https://martin.ankerl.com/2022/08/27/hashmap-bench-01/)
- [An Extensive Benchmark of C and C++ Hash Tables by Jackson Allan](https://jacksonallan.github.io/c_cpp_hash_tables_benchmark)
- [Official Boost.Unordered benchmarks](https://www.boost.org/doc/libs/latest/libs/unordered/doc/html/unordered/benchmarks.html)
- [Inside Boost.Container: Comparing different deque implementations](https://boostedcpp.net/2026/03/30/deque/)

## License

This project is licensed under the MIT License - see the [LICENSE.md](../LICENSE.md) for details.
