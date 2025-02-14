
/* 
the proto

message PhoneNumber {
    optional string number = 1;
    optional string type = 2;
  }
  
  message Person {
    optional string name = 1;
    optional int32 id = 2;
    repeated PhoneNumber phones = 3;
  }
   */

use log::{info, debug, warn, error, trace, LevelFilter}; // Import log *macros*
use function_name::named;


/// A wire type as seen on the wire.
enum WireType {
    /// The Varint WireType indicates the value is a single VARINT.
    Varintwt,
    // The I64 WireType indicates that the value is precisely 8 bytes in
    // little-endian order containing a 64-bit signed integer or double type.
    //I64,  -- not needed for this exercise
    /// The Len WireType indicates that the value is a length represented as a
    /// VARINT followed by exactly that number of bytes.
    Lenwt,
    // The I32 WireType indicates that the value is precisely 4 bytes in
    // little-endian order containing a 32-bit signed integer or float type.
    //I32,  -- not needed for this exercise
}

#[derive(Debug)]
/// A field's value, typed based on the wire type.
enum FieldValue<'a> {
    Varintfv(u64),
    //I64(i64),  -- not needed for this exercise
    Lenfv(&'a [u8]),
    //I32(i32),  -- not needed for this exercise
}

#[derive(Debug)]
/// A field, containing the field number and its value.
struct Field<'a> {
    field_numf: u64,
    valuef: FieldValue<'a>,
}

trait ProtoMessage<'a>: Default {
    fn add_field(&mut self, field: Field<'a>);
}

impl From<u64> for WireType {
    #[named]
    fn from(value: u64) -> Self {
        trace!("fn: {}", function_name!());
        match value {
            0 => debug!("WireType::Varintwt"),
            2 => debug!("WireType::Lenwt"),
            _ => ()
        }
        match value {
            0 => WireType::Varintwt,
            //1 => WireType::I64,  -- not needed for this exercise
            2 => WireType::Lenwt,
            //5 => WireType::I32,  -- not needed for this exercise
            _ => panic!("Invalid wire type: {value}"),
        }
    }
}

impl<'a> FieldValue<'a> {
    #[named]
    fn as_str(&self) -> &'a str {
        trace!("fn: {}", function_name!());
        // is self Len? if so, data = self.data
        // else panic
        let FieldValue::Lenfv(data) = self else {
            panic!("Expected string to be a `Len` field");
        };
        // The from_utf8 function returns a Result<&str, Utf8Error>, 
        // which means it can either succeed and return the string slice 
        // or fail and return an error indicating that the byte slice is 
        // not valid UTF-8. In this code, the expect method is called on 
        // the Result returned by from_utf8. The expect method is a convenience 
        // method that either returns the contained value if the Result is Ok, or 
        // it panics with a provided error message if the Result is Err.
        trace!("return: {}", std::str::from_utf8(data).expect("Invalid string"));
        std::str::from_utf8(data).expect("Invalid string")
    }

    #[named]
    fn as_bytes(&self) -> &'a [u8] {
        trace!("fn: {}", function_name!());
        let FieldValue::Lenfv(data) = self else {
            panic!("Expected bytes to be a `Len` field");
        };
        // trace!("return: {:?}", data);
        data
    }

    #[named]
    fn as_u64(&self) -> u64 {
        trace!("fn: {}", function_name!());
        let FieldValue::Varintfv(value) = self else {
            panic!("Expected `u64` to be a `Varint` field");
        };
        trace!("return: {}", *value);
        *value
    }
}

/// Parse a VARINT, returning the parsed value and the remaining bytes.
#[named]
fn parse_varint(data: &[u8]) -> (u64, &[u8]) {
    trace!("fn: {}", function_name!());
    for i in 0..7 {
        let Some(b) = data.get(i) else {
            panic!("Not enough bytes for varint");
        };
        let mut multibyte = false;
        if b & 0x80 == 0 {
            // This is the last byte of the VARINT, so convert it to
            // a u64 and return it.
            let mut ret_value = 0u64;
            // construct a u64 from elements of data, in reverse order
            for b in data[..=i].iter().rev() {
                ret_value = (ret_value << 7) | (b & 0x7f) as u64;
            }
            // debug!("i = {i}");
            trace!("return: {ret_value}");
            return (ret_value, &data[i + 1..]);
        }
        else if !multibyte {
            debug!("**************** multi-byte VARINT");
            multibyte = true;
        }
    }

    // More than 7 bytes is invalid.
    panic!("Too many bytes for varint");
}

/// Convert a tag into a field number and a WireType.
#[named]
fn unpack_tag(tag: u64) -> (u64, WireType) {
    trace!("fn: {}", function_name!());
    let field_num = tag >> 3;
    let wire_type = WireType::from(tag & 0x7);
    // trace!("return: {field_num}, {}", wire_type);
    trace!("return: {field_num}");
    (field_num, wire_type)
}


