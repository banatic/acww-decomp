/* func_020f3628 @ 0x020f3628, 0x58 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f4220(void *p1, void *p2, int n);
extern void func_020f41f4(void *obj);
extern void func_020f4178(void *obj);
extern void func_020f4130(void *obj);
extern void func_020f4038(void *obj);
extern void func_020eef70(void);
extern void NNS_SndHeapSaveState(void);
#define global1 ((char *) 0x0002a824)
extern struct global2_t {
    char pad_00[0x62];
    char flag;
} data_021fd1bc;

void func_020f3628(void *obj)
{
    func_020f4220(obj, global1, 10);
    func_020f41f4(obj);
    func_020f4178(obj);
    func_020f4130(obj);
    func_020f4038(obj);
    func_020eef70();
    NNS_SndHeapSaveState();
    data_021fd1bc.flag = 0;
}
