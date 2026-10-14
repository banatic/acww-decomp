/* func_ov004_0220c5cc @ 0x0220c5cc, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e895c(void *, int, unsigned int);
extern void func_ov004_0220ccf8(void *obj, int arg);
extern void func_ov004_0220fefc(void *obj, void *arg);
extern void func_ov004_0220e61c(void *obj, void *arg);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned char pad_0C[0x3F4];
} UnkStruct_0220c5cc;

typedef struct {
    char pad_00[0x150];
    UnkStruct_0220c5cc sub;
    char pad_550[0x220];
    unsigned short unk_770;
} RoomObject;

void func_ov004_0220c5cc(RoomObject *obj)
{
    func_020e895c(&obj->sub, 0, sizeof(obj->sub));
    obj->sub.unk_08 = obj->sub.unk_00;
    obj->sub.unk_04 = obj->sub.unk_08;
    if (obj->sub.unk_00 == 0) {
        func_ov004_0220ccf8(obj, 7);
    } else {
        if (obj->unk_770 == 1) {
            char local[16];
            func_ov004_0220fefc(obj, local);
            func_ov004_0220e61c(obj, local);
        }
    }
    obj->unk_770++;
}
