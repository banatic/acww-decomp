/* func_020b4a20 @ 0x020b4a20, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b4a20 {
    char pad_00[0x1e];
    unsigned char flag;
    char pad_1F[5];
    int value;
    char pad_28[8];
};

extern int data_021f4dac;
extern void func_020b4044(struct UnkStruct_020b4a20 *p);
extern void func_020a8164(struct UnkStruct_020b4a20 *p, int p3);
extern void func_020b43f4(int *g);
extern int func_020b4344(int *g, struct UnkStruct_020b4a20 *p);
extern void func_020b402c(struct UnkStruct_020b4a20 *p);

int func_020b4a20(int p1, unsigned char *p2, int p3)
{
    struct UnkStruct_020b4a20 local;
    int result;
    func_020b4044(&local);
    func_020a8164(&local, p3);
    local.flag = *p2;
    local.value = p1;
    func_020b43f4(&data_021f4dac);
    result = func_020b4344(&data_021f4dac, &local);
    func_020b402c(&local);
    return result;
}
