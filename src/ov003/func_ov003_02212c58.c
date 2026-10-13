/* func_ov003_02212c58 @ 0x02212c58, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0204f818(int *, int *, int *);
extern void func_ov003_02212d04(void *, unsigned char, unsigned char, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

typedef struct {
    unsigned char pad_00[0x144];
    unsigned int unk_144;
    unsigned char unk_148;
    unsigned int unk_14C;
    unsigned char pad_150[4];
    unsigned int unk_154;
    unsigned int unk_158;
    unsigned char pad_15C[4];
    unsigned int unk_160;
} UnkStruct_02212c58;

int func_ov003_02212c58(UnkStruct_02212c58 *p0, int p1, int p2)
{
    struct {
        int a;
        int b;
        unsigned char buffer[12];
        unsigned char obj[16];
        int arr[3];
    } local;
    unsigned char *obj;
    int flag;

    func_0200e92c(local.buffer);
    obj = local.obj;

    func_0200e90c(local.buffer, 0x59, p1, p2);

    if (p0->unk_148 != 0) {
        int temp = p0->unk_160;
        local.arr[0] = p0->unk_158;
        local.arr[1] = 0;
        local.arr[2] = temp;
        flag = 1;
    } else {
        int temp = p0->unk_154;
        local.arr[0] = p0->unk_14C;
        local.arr[1] = 0;
        local.arr[2] = temp;
        flag = 0;
        if (p0->unk_144 != 0) {
            flag = 1;
        }
    }

    local.a = 0;
    local.b = 0;
    func_0204f818(&local.a, &local.b, local.arr);

    func_ov003_02212d04(obj, (unsigned char) local.a, (unsigned char) local.b, flag);

    {
        int ret = func_0200e894(p0, local.buffer);
        func_0200e91c(local.buffer);
        return ret;
    }
}
