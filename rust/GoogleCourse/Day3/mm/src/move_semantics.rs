
pub fn main() {
    let s1: String = String::from("Hello!");
    // transfer ownership of s1 to s2, s1 is no longer valid
    let s2: String = s1;
    println!("s2: {s2}");
    // println!("s1: {s1}");
}


fn say_hello(name: String) {
    println!("Hello {name}")
}

fn say_hello_ref(name: & String) {
    println!("Hello {name}")
}

pub fn main2() {
    let name = String::from("Alice");
    say_hello_ref(&name);
    say_hello(name.clone());
    // transfer ownership of name to say_hello
    say_hello(name);
    // say_hello(name);
}