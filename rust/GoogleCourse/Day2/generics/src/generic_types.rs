#[derive(Debug)]
struct Point<T,U> {
    x: T,
    y: U,
}

impl<T,U> Point<T,U> {
    fn coords(&self) -> (&T, &U) {
        (&self.x, &self.y)
    }

    fn set_x(&mut self, x: T) {
        self.x = x;
    }
}

pub fn generic_types_main() {
    let integer = Point { x: 5, y: 10 };
    let float = Point { x: 1.0, y: 4.0 };
    let mixed = Point { x: 5, y: 10.0 };
    println!("{integer:?} and {float:?}");
    println!("{mixed:?}");
    println!("coords: {:?}", integer.coords());
    println!("coords: {:?}", mixed.coords());
}