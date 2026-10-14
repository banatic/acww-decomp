/* func_02033894 @ 0x02033894, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *a, int b, int c, void (*d)(void), void (*e)(void));
extern void func_020339b8(void);
extern void func_020339dc(void);

typedef struct {
    char pad_00[0x480];
    unsigned int unk_480;
} UnkStruct_02033894;

void *func_02033894(void *obj)
{
    __cxa_vec_ctor(obj, 0x18, 0x30, func_020339dc, func_020339b8);
    ((UnkStruct_02033894 *) obj)->unk_480 = 0;
    return obj;
}
