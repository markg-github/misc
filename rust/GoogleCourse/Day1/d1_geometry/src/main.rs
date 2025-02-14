

// Calculate the magnitude of a vector by summing the squares of its coordinates
// and taking the square root. Use the `sqrt()` method to calculate the square
// root, like `v.sqrt()`.


fn magnitude(v:&[f64;3]) -> f64 {
    // let mag_squared = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    let mut mag_squared = 0.;
    for coord in v {
        mag_squared += *coord * *coord;
    }
    mag_squared.sqrt()
}

// Normalize a vector by calculating its magnitude and dividing all of its
// coordinates by that magnitude.


fn normalize(v:&mut [f64;3]) {
    let mag = magnitude(v);
    for coord in v {
        *coord /= mag
    }
    // v[0] /= mag;
    // v[1] /= mag;
    // v[2] /= mag;
}

/// Calculate the magnitude of the given vector.
fn magnitude_soln(vector: &[f64; 3]) -> f64 {
    let mut mag_squared = 0.0;
    for coord in vector {
        mag_squared += coord * coord;
    }
    mag_squared.sqrt()
}

/// Change the magnitude of the vector to 1.0 without changing its direction.
fn normalize_soln(vector: &mut [f64; 3]) {
    let mag = magnitude(vector);
    for item in vector {
        *item /= mag;
    }
}

// Use the following `main` to test your work.

fn main() {
    println!("Magnitude of a unit vector: {}", magnitude(&[0.0, 1.0, 0.0]));

    let mut v = [1.0, 2.0, 9.0];
    println!("Magnitude of {v:?}: {}", magnitude(&v));
    normalize(&mut v);
    println!("Magnitude of {v:?} after normalization: {}", magnitude(&v));
}