/* func_ov004_0223b004 @ 0x0223b004, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055124(void *);
extern void func_02055e64(void *);
extern int func_02056f94(void *);
typedef struct {
    long x, y, z;
} UnkStruct_0223b004;
int func_ov004_0223b004(char *self, unsigned char *flag, UnkStruct_0223b004 *out)
{
    if (*(unsigned char *) self != 0 && *flag != 0) {
        func_02055124(self + 0x2c);
        func_02055e64(self + 0x2c);
        out->x = *(long *) (self + 4);
        out->y = *(long *) (self + 8);
        out->z = *(long *) (self + 0xc);
        if (func_02056f94(self + 0xc8) != 0) {
            *flag = 0;
            *(unsigned char *) self = *flag;
            return 1;
        }
        return 0;
    }
    return 0;
}
