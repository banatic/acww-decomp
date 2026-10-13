/* func_0207d2b4 @ 0x0207d2b4, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003704(void);
extern void *func_0207f270(void *);
extern void *func_020984e8(void);
extern int func_02099870(void *);
extern int func_020951bc(void);
extern int func_02099020(void *, int);
extern int func_020807a8(void *, int);
extern int func_02081d20(void);
extern int func_020644cc(int);
extern void func_0208150c(void *, void *);

typedef struct {
    char pad_00[0x1e];
    unsigned char unk_1E;
} UnkStruct_0207d2b4;

void func_0207d2b4(void *a, void *b)
{
    UnkStruct_0207d2b4 *ptr;
    int c, d, e, val;

    func_0208150c(a, b);
    if (func_02003704() == 0) {
        goto end;
    }
    ptr = (UnkStruct_0207d2b4 *) func_0207f270(a);
    ptr->unk_1E = 0;
    if (b == 0) {
        b = func_020984e8();
    }
    if (b == 0) {
        goto end;
    }
    func_02099870(b);
    if (func_020951bc() == 0) {
        goto end;
    }
    if (func_02099020(b, 1) != 0) {
        goto end;
    }
    c = (int) func_02099870(b);
    if (func_020807a8(a, c) == 0) {
        goto end;
    }
    d = (int) func_02081d20();
    e = (int) func_020644cc(10);
    val = (d + 0x100) >> 7;
    val *= e + 1;
    if (val < 0) {
        val = 0;
    } else if (val > 32) {
        val = 32;
    }
    ptr->unk_1E = (unsigned char) val;
end:
    return;
}
