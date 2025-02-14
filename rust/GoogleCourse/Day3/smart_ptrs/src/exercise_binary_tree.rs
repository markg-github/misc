
use std::cmp::Ordering;
use std::fmt;

use rand::{Rng, SeedableRng};
use rand_chacha::ChaCha8Rng;



/// A node in the binary tree.
#[derive(Debug)]
struct Node<T: Ord+std::fmt::Debug> {
    value: T,
    left: Subtree<T>,
    right: Subtree<T>,
}

impl<T: Ord+std::fmt::Debug> Node<T> {
    fn new(thevalue: T) -> Self {
        Self { value: thevalue, left: Subtree::new(), right: Subtree::new()}
    }
}

// Implementing Debug for the Node's data type (T)
// impl<T> fmt::Debug for Node<T>
// where
//     T: fmt::Debug, // Important: Trait bound!
// {
//     fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
//         f.debug_struct("Node")
//          .field("value", &self.value)
//          // ... other fields
//          .finish()
//     }
// }


/// A possibly-empty subtree.
#[derive(Debug)]
struct Subtree<T: Ord+std::fmt::Debug>(Option<Box<Node<T>>>);

/// A container storing a set of values, using a binary tree.
///
/// If the same value is added multiple times, it is only stored once.
#[derive(Debug)]
pub struct BinaryTree<T: Ord+std::fmt::Debug> {
    root: Subtree<T>,
}

impl<T: Ord+std::fmt::Debug> BinaryTree<T> {
    fn new() -> Self {
        Self { root: Subtree::new() }
    }

    fn insert(&mut self, value: T) {
            self.root.insert(value);
    }

    fn has(&self, value: &T) -> bool {
        self.root.has(value)
    }

    fn len(&self) -> usize {
        self.root.len()
    }

    fn inorder(&self) {
        println!("BinaryTree::inorder");
        self.root.inorder();
    }
}

// Implement `new`, `insert`, `len`, and `has` for `Subtree`.
impl<T: Ord+std::fmt::Debug> Subtree<T> {
    fn new() -> Self {
        Self(None)
    }

    fn insert(&mut self, thevalue: T)
    
    where
        T: Ord + fmt::Debug
    {
        match &mut self.0 {
            None => self.0 = Some(Box::new(Node::new(thevalue))),
            Some(thenode) => match thevalue.cmp(&thenode.value) {
                Ordering::Less => thenode.left.insert(thevalue),
                Ordering::Equal => println!("{:?}", thenode),
                Ordering::Greater => thenode.right.insert(thevalue)
            }
        }
    }

    fn has(&self, thevalue: &T) -> bool {
        match &self.0 {
            None => false,
            Some(thenode) => match thevalue.cmp(&thenode.value) {
                Ordering::Less => thenode.left.has(thevalue),
                Ordering::Equal => true,
                Ordering::Greater => thenode.right.has(thevalue)
            }
        }
        
    }

    fn len(&self) -> usize {
        match &self.0 {
            None => 0,
            Some(thenode) => 1 + thenode.left.len() + thenode.right.len()
        }
    }

    fn inorder(&self) {

        if let Some(thenode) = &self.0 {
            thenode.left.inorder();
            println!("node: {:?}", thenode.value);
            thenode.right.inorder();
}
    }
}

pub fn main() {
    let mut tree = BinaryTree::new();
    tree.insert("foo".to_string());
    assert_eq!(tree.len(), 1);
    tree.insert("bar".to_string());
    assert!(tree.has(&"foo".to_string()));

    println!("MAIN TREE INORDER");
    tree.inorder();
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn len() {
        let mut tree = BinaryTree::new();
        assert_eq!(tree.len(), 0);
        tree.insert(2);
        assert_eq!(tree.len(), 1);
        tree.insert(1);
        assert_eq!(tree.len(), 2);
        tree.insert(2); // not a unique item
        assert_eq!(tree.len(), 2);

        println!("LEN TEST TREE INORDER");
        tree.inorder();
    }

    #[test]
    fn has() {
        let mut tree = BinaryTree::new();
        fn check_has(tree: &BinaryTree<i32>, exp: &[bool]) {
            let got: Vec<bool> =
                (0..exp.len()).map(|i| tree.has(&(i as i32))).collect();
            assert_eq!(&got, exp);
        }

        check_has(&tree, &[false, false, false, false, false]);
        tree.insert(0);
        check_has(&tree, &[true, false, false, false, false]);
        tree.insert(4);
        check_has(&tree, &[true, false, false, false, true]);
        tree.insert(4);
        check_has(&tree, &[true, false, false, false, true]);
        tree.insert(3);
        check_has(&tree, &[true, false, false, true, true]);

        println!("HAS TEST TREE INORDER");
        tree.inorder();
    }

    #[test]
    fn unbalanced() {
        let mut tree = BinaryTree::new();
        for i in 0..100 {
            tree.insert(i);
        }
        assert_eq!(tree.len(), 100);
        assert!(tree.has(&50));

        println!("UNBALANCED TEST TREE INORDER");
        tree.inorder();
    }

    #[test]
    fn mytest() {
        let mut rng = ChaCha8Rng::seed_from_u64(42);
        let mut tree = BinaryTree::new();
        const mycount: usize = 30;
        for i in 0..mycount {
            let random_i32 = rng.gen_range(-100..100); // Generates a random i32
            tree.insert(random_i32);
        }
        // won't work in general since duplicates
        // assert_eq!(tree.len(), mycount);

        println!("MYTEST TEST TREE INORDER");
        tree.inorder();
    }


}
