use std::ops::Deref;

pub fn string_main() {
    let mut s1 = String::new();
    s1.push_str("Hello");
    println!("s1: len = {}, capacity = {}", s1.len(), s1.capacity());

    let mut s2 = String::with_capacity(s1.len() + 1);
    s2.push_str(&s1);
    s2.push('!');
    println!("s2: len = {}, capacity = {}", s2.len(), s2.capacity());

    let s3 = String::from("🇨🇭");
    println!("s3: len = {}, number of chars = {}", s3.len(), s3.chars().count());

    // let s4 = s1.deref();
    // println!("s4: len = {}, capacity = {}", s4.len(), s4.capacity());
    // let s5 =&*s1;
    // println!("s5: len = {}, capacity = {}", s5.len(), s5.capacity());

    let s4 = s1.deref();
    println!("s4: len = {}", s4.len());
    let s5 =&*s1;
    println!("s5: len = {}", s5.len());

    let char1 = s1.chars().nth(3).unwrap();
    println!("char1: {char1}");
    let sub1 = &s1[1..4];
    println!("sub1: {sub1}");
    s1 = s1[1..4].to_string();
    println!("s1: {s1}");
}