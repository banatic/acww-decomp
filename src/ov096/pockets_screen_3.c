/* pockets_screen_3: 3 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229d508 @ 0x0229d508, 0x68 bytes, Thumb
 * func_ov096_0229d4f0 @ 0x0229d4f0, 0x16 bytes, Thumb
 * func_ov096_0229d4d4 @ 0x0229d4d4, 0x1c bytes, Thumb
 */

typedef struct UnkStruct_0229d508 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0229d508;

extern int func_02073d90(void *);
extern int func_0208b500(void);
extern int func_0208d12c(void *argument0);
extern void func_0207055c(unsigned char, int);
extern void func_02070490(int);
extern UnkStruct_0229d508 *data_020ccf94;
extern void func_ov096_0229fb9c(int);

void func_ov096_0229d508(void *a1, int a2)
{
    UnkStruct_0229d508 *p;
    int flag;

    p = data_020ccf94;
    if (func_02073d90(p)) {
        if (p->unk_64 == 0) {
            flag = (a2 == 0) ? 1 : 0;

            if (flag != func_0208d12c((void *) func_0208b500())) {
                func_0207055c((unsigned char) (a2 + 0x12), 4);
                func_02070490(a2);
            }
        } else {
            func_0207055c((unsigned char) (a2 + 0xd), 0);
        }
    } else {
        func_02070490(a2);
    }
}

void func_ov096_0229d4f0(int r0)
{
    int r4 = r0;
    func_ov096_0229d508((void *) r4, 0);
    func_ov096_0229fb9c(r4);
}

void func_ov096_0229d4d4(void *p)
{
    func_ov096_0229d508(p, ((unsigned char *) p)[0xbb] - 0x1c);
    func_ov096_0229fb9c((int) p);
}
