/* func_ov140_0229ae74 @ 0x0229ae74, 0x44 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9c];
    int unk_9C;
} UnkStruct_0229ae74;

extern int func_ov140_02299fb0(UnkStruct_0229ae74 *p, int a);
extern void func_0206fc4c(int arg);
extern void func_0206fc80(int arg);
extern void func_0206f7c8(void);
extern void func_020ee470(UnkStruct_0229ae74 *p);

int func_ov140_0229ae74(UnkStruct_0229ae74 *p)
{
    if (func_ov140_02299fb0(p, 2) != 0) {
        func_0206fc4c(0);
    } else {
        func_0206fc4c(1);
        func_0206fc80(*(unsigned char *) ((char *) p + p->unk_9C + 0x8d5));
    }
    func_0206f7c8();
    func_020ee470(p);
    return 1;
}
