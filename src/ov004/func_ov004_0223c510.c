/* func_ov004_0223c510 @ 0x0223c510, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long a, b, c;
} UnkStruct_0223c510;
extern unsigned long data_ov004_022595cc;
extern UnkStruct_0223c510 data_ov004_0225964c;
extern int data_ov004_02259640;
extern void func_020012dc(void);
extern void __register_global_object(void *, void (*)(void), void *);
extern int func_ov004_0223c568(void *, int, UnkStruct_0223c510 *);
int func_ov004_0223c510(void *p0, int p1)
{
    if (!(data_ov004_022595cc & 1)) {
        data_ov004_0225964c.a = 0x2000;
        data_ov004_0225964c.b = 0;
        data_ov004_0225964c.c = 0;
        __register_global_object(&data_ov004_0225964c, func_020012dc, &data_ov004_02259640);
        data_ov004_022595cc |= 1;
    }
    return func_ov004_0223c568(p0, p1, &data_ov004_0225964c);
}
