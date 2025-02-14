struct Person {
    name: String,
    age: u8,
}

fn describe(person: &Person) {
    println!("{} is {} years old", person.name, person.age);
}

fn describe2(person: Person) {
    println!("{} is {} years old", person.name, person.age);
}

// struct MyPerson {
//     name: &str,
//     age: u8,
// }

// fn my_describe(person: &MyPerson) {
//     println!("{} is {} years old", person.name, person.age);
// }

struct Point(i32, i32);

fn tuple_struct_main() {
    let p = Point(17, 23);
    println!("({}, {})", p.0, p.1);
    let force = compute_thruster_force();
    let mut n = Newtons(0.);
    n.0 = force.0;
    // set_thruster_force(force);
    set_thruster_force(n);
}

struct PoundsOfForce(f64);
struct Newtons(f64);

fn compute_thruster_force() -> PoundsOfForce {
    // todo!("Ask a rocket scientist at NASA")
    PoundsOfForce(0.)
}

fn set_thruster_force(force: Newtons) {
    // ...
}

#[derive(Debug)]
enum Direction {
    Left,
    Right,
}

#[derive(Debug)]
enum PlayerMove {
    Pass,                        // Simple variant
    Run(Direction),              // Tuple variant
    Teleport { x: u32, y: u32 }, // Struct variant
}

fn enums_main() {
    let player_move: PlayerMove = PlayerMove::Run(Direction::Left);
    println!("On this turn: {player_move:?}");
}

const DIGEST_SIZE: usize = 3;
// const ZERO: Option<u8> = Some(42);
// const ZERO: Option<u8> = 42;
const ZERO: Option<u8> = Some(0);

fn compute_digest(text: &str) -> [u8; DIGEST_SIZE] {
    let mut digest = [ZERO.unwrap_or(0); DIGEST_SIZE];
    println!("digest: {digest:?}");

    for (idx, &b) in text.as_bytes().iter().enumerate() {
        digest[idx % DIGEST_SIZE] = digest[idx % DIGEST_SIZE].wrapping_add(b);
        println!("digest: {digest:?}");

    }
    digest
}

fn const_main() {
    let digest = compute_digest("Hello");
    println!("digest: {digest:?}");
}

static BANNER: &str = "Welcome to RustOS 3.14";

fn static_main() {
    println!("{BANNER}");
}

enum CarryableConcreteItem {
    Left,
    Right,
}

type Item = CarryableConcreteItem;

// Aliases are more useful with long, complex types:
use std::cell::RefCell;
use std::sync::{Arc, RwLock};
type PlayerInventory = RwLock<Vec<Arc<RefCell<Item>>>>;


fn main() {
    static_main();
    todo!("static only");

    const_main();
    todo!("const only");

    enums_main();
    todo!("enums only");

    tuple_struct_main();
    todo!("tuple struct only");

    let mut peter = Person { name: String::from("Peter"), age: 27 };
    // let mut peter = Person { name: "PETER", age: 27 };
    describe(&peter);

    peter.age = 28;
    describe(&peter);

    let name = String::from("Avery");
    let age = 39;
    let avery = Person { name, age };
    describe(&avery);

    let jackie = Person { name: String::from("Jackie"), ..avery };
    describe(&jackie);

    let avery2 = Person { ..avery };
    describe(&avery2);
    describe2(avery2);

}
