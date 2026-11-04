/* sound_point_3: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020f5134 @ 0x020f5134, 0x44 bytes, ARM
 * func_020f50e4 @ 0x020f50e4, 0x50 bytes, ARM
 */

struct UnkStruct_020f50e4 {
    unsigned int a;
    unsigned int b;
    unsigned int unk_08;
    unsigned int unk_0C;
};

extern int func_020f5e50(unsigned int *ptr, int n);
extern int func_020f5e24(int val);
extern int func_020f5c64(unsigned int *ptr, int n);
extern void NNS_SndPlayerSetVolume(unsigned int *ptr, int n);
extern void func_0210b634(unsigned int *ptr, int n1, int n2);

int func_020f5134(void *self)
{
    int r2;
    unsigned char r1;
    unsigned char r0;

    r1 = *(unsigned char *) ((char *) self + 0x1b);
    r2 = 0;
    if (r1 == 0) {
        if (*(int *) ((char *) self + 8) != 0) {
            r2 = 1;
        }
        if (r2 != 0) {
            r0 = *(unsigned char *) ((char *) self + 0x1a);
            if (r0 != 0) {
                r2 = 0;
            } else {
                r2 = 1;
            }
        } else {
            r2 = 1;
        }
    }
    return r2;
}

void func_020f50e4(struct UnkStruct_020f50e4 *p)
{
    int r5, r4;
    r5 = func_020f5e24(func_020f5e50(&p->unk_0C, 0));
    r4 = func_020f5c64(&p->unk_0C, 0);
    NNS_SndPlayerSetVolume(&p->unk_08, r5);
    func_0210b634(&p->unk_08, 0xff, r4);
}
