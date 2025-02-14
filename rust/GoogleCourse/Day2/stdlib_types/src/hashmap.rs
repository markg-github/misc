use std::collections::HashMap;

pub fn hashmap_main() {
    let mut page_counts = HashMap::new();
    page_counts.insert("Adventures of Huckleberry Finn", 207);
    page_counts.insert("Grimms' Fairy Tales", 751);
    page_counts.insert("Pride and Prejudice", 303);

    if !page_counts.contains_key("Les Misérables") {
        println!(
            "We know about {} books, but not Les Misérables.",
            page_counts.len()
        );
    }

    for book in ["Pride and Prejudice", "Alice's Adventure in Wonderland"] {
        match page_counts.get(book) {
            Some(count) => println!("{book}: {count} pages"),
            None => println!("{book} is unknown."),
        }
    }

    // Use the .entry() method to insert a value if nothing is found.
    for book in ["Pride and Prejudice", "Alice's Adventure in Wonderland"] {
        let page_count: &mut i32 = page_counts.entry(book).or_insert(0);
        *page_count += 1;
    }

    println!("{page_counts:#?}");

    let pc1 = page_counts
    .get("Harry Potter and the Sorcerer's Stone")
    // NOTE: unwrap_or is a method of Option
    .unwrap_or(&336);
    // .unwrap_or(336);
    let pc2 = page_counts
    .entry("The Hunger Games")
    // NOTE: or_insert is a method of an entry in a HashMap
    .or_insert(374);

    println!("{page_counts:#?}");

    let page_counts = HashMap::from([
        ("Harry Potter and the Sorcerer's Stone".to_string(), 336),
        ("The Hunger Games".to_string(), 374),
      ]);

}