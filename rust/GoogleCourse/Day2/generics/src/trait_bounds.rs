fn duplicate<T: Clone>(a: &T) -> (T, T) {
    (a.clone(), a.clone())
}

fn duplicateh<T: Clone+std::hash::Hash>(a: &T) -> (T, T) {
    (a.clone(), a.clone())
}

fn duplicated<T>(a: &T) -> (T, T)
where T: Clone+std::fmt::Display
{
    (a.clone(), a.clone())
}

fn duplicatei<T: Clone+Iterator>(a: &T) -> (T, T) {
    (a.clone(), a.clone())
}

// struct NotCloneable;

pub fn trait_bounds_main() {
    let foo = String::from("foo");
    // let foo = (1,2,3,4);
    let mut pair = duplicate(&foo);

    // let nc: NotCloneable;
    // let ncpair = duplicate(nc);

    println!("{pair:?}");

    // pair = duplicatei(foo);
    // println!("{pair:?}");
    pair = duplicated(&foo);
    println!("{pair:?}");
    pair = duplicateh(&foo);
    println!("{pair:?}");
}