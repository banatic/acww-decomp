/* func_0204cb50 @ 0x0204cb50, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204cb90(int, int);
extern void func_0203fb80(int *, int *, int);
extern char func_0209dee8(void);
typedef struct {
    unsigned short unk_00;
    char unk_02;
    int unk_04;
    int unk_08;
} UnkStruct_0204cb50;
extern UnkStruct_0204cb50 *func_0204cc04(int);
int func_0204cb50(int a, int b)
{
    int r;
    UnkStruct_0204cb50 *p;

    r = func_0204cb90(a, b);
    if (r >= 0) {
        goto done;
    }
    r = func_0204cb90(a, 99);
    if (r < 0) {
        goto done;
    }
    p = func_0204cc04(r);
    p->unk_00 = (unsigned short) b;
    func_0203fb80(&p->unk_04, &p->unk_08, b);
    p->unk_02 = func_0209dee8();
done:
    return r;
}
