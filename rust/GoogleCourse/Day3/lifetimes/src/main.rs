#[derive(Debug)]
struct Point(i32, i32);

// won't compile since lifetime of returned reference is
// ambiguous (compiler can't infer it)
// fn left_most(p1: &Point, p2: &Point) -> &Point {
//     if p1.0 < p2.0 {
//         p1
//     } else {
//         p2
//     }
// }

// Lifetimes are always inferred by the compiler: you cannot assign a lifetime 
// yourself. Explicit lifetime annotations like 'a below create constraints where there is 
// ambiguity; the compiler verifies that there is a valid solution.
fn left_most_w_lifetime<'a>(p1: &'a Point, p2: &'a Point) -> &'a Point {
        if p1.0 < p2.0 {
        p1
    } else {
        p2
    }
}

mod lifetime_elision;
mod lifetimes_datastructs;
mod exercise_protobuf_parsing;
mod testlogging2;

// mod mylogging;
// use mylogging::Logger;

// fn logging_test() {
//     let logger = mylogging::VerbosityFilter { max_verbosity: 3, inner: mylogging::StdoutLogger };
//     logger.log(5, "FYI");
//     logger.log(2, "Uhoh");

// }

fn main() {

    // logging_test();

    let p1: Point = Point(10, 10);
    let p2: Point = Point(20, 20);
    // won't compile - What is the lifetime of p3?
    // let p3 = left_most(&p1, &p2);
    let p3 = left_most_w_lifetime(&p1, &p2);
    println!("p3: {p3:?}");

    lifetime_elision::main();
    lifetimes_datastructs::main();
    testlogging2::logging_main();
    exercise_protobuf_parsing::main();
}

