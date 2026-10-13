/* func_ov096_0229d8ec @ 0x0229d8ec, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a1e8(void);
extern void func_ov096_0229fb9c(void *p);
extern void func_ov096_0229f874(void *p, int a, int b, int c);
extern int func_0206fba8(int c);

typedef struct {
    char pad_00[0xb6];
    unsigned char unk_B6;
    unsigned char unk_B7;
    unsigned char unk_B8;
} UnkStruct_0229d8ec;

int func_ov096_0229d8ec(UnkStruct_0229d8ec *p)
{
    int r4 = func_0209a1e8();
    if (r4 == -1) {
        func_ov096_0229fb9c(p);
        func_ov096_0229f874(p, 2, 0xff, 1);
        return 0;
    } else {
        func_0206fba8(p->unk_B6);
        p->unk_B8 = p->unk_B6;
        p->unk_B6 = (unsigned char) (r4 + 0xf);
        return 1;
    }
}
