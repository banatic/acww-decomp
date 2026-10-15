/* func_02074958 @ 0x02074958, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the no-op 64-bit mask keeps val in r5 and ret in r4; without it the registers swap */

extern int func_020e9a3c(int, int);
extern unsigned int func_02073044(void);
extern int func_020ec4a8(void);
extern void func_020b8d6c(void);
extern void func_02073f00(void *);
typedef struct {
    char pad_00[0x74];
    unsigned char flag_0x74;
} UnkStruct_02074958;
extern UnkStruct_02074958 *data_020ccf94;
extern int data_021c9b30;
void func_02074958(void)
{
    int ret;
    int val;
    UnkStruct_02074958 *p;
    if (data_020ccf94->flag_0x74 == 0) {
        return;
    }
    val = data_021c9b30;
    ret = func_020e9a3c(val, 0x8000);
    ret = ret & 0xFFFFFFFFFFFFFFFFu;
    ((unsigned int) func_020e9a3c(val, ret | 0x2000), func_02073044());
    if (func_020ec4a8() == 0) {
        func_020b8d6c();
    }
    func_020e9a3c(val, ret);
    p = data_020ccf94;
    func_02073f00(p);
    p->flag_0x74 = 0;
}
