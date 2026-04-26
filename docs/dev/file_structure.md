# File structure

## Granular headers

The project should use a granular file structure with a clear naming & scope of every `#include`.

E.g. below is an initial draft of "how it should look":

```
tmc/
	concepts/
		is_reference.hpp
		is_rvalue_reference.hpp
		is_lvalue_reference.hpp
		is_const_reference.hpp
		is_cv_unqualified.hpp
		is_array.hpp
		is_enum.hpp
		is_arithmetic.hpp
		is_bool_testable.hpp
		is_aggregate.hpp
		has_find_for.hpp
		has_contains_for.hpp
		has_count_for.hpp
		has_at_for.hpp
		has_bracket_operator_for.hpp
		has_equal_range_for.hpp
		has_emplace_for.hpp
		has_try_emplace_for.hpp
		has_insert_for.hpp
		has_push_back_for.hpp
		has_push_front_for.hpp
		has_push_for.hpp
		has_pop_back.hpp
		has_pop_front.hpp
		has_pop.hpp
		has_erase_for.hpp
		has_resize.hpp
		has_reserve.hpp
		has_dereference_operator.hpp
		has_is_transparent.hpp
		has_is_avalanching.hpp
	requirements/
		is_trivially_default_constructible.hpp
		is_trivially_constructible.hpp
		is_trivially_copyable.hpp
		is_copy_constructible.hpp
		is_move_constructible.hpp
		is_assignable.hpp
		is_copy_assignable.hpp
		is_move_assignable.hpp
		is_nothrow_default_constructible.hpp
		is_nothrow_constructible.hpp
		is_nothrow_copy_constructible.hpp
		is_nothrow_move_constructible.hpp
		is_nothrow_assignable.hpp
		is_nothrow_copy_assignable.hpp
		is_nothrow_move_assignable.hpp
		satisfies_object_requirement.hpp
		satisfies_allocator_requirement.hpp
		satisfies_allocator_requirement_for.hpp
	functional/
		hash.h
		less.h
		less_equal.h
		greater.h
		greater_equal.h
		equal.h
		not_equal.h
		less_than.h
		less_greater_than.h
		greater_than.h
		greater_equal_then.h
		equal_to.h
		not_equal_to.h
		singular_closure.h
		variadic_closure.h
	memory/
		allocator.h
		polymorphic_allocator.h
		allocate.h
		deallocate.h
		construct_at_a.hpp
		destroy_at_a.hpp
	containers/
		dynamic_value.hpp
		dynamic_array.hpp
	concurrency/
		parallel_for.hpp
		parallel_reduce.hpp
		async_parallel_task.hpp
		async_parallel_for.hpp
		async_parallel_reduce.hpp
		detached_parallel_task.hpp
		detached_parallel_for.hpp
		detached_parallel_reduce.hpp
		parallel_invoke.hpp
		thread_pool.hpp
		locked_ref.hpp
		hardware_concurrency.hpp
	math/
		approx.hpp
		isinf.hpp
		isnan.hpp
		isfinite.hpp
		abs.hpp
		distance.hpp
	utility/
		scope_guard.hpp
	macros/
		assert.hpp
		version.hpp
		cpp_version.hpp
		no_discard.hpp
		no_unique_address.hpp
		no_inline.hpp
		always_inline.hpp
		try_catch.hpp
```	

## Public headers

For public usage we can also provide aggregated headers:

```
tmc/
	concepts.hpp
	functional.hpp
	memory.hpp
	containers.hpp
	concurrency.hpp
	math.h
	utility.h
```