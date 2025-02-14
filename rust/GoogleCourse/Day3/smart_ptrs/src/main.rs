
#[derive(Debug)]
enum List<T> {
    /// A non-empty list: first element and the rest of the list.
    Element(T, Box<List<T>>),
    /// An empty list.
    Nil,
}

enum List2<'a, T> {
    /// A non-empty list: first element and the rest of the list.
    // Element(T, Box<List<T>>),
    Element(T, &'a List2<'a, T>),
    /// An empty list.
    Nil,
}

impl<T> List<T> {
    fn new() -> Self {
        List::Nil
    }

    fn prepend(self, elem: T) -> List<T> {
        List::Element(elem, Box::new(self))
    }
}

fn main2() {
    let mut list: List<i32> =
        List::Element(1, Box::new(List::Element(2, Box::new(List::Nil))));
    println!("{list:?}");
    list = list.prepend(42);
    println!("{list:?}");
}

mod refcount;
mod owned_trait_objects;
mod exercise_binary_tree;

fn main() {
    let five = Box::new(5);
    println!("five: {}", *five);
    main2();
    
    println!("refcount");
    refcount::main();
    
    println!("owned trait objects");
    owned_trait_objects::main();
    
    println!("binary tree");
    exercise_binary_tree::main();
}

