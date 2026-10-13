/* func_ov004_0223c8b4 @ 0x0223c8b4, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// 0x20 is loaded from the literal pool, so it is written as the address of g_00000020.
// The destructor of the local static object is registered with __register_global_object.
typedef struct {
    long a, b, c;
} UnkStruct_0223c8b4;
extern unsigned long data_ov004_022595dc;
extern UnkStruct_0223c8b4 data_ov004_02259628;
extern int data_ov004_0225961c;
#define g_00000020 (*(int *) 0x00002000)
extern void func_020012dc(void);
extern void __register_global_object(void *, void (*)(void), void *);
extern void func_020ea6e0(void *, int);
UnkStruct_0223c8b4 *func_ov004_0223c8b4(void *unused, int p)
{
    if (!(data_ov004_022595dc & 1)) {
        __register_global_object(&data_ov004_02259628, func_020012dc, &data_ov004_0225961c);
        data_ov004_022595dc |= 1;
    }
    data_ov004_02259628.a = 0;
    data_ov004_02259628.b = 0;
    data_ov004_02259628.c = (long) &g_00000020;
    func_020ea6e0(&data_ov004_02259628, p);
    return &data_ov004_02259628;
}
