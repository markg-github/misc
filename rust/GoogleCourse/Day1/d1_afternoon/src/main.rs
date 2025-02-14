

fn transpose(matrix:[[i32;3];3]) -> [[i32;3];3]
{
    let mut output = matrix;
    for r in 0..3 {
        for c in 0..3 {
            if r == c {
                continue
            }
            else {
                output[r][c] = matrix[c][r];
                // output[c][r] = matrix[r][c]
            }
        }
    }
    output
}

fn transpose3(mut matrix:[[i32;3];3]) -> [[i32;3];3]
{
    // let mut output = matrix;
    for r in 0..3 {
        for c in r..3 {
            if r == c {
                continue
            }
            else {
                // top half
                let temp = matrix[r][c];
                // println!("temp = {temp}");
                matrix[r][c] = matrix[c][r];
                // println!("temp = {temp}");
                matrix[c][r] = temp;
                // lower half
                // temp = matrix[2-r][2-c];
                // matrix[2-r][2-c] = matrix[2-c][2-r];
                // matrix[2-c][2-r] = temp
            }
        }
    }
    // println!("{matrix:#?}");

    matrix
}

fn transpose4(mut matrix:[[i32;4];4]) -> [[i32;4];4]
{
    let size = 4;
    let mut output = [[0;4];4];
    for r in 0..size {
        for c in 0..size {
                output[r][c] = matrix[c][r];
                // output[c][r] = matrix[r][c]
        }
    }
    println!("copy: {output:#?}");

    for r in 0..size {
        for c in r..size {
            if r == c {
                continue
            }
            else {
                // top half
                let temp = matrix[r][c];
                // println!("temp = {temp}");
                matrix[r][c] = matrix[c][r];
                // println!("temp = {temp}");
                matrix[c][r] = temp;
                // lower half
                // temp = matrix[2-r][2-c];
                // matrix[2-r][2-c] = matrix[2-c][2-r];
                // matrix[2-c][2-r] = temp
            }
        }
    }
    println!("in place: {matrix:#?}");

    matrix
}

fn slice_main() {
    let mut a: [i32; 6] = [10, 20, 30, 40, 50, 60];
    println!("a: {a:?}");

    let mut s: &[i32] = &a[2..4];

    println!("s: {s:?}");

    s = &a[..];

    println!("s: {s:?}");
}

fn string_main() {
    let s1: &str = "World";
    let mys1 = "World";
    println!("s1: {s1}");

    let mut s2: String = String::from("Hello ");
    // let mut mys2: String = "Hello ";
    println!("s2: {s2}");
    s2.push_str(s1);
    println!("s2: {s2}");

    let s3: &str = &s2[s2.len() - s1.len()..];
    println!("s3: {s3}");

    let mut mynewstring: String = String::new();
    let mut mynewstring2: String = format!("{s2}");
    mynewstring.push('0');
    let mynewstr: &str = &mynewstring2;
    mynewstring.push_str(mynewstr);

    println!("mynewstring: {mynewstring}");
    println!("mynewstring2: {mynewstring2}");

    println!("s1");
    for c in s1.chars() {
        print!("{c} ");
    }
    println!("");
    println!("mys1");
    println!("");
    for c in mys1.chars() {
        print!("{c} ");
    }
    println!("");
    println!("s2");
    println!("");
    for c in s2.chars() {
        print!("{} ", c);
    }
    println!("");
    println!("s3");
    println!("");
    for c in s3.chars() {
        print!("{} ", c);
    }
    println!("");
    println!("mynewstring");
    println!("");
    for c in mynewstring.chars() {
        print!("{} ", c);
    }
    println!("");
    println!("mynewstring2");
    println!("");
    for c in mynewstring2.chars() {
        print!("{} ", c);
    }
    println!("");
    println!("mynewstr");
    println!("");
    for c in mynewstr.chars() {
        print!("{} ", c);
    }
    println!("")
}

fn string_literals_main() {
    println!("{:?}", b"abc");
    println!("{:?}", "abc");
    println!("{:?}", &[97, 98, 99]);
    println!("{:?}", [97, 98, 99]);

    println!("{:#?}", b"abc");
    println!("{:#?}", "abc");
    println!("{:#?}", &[97, 98, 99]);
    println!("{:#?}", [97, 98, 99]);
}

fn string_raw_main() {
    // the number of # characters at the beginning determines how many consecutive # characters 
    // you can have after a double quote in the string
    let nested_string1 = r####"This is a raw string with "### a nested raw"####;
    println!("1: {}", nested_string1);
    let nested_string2 = format!(r#"This is a raw string {nested_string1} with a nested raw string: r#"Hello, "world!""#);
    println!("2: {}", nested_string2);
    // let nested_string = r#"This is a raw string with a nested raw string: r#"Hello, world!"#"#;
    // println!("{}", nested_string);
    let nested_string3 = format!(r#"This is a raw {nested_string2} string with a nested raw string: r"Hello, world!""#);
    println!("3: {}", nested_string3);
    let nested_string4 = format!(r#"This is a raw string with a nested {nested_string3} raw string: r"Hello, r"penguin" world!""#);
    println!("4: {}", nested_string4);
    let nested_string5 = format!(r"This is a {nested_string4} raw string with a nested raw string");
    println!("5: {}", nested_string5);
    
    println!(r#"<a href=""link.html""">link</a>"#);
    println!("<a href=\"link.html\">link</a>");
    println!(r"<a href=link.html>link</a>");
}

fn main() {
    println!("Hello, world!");
    string_main();
    string_literals_main();
    string_raw_main();
    todo!("string only");
    slice_main();
    todo!("slice only");
    let array = [[1, 2, 3, 4], [5, 6, 7,8], [9,10,11,12], [13,14,15,16]];
    println!("{array:#?}");
    let tarray = transpose4(array);
    // println!("{array:#?}");
    // println!("{tarray:#?}")

}
