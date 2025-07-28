
#if defined(VERY_BASIC)

// In the ISR
void my_isr(int irq, void *dev_id) {
    // 1. Acknowledge interrupt (hardware-specific)

    // 2. Read critical data (if needed)
    unsigned char data = read_from_hardware();

    // 3. Schedule a tasklet (softirq context: same cpu as isr, can't sleep)
    tasklet_schedule(&my_tasklet); // my_tasklet does the real work

    // could also use:
    // atomic variable or 
    // spin lock, including spin lock variants that disable (and re-enable) interrupts
    // workqueue (process context, possibly different cpu than isr, can sleep)
    // wake of kernel thread (similar to workqueue, process context, etc.)
}

// The tasklet function (runs later, in a safe context)
void my_tasklet_function(unsigned long data) {
    // Process the data here (can use mutexes, etc., as it's not an ISR)
    // ...
}

#elif defined(WAKE_KERNEL_THREAD)


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/kthread.h>

static struct task_struct *my_kernel_thread;
static wait_queue_head_t my_wait_queue;
static int my_data; // Data shared between ISR and thread
static int irq_number = 10; // Replace with your actual IRQ number

// Kernel thread function
static int my_thread_function(void *data) {
    while (1) {
        wait_event_interruptible(my_wait_queue, my_data != 0); // Sleep until data is set

        // Do the actual processing here
        printk(KERN_INFO "Kernel thread: Processing data %d\n", my_data);
        my_data = 0; // Reset data
    }
    return 0;
}

// ISR
static irqreturn_t my_isr(int irq, void *dev_id) {
    // 1. Acknowledge the interrupt (hardware-specific)
    // ...

    // 2. Read critical data (if necessary)
    my_data = read_from_hardware(); // Or whatever data needs to be processed

    // 3. Wake up the kernel thread
    wake_up_interruptible(&my_wait_queue);

    return IRQ_HANDLED;
}

// Module initialization
static int __init my_module_init(void) {
    // Initialize the wait queue
    init_waitqueue_head(&my_wait_queue);

    // Create the kernel thread
    my_kernel_thread = kthread_run(my_thread_function, NULL, "my_kernel_thread");
    if (my_kernel_thread == ERR_PTR(-ENOMEM)) {
        printk(KERN_ERR "Failed to create kernel thread\n");
        return -ENOMEM;
    }

    // Request the IRQ
    if (request_irq(irq_number, my_isr, IRQF_SHARED, "my_device", NULL)) {
        printk(KERN_ERR "Failed to request IRQ\n");
        kthread_stop(my_kernel_thread);
        return -EBUSY;
    }

    printk(KERN_INFO "Module loaded\n");
    return 0;
}

// Module exit
static void __exit my_module_exit(void) {
    // Free the IRQ
    free_irq(irq_number, NULL);

    // Stop the kernel thread
    if (my_kernel_thread) {
        kthread_stop(my_kernel_thread);
    }

    printk(KERN_INFO "Module unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");

#elif defined(SYSCALL_EXAMPLE)

// Kernel (driver)
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    if (cmd == MY_IOCTL_COMMAND) {
        int kernel_data;
        if (copy_from_user((int *)arg, &kernel_data, sizeof(int))) {
            return -EFAULT; // Bad user pointer
        }
        // ... use kernel_data ...
    }
    return 0;
}

// User Space
int user_data = 10;
ioctl(fd, MY_IOCTL_COMMAND, &user_data); // Send data to kernel

#elif defined(NESTED_INTS)

// Shared data
static spinlock_t my_lock;
static int shared_variable;

// ISR
static irqreturn_t my_isr(int irq, void *dev_id) {
    unsigned long flags; // For spin_lock_irqsave()
    spin_lock_irqsave(&my_lock, flags); // Disable interrupts and acquire lock

    // Access shared_variable here (protected by the spinlock)
    shared_variable++;

    spin_unlock_irqrestore(&my_lock, flags); // Re-enable interrupts and release lock
    return IRQ_HANDLED;
}

// Other kernel code
void my_kernel_function(void) {
    unsigned long flags;
    spin_lock_irqsave(&my_lock, flags); // Protect access to shared_variable

    // ... use shared_variable ...

    spin_unlock_irqrestore(&my_lock, flags);
}

#elif defined(DIFFERENT_SPINLOCKS)

spinlock_t my_lock;
int shared_variable;

// ISR
irqreturn_t my_isr(int irq, void *dev_id) {
    unsigned long flags;
    spin_lock_irqsave(&my_lock, flags); // Use _irqsave

    shared_variable++; // Access shared data

    spin_unlock_irqrestore(&my_lock, flags); // Use _irqrestore
    return IRQ_HANDLED;
}

// Kernel Thread
void my_kernel_thread(void) {
    unsigned long flags;
    spin_lock_irqsave(&my_lock, flags); // Use _irqsave

    shared_variable = 0; // Access shared data

    spin_unlock_irqrestore(&my_lock, flags); // Use _irqrestore
}

#endif
