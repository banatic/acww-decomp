/* func_020805bc @ 0x020805bc, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x80];
} UnkStruct_020805bc;

extern int func_02064294(void *s);
extern int func_02081edc(UnkStruct_020805bc *p);
extern void *func_02081d60(UnkStruct_020805bc *p);
extern int func_02081cd8(UnkStruct_020805bc *p);
extern int func_02081d20(UnkStruct_020805bc *p);
extern void *func_02081e10(UnkStruct_020805bc *p);
extern int func_0209e3ac(void *a, void *b, int k);
extern unsigned char data_021dc7aa[];
extern unsigned char data_021dc7bc[];

int func_020805bc(UnkStruct_020805bc *p, int (*cb)(void *, void *, void *))
{
    UnkStruct_020805bc *sel;
    int i;
    int best = -1;

    if (func_02064294(data_021dc7aa) != 0) {
        sel = 0;
        for (i = 0; i < 8; p++, i++) {
            if (func_02081edc(p) == 0) {
                continue;
            }
            if (cb(func_02081d60(p), data_021dc7aa, data_021dc7bc) == 0) {
                continue;
            }
            if (sel != 0) {
                if (func_02081cd8(sel) == func_02081cd8(p)) {
                    if (func_02081d20(sel) > func_02081d20(p)) {
                        sel = p;
                        best = i;
                    } else if (func_02081d20(sel) == func_02081d20(p)) {
                        if (func_0209e3ac(func_02081e10(sel), func_02081e10(p), 0x3f) == 1) {
                            sel = p;
                            best = i;
                        }
                    }
                } else if (func_02081cd8(p) == 0) {
                    sel = p;
                    best = i;
                }
            } else {
                sel = p;
                best = i;
            }
        }
    }
    return best;
}
