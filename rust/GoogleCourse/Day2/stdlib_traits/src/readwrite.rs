

use std::io::{BufRead, BufReader, Read, Result};

fn count_lines<R: Read>(reader: R) -> usize {
    let buf_reader = BufReader::new(reader);
    buf_reader.lines().count()
}

pub fn main1() -> Result<()> {
    let slice: &[u8] = b"foo\nbar\nbaz\n";
    println!("lines in slice: {}", count_lines(slice));

    // You have to unwrap the results of current_exe and open while
    // still allowing for the possibility that they return error. The ?s
    // are the way to do this. The uncommented code below, with the match
    // statements shows how much
    // more verbose one alternative way of doing it is.

    // let file = std::fs::File::open(std::env::current_exe()?)?;
    let path = match std::env::current_exe() {
        Ok(p) => p,
        Err(e) => return Err(e.into())
    };
    let file = match std::fs::File::open(path) {
        Ok(f) => f,
        Err(e) => return Err(e.into())
    };
    println!("lines in file: {}", count_lines(file));
    Ok(())
}

// use std::io::{Result, Write};

fn log<W: std::io::Write>(writer: &mut W, msg: &str) -> Result<()> {
    // writer.write_all(msg.as_bytes())?;
    writer.write_all(msg.as_bytes());
    writer.write_all("\n".as_bytes())
}

pub fn main2() -> Result<()> {
    let mut buffer = Vec::new();
    // log(&mut buffer, "Hello")?;
    // log(&mut buffer, "World")?;
    log(&mut buffer, "Hello");
    log(&mut buffer, "World");
    // println!("Logged: {buffer:?}");
    println!("Logged: {buffer:?}");
    Ok(())
}

