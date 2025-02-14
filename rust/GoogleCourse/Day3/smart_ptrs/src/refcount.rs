
use std::rc::Rc;

pub fn main() {
    let a = Rc::new(10);
    // compile error
    // let b = Rc::clone(a);
    let mut b = Rc::clone(&a);

    // let c = a.clone();


    println!("a: {a}");
    println!("b: {b}");

    let c = Rc::make_mut(&mut b);
    println!("c: {c}");

    println!("rc b: {}", Rc::strong_count(&b));

    println!("rc a: {}", Rc::strong_count(&a));
}
