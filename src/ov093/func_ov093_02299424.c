/* func_ov093_02299424 @ 0x02299424, 0x6c bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[5];
    char unk_05;
    char unk_06;
    char pad_07[5];
    unsigned int unk_0C;
} UnkStruct_02299424;

extern void func_0200277c(int);
extern unsigned char func_02001b60(void);
extern void func_02001bb4(int);
extern void func_02001da0(int);
extern void func_02001d1c(int);
extern void func_02002808(int, int, int, int, int);
extern void func_0200284c(int, int, int);

void func_ov093_02299424(UnkStruct_02299424 *s)
{
    int val;

    func_0200277c(0);
    val = func_02001b60();
    *(volatile unsigned int *) 0x04000000 = (*(volatile unsigned int *) 0x04000000 & 0xffffe0ff) | (val << 8);
    func_02001bb4(1);
    func_02001da0(0x1f);
    func_02001d1c(0x1d);
    func_02002808(0, 0, 0x78, 0xfe, 0xbf);
    func_0200284c(0, 0, ~0x77);
    s->unk_05 = 4;
    s->unk_06 = 0;
    s->unk_0C = 0xfff88000;
}
