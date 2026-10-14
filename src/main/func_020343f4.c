/* func_020343f4 @ 0x020343f4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x498];
    int a;
    int b;
    int c;
    int d;
} UnkStruct_020343f4;

extern void func_020343f0(void);
extern void func_02031608(void);
extern void __cxa_vec_ctor(void *param, int p1, int p2, void (*f)(void), void (*g)(void));

void *func_020343f4(void *param)
{
    UnkStruct_020343f4 *obj = (UnkStruct_020343f4 *) param;
    __cxa_vec_ctor(param, 0x31, 0x18, func_020343f0, func_02031608);
    obj->d = 0;
    obj->c = obj->d;
    obj->b = obj->c;
    obj->a = obj->b;
    return param;
}
