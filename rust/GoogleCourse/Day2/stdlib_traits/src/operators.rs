#[derive(Debug, Copy, Clone)]
struct Point {
    x: i32,
    y: i32,
}

impl std::ops::Add for Point {
    type Output = Self;

    fn add(self, other: Self) -> Self {
        Self { x: self.x + other.x, y: self.y + other.y }
    }
}

impl std::ops::Add<Point> for &Point {
    type Output = Point;

    fn add(self, other: Point) -> Self::Output {
        Point { x: 10*self.x + 20*other.x, y: 30*self.y + 40*other.y }
    }
}

impl std::ops::Add for &Point {
    type Output = Point;

    fn add(self, other: Self) -> Self::Output {
        Point { x: 10*self.x + 20*other.x, y: 30*self.y + 40*other.y }
    }
}

impl std::ops::Add<&Point> for Point {
    type Output = Point;

    fn add(self, other: &Point) -> Self::Output {
        Point { x: 10*self.x + 20*other.x, y: 30*self.y + 40*other.y }
    }
}

impl std::ops::Add<(i32,i32)> for &Point {
    type Output = Point;

    fn add(self, other: (i32,i32)) -> Self::Output {
        Point { x: 100*self.x + 200*other.0, y: 300*self.y + 400*other.1 }
    }
}

pub fn operators_main() {
    let p1 = Point { x: 10, y: 20 };
    let p2 = Point { x: 100, y: 200 };
    let p3 = (1,2);
    println!("{p1:?} + {p2:?} = {:?}", p1 + p2);
    println!("{p1:?} + {p2:?} = {:?}", &p1 + p2);
    println!("{p1:?} + {p2:?} = {:?}", p1 + &p2);
    println!("{p1:?} + {p2:?} = {:?}", &p1 + &p2);
    // println!("{p1:?} + {p2:?} = {:?}", &p1 + &p2);
    println!("{p1:?} + {p3:?} = {:?}", &p1 + p3);
    // println!("{p1:?} + {p2:?} = {:?}", &p1 + &p2);

    // println!("5 {5}, !5 {!5}");
    println!("5 {}, !5 {}", 5, !5);
}