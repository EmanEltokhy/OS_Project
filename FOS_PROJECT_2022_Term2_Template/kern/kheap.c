#include <inc/memlayout.h>
#include <kern/kheap.h>
#include <kern/memory_manager.h>

//2022: NOTE: All kernel heap allocations are multiples of PAGE_SIZE (4KB)
int frames = (KERNEL_HEAP_MAX - KERNEL_HEAP_START)/PAGE_SIZE;
char* Last_Allocation = (char*)KERNEL_HEAP_START;
int heap_page_table[1024];

void* kmalloc(unsigned int size)
{
	void* ret;
	int page_count = (size / PAGE_SIZE) + (size % PAGE_SIZE != 0);
	int page_number = (Last_Allocation - (char*)KERNEL_HEAP_START) / PAGE_SIZE;
	if(page_count+1 < frames){
		ret = (void*)Last_Allocation;
		while(page_count != 0)
		{
			if(Last_Allocation > (char*)KERNEL_HEAP_MAX)
			{
				Last_Allocation = (char*)KERNEL_HEAP_START;
				page_number = 0;
			}
			if((((char*)KERNEL_HEAP_MAX - Last_Allocation) / PAGE_SIZE) < page_count)
			{
				Last_Allocation = (char*)KERNEL_HEAP_START;
				page_number = 0;
			}
			if(heap_page_table[page_number] == 0)
			{
				struct Frame_Info* x;
				allocate_frame(&x);
				heap_page_table[page_number] = to_physical_address(x);
				map_frame(ptr_page_directory,x,Last_Allocation,PERM_WRITEABLE);
				Last_Allocation+=PAGE_SIZE;
				page_number++;
				frames--;
				page_count--;
			}
			else if(frames == 0)
				return NULL;
			else
				page_number++;
		}
		return ret;
	}
	else
		return 0;
	return NULL;



}

void kfree(void* virtual_address)
{
	//TODO: [PROJECT 2022 - [2] Kernel Heap] kfree()
	// Write your code here, remove the panic and write your code
	panic("kfree() is not implemented yet...!!");

	//you need to get the size of the given allocation using its address
	//refer to the project presentation and documentation for details

}

unsigned int kheap_virtual_address(unsigned int physical_address)
{
	//TODO: [PROJECT 2022 - [3] Kernel Heap] kheap_virtual_address()
	// Write your code here, remove the panic and write your code
	panic("kheap_virtual_address() is not implemented yet...!!");

	//return the virtual address corresponding to given physical_address
	//refer to the project presentation and documentation for details

	//change this "return" according to your answer

	return 0;
}

unsigned int kheap_physical_address(unsigned int virtual_address)
{
	//TODO: [PROJECT 2022 - [4] Kernel Heap] kheap_physical_address()
	// Write your code here, remove the panic and write your code
	panic("kheap_physical_address() is not implemented yet...!!");

	//return the physical address corresponding to given virtual_address
	//refer to the project presentation and documentation for details

	//change this "return" according to your answer
	return 0;
}

