/* func_ov068_02268020 @ 0x02268020, 0x84 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(const void *ptr, int val);
extern int func_02019de8(const void *ptr);
extern void func_02016638(const void *a, const void *b, const void *c, int d, int e);
extern void func_ov068_0226cce8(const void *a, const void *b, int c);

void func_ov068_02268020(void *p0, void *p1)
{
    if (func_020164a0((char *) p1 + 0x334, 0) == 0x12b || func_020164a0((char *) p1 + 0x334, 0) == 0x12a) {
        if (func_02019de8((char *) p1 + 0x564) == 0) {
            return;
        }
        *(unsigned int *) ((char *) p1 + 0x4e8) &= ~2;
        *((unsigned char *) p0 + 0x1c) = 5;
        func_02016638((char *) p1 + 0x334, p1, (char *) p1 + 0x9b4, 0, 3);
        func_ov068_0226cce8(p0, p1, 0);
    }
}
