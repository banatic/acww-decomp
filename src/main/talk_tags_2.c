/* talk_tags_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02069510 @ 0x02069510, 0x2 bytes, Thumb
 * func_02069508 @ 0x02069508, 0x8 bytes, Thumb
 * func_02069500 @ 0x02069500, 0x8 bytes, Thumb
 * func_020694f8 @ 0x020694f8, 0x8 bytes, Thumb
 * func_020694f0 @ 0x020694f0, 0x8 bytes, Thumb
 */

extern void func_0206b980(void);

void func_02069510(void *object) {}

void func_02069508(int p0)
{
    *(int *) ((char *) (((int) (p0) + (224))) + (0)) = 1;
}

void func_02069500(int p0)
{
    *(int *) ((char *) (((int) (p0) + (224))) + (0)) = 2;
}

void func_020694f8(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (217))) + (0)) = 1;
}

void func_020694f0(void)
{
    func_0206b980();
}
