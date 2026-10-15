/* func_020259a8 @ 0x020259a8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fc8c(void);
extern void func_0209a088(void *, int, int);
extern int func_02015094(void *);
typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_020259a8;
extern UnkStruct_020259a8 data_020d8f28;
extern void func_0202dbf0(void *, UnkStruct_020259a8);

void func_020259a8(void *param)
{
    unsigned short buf[2];
    int x;
    x = func_0206fc8c();
    buf[0] = 0xfff1;
    func_0209a088(buf, 0, x);
    func_02015094(param);
    func_0202dbf0(param, data_020d8f28);
}
