/* func_0206dba8 @ 0x0206dba8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8a70(void *a, int b, int c, int d);

void func_0206dba8(void *obj, int p2, int p3)
{
    func_020a8a70(obj, p2, 1, p3);
    ((unsigned char *) obj)[0x6c] = 1;
}
