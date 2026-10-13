/* func_020a259c @ 0x020a259c, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a259c {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_020a259c *func_020682e0(int a);
extern void func_02068364(struct UnkStruct_020a259c *p, int b);

int func_020a259c(int a, int b)
{
    struct UnkStruct_020a259c *ptr;
    ptr = func_020682e0(0);
    if (ptr->unk_04 == 2) {
        if (b != 0) {
            func_02068364(ptr, 1);
        } else {
            func_02068364(ptr, 0);
        }
        return 1;
    } else {
        return 0;
    }
}
