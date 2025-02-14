use trpl::{Either, Html};

mod concurrency;


fn main() {
    println!("Hello, world!");
    // page_title("https://doc.rust-lang.org/beta/book/ch17-01-futures-and-syntax.html").await;
    trpl::run(async {
        match page_title("https://doc.rust-lang.org/beta/book/ch17-01-futures-and-syntax.html").await {
            Some(ref x) => println!("{:?}", x),
            None => {}
        }
    });

    race_urls();

    concurrency::main()
}

async fn page_title(url: &str) -> Option<String> {
    let response_text = trpl::get(url).await.text().await;
    // could also use
    // let response = trpl::get(url).await;
    // let response_text = response.text().await;
    let the_html = Html::parse(&response_text)
        .select_first("title")
        .map(|title_element| title_element.inner_html());

    the_html

    
}

fn race_urls() {
    // let args: Vec<String> = std::env::args().collect();

    trpl::run(async {
        let title_fut_1 = page_title2("https://doc.rust-lang.org/beta/book/ch10-02-traits.html#traits-as-parameters");
        let title_fut_2 = page_title2("https://doc.rust-lang.org/beta/std/sync/atomic/index.html");

        let (url, maybe_title) =
            match trpl::race(title_fut_1, title_fut_2).await {
                Either::Left(left) => left,
                Either::Right(right) => right,
            };

        println!("{url} returned first");
        match maybe_title {
            Some(title) => println!("Its page title is: '{title}'"),
            None => println!("Its title could not be parsed."),
        }
    })
}

async fn page_title2(url: &str) -> (&str, Option<String>) {
    let text = trpl::get(url).await.text().await;
    let title = Html::parse(&text)
        .select_first("title")
        .map(|title| title.inner_html());
    (url, title)
}