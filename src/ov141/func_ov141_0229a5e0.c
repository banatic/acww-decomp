/* func_ov141_0229a5e0 @ 0x0229a5e0, 0x54 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char base[0xa38];
    int unk_A38;
    char pad_A3C[0x1042];
    unsigned char unk_1A7E;
    char pad_1A7F[13];
    unsigned char unk_1A8C;
} UnkStruct_0229a5e0;

extern int func_0208e484(void *addr);
extern void func_ov141_0229a3a4(UnkStruct_0229a5e0 *obj);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov141_02299f7c(UnkStruct_0229a5e0 *obj, int x);
extern void func_ov141_02299f5c(UnkStruct_0229a5e0 *obj, int x);
extern void func_ov141_0229a428(UnkStruct_0229a5e0 *obj);

void func_ov141_0229a5e0(UnkStruct_0229a5e0 *obj)
{
    if (func_0208e484(&obj->unk_A38) != 0) {
        func_ov141_0229a3a4(obj);
        func_ov002_02208098((void *) (obj), obj->unk_1A7E);
        if (func_ov141_02299f7c(obj, 8) != 0) {
            func_ov141_02299f5c(obj, 8);
            obj->unk_1A8C = 7;
            func_ov141_0229a428(obj);
        }
    }
}
