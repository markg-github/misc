
#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<std::string> message = std::make_unique<std::string>("Hello, unique_ptr!");
    std::cout << *message << std::endl;
    
    // Transfer ownership
    std::unique_ptr<std::string> another_message = std::move(message);
    std::cout << *another_message << std::endl;
    // message is now null

    // core dump
    // std::cout << *message << std::endl;

    std::shared_ptr<int> shared1 = std::make_shared<int>(42);
    std::shared_ptr<int> shared2 = shared1;

    std::cout << *shared1 << " " << *shared2 << std::endl;

    std::shared_ptr<int> shared = std::make_shared<int>(99);
    std::weak_ptr<int> weak = shared;

    // check if resource still exists
    if (std::shared_ptr<int> ptr = weak.lock()) {
        std::cout << *ptr << std::endl;
    }
    else {
        std::cout << "Resource has been deleted." << std::endl;
    }

    int main2(void);

    main2();

    return 0;
    
}

std::unique_ptr<int> createUniquePtr() {
    return std::make_unique<int>(123);
}

int main2() {
    std::unique_ptr<int> ptr1 = createUniquePtr();      // ptr1 owns the resource returned from the function.
    std::cout << *ptr1 << std::endl;        // Output: 123

    // Transfer ownership (within same scope).
    // It would be a compilation error without std::move.
    std::unique_ptr<int> ptr2 = std::move(ptr1);
    std::cout << *ptr2 << std::endl;        // Output: 123

    // ptr1 is now null
    if (ptr1) {
        std::cout << "ptr1 still owns a resource" << std::endl;
    }
    else {
        std::cout << "prt1 is null" << std::endl;
    }

    return 0;
}

