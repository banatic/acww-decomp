/* func_ov130_0229a188 @ 0x0229a188, 0x54 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov130_0229a888[];
extern char *data_ov130_0229a8b4[];
extern char *data_ov130_0229a8e0[];

extern void func_0206fdd4(void *a, void *b, void *c, void *d, void *e, int f);
extern void func_ov130_022999a8(void *p, int n);

void func_ov130_0229a188(void *p, unsigned int index, int arg2)
{
    char *ptr1 = data_ov130_0229a888[index];
    char *ptr2 = data_ov130_0229a8b4[index];
    char *ptr3 = data_ov130_0229a8e0[index];
    char *ptr3_plus = ptr3 + 1;
    unsigned char b = *(unsigned char *) ((char *) p + 8);

    if (b == 0 || b == 2) {
        ptr1 += 8;
        ptr2 += 8;
    }
    func_0206fdd4((char *) p + 0xA90, ptr1, ptr3, ptr2, ptr3_plus, arg2);
    func_ov130_022999a8(p, 2);
}
