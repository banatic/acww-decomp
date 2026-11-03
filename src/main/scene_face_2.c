/* scene_face_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201a430 @ 0x0201a430, 0x54 bytes, Thumb
 * func_0201a3f8 @ 0x0201a3f8, 0x36 bytes, Thumb
 * func_0201a3e8 @ 0x0201a3e8, 0x10 bytes, Thumb
 * func_0201a3e4 @ 0x0201a3e4, 0x4 bytes, Thumb
 */

typedef struct {
    char unk_00[0x04];
    char unk_04[0x08];
    char unk_0C[0x08];
    char unk_14[0x08];
    char unk_1C[0x2c];
    char unk_48;
} UnkStruct_0201a3f8;

typedef struct {
    char pad_00[0x84];
    unsigned char flag;
} UnkStruct_0201a3e8;

extern void func_0206463c(void *object);
extern void *func_02082d90(void *p);
extern void *func_02082e78(void *p);
extern void *func_02082e04(void *p);
extern void *func_02056928(void *p);
extern void *func_02056910(void *);
extern void *func_02082dec(void *);
extern void *func_02082e60(void *);
extern void *func_02082d78(void *);
extern void func_02064638(void *);

void *func_0201a430(void *ptr)
{
    unsigned char *base = (unsigned char *) ptr;

    func_0206463c(ptr);
    func_02082d90(base + 4);
    func_02082e78(base + 0xc);
    func_02082e04(base + 0x14);
    func_02056928(base + 0x1c);
    func_02056928(base + 0x48);

    base[0x84] = 0;

    *(unsigned int *) (base + 0x74) = 0x16f;
    *(unsigned int *) (base + 0x78) = 0x16f;
    *(unsigned int *) (base + 0x7c) = 0x16f;
    *(unsigned int *) (base + 0x80) = 2;

    return ptr;
}

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

int func_0201a3e8(UnkStruct_0201a3e8 *self)
{
    if (self->flag != 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_0201a3e4(int *p0)
{
    return p0[30];
}