/// Parse a field, returning the remaining bytes
#[named]
fn parse_field(data: &[u8]) -> (Field, &[u8]) {
    trace!("fn: {}", function_name!());
    // all fields start with a tag
    let (tag, remainder) = parse_varint(data);
    let (field_num, wire_type) = unpack_tag(tag);
    // Based on the wire type, build a Field, consuming as many bytes as necessary.
    let (fieldvalue, remainder2) = match wire_type {
        WireType::Varintwt => {
            let (value, remainder3) = parse_varint(remainder);
            (FieldValue::Varintfv(value), remainder3)
        }
        WireType::Lenwt => {
            let (len, remainder4) = parse_varint(remainder);
            let len2: usize = len.try_into().expect("len not a valid 'usize'");
            debug!("len2: {}", len2);
            if remainder4.len() < len2 {
                panic!("Unexpected EOF");
            }
            // finish with the VARINT at the beginning of remainder
            // and basically return parsed remainder4
            let (value2, remainder5) = remainder4.split_at(len2);
            debug!("value2: {:?}", value2);
            (FieldValue::Lenfv(value2), remainder5)
        }
    };
    // Return the field, and any un-consumed bytes.
    trace!("return: {field_num}, {:?}", fieldvalue);
    (Field { field_numf: field_num, valuef: fieldvalue }, remainder2)
}

/// Parse a message in the given data, calling `T::add_field` for each field in
/// the message.
///
/// The entire input is consumed.
///
/// Note that the compiler infers T based on what must be returned in the calling code.
#[named]
fn parse_message<'a, T: ProtoMessage<'a>>(mut data: &'a [u8]) -> T {
    trace!("fn: {}", function_name!());

    // type of result must match what caller expects
    let mut result = T::default();
    while !data.is_empty() {
        let parsed = parse_field(data);
        // parsed is a tuple holding current field and remaining bytes, respectively
        result.add_field(parsed.0);
        data = parsed.1;
    }
    result
}

#[derive(PartialEq)]
#[derive(Debug, Default)]
struct PhoneNumber<'a> {
    number: &'a str,
    type_: &'a str,
}

#[derive(PartialEq)]
#[derive(Debug, Default)]
struct Person<'a> {
    name: &'a str,
    id: u64,
    phone: Vec<PhoneNumber<'a>>,
}

// TODO: Implement ProtoMessage for Person and PhoneNumber.
impl<'a> ProtoMessage<'a> for Person<'a> {
    #[named]
    fn add_field(&mut self, field: Field<'a>) {
        trace!("fn: {}", function_name!());
        match field.field_numf {
            1 => debug!("name"),
            2 => debug!("id"),
            3 => debug!("phone"),
            _ => {} // skip everything else
        }
        match field.field_numf {
            1 => self.name = field.valuef.as_str(),
            2 => self.id = field.valuef.as_u64(),
            3 => self.phone.push(parse_message(field.valuef.as_bytes())),
            _ => {} // skip everything else
        }
    }
}

impl<'a> ProtoMessage<'a> for PhoneNumber<'a> {
    #[named]
    fn add_field(&mut self, field: Field<'a>) {
        trace!("fn: {}", function_name!());
        match field.field_numf {
            1 => debug!("number"),
            2 => debug!("type"),
            _ => {} // skip everything else

        }
        match field.field_numf {
            1 => self.number = field.valuef.as_str(),
            2 => self.type_ = field.valuef.as_str(),
            _ => {} // skip everything else
        }
    }
}

pub fn main() {


    debug!("\n person_id");
    let person_id: Person = parse_message(&[0x10, 0x2a]);
    assert_eq!(person_id, Person { name: "", id: 42, phone: vec![] });

    // return;

    debug!("\n person_name");
    let person_name: Person = parse_message(&[
        0x0a, // person, name, len
        0x0e, 
        0x62, 0x65, 0x61, 0x75, 0x74, 0x69, 0x66, 0x75, 0x6c, 0x20, 0x6e, 0x61, 0x6d, 0x65,
    ]);
    assert_eq!(person_name, Person { name: "beautiful name", id: 0, phone: vec![] });

    // return;

    debug!("\n person_name_id");
    let person_name_id: Person =
        parse_message(&[0x0a, 0x04, 0x45, 0x76, 0x61, 0x6e, 0x10, 0x16]);
    assert_eq!(person_name_id, Person { name: "Evan", id: 22, phone: vec![] });

    // return;

    debug!("\n phone");
    let phone: Person = parse_message(&[
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
    ]);
    assert_eq!(
        phone,
        Person {
            name: "",
            id: 0,
            phone: vec![PhoneNumber { number: "+1234-777-9090", type_: "home" },],
        }
    );

    // return;

    debug!("\n person");
    // Put that all together into a single parse.
    let person: Person = parse_message(&[
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
    ]);
    assert_eq!(
        person,
        Person {
            name: "maxwell",
            id: 42,
            phone: vec![
                PhoneNumber { number: "+1202-555-1212", type_: "home" },
                PhoneNumber { number: "+1800-867-5308", type_: "mobile" },
            ]
        }
    );
}  

