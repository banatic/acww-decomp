/* func_02059598 @ 0x02059598, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Data12 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};
struct PtrType {
    unsigned char pad_00[12];
    unsigned short type;
};
extern struct Data12 data_020cbb10;
extern struct Data12 data_020cbb1c;
extern struct Data12 data_020cbb28;
extern struct Data12 data_020cbb04;
void func_02059598(void *dst, char *base, int index)
{
    unsigned short type;
    void *ptr;
    type = 0xd8;
    ptr = *(void **) (base + (index << 2) + 0xcc);
    if (ptr) {
        type = ((struct PtrType *) ptr)->type;
    }
    if (type == 0x6b) {
        *(struct Data12 *) dst = data_020cbb10;
    } else if (type == 0x6a) {
        *(struct Data12 *) dst = data_020cbb1c;
    } else if (type == 0x76) {
        *(struct Data12 *) dst = data_020cbb28;
    } else {
        *(struct Data12 *) dst = data_020cbb04;
    }
}
