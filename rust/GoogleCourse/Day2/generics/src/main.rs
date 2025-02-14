/// Pick `even` or `odd` depending on the value of `n`.
fn pick<T>(n: i32, even: T, odd: T) -> T {
    // if n == 0 {
    //     even + odd
    // }
    // else 
    if n % 2 == 0 {
        even
    } 
    else {
        odd
    }
}

#[derive(Debug)]
struct Foo {
    val: u16,
}

mod generic_types;
mod generic_traits;
mod trait_bounds;
mod impl_trait;
mod dyn_trait;
mod min_exercise;

fn main() {
    println!("picked a number: {:?}", pick(97, 222, 333));
    println!("picked a string: {:?}", pick(28, "dog", "cat"));
    println!("picked a struct: {:?}", pick(123, Foo { val: 7 }, Foo { val: 456 }));

    generic_types::generic_types_main();
    generic_traits::generic_traits_main();
    trait_bounds::trait_bounds_main();
    impl_trait::impl_trait_main();
    dyn_trait::dyn_trait_main();
    min_exercise::min_main();
    
}