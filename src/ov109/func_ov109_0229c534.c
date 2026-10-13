/* func_ov109_0229c534 @ 0x0229c534, 0x30 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov109_0229c678(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov109_0229c534(void *self)
{
    *(unsigned char *) ((char *) self + 0x29d7) = 1;
    func_ov109_0229c678(self);
    func_ov002_022096d8((char *) self + 0x22d8, 0);
    func_ov002_02208098(self, 0xd);
}
