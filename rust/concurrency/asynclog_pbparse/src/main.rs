mod protobuf_parsing;
mod logging_setup;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut builder = Builder::new();
    builder
        .format(|buf, record| {
            let file = record.file().unwrap_or("unknown_file");
            let line = record.line().unwrap_or(0);
            let module_path = record.module_path().unwrap_or("unknown_module");
            writeln!(buf, "{}:{}:{} - {}", record.level(), file, line, record.args())
        })
        .filter_level(LevelFilter::Debug);

    let (tx, rx) = mpsc::channel();
    let logger = Arc::new(Mutex::new(logging_setup::RemoteLogger::new(tx)));
    let logger_clone = logger.clone();

    task::spawn(async move {
        for message in rx {
            println!("Sending log remotely: {}", message);
            sleep(Duration::from_millis(100)).await;
        }
    });

    builder.try_init()?;

    async fn process_person<'a>(data: &'a [u8], logger: &Arc<Mutex<logging_setup::RemoteLogger>>) -> protobuf_parsing::Person<'a> {
        let person = protobuf_parsing::parse_message(data);
        let log_message = format!("Parsed person: {:?}", person);
        let logger_guard = logger.lock().unwrap();
        logger_guard.log(log_message);
        person
    }

    let person_id = process_person(&[0x10, 0x2a], &logger).await;
    assert_eq!(person_id, protobuf_parsing::Person { name: "", id: 42, phone: vec![] });

    // ... (rest of your test cases, using process_person and .await)

    let person_name = process_person(&[
        0x0a, // person, name, len
        0x0e,
        0x62, 0x65, 0x61, 0x75, 0x74, 0x69, 0x66, 0x75, 0x6c, 0x20, 0x6e, 0x61, 0x6d, 0x65,
    ], &logger).await;
    assert_eq!(person_name, protobuf_parsing::Person { name: "beautiful name", id: 0, phone: vec![] });


    let person_name_id = process_person(&[0x0a, 0x04, 0x45, 0x76, 0x61, 0x6e, 0x10, 0x16], &logger).await;
    assert_eq!(person_name_id, protobuf_parsing::Person { name: "Evan", id: 22, phone: vec![] });

    let phone = process_person(&[
        0x0a, // person, name, len
        0x00,
        0x10, // person, id, VARINT
        0x00,
        0x1a, // person, phones, len
        0x16,
        0x0a, // phone, number, len
        0x0e,
        0x2b, 0x31, 0x32, 0x33, 0x34, 0x2d, 0x37, 0x37, 0x37, 0x2d, 0x39, 0x30, 0x39, 0x30,
        0x12, // phone, type, len
        0x04,
        0x68, 0x6f, 0x6d, 0x65,
    ], &logger).await;
    assert_eq!(
        phone,
        protobuf_parsing::Person {
            name: "",
            id: 0,
            phone: vec![protobuf_parsing::PhoneNumber { number: "+1234-777-9090", type_: "home" },],
        }
    );

    let person = process_person(&[
        0x0a, // person, name, len
        0x07,
        0x6d, 0x61, 0x78, 0x77, 0x65, 0x6c, 0x6c,
        0x10, // person, id, varint
        0x2a,
        0x1a, // person, phones, len
        0x16,
        0x0a, // phone, number, len
        0x0e,
        0x2b, 0x31, 0x32, 0x30, 0x32, 0x2d, 0x35, 0x35, 0x35, 0x2d, 0x31, 0x32, 0x31, 0x32,
        0x12, // phone, type, len
        0x04,
        0x68, 0x6f, 0x6d, 0x65,
        0x1a, // person, phones, len
        0x18,
        0x0a, // phone, number, len
        0x0e,
        0x2b, 0x31, 0x38, 0x30, 0x30, 0x2d, 0x38, 0x36, 0x37, 0x2d, 0x35, 0x33, 0x30, 0x38,
        0x12, // phone, type, len
        0x06,
        0x6d, 0x6f, 0x62, 0x69, 0x6c, 0x65,
    ], &logger).await;
    assert_eq!(
        person,
        protobuf_parsing::Person {
            name: "maxwell",
            id: 42,
            phone: vec![
                protobuf_parsing::PhoneNumber { number: "+1202-555-1212", type_: "home" },
                protobuf_parsing::PhoneNumber { number: "+1800-867-5308", type_: "mobile" },
            ]
        }
    );

    Ok(())
}
