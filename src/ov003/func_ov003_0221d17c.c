/* func_ov003_0221d17c @ 0x0221d17c, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);

typedef struct {
    int unk_00;
    int w1;
} UnkStruct_0221d17c;
typedef struct {
    char pad_00[0x2b4];
    unsigned char unk_2B4;
} UnkStruct_0221d17c_2;

int func_ov003_0221d17c(UnkStruct_0221d17c_2 *p)
{
    UnkStruct_0221d17c s;
    int r;
    s.unk_00 = 0;
    s.w1 = 0;
    func_0209e474(&s);
    if (((unsigned char *) &s)[2] >= 6) {
        if (p->unk_2B4 < 6) {
            r = 0;
        } else {
            r = 1;
        }
    } else {
        r = 0;
    }
    return r;
}
