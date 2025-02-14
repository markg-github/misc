fn main() {
    println!("Hello, Day2!");
    matching_main();
}

fn hex_or_die_trying2(maybe_string: Option<String>) -> Result<u32, String> {
    let Some(s) = maybe_string else {
        return Err(String::from("got None"));
    };

    let Some(first_byte_char) = s.chars().next() else {
        return Err(String::from("got empty string"));
    };

    let Some(digit) = first_byte_char.to_digit(16) else {
        return Err(String::from("not a hex digit"));
    };

    return Ok(digit);
}

fn while_let() {
    let mut name = String::from("Comprehensive Rust 🦀");
    loop {
        let temp = name.pop();
        if temp == None {
            break
        }
        println!("{}", temp.unwrap())
    }    
    name = String::from("Comprehensive Rust 🦀 again");

    while let Some(c) = name.pop() {
        println!("character: {c}");
    }
    // (There are more efficient ways to reverse a string!)
}

fn hex_or_die_trying(maybe_string: Option<String>) -> Result<u32, String> {
    if let Some(s) = maybe_string {
        if let Some(first_byte_char) = s.chars().next() {
            if let Some(digit) = first_byte_char.to_digit(16) {
                Ok(digit)
            } else {
                return Err(String::from("not a hex digit"));
            }
        } else {
            return Err(String::from("got empty string"));
        }
    } else {
        return Err(String::from("got None"));
    }
}

fn match_guard1() {
    let number = 4;

    let result = match number {
        0 => "zero",
        n @ 1..=5 => {
            if n % 2 == 0 {
                "even"
            } else {
                "odd"
            }
        },
        _ => "other",
    };

    println!("{}", result); // Output: even
}

fn match_guard2() {
    let x = Some(5);
    let y = 10;

    match x {
        Some(i) if i > y => println!("i ({}) is greater than y ({})", i, y),
        Some(i) => println!("i ({}) is less than or equal to y ({})", i, y),
        None => println!("x is None"),
    }
}

struct Foo {
    x: (u32, u32),
    y: u32,
    z: u32
}

#[rustfmt::skip]
fn structs_destructure() {
    let foo = Foo { x: (0, 2), y: 2, z: 42 };
    const TEST: u32 = 3;
    match foo {
        Foo { x: (1, b), y, .. } => println!("x.0 = 1, b = {b}, y = {y}"),
        Foo { y: TEST, x: i, .. }   => println!("y = 2, x = {i:?}"),
        Foo { y, .. }        => println!("y = {y}, other fields were ignored"),
    }
}


enum MyResult {
    Ok(i32),
    Err(String),
    Test(i32)
}

fn divide_in_two(n: i32) -> MyResult {
    if n % 2 == 0 {
        MyResult::Ok(n / 2)
    } else {
        MyResult::Err(format!("cannot divide {n} into two equal parts"))
    }
}

fn enums_destructure() {
    let n = 111;
    match divide_in_two(n) {
        MyResult::Ok(half) => println!("{n} divided in two is {half}"),
        MyResult::Err(msg) => println!("sorry, an error happened: {msg}"),
        MyResult::Test(_) => println!("Test"),
        _ => println!("default")
    }
}

use std::time::Duration;

fn sleep_for(secs: f32) {
    if let Ok(duration) = Duration::try_from_secs_f32(secs) {
        std::thread::sleep(duration);
        println!("slept for {duration:?}");
    }
    // let myresult = Duration::try_from_secs_f32(secs);
    // if myresult == Ok(duration) {
    //     std::thread::sleep(duration);
    //     println!("slept for {duration:?}");
        
    // }
}

fn let_control_flow() {
    sleep_for(-10.0);
    sleep_for(0.8);
}

#[rustfmt::skip]
fn matching_main() {
    let input = 'x';
    match input {
        'q'                       => println!("Quitting"),
        'a' | 's' | 'w' | 'd'     => println!("Moving around"),
        '0'..='9'                 => println!("Number input"),
        key if key.is_lowercase() => println!("Lowercase: {key}"),
        _                         => println!("Something else"),
    }

    let opt = Some(123);
    match opt {
        outer @ Some(inner) => {
            println!("outer: {outer:?}, inner: {inner}");
        }
        None => {}
    }

    match_guard1();
    match_guard2();

    structs_destructure();
    enums_destructure();

    let_control_flow();


    println!("result: {:?}", hex_or_die_trying2(Some(String::from("foo"))));
    println!("result: {:?}", hex_or_die_trying2(Some(String::from("goo"))));
    println!("result: {:?}", hex_or_die_trying2(Some(String::from(""))));

    while_let()
    
    
}

