/* func_ov004_0223c4b8 @ 0x0223c4b8, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    long a, b, c;
} UnkStruct_0223c4b8;
extern unsigned long data_ov004_022595c8;
extern UnkStruct_0223c4b8 data_ov004_02259664;
extern int data_ov004_02259658;
extern void func_020012dc(void *object);
extern void __register_global_object(void *, void *destructor, void *);
extern int func_ov004_0223c568(void *, int, UnkStruct_0223c4b8 *);

int func_ov004_0223c4b8(void *p0, int p1)
{
    if (!(data_ov004_022595c8 & 1)) {
        data_ov004_02259664.a = 0xffffe000;
        data_ov004_02259664.b = 0;
        data_ov004_02259664.c = 0;
        __register_global_object(&data_ov004_02259664, ((void *) &func_020012dc), &data_ov004_02259658);
        data_ov004_022595c8 |= 1;
    }
    return func_ov004_0223c568(p0, p1, &data_ov004_02259664);
}
