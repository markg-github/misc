use std::fs::File;
use std::io::Read;

pub fn result_main() {
    // println!("result_main");
    let fileo: Result<File, std::io::Error> = File::open("diary.txt");
    match fileo {
        Ok(mut filei) => {
            let mut contents = String::new();
            if let Ok(bytes) = filei.read_to_string(&mut contents) {
                println!("Dear diary: {contents} ({bytes} bytes)");
            } else {
                println!("Could not read file content");
            }
        }
        Err(err) => {
            println!("The diary could not be opened: {err}");
        }
    }
}