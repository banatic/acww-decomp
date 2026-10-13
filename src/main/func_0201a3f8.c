/* func_0201a3f8 @ 0x0201a3f8, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056910(void *);
extern void func_02082dec(void *);
extern void func_02082e60(void *);
extern void func_02082d78(void *);
extern void func_02064638(void *);

typedef struct {
    char unk_00[0x04];
    char unk_04[0x08];
    char unk_0C[0x08];
    char unk_14[0x08];
    char unk_1C[0x2c];
    char unk_48;
} UnkStruct_0201a3f8;

UnkStruct_0201a3f8 *func_0201a3f8(UnkStruct_0201a3f8 *obj)
{
    func_02056910(&obj->unk_48);
    func_02056910(&obj->unk_1C);
    func_02082dec(&obj->unk_14);
    func_02082e60(&obj->unk_0C);
    func_02082d78(&obj->unk_04);
    func_02064638(obj);
    return obj;
}
