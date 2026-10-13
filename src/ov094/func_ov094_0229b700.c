/* func_ov094_0229b700 @ 0x0229b700, 0x38 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b3f0(void *p1, int a, int b, int c, int d);

typedef struct {
    int unk_00;
    int unk_04;
} Struct_ov094_0229b700;

void func_ov094_0229b700(Struct_ov094_0229b700 *p1, int param2, int param3)
{
    int field = p1->unk_04;
    int count = 10;
    int i = 0;

    do {
        func_ov094_0229b3f0(p1, field, count, param2, param3);
        field += 256;
        count++;
        i++;
    } while (i < 25);
}
