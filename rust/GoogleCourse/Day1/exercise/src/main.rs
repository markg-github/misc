


fn factorial(n: u32) -> u32 {
    let recursive = true;
    // unreachable!();
    if recursive {
        if n < 2 {
            n
        }
        else {
            n * factorial(n-1)
        }
    }
    else {
    let mut product = 1;
    for i in 1..=n {
        product *= dbg!(i);
    }
    product
        
    }
}

fn fizzbuzz(n: u32) -> u32 {
    {
        println!("n: {n}");
      
    }
    todo!();
}

fn collatz(n: u32) -> u32 {
    let mut length = 0;
    let mut current = n;
    loop {
        println!("{current}");
        length += 1;
        if current == 1 {
            break (length)
        }
        else {
            if current % 2 == 1 {
                current = 3 * current + 1
            }
            else {
                current /= 2
            }
        }
    }
}

fn array_main() {
    let mut a: [i8; 10] = [42; 10];
    a[5] = 0;
    // a[10] = 42;
    println!("a: {a:?}");
    println!("a: {}", a[1]);
    // println!("a: {}", a[10]);
    let array = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];
    
    // trick way to get compiler to give type of array ([[i32; 3]; 3]) 
    // let (test1, test2) = array

}

fn print_tuple(tuple: (i8, bool)) {
    let (left, right) = tuple;
    // let (left, middle, right) = tuple;
    let (only) = tuple;
    println!("left: {left}, right: {right}");
}

fn tuple_main() {
    let t: (i8, bool) = (7, true);
    println!("t.0: {}", t.0);
    println!("t.1: {}", t.1);
    // println!("t.1: {}", t[1]);
    print_tuple(t)
}

fn iter_main() {
    let primes = [2, 3, 5, 7, 11, 13, 17, 19, 16, 29, 23, 160];
    for prime in primes {
        for i in 2..prime {
            println!("test {}, {}", prime, i);
            assert_ne!(prime % i, 0);
        }
    }
}

fn main() {
    println!("Edit me, Sofia!");
    // iter_main();
    // todo!("iter only");
    tuple_main();
    todo!("tuple only");
    array_main();
    todo!("todo test");
    let n = 11;
    // println!("{n}! = {}", factorial(n));
    println!("collatz({n}) = {}", collatz(n));
}



