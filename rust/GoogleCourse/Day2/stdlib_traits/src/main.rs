
#[derive(Debug)]
struct Key {
    id: u32,
    metadata: Option<String>,
}
impl PartialEq for Key {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}


use std::cmp::Ordering;
#[derive(Eq, PartialEq)]
struct Citation {
    author: String,
    year: u32,
}
impl PartialOrd for Citation {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        match self.author.partial_cmp(&other.author) {
            Some(Ordering::Equal) => self.year.partial_cmp(&other.year),
            author_ord => author_ord,
        }
    }
}

mod operators;
mod frominto;
mod casting;
mod readwrite;
mod defaults;
mod closures;
mod rot13;

fn main() {
    println!("Hello, world!");
    let k1 = Key{id: 3, metadata: Some(String::from("o1string"))};
    let k2 = Key{id: 3, metadata: Some(String::from("o2string"))};
    let k3 = Key{id: 4, metadata: Some(String::from("o1string"))};
    let k4 = Key{id: 5, metadata: Some(String::from("o4string"))};
    let k5 = Key{id: 3, metadata: Some(String::from("o5string"))};

    assert_eq!(k1,k2);
    assert_ne!(k1,k3);
    assert_ne!(k1,k4);
    assert_eq!(k1,k5);

    assert_ne!(k2,k3);
    assert_ne!(k2,k4);
    assert_eq!(k2,k5);

    assert_ne!(k3,k4);
    assert_ne!(k3,k5);

    assert_ne!(k4,k5);

    let c1 = Citation{author: String::from("Hemingway"), year: 1960};
    let c2 = Citation{author: String::from("Ellis"), year: 1980};
    // suppress unused warnings by prepending with '_'
    let _c3 = Citation{author: String::from("Shakeseare"), year: 1800};
    let _c4 = Citation{author: String::from("Faulkner"), year: 1930};
    let _c5 = Citation{author: String::from("Roth"), year: 1990};
    let _c6 = Citation{author: String::from("Delillo"), year: 2010};
    let _c7 = Citation{author: String::from("Vance"), year: 2010};
    let _c8 = Citation{author: String::from("Cervantes"), year: 1960};
    let c9 = Citation{author: String::from("Wallace"), year: 1980};
    let c10 = Citation{author: String::from("Wallace"), year: 1990};
    let _c11 = Citation{author: String::from("Wallace"), year: 2000};

    println!("{}", c1 < c2);

    println!("{}", c9 < c10);
    println!("{}", c9 > c10);

    println!("{}", c9 <= c10);
    println!("{}", c9 >= c10);

    operators::operators_main();

    print_stringa(c10);
    // print_stringb(c11);
    // print_stringc(c11);

    frominto::main1();
    frominto::main2();

    casting::main();
    casting::main2();

    readwrite::main1();
    readwrite::main2();

    defaults::main();

    closures::main();
    closures::main2();

    rot13::main();

}

impl Into<String> for Citation {
    fn into(self) -> String {
        self.year.to_string()
    }
}

// impl From<Citation> for String {
//     fn from(c: Citation) -> Self {
//         c.year.to_string()
//     }
// }

fn print_stringa<T: Into<String>>(c: T) {
    println!("{}", c.into());
}

// fn print_stringb<T: From<Citation>>(c: T) {
//     println!("{}", c.into());
// }

// fn print_stringc(c: Citation) {
//     println!("{}", String::from(c));
// }


