#[derive(Debug)]
struct Point(i32, i32);

fn add(p1: &Point, p2: &Point) -> Point {
    Point(p1.0 + p2.0, p1.1 + p2.1)
}

mod interior_mutability;

fn main() {
    let p1 = Point(3, 4);
    let p2 = Point(10, 20);
    // The caller, main, retains ownership of the inputs.
    let p3 = add(&p1, &p2);
    println!("{p1:?} + {p2:?} = {p3:?}");

    println!("ADDRESSES");
    main2();
    checking();
    checking2();
    borrow_errors();
    borrow_errors2();

    interior_mutability::cell_main();
    interior_mutability::refcell_main()

    
}

// #[inline(never)]
fn add2(p1: &Point, p2: &Point) -> Point {
    let p = Point(p1.0 + p2.0, p1.1 + p2.1);
    println!("&p.0: {:p}", &p.0);
    p
}

pub fn main2() {
    let p1 = Point(3, 4);
    let p2 = Point(10, 20);
    // if you do a release build, the following
    // won't do a copy, add2 will be inlined
    // unless you use inline(never) on add2 above
    let p3 = add2(&p1, &p2);
    println!("&p3.0: {:p}", &p3.0);
    println!("{p1:?} + {p2:?} = {p3:?}");
}


fn checking() {
    let x_ref = {
        let x = 10;
        // a reference cannot outlive the value it borrows
        // &x
    };
    // println!("x: {x_ref}");
}

fn checking2() {
    // You can have one or more shared references to the value, or
    // You can have exactly one exclusive reference to the value.
    let mut a: i32 = 10;
    // error a itself has to be mutable to take mutable reference
    // let a: i32 = 10;
    // shared (&, not &mut)
    let b: &i32 = &a;

    // no compile error since b doesn't need
    // to live after the println!
    println!("b: {b}");
    {
        // exclusive (&mut)
        let c: &mut i32 = &mut a;
        *c = 20;
    }

    println!("a: {a}");
    // compile error since b and c lifetimes overlap
    // println!("b: {b}");
}

fn borrow_errors() {
    let mut vec = vec![1, 2, 3, 4, 5];
    let elem = &vec[2];
    // this causes error since basically exclusive while
    // we have shared elem
    // vec.push(6);
    println!("{elem}");
}

fn borrow_errors2() {
    let mut vec = vec![1, 2, 3, 4, 5];
    // similar to above: elem shared, vec exclusive -> error
    for elem in &vec {
        // vec.push(elem * 2);
        // vec.push(2);
        println!("{elem}")
    }
}