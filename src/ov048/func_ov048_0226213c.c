/* func_ov048_0226213c @ 0x0226213c, 0x64 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x810 - 0x44];
    unsigned char unk_810;
} UnkStruct_0226213c;

extern void func_020984e8(int _x);
extern void func_02099664(void);
extern void func_02077bcc(void);
extern unsigned long long func_020eb694(void);
extern void func_ov048_02262588(void *p, unsigned int low, unsigned int high);
extern void func_0206844c(void *dst, void *src, unsigned int info);
extern int func_ov048_02260a60(void);
extern unsigned int data_ov048_02263d20;

void func_ov048_0226213c(UnkStruct_0226213c *p)
{
    unsigned char local[8];
    unsigned long long ret;
    unsigned int low, high;

    if (p->unk_810) {
        func_020984e8(ret);
        func_02099664();
        func_02077bcc();
        ret = func_020eb694();
        low = (unsigned int) ret;
        high = (unsigned int) (ret >> 32);
        func_ov048_02262588(p, low, high);
        local[0] = 0x76;
        func_0206844c(p->unk_40, &local[0], data_ov048_02263d20);
    } else {
        local[1] = (unsigned char) func_ov048_02260a60();
        func_0206844c(p->unk_40, &local[1], data_ov048_02263d20);
    }
}