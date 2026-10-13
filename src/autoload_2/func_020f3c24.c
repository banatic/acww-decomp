/* func_020f3c24 @ 0x020f3c24, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *a, void *b, int c);
extern void func_020f41a4(void *a, int b);
extern void func_020f4080(void *a);
extern void func_020f4038(void *a);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
extern void func_020f1d84(void *a, int b);

#define gSomeData (*(int *) 0x00021ef8)
extern struct UnkStruct_020f3c24 {
    char pad_00[0x62];
    unsigned char unk_62;
} data_021fd1bc;

void func_020f3c24(void *ptr)
{
    func_020f4220(ptr, &gSomeData, 3);
    func_020f41a4(ptr, 2);
    func_020f4080(ptr);
    func_020f4038(ptr);
    func_020eef70();
    NNS_SndHeapSaveState();
    func_020f1d84(&data_021fd1bc, 0x8f);
    data_021fd1bc.unk_62 = 0;
}
