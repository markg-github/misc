
struct Point(i32, i32);

pub fn main() {
    {
        let p = Point(3, 4);
        println!("x: {}", p.0);
    }
    // p dropped and its memory freed above
    // println!("y: {}", p.1);
}