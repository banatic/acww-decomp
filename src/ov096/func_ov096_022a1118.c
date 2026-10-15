/* func_ov096_022a1118 @ 0x022a1118, 0x48 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207cc0(int object);
extern void func_ov096_0229cc74(void *, int, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    char pad_00[0xb2];
    unsigned char b2;             // offset 0xb2
    char pad_B3[0xc2 - 0xb2 - 1]; // to offset 0xc1
    unsigned char c2;             // offset 0xc2
} UnkStruct_022a1118;

void func_ov096_022a1118(UnkStruct_022a1118 *obj)
{
    if (func_ov002_02207cc0((int) ((char *) obj + 0x2418))) {
        if (obj->c2 != 0) {
            obj->c2--;
        } else {
            func_ov096_0229cc74(obj, obj->b2, 1);
            func_ov002_02208098((void *) (obj), 2);
        }
    }
}
