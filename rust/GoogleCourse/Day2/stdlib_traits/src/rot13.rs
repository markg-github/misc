use std::io::Read;

struct RotDecoder<R: Read> {
    input: R,
    rot: u8,
}

impl<R: Read> Read for RotDecoder<R> {
    fn read(&mut self, buf: &mut [u8]) -> std::io::Result<usize> {
        let size = self.input.read(buf)?;

        // original (works)
        // for b in &mut buf[..size] {
        // doesn't work
        // for b in &mut buf {
        for b in buf {

            // b or (*b) works below
            if (*b).is_ascii_alphabetic() {
                let base = if (*b).is_ascii_uppercase() { 'A' } else { 'a' } as u8;

                // why not just b, instead of *b?
                // original (works)
                *b = (*b - base + self.rot) % 26 + base;
                // doesn't work
                // b = (b - base + self.rot) % 26 + base;
                // doesn't work
                // *b = (b - base + self.rot) % 26 + base;
            }
        }
        Ok(size)
    }
}

pub fn main() {
    let mut rot =
        RotDecoder { input: "Gb trg gb gur bgure fvqr!".as_bytes(), rot: 13 };
    let mut result = String::new();
    // rot.read_to_string(&mut result).unwrap();

    // if no errors, don't need to unwrap, since we don't the return value (just the buffer/string)
    rot.read_to_string(&mut result);

    println!("{}", result);
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn joke() {
        let mut rot =
            RotDecoder { input: "Gb trg gb gur bgure fvqr!".as_bytes(), rot: 13 };
        let mut result = String::new();

        // what does unwrap do here? does it affect/change result?
        rot.read_to_string(&mut result).unwrap();
        assert_eq!(&result, "To get to the other side!");
    }

    #[test]
    fn binary() {
        let input: Vec<u8> = (0..=255u8).collect();

        // doesn't work since 256 is out of range
        // let input: Vec<u8> = (0..256u8).collect();

        // original (works)
        // let mut rot = RotDecoder::<&[u8]> { input: input.as_ref(), rot: 13 };
        // doesn't work
        // let mut rot = RotDecoder::<&[u8]> { input: input, rot: 13 };
        // works
        let mut rot = RotDecoder::<&[u8]> { input: &input, rot: 13 };

        // 256 zeros
        let mut buf = [0u8; 256];
        assert_eq!(rot.read(&mut buf).unwrap(), 256);
        for i in 0..=255 {
            if input[i] != buf[i] {
                assert!(input[i].is_ascii_alphabetic());
                assert!(buf[i].is_ascii_alphabetic());
            }
        }
    }
}


