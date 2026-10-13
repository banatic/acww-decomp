/* func_0208b990 @ 0x0208b990, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208b954(void *p);

struct UnkStruct_0208b990 {
    unsigned char pad_00[0x80];
    unsigned char flag;
};

void func_0208b990(struct UnkStruct_0208b990 *p)
{
    if (p->flag != 0) {
        func_0208b954(p);
    }
}
