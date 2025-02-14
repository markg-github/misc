
#[derive(Debug)]
enum HighlightColor {
    Pink,
    Yellow,
}

// If a data type stores borrowed data, it must be annotated with a lifetime.
// the annotation on Highlight enforces that the data 
// underlying the contained &str lives at least as long as any instance of 
// Highlight that uses that data. A struct cannot live longer than the data 
// it references.
#[derive(Debug)]
struct Highlight<'document> {
    slice: &'document str,
    color: HighlightColor,
}

pub fn main() {
    let doc = String::from("The quick brown fox jumps over the lazy dog.");
    let noun = Highlight { slice: &doc[16..19], color: HighlightColor::Yellow };
    let verb = Highlight { slice: &doc[20..25], color: HighlightColor::Pink };
    // compile error 
    // drop(doc);
    println!("{noun:?}");
    println!("{verb:?}");
    // even if you only have these statements, drop will cause compile error
    println!("{:?}", noun.color);
    println!("{:?}", verb.color);
}