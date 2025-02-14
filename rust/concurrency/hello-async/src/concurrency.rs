
use std::time::Duration;
use std::pin::Pin;
use std::pin::pin;
use std::future::Future;

use std::thread;

use std::time::Instant;

use trpl::Either;

pub fn main() {
    trpl::run(async {
        trpl::spawn_task(async {
            for i in 1..10 {
                println!("hi number {i} from the first task!");
                trpl::sleep(Duration::from_millis(30)).await;
            }
        });

        let handle = trpl::spawn_task(async {
            for i in 11..20 {
                println!("hi number {i} from the first task!");
                trpl::sleep(Duration::from_millis(20)).await;
            }
        });

        for i in 21..25 {
            println!("hi number {i} from the second task!");
            trpl::sleep(Duration::from_millis(10)).await;
        }

        // wait for 11-19 before returning
        handle.await.unwrap();
    });

    trpl_join();

    message_passing();

    tx_cloning();

    elegant_tx_cloning();

    yield_control();

    test_timeout();
}

fn trpl_join() {

    trpl::run(async {

        println!("*************** both asyncs");
        let fut1 = async {
            for i in 11..20 {
                println!("hi number {i} from the first task!");
                trpl::sleep(Duration::from_millis(20)).await;
            }
        };

        let fut2 = async {
            for i in 21..25 {
                println!("hi number {i} from the second task!");
                trpl::sleep(Duration::from_millis(10)).await;
            }
        };

        trpl::join(fut1, fut2).await;

        println!("************************ remove 1st async");
        // remove async from 1st
        // let fut1 = async {
            for i in 11..20 {
                println!("hi number {i} from the first task!");
                trpl::sleep(Duration::from_millis(20)).await;
            };
        // };

        let fut3 = async {
            for i in 21..25 {
                println!("hi number {i} from the second task!");
                trpl::sleep(Duration::from_millis(10)).await;
            }
        };

        fut3.await;

        println!("************************ remove 2nd async");
        // remove async from 2nd
        let fut4 = async {
            for i in 11..20 {
                println!("hi number {i} from the first task!");
                trpl::sleep(Duration::from_millis(20)).await;
            }
        };

        // let fut2 = async {
            for i in 21..25 {
                println!("hi number {i} from the second task!");
                trpl::sleep(Duration::from_millis(10)).await;
            };
        // };

        fut4.await;

        println!("************************ remove both asyncs");
        // remove async from both
        // let fut1 = async {
            for i in 11..20 {
                println!("hi number {i} from the first task!");
                trpl::sleep(Duration::from_millis(20)).await;
            };
        // };

        // let fut2 = async {
            for i in 21..25 {
                println!("hi number {i} from the second task!");
                trpl::sleep(Duration::from_millis(10)).await;
            };
        // };

        
        println!("************************ await immediately");
        let fut5 = async {
            for i in 11..20 {
                println!("hi number {i} from the first task!");
                trpl::sleep(Duration::from_millis(20)).await;
            }
        };
        fut5.await;

        let fut6 = async {
            for i in 21..25 {
                println!("hi number {i} from the second task!");
                trpl::sleep(Duration::from_millis(10)).await;
            }
        };
        fut6.await;
        
    });
}

fn message_passing() {
    trpl::run(async {
        let (tx, mut rx) = trpl::channel();

        // move tx so it gets dropped at the end of the async
        // block and the while let in the rx async block can finish
        let tx_fut = async move {
            let vals = vec![
                String::from("hi"),
                String::from("from"),
                String::from("the"),
                String::from("future"),
            ];

            for val in vals {
                tx.send(val).unwrap();
                trpl::sleep(Duration::from_millis(350)).await;
            }
        };
    
        let rx_fut = async {
            while let Some(value) = rx.recv().await {
                println!("Got: {value}");
            }
        };

        trpl::join(tx_fut, rx_fut).await;
    
    });

}

fn tx_cloning() {
    trpl::run(async {
        let (tx, mut rx) = trpl::channel();

        let tx1 = tx.clone();
        let tx1_fut = async move {
            let vals = vec![
                String::from("hi"),
                String::from("from"),
                String::from("the"),
                String::from("future"),
            ];

            for val in vals {
                tx1.send(val).unwrap();
                trpl::sleep(Duration::from_millis(50)).await;
            }
        };

        let rx_fut = async {
            while let Some(value) = rx.recv().await {
                println!("received '{value}'");
            }
        };

        let tx_fut = async move {
            let vals = vec![
                String::from("more"),
                String::from("messages"),
                String::from("for"),
                String::from("you"),
            ];

            for val in vals {
                tx.send(val).unwrap();
                trpl::sleep(Duration::from_millis(150)).await;
            }
        };

        // trpl::join3(tx1_fut, tx_fut, rx_fut).await;

        // join! handles arbitrary number of futures,
        // but the number has to be known "ahead of time" (at compile time?)
        // trpl::join!(tx1_fut, tx_fut, rx_fut);

        // a more flexible approach
        // but this doesn't work for complicated reasons
        // let futures = vec![tx1_fut, rx_fut, tx_fut];
        let futures: Vec<Pin<Box<dyn Future<Output = ()>>>> = vec![
            Box::pin(tx1_fut), 
            Box::pin(rx_fut), 
            Box::pin(tx_fut)
        ];


        trpl::join_all(futures).await;


    })
}

fn elegant_tx_cloning() {
    trpl::run(async {
        let (tx, mut rx) = trpl::channel();

        let tx1 = tx.clone();
        let tx1_fut = pin!(async move {
            let vals = vec![
                String::from("pin hi"),
                String::from("pin from"),
                String::from("pin the"),
                String::from("pin future"),
            ];

            for val in vals {
                tx1.send(val).unwrap();
                trpl::sleep(Duration::from_millis(50)).await;
            }
        });

        let rx_fut = pin!(async {
            while let Some(value) = rx.recv().await {
                println!("pin received '{value}'");
            }
        });

        let tx_fut = pin!(async move {
            let vals = vec![
                String::from("pin more"),
                String::from("pin messages"),
                String::from("pin for"),
                String::from("pin you"),
            ];

            for val in vals {
                tx.send(val).unwrap();
                trpl::sleep(Duration::from_millis(150)).await;
            }
        });

        let futures: Vec<Pin<&mut dyn Future<Output = ()>>> =
            vec![tx1_fut, rx_fut, tx_fut];

        trpl::join_all(futures).await;

        let a = async { 1u32 };
        let b = async { "Hello!" };
        let c = async { true };

        // we can either use join_all with the same type but dynamic count
        // or join! with different types and fixed count
        let (a_result, b_result, c_result) = trpl::join!(a, b, c);
        println!("{a_result}, {b_result}, {c_result}");
    })
}

fn slow(name: &str, ms: u64) {
    thread::sleep(Duration::from_millis(ms));
    println!("'{name}' ran for {ms}ms");
}

fn yield_control() {
    trpl::run(async {
        // could use short trpl::sleep instead of yield_now
        // but yield_now is faster - see end of this function
        let a = async {
            println!("'a' started.");
            slow("a", 30);
            trpl::yield_now().await;
            slow("a", 10);
            trpl::yield_now().await;
            slow("a", 20);
            trpl::yield_now().await;
            // trpl::sleep(Duration::from_millis(50)).await;
            println!("'a' finished.");
        };

        let b = async {
            println!("'b' started.");
            slow("b", 75);
            trpl::yield_now().await;
            slow("b", 10);
            trpl::yield_now().await;
            slow("b", 15);
            trpl::yield_now().await;
            slow("b", 350);
            trpl::yield_now().await;
            // trpl::sleep(Duration::from_millis(50)).await;
            println!("'b' finished.");
        };

        trpl::race(a, b).await;

        // micro-benchmark: sleep vs. yield_now
        let one_ns = Duration::from_nanos(1);
        let start = Instant::now();
        async {
            for _ in 1..1000 {
                trpl::sleep(one_ns).await;
            }
        }
        .await;
        let time = Instant::now() - start;
        println!(
            "'sleep' version finished after {} seconds.",
            time.as_secs_f32()
        );

        let start = Instant::now();
        async {
            for _ in 1..1000 {
                trpl::yield_now().await;
            }
        }
        .await;
        let time = Instant::now() - start;
        println!(
            "'yield' version finished after {} seconds.",
            time.as_secs_f32()
        );
    });
    
}

fn test_timeout() {
    trpl::run(async {
        let slow = async {
            trpl::sleep(Duration::from_secs(5)).await;
            "Finally finished"
        };

        match mytimeout(slow, Duration::from_secs(20)).await {
            Ok(message) => println!("Succeeded with '{message}'"),
            Err(duration) => {
                println!("Failed after {} seconds", duration.as_secs())
            }
        }

    })
}

async fn mytimeout<F: Future>(future_to_try: F, max_time: Duration) -> Result<F::Output, Duration> {
    match trpl::race(future_to_try, trpl::sleep(max_time)).await {
        Either::Left(output) => Ok(output),
        Either::Right(_) => Err(max_time),
    }

}


