/* func_020ab42c @ 0x020ab42c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_020ab794(void *);
extern const char *func_020ab798(void *);
extern void *func_020a8bb8(char *, const char *);
extern const char *func_020ab790(void *);
extern char *strncpy(char *, const char *, int);
extern void *func_020ab78c(void *);
extern void *func_020a82ac(void);
extern void func_020a82bc(char *, const void *);

typedef struct {
    char data[0x90];
} UnkStruct_020ab42c;

typedef struct {
    UnkStruct_020ab42c arr[1];
    char pad_90[0x2d8 - 0x90];
    int unk_2D8;
    char unk_2DC;
    char unk_2DD;
    char pad_2DE[0x2f6 - 0x2de];
    char unk_2F6;
    char pad_2F7[1];
    char unk_2F8[1];
    char pad_2F9[0x354 - 0x2f9];
    char unk_354[1];
} LargeStruct;

void func_020ab42c(LargeStruct *obj, int index)
{
    UnkStruct_020ab42c *elem;
    const char *name;
    void *temp;

    elem = &obj->arr[index];
    obj->unk_2D8 = index;
    obj->unk_2DC = *func_020ab794(elem);
    func_020a8bb8(obj->unk_2F8, func_020ab798(elem));
    name = func_020ab790(elem);
    obj->unk_2F6 = 0;
    strncpy((char *) obj + 0x2dd, name, 0x19);
    temp = (func_020ab78c(elem), func_020a82ac());
    func_020a82bc((char *) obj + 0x354, temp);
}
