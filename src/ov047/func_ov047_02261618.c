/* func_ov047_02261618 @ 0x02261618, 0x9c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(const void *ptr);
extern int func_0204bc64(const void *ptr);
extern int func_020984e8(void);
extern void func_02071110(const void *a, const void *b);
extern void func_0209f128(const void *a, unsigned int b);
extern void func_02098ff8(int a, int b);
extern void func_0209a050(void);

struct UnkStruct_02261618 {
    unsigned char pad_00[0xc8];
    int unk_C8;
    unsigned char pad_CC[2];
    unsigned short unk_CE;
};

extern unsigned char data_021dc7a8[];
extern unsigned char data_021f38f8[];

void func_ov047_02261618(struct UnkStruct_02261618 *p)
{
    int flag;

    if (func_0204bcdc(&p->unk_CE) != 0) {
        unsigned short local = 0xfff1;
        int a = func_0204bc64(&p->unk_CE);
        int b = func_0204bc64(&local);
        flag = (a == b) ? 1 : 0;
    } else {
        flag = (p->unk_CE == 0xfff1) ? 1 : 0;
    }

    if (flag != 0) {
        return;
    } else {
        int ret = func_020984e8();
        func_02071110((const void *) data_021f38f8, &p->unk_CE);
        func_0209f128((const void *) data_021dc7a8, 0xc);
        func_02098ff8(ret, 8);

        if (p->unk_C8 >= 0) {
            func_0209a050();
            p->unk_C8 = -1;
        }
        p->unk_CE = 0xfff1;
    }
}
