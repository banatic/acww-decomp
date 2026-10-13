/* func_020bc464 @ 0x020bc464, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Object {
    char pad_00[0x2f08];
    int unk_2F08;
    int unk_2F0C;
};

struct Global {
    char pad_00[0x34];
    int state;
};

extern struct Global data_021f8ab0;

extern void func_020bd938(struct Object *);
extern void func_020bd7a4(struct Object *);
extern void func_020bceb4(struct Object *);
extern void func_020bd688(struct Object *);
extern void func_020bd054(struct Object *);
extern void func_020bd6d0(struct Object *);
extern void func_020bd3b4(struct Object *);
extern int func_020b65c4(void);
extern void func_020bd2d0(struct Object *);
extern void func_020bd1c4(struct Object *);
extern void func_020bd124(struct Object *);
extern void func_020bcfbc(struct Object *);

void func_020bc464(struct Object *obj)
{
    switch (data_021f8ab0.state) {
        case 1:
            func_020bd938(obj);
            break;
        case 2:
            func_020bd7a4(obj);
            break;
        default:
            obj->unk_2F08 = 0;
            obj->unk_2F0C = 0;
            break;
    }
    func_020bceb4(obj);
    func_020bd688(obj);
    func_020bd054(obj);
    func_020bd6d0(obj);
    func_020bd3b4(obj);
    if (func_020b65c4() != 0x2c) {
        func_020bd2d0(obj);
        func_020bd1c4(obj);
        func_020bd124(obj);
        func_020bcfbc(obj);
    }
}
