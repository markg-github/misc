
for custom logger/logging
use std::cell::RefCell;
use log::{LevelFilter, SetLoggerError}; // Or your logging crate
use env_logger::Builder;
use std::sync::Mutex; // If you need thread safety

// Example using RefCell (not thread-safe):
static LOGGER: RefCell<Option<Box<dyn log::Log>>> = RefCell::new(None);

// Example using Mutex (thread-safe):
// static LOGGER: Mutex<Option<Box<dyn log::Log>>> = Mutex::new(None);

fn initialize_logger() -> Result<(), SetLoggerError> {
    let builder = Builder::new().filter_level(LevelFilter::Info); // Customize
    builder.try_init()?; // Initialize the global logger

    // Store the logger in the static variable.  Use .get_or_insert() to ensure only one logger is initialized.
    LOGGER.borrow_mut().get_or_insert(|| log::logger()); // For RefCell
    // LOGGER.lock().unwrap().get_or_insert(|| log::logger()); // For Mutex

    Ok(())
}

fn my_function() {
    // Access the logger:
    if let Some(logger) = LOGGER.borrow().as_ref() { // For RefCell
    // if let Some(logger) = LOGGER.lock().unwrap().as_ref() { // For Mutex
        logger.info!("Hello from my_function!");
    }
}

fn another_function() {
    if let Some(logger) = LOGGER.borrow().as_ref() { // For RefCell
    // if let Some(logger) = LOGGER.lock().unwrap().as_ref() { // For Mutex
        logger.debug!("This is a debug message.");
    }
}

pub fn main() -> Result<(), SetLoggerError> {
    initialize_logger()?;
    my_function();
    another_function();
    Ok(())
}