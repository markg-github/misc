
#include <vector>
#include <iostream>

// These would be needed more if there was a background task
// to keep empty slots between min and max. The idea would be
// to avoid the one case where you have to block: requesting a VM
// when there aren't any.
#define VM_MIN_HEADROOM     5
#define VM_MAX_HEADROOM     10

typedef int     VM;

// Poorly named. It's just isfree that's metadata. The VM
// represents the actual resource.
struct _metadata
{
    VM vm;
    bool isfree;
};

struct RM
{

    std::vector<_metadata> pool;
    // Keep this between low and high water marks.
    int empty_slots;

    RM() : empty_slots(0) {}

    void add_vm() {
        // pool.size just to get something interesting in the pool
        _metadata vm_meta = {(int) pool.size(), true};
        pool.push_back(vm_meta);
        empty_slots++;
    }
    VM get_vm() {
        VM ret;
        for (auto it = pool.begin(); it != pool.end(); ) {

            if (it->isfree) {
                it->isfree = false;
                ret = it->vm;
                empty_slots--;
                break;
            }
            it++;
        }
        // maintain headroom
        if (empty_slots < VM_MIN_HEADROOM) {
            add_vm();
        }
        

        return ret;

    }

    void release_vm(VM vm_) {
        for (auto it = pool.begin(); it != pool.end(); ) {
            _metadata vm = *it;
            if (vm_ == vm.vm && !vm.isfree) {
                if (empty_slots >= VM_MAX_HEADROOM) {
                    pool.erase(it);
                }
                else {
                    it->isfree = true;
                    empty_slots++;
                }
                break;
                
            }
            else {
                it++;
            }
        }
    }

    void print() {
        std::cout << "empty_slots = " << empty_slots << std::endl;
        std::cout << "size of pool = " << pool.size() << std::endl;

        for (auto it = pool.begin(); it != pool.end(); ) {
            std::cout << "vm = " << it->vm << std::endl;
            std::cout << "isfree = " << (it->isfree ? "true" : "false") << std::endl;
            it++;
        }
        puts("");

    }

};

int main()
{

    RM the_rm;
    the_rm.print();
    // maintain high water mark of VMs
    for (unsigned i = 0; i < VM_MIN_HEADROOM; i++) {
        the_rm.add_vm();
        the_rm.print();
    }

    // simulate "customer activity"
    VM vm1 = the_rm.get_vm();
    the_rm.print();
    VM vm2 = the_rm.get_vm();
    the_rm.print();
    VM vm3 = the_rm.get_vm();
    the_rm.print();
    the_rm.release_vm(vm2);
    the_rm.print();
    VM vm4 = the_rm.get_vm();
    the_rm.print();
    the_rm.release_vm(vm1);
    the_rm.print();
    the_rm.release_vm(vm4);
    the_rm.print();
    VM vm5 = the_rm.get_vm();
    the_rm.print();
    VM vm6 = the_rm.get_vm();
    the_rm.print();
    

}

