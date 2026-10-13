/* func_ov094_0229b950 @ 0x0229b950, 0x3a bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    unsigned char unk_24;
    unsigned char unk_25;
} UnkStruct_0229b950;

extern int func_ov094_0229b788(UnkStruct_0229b950 *p, unsigned char c);
extern void func_ov094_0229b98c(UnkStruct_0229b950 *p);

void func_ov094_0229b950(UnkStruct_0229b950 *p, int arg)
{
    if (func_ov094_0229b788(p, arg)) {
        func_ov094_0229b98c(p);
    } else {
        if (p->unk_24 != arg) {
            p->unk_24 = arg;
            p->unk_25 = 2;
        }
    }
}
