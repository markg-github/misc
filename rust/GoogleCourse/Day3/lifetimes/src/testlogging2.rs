use log::{info, debug, warn, error, trace, LevelFilter}; // Import log *macros*
use env_logger::Builder;
use std::io::Write;

pub fn logging_main() -> Result<(), Box<dyn std::error::Error>> {
    // Initialize the logger (do this *once* in your application)
    Builder::new()
        .format(|buf, record| {
            let file = record.file().unwrap_or("unknown_file");
            let line = record.line().unwrap_or(0);
            let module_path = record.module_path().unwrap_or("unknown_module");
            writeln!(buf, "{}:{}:{} - {}", record.level(), file, line, record.args())
            // writeln!(buf, "{}:{}:{} - {}", module_path, record.level(), line, record.args())
        })
        // can use Error, Warn, Info, Debug, Trace
        .filter_level(LevelFilter::Debug) // Set the minimum log level
        .try_init()?;

    info!("Application started."); // Use the log *macros* directly!
    debug!("This is a debug message.");
    warn!("This is a warning.");
    error!("This is an error.");

    test_log();

    // ... rest of your code

    Ok(())
}

fn test_log() {
    trace!("This is a trace message.");

    let x = 10;
    let y = 20;

    debug!("x = {}, y = {}", x, y); // Example of formatted debug output

}