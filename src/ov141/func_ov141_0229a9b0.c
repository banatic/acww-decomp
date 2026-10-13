/* func_ov141_0229a9b0 @ 0x0229a9b0, 0x54 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov139_02299af8(void *p, int a, int b);
extern void func_ov141_02299f94(void *p, int a);

void func_ov141_0229a9b0(void *self)
{
    unsigned char *p;
    int i;

    *(unsigned short *) ((char *) self + 0x1a7c) = 0;
    func_ov139_02299af8((char *) self + 0x94, 6, 0x7e);

    for (i = 0; i < 6; i++) {
        *((unsigned char *) self + 0x1a7f + i) = 0;
    }

    func_ov141_02299f94(self, -1);
    *(int *) ((char *) self + 0x1278) = 8;
    *((unsigned char *) self + 0x1a8c) = 0;
}
