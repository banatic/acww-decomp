/* func_0209e234 @ 0x0209e234, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char unk_00;
    unsigned char unk_01;
} UnkStruct_0209e234;

extern void func_0209e268(UnkStruct_0209e234 *p, int n);

void func_0209e234(UnkStruct_0209e234 *p, int n)
{
    int val = p->unk_01 + n;
    if (val >= 60) {
        func_0209e268(p, val / 60);
        val = val % 60;
    }
    p->unk_01 = (unsigned char) val;
}
