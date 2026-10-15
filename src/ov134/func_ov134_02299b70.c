/* func_ov134_02299b70 @ 0x02299b70, 0x28 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a574(void *);
extern void func_ov002_0220a4bc(void *receiver);

int func_ov134_02299b70(void *self)
{
    if (*(unsigned char *) ((char *) self + 0xb0) == 0) {
        func_ov002_0220a574((char *) self + 0x18);
        self = (void *) ((char *) self + 0x18);
        func_ov002_0220a4bc(self);
        return 1;
    }
    return 0;
}
