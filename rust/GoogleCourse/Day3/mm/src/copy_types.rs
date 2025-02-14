
pub fn main() {
    let x = 42;
    let y = x;
    println!("x: {x}"); // would not be accessible if not Copy
    println!("y: {y}");
}

#[derive(Copy, Clone, Debug)]
// struct PointCC(i32, i32, String);
struct PointCC(i32, i32);

// Copy needs Clone
// #[derive(Copy, Debug)]
// struct PointCo(i32, i32);

#[derive(Clone, Debug)]
struct PointCl(i32, i32, String);

#[derive(Debug)]
struct Point(i32, i32, String);

fn testref(tinput: &u8) {
    let q1 = tinput;
    println!("q1: {q1}");
    println!("tinput: {tinput}")
}

fn testmref(tinput: &mut u8) {
    let q2 = tinput;
    println!("q2: {q2}");
    // println!("tinput: {tinput}")
}

pub fn main2() {
    {
        // let p1 = PointCC(3, 4, String::from("hello"));
        let p1 = PointCC(3, 4 );
        let p2 = p1;
        println!("PointCC");
        println!("p1: {p1:?}");
        println!("p2: {p2:?}");

        let p3: u8 = 42;
        let mut p4: u8 = 142;
        testref(&p3);
        testref(&p3);
        testmref(&mut p4);
        testmref(&mut p4);

    }

    {
        let p1 = Point(30, 40, String::from("hello"));
        println!("Point");
        println!("p1: {p1:?}");
        let p2 = p1;
        // println!("p1: {p1:?}");
        println!("p2: {p2:?}");
    

    }

    {
        // let p1 = PointCo(30, 40);
        // println!("PointCo");
        // // let p2 = p1.clone();
        // println!("p1: {p1:?}");
        // let p2 = p1;
        // // println!("p1: {p1:?}");
        // println!("p2: {p2:?}");
    

    }

    {
        let p1 = PointCl(30, 40, String::from("hello"));
        println!("PointCl");
        let p2 = p1.clone();
        println!("p1: {p1:?}");
        let p2 = p1;
        // println!("p1: {p1:?}");
        println!("p2: {p2:?}");
    

    }

}