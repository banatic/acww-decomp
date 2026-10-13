/* func_ov004_02235728 @ 0x02235728, 0xe8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_ov004_02235a18(void *, void *);
struct Entry {
    unsigned char value;
    unsigned char rest[16];
};
extern "C" {
extern Entry data_ov004_02247924[];
}
static inline void mark(unsigned int *bits, int id)
{
    bits[id >> 5] |= 1u << (id & 31);
}
static inline void select(unsigned char **slot, int id, int flags)
{
    (*slot)[0x1ea] = flags;
    (*slot)[0x1e8] = id;
    (*slot)[0x1c9] = 0;
}
extern "C" void func_ov004_02235728(void *unused, unsigned char **slot, unsigned char **other)
{
    ++(*slot)[0x1f1];
    // Spill slots in the original order.
    int previous;
    int own;
    own = *(int *) (*slot + 0x15c);
    previous = (*slot)[0x1e8];
    int next = *(int *) (*other + 0x15c);
    int added = func_ov004_02235a18(*slot, other);
    int flags = (*slot)[0x1ea];
    mark((unsigned int *) (*slot + 0x1f4), next);
    if (previous == own) {
        select(slot, next, added | flags);
    } else if (data_ov004_02247924[previous].value < data_ov004_02247924[next].value) {
        select(slot, next, added | flags);
    } else if (data_ov004_02247924[previous].value == data_ov004_02247924[next].value && flags < added) {
        select(slot, next, added | flags);
    }
}
