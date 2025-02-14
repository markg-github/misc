
mod result;
mod string;
mod vec;
mod hashmap;
mod counter_exercise;

fn main() {
    let name = "Löwe 老虎 Léopard Gepardi";
    let mut position: Option<usize> = name.find('é');
    println!("find returned {position:?}");
    assert_eq!(position.unwrap(), 14);
    position = name.find('Z');
    println!("find returned {position:?}");
    // assert_eq!(position.expect("Charafafafafcter not found"), 0);

    result::result_main();
    string::string_main();
    vec::vec_main();
    hashmap::hashmap_main();
    counter_exercise::counter_main();
}