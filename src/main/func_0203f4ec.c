/* func_0203f4ec @ 0x0203f4ec, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0203f4ec UnkStruct_0203f4ec;
struct UnkStruct_0203f4ec {
    unsigned char type;
};
typedef void (*Handler)(UnkStruct_0203f4ec *, int);
extern Handler data_020dab98[];

void func_0203f4ec(UnkStruct_0203f4ec *obj, int arg)
{
    data_020dab98[obj->type](obj, arg);
}
