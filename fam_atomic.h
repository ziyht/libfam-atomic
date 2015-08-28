#ifndef _FAM_ATOMIC_H_
#define _FAM_ATOMIC_H_

/*
 * fam-atomic operations: Atomic across all SOCs on the system
 * and different cache coherence domains. fam-atomic variables
 * should be in their own cacheline and should not share cachelines
 * with non fam-atomic data.
 */
#include <stdint.h>

/*
 * fam-atomic data types
 * ----------------------
 * struct fam_atomic_32 - 32 bit fam-atomic type
 * struct fam_atomic_64 - 64 bit fam-atomic type
 * struct fam_atomic_128 - 128 bit fam-atomic type
 */
struct fam_atomic_32 {
	int32_t __v__ __attribute__((__aligned__(64)));
};

struct fam_atomic_64 {
	int64_t __v__ __attribute__((__aligned__(64)));
};

struct fam_atomic_128 {
	int64_t __v__[2] __attribute__((__aligned__(64)));
};

/*
 * fam_atomic_register_region() - Registers an NVM region which
 * contains fam-atomics. Must register an NVM region as an
 * fam-atomic region before any fam-atomic within the region
 * can be used.
 *
 * @region_start: Address of the start of the NVM region.
 * @region_length: The length of the NVM region.
 * @fd: The file descriptor associated with the NVM region.
 * @offset: The offset from the start of the file.
 *	    (If address, is the start of the file, then offset can be 0.
 */
extern int
fam_atomic_register_region(void *region_start,
		    size_t region_length,
		    int fd,
		    off_t offset);

extern void
fam_atomic_unregister_region(void *region_start,
			     size_t region_length);

/*
 * Returns the value of the atomic variable.
 *
 * @address: Pointer to an fam-atomic variable.
 */
extern int32_t
fam_atomic_32_read(struct fam_atomic_32 *address);

extern int64_t
fam_atomic_64_read(struct fam_atomic_64 *address);

extern void
fam_atomic_128_read(struct fam_atomic_128 *address,
		    int64_t result[2]);

/*
 * Writes "value" to the atomic variable.
 *
 * @address: Pointer to an fam-atomic variable.
 * @value: The value that will be written to the atomic.
 */
extern void
fam_atomic_32_write(struct fam_atomic_32 *address,
		    int32_t value);

extern void
fam_atomic_64_write(struct fam_atomic_64 *address,
		    int64_t value);

extern void
fam_atomic_128_write(struct fam_atomic_128 *address,
		     int64_t value[2]);

/*
 * Atomically writes "value" to the atomic variable and returns
 * the previous value of the atomic variable.
 *
 * @address: Pointer to an fam-atomic variable.
 * @value: The new value that will be written to the atomic.
 */
extern int32_t
fam_atomic_32_swap(struct fam_atomic_32 *address,
		   int32_t value);

extern int64_t
fam_atomic_64_swap(struct fam_atomic_64 *address,
		   int64_t value);

extern void
fam_atomic_128_swap(struct fam_atomic_128 *address,
		    int64_t value[2],
		    int64_t result[2]);

/*
 * Atomically checks if the atomic variable is equal to "expected"
 * and sets the atomic to "desired" if true. Returns 1 if the operations
 * succeeded in modifying the atomic, else returns 0.
 *
 * @address: Pointer to an fam-atomic variable.
 * @expected: The value which the atomic is expected to equal.
 * @desired: The value the atomic will be set to if equal to "expected".
 */
extern int32_t
fam_atomic_32_compare_and_store(struct fam_atomic_32 *address,
				int32_t expected,
				int32_t desired);

extern int64_t
fam_atomic_64_compare_and_store(struct fam_atomic_64 *address,
				int64_t expected,
				int64_t desired);

extern void
fam_atomic_128_compare_and_store(struct fam_atomic_128 *address,
				 int64_t expected[2],
				 int64_t desired[2]);

/*
 * Atomically adds "increment" to the atomic variable and returns the
 * previous value of the atomic.
 *
 * @address: Pointer to an fam-atomic variable.
 * @increment: The value which will be added to the atomic.
 */
extern int32_t
fam_atomic_32_fetch_and_add(struct fam_atomic_32 *address,
			    int32_t increment);

extern int64_t
fam_atomic_64_fetch_and_add(struct fam_atomic_64 *address,
			    int64_t increment);

/*
 * The following are the unpadded variant of the fam-atomics. Users of
 * the atomics below must manually keep the fam-atomic variables in their
 * own cachelines so that they do not share cachelines with regular data.
 * This is required to ensure the correctness of the atomic data.
 */
extern int32_t
fam_atomic_32_read_unpadded(int32_t *address);

extern int64_t
fam_atomic_64_read_unpadded(int64_t *address);

extern void
fam_atomic_128_read_unpadded(int64_t *address,
			     int64_t result[2]);

extern void
fam_atomic_32_write_unpadded(int32_t *address,
			     int32_t value);

extern void
fam_atomic_64_write_unpadded(int64_t *address,
			     int64_t value);

extern void
fam_atomic_128_write_unpadded(int64_t *address,
			      int64_t value[2]);

extern int32_t
fam_atomic_32_swap_unpadded(int32_t *address,
			    int32_t value);

extern int64_t
fam_atomic_64_swap_unpadded(int64_t *address,
			    int64_t value);

extern void
fam_atomic_128_swap_unpadded(int64_t *address,
			     int64_t value[2],
			     int64_t result[2]);

extern int32_t
fam_atomic_32_compare_and_store_unpadded(int32_t *address,
					 int32_t expected,
					 int32_t desired);

extern int64_t
fam_atomic_64_compare_and_store_unpadded(int64_t *address,
					 int64_t expected,
					 int64_t desired);

extern void
fam_atomic_128_compare_and_store_unpadded(int64_t *address,
					  int64_t compare[2],
					  int64_t result[2]);

extern int32_t
fam_atomic_32_fetch_and_add_unpadded(int32_t *address,
				     int32_t increment);

extern int64_t
fam_atomic_64_fetch_and_add_unpadded(int64_t *address,
				     int64_t increment);
#endif