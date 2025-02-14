#[derive(Debug)]
/// An event in the elevator system that the controller must react to.
enum Event {
    // TODO: add required variants
    // UP_BUTTON,
    // DOWN_BUTTON,
    // FLOOR_BUTTON,
    // CLOSE_BUTTON,
    // HOLD_BUTTON,
    // STARTED,
    // STOPPED,
    // ARRIVED,
    DoorOpened,
    DoorClosed,
    ButtonPressed(Button),
    CarStarted(Floor),
    CarArrived(Floor),
    CarStopped,
    CarRestarted
}

/// A direction of travel.
#[derive(Debug)]
enum Direction {
    Up,
    Down,
}

type Floor = i32;

#[derive(Debug)]
/// An event in the elevator system that the controller must react to.
enum Button {
    // TODO: add required variants
    LobbyButton(Floor, Direction),
    CarButton(Floor)
}

/// The car has arrived on the given floor.
fn car_arrived(floor: i32) -> Event {
    return Event::CarArrived(floor);
    // todo!()
}

/// The car doors have opened.
fn car_door_opened() -> Event {
    return Event::DoorOpened;
    // todo!()
}

/// The car doors have closed.
fn car_door_closed() -> Event {
    return Event::DoorClosed;
    // todo!()
}

/// A directional button was pressed in an elevator lobby on the given floor.
fn lobby_call_button_pressed(floor: i32, dir: Direction) -> Event {
    return Event::ButtonPressed(Button::LobbyButton(floor, dir));
    // todo!()
}

/// A floor button was pressed in the elevator car.
fn car_floor_button_pressed(floor: i32) -> Event {
    return Event::ButtonPressed(Button::CarButton(floor));
    // todo!()
}

fn main() {
    println!(
        "A ground floor passenger has pressed the up button: {:?}",
        lobby_call_button_pressed(0, Direction::Up)
    );
    println!("The car has arrived on the ground floor: {:?}", car_arrived(0));
    println!("The car door opened: {:?}", car_door_opened());
    println!(
        "A passenger has pressed the 3rd floor button: {:?}",
        car_floor_button_pressed(3)
    );
    println!("The car door closed: {:?}", car_door_closed());
    println!("The car has arrived on the 3rd floor: {:?}", car_arrived(3));
}