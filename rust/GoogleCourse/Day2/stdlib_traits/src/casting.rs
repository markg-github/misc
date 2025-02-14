
pub fn main() {
    let value: i64 = 1000;
    println!("as u16: {}", value as u16);
    println!("as i16: {}", value as i16);
    println!("as u8: {}", value as u8);

    // println!("as u8: {}", u8::from(value));
    // println!("as u8: {}", value.into());
    
}

use std::convert::TryFrom;
use std::num::ParseIntError;

pub fn main2() {
    let s = "123";
    // let i: Result<i32, ParseIntError> = i32::try_from(s);

    // match i {
    //     Ok(i) => println!("Integer: {}", i),
    //     Err(e) => println!("Error: {}", e),
    // }
}



