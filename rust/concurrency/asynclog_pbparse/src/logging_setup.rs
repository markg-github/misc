
use log::{info, debug, warn, error, trace, LevelFilter, Record, Level};
use env_logger::Builder;
use std::io::Write;
use std::sync::mpsc;
use tokio::task;
use tokio::time::{sleep, Duration};
use std::sync::{Arc, Mutex};

struct RemoteLogger {
    sender: mpsc::Sender<String>,
}

impl RemoteLogger {
    fn new(sender: mpsc::Sender<String>) -> Self {
        RemoteLogger { sender }
    }

    fn log(&self, message: String) {
        if let Err(e) = self.sender.send(message) {
            eprintln!("Error sending log message: {}", e);
        }
    }
}

