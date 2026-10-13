/* func_ov070_02278ab8 @ 0x02278ab8, 0xac bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_020160b4(void *p);
extern int func_020ab504(int x);
extern int func_ov070_02279724(void *a, void *b, int n);
extern void MI_CpuFill8(void *dest, int val, int size);
extern void func_0202ea80(int a, int b);
extern int func_0209a1e8(void);
extern void func_0206844c(void *a, void *b, void *c);
extern unsigned char data_ov070_02279d58[];
typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x21];
    void *unk_40;
    unsigned char pad_44[0x70];
    unsigned char *unk_B4;
} UnkStruct_02278ab8;
void func_ov070_02278ab8(UnkStruct_02278ab8 *p)
{
    int r4 = func_020ab504(func_020160b4(p));
    unsigned char *data = data_ov070_02279d58;
    unsigned char result = 0xff;
    if (((int) p->unk_1E >= 15) && ((int) p->unk_1E < 35)) {
        if (p->unk_B4[0x738] < 5) {
            unsigned long ret = func_ov070_02279724(p->unk_B4, p->unk_B4 + 0x724, 20);
            if (p->unk_B4[0x724 + ret] == 0) {
                p->unk_B4[0x724 + ret] = 1;
            }
            result = (unsigned char) (ret + 15);
        } else {
            MI_CpuFill8(p->unk_B4 + 0x724, 0, 20);
            func_0202ea80(8, 1);
            result = 0x23;
        }
    }
    if (p->unk_1E == 9) {
        if (r4 == 0) {
            int v = func_0209a1e8();
            if (v != (-1)) {
                result = 11;
            } else {
                result = 12;
            }
        }
    }
    if (result != 0xff) {
        unsigned char b = result;
        func_0206844c(p->unk_40, &b, data);
    }
}
