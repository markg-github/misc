use std::cmp::Ordering;

fn min<T: Ord>(a: T, b: T) -> T {
    min_solution(a,b)
}

// TODO: implement the `min` function used in `main`.
fn min_answer<T: Ord>(a: T, b: T) -> T {
    if a < b {
        a
    }
    else {
        b
    }
}

fn min_solution<T: Ord>(l: T, r: T) -> T {
    match l.cmp(&r) {
        Ordering::Less | Ordering::Equal => l,
        Ordering::Greater => r,
    }
}


pub fn min_main() {
    assert_eq!(min(0, 10), 0);
    assert_eq!(min(500, 123), 123);

    assert_eq!(min('a', 'z'), 'a');
    assert_eq!(min('7', '1'), '1');

    assert_eq!(min("hello", "goodbye"), "goodbye");
    assert_eq!(min("bat", "armadillo"), "armadillo");
}

