/* func_0206c4d8 @ 0x0206c4d8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d420(void *arg, void *addr);

typedef struct {
    unsigned char data[0x14b8];
} BigStruct;

typedef struct {
    unsigned char pad_00[0x2c];
    BigStruct *big;
} UnkStruct_0206c4d8;

void func_0206c4d8(UnkStruct_0206c4d8 *obj)
{
    func_0206d420(obj, (char *) (obj->big + 1) + 0x398);
}
