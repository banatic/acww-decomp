/* func_02035b38 @ 0x02035b38, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02035b38 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10;
} UnkStruct_02035b38;

typedef struct UnkStruct_02035b38_2 {
    unsigned short a;
    unsigned short b;
} UnkStruct_02035b38_2;

extern unsigned char data_020e54a8;
extern int func_020b6660(void);
extern void func_02095764(UnkStruct_02035b38_2 *p, int n);
extern int func_0204bcdc(UnkStruct_02035b38_2 *p);
extern int func_0204bc64(unsigned short *p);
extern void func_02035624(int n);

void func_02035b38(UnkStruct_02035b38 *p)
{
    UnkStruct_02035b38_2 buf;
    int v;

    if (p->unk_0C > 0) {
        p->unk_0C = p->unk_0C - 1;
        if (p->unk_0C <= 0) {
            int on;
            v = 1;
            on = data_020e54a8 ? 0 : 1;
            if (on != 0 && func_020b6660()) {
                int ok;
                func_02095764(&buf, 4);
                if (func_0204bcdc(&buf)) {
                    buf.b = 0xfff1;
                    ok = func_0204bc64(&buf.a) == func_0204bc64(&buf.b) ? 1 : 0;
                } else {
                    ok = buf.a == 0xfff1 ? 1 : 0;
                }
                if (ok == 0) {
                    v = 0x14;
                }
            }
            p->unk_10 = v;
        }
    }
    if (p->unk_10 > 0) {
        p->unk_10 = p->unk_10 - 1;
        if (p->unk_10 <= 0) {
            func_02035624(7);
        }
    }
}
