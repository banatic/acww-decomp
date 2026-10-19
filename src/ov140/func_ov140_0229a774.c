/* func_ov140_0229a774 @ 0x0229a774, 0x38 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov140_02299f90(int, int);
extern void func_ov002_02208090(int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0200467c(int);

void func_ov140_0229a774(int r0)
{
    int r4 = r0;
    func_ov140_02299f90(r4, 2);
    *(int *) (r4 + 0xa0) = 0xa;
    *(char *) (r4 + 0x8db) = 5;
    func_ov002_02208090(r4, 3);
    func_ov002_02208098((void *) (r4), 5);
    func_0200467c(0x27);
}
