mod ownership;
mod move_semantics;
mod copy_types;
mod drop_trait;
mod exercise_builder;


fn main() {
    let mut s1 = String::from("Hello");
    s1.push(' ');
    println!("{}", s1);
    println!("{s1}");
    s1.push_str("world");
    println!("{}", s1);
    println!("{s1}");
    // DON'T DO THIS AT HOME! For educational purposes only.
    // String provides no guarantees about its layout, so this could lead to
    // undefined behavior.
    unsafe {
        let (capacity, ptr, len): (usize, usize, usize) = std::mem::transmute(s1);
        println!("capacity = {capacity}, ptr = {ptr:#x}, len = {len}");
    }

    println!("ownership");
    ownership::main();
    
    println!("move_semantics");
    move_semantics::main();
    move_semantics::main2();

    println!("copy_types");
    copy_types::main();
    copy_types::main2();

    println!("drop_trait");
    drop_trait::main();

    println!("exercise_builder");
    exercise_builder::main();
}