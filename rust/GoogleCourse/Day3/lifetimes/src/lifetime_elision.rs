
#[derive(Debug)]
struct Point(i32, i32);

fn cab_distance(p1: &Point, p2: &Point) -> i32 {
    (p1.0 - p2.0).abs() + (p1.1 - p2.1).abs()
}

// commented out line won't compile - interesting error, on the return 
// compiler knows "return lifetime" needs to match points input, 'a, not query
// this IS (part of) the point of this lesson
// for related rules, see https://doc.rust-lang.org/nomicon/lifetime-elision.html
// fn nearest<'a, 'q>(points: &'a [Point], query: &'q Point) -> Option<&'q Point> {
fn nearest<'a, 'q>(points: &'a [Point], query: &'q Point) -> Option<&'a Point> {
    let mut nearest = None;
    for p in points {
        // note that the following isn't really the emphasis of the lifetime elision lesson here
        // 
        // let is important here
        // it's not like C if (x=y)
        // it's if nearest is already Some, then execute the "true clause"
        // making nearest_dist the 2nd element of the nearest 2-tuple in the process
        // if nearest is still None, then execute the "false clause"
        // where nearest goes from None to Some
        if let Some((_, nearest_dist)) = nearest {
            let dist = cab_distance(p, query);
            if dist < nearest_dist {
                nearest = Some((p, dist));
            }
        } else {
            nearest = Some((p, cab_distance(p, query)));
        };
    }
    // same disclaimer as above, the following isn't really the emphasis of the 
    // lifetime elision lesson here
    // 
    // The map method takes a closure (an anonymous function) as an argument. 
    // This closure is applied to the value inside the Option if it is Some, 
    // and it returns a new Option with the transformed value. If the Option is None, 
    // the map method simply returns None.
    // The closure |(p, _)| p takes a tuple (p, _) as its argument. The underscore _ is 
    // used to ignore the second element of the tuple, meaning it is not needed for the 
    // transformation. The closure then returns p, the first element of the tuple. As a 
    // result, the map method transforms an Option<(p, _)> into an Option<p>, effectively 
    // extracting the first element of the tuple if it exists.
    nearest.map(|(p, _)| p)
}

pub fn main() {
    let points = &[Point(1, 0), Point(1, 0), Point(-1, 0), Point(0, -1)];
    println!("{:?}", nearest(points, &Point(0, 2)));
}

