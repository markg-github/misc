use std::thread;
use std::time::Duration;

fn main() {
    let v = vec![1, 2, 3];

    let handle = thread::spawn(move || {
        for i in 1..10 {
            println!("hi number {i} from the spawned thread!");
            println!("Here's a vector: {v:?}");
            thread::sleep(Duration::from_millis(100));
        }
    });

    // handle.join().unwrap();

    for i in 1..5 {
        println!("hi number {i} from the main thread!");
        thread::sleep(Duration::from_millis(50));
    }

    handle.join().unwrap();

    message_passing();

    show_concurrent();

    multi_producer();

    shared_state();

}

use std::sync::mpsc;

fn message_passing() {
    let (tx, rx) = mpsc::channel();

    let handle = thread::spawn(move || {
        let val = String::from("hi");
        tx.send(val).unwrap();
    });
    let received = rx.recv().unwrap();
    println!("Got: {received}");

    handle.join().unwrap();
}


/* fn invalid() {
    let (tx, rx) = mpsc::channel();

    thread::spawn(move || {
        let val = String::from("hi");
        tx.send(val).unwrap();
        println!("val is {val}");
    });

    let received = rx.recv().unwrap();
    println!("Got: {received}");
}
 */

fn show_concurrent() {
    let (tx, rx) = mpsc::channel();

    let handle = thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];

        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_millis(300));
        }
    });

    for received in rx {
        println!("Got: {received}");
    }

    if let Err(e) = handle.join() {
        println!("Thread panicked: {:?}", e);
    }
}

// use std::sync::mpsc;
// use std::thread;
// use std::time::Duration;

fn multi_producer() {

    let (tx, rx) = mpsc::channel();

    let tx1 = tx.clone();
    let h1 = thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];

        for val in vals {
            tx1.send(val).unwrap();
            thread::sleep(Duration::from_millis(250));
        }
    });

    let h2 = thread::spawn(move || {
        let vals = vec![
            String::from("more"),
            String::from("messages"),
            String::from("for"),
            String::from("you"),
        ];

        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_millis(350));
        }
    });

    for received in rx {
        println!("Got: {received}");
    }

    h1.join().unwrap();
    match h2.join() {
        Ok(_) => (),        // could also use {}
        Err(e) => println!("{:?}", e)
    };

}

use std::sync::{Arc, Mutex};
// use std::thread;

fn shared_state() {
    // can't only use Mutex here since it couldn't be moved into multiple threads
    // can't wrap in Rc since Rc is not threadsafe
    // have to wrap in Arc (atomic reference count)
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();

            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());
}