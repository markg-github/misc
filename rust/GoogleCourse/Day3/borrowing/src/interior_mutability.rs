
use std::cell::Cell;

pub fn cell_main() {
    // Note that `cell` is NOT declared as mutable.
    let cell = Cell::new(5);
    // let mut cell = Cell::new(5);
    let a = &cell;
    // let mut b = &mut cell;
    // println!("{}", b.get());

    // i think the idea is that cell is immutable but it
    // has a set method, which works even if you don't
    // declare cell as mutable
    cell.set(123);
    println!("{}", cell.get());
    println!("{}", a.get());
    // println!("{}", b.get());
}

use std::cell::RefCell;

pub fn refcell_main() {
    // Note that `cell` is NOT declared as mutable.
    let cell = RefCell::new(5);

    {
        let mut cell_ref = cell.borrow_mut();
        *cell_ref = 123;

        // This triggers an error at RUNTIME,
        // with either borrow() or borrow_mut().
        // let other = cell.borrow();
        // println!("{}", *other);
        // let other2 = cell.borrow_mut();
        // println!("{}", *other2);

        // won't work as expected since another borrow
        println!("{cell:?}");
    }

    println!("{cell:?}");
}