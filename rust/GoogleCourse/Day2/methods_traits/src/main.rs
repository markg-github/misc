#[derive(Debug)]
struct Race {
    name: String,
    laps: Vec<i32>,
}

impl Race {
    // No receiver, a static method
    fn new(name: &str) -> Self {
        Self { name: String::from(name), laps: Vec::new() }
    }

    // Exclusive borrowed read-write access to self
    fn add_lap(self: &mut Race, lap: i32) {
        self.laps.push(lap);
    }

    // Shared and read-only borrowed access to self
    fn print_laps(self: &Self) {
        println!("Recorded {} laps for {}:", self.laps.len(), self.name);
        for (idx, lap) in self.laps.iter().enumerate() {
            println!("Lap {idx}: {lap} sec");
        }
    }

    // Exclusive ownership of self (covered later)
    fn finish(self: Race) {
        let total: i32 = self.laps.iter().sum();
        println!("Race {} is finished, total lap time: {}", self.name, total);
    }
}

mod traits;
mod supertraits;
mod assoc_types;
mod deriving;
mod logger_exercise;

fn main() {
    let mut race = Race::new("Monaco Grand Prix");
    // let mut race = Race { name: String::from("Monaco Grand Prix") };
    race.add_lap(70);
    race.add_lap(68);
    race.print_laps();
    race.add_lap(71);
    race.print_laps();
    race.finish();
    // race.add_lap(42);

    traits::traits_main();

    supertraits::supertraits_main();

    assoc_types::assoc_types_main();

    deriving::deriving_main();

    logger_exercise::logger_main();
}
