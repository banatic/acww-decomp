/* func_ov096_0229d93c @ 0x0229d93c, 0x64 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f55c(void);
extern void func_ov096_0229fb9c(void *);
extern void func_ov096_0229f874(void *, int, int, int);
extern int func_ov096_0229f088(void *, unsigned char);
extern int func_ov096_0229f0dc(void *, unsigned char);
extern void func_ov096_0229f5ac(void *, unsigned char);
extern int func_ov096_0229f8cc(void *, unsigned char, int, int, int);

typedef struct {
    char pad_00[0xB6];
    unsigned char unk_B6;
} UnkStruct_0229d93c;

void func_ov096_0229d93c(UnkStruct_0229d93c *ptr)
{
    int rv;

    rv = func_ov096_0229f55c();
    if (rv == 0x26) {
        func_ov096_0229fb9c(ptr);
        func_ov096_0229f874(ptr, 0xb, 0xff, 1);
        return;
    } else {
        int r4;
        int r7;

        r4 = func_ov096_0229f088(ptr, ptr->unk_B6);
        r7 = func_ov096_0229f0dc(ptr, ptr->unk_B6);
        func_ov096_0229f5ac(ptr, ptr->unk_B6);
        func_ov096_0229f8cc(ptr, ptr->unk_B6, rv, r7, r4);
    }
}
