/* func_020ab71c @ 0x020ab71c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(char *dest, const char *fmt, ...);
extern int func_020ab83c(void *a, void *b, void *c, void *d);
typedef struct {
    int unk_00;
    const char *name;
    char unk_08[0x5c];
    char unk_64;
} UnkStruct_020ab71c;

void func_020ab71c(UnkStruct_020ab71c *p)
{
    char path[0x40];
    const char *lang = "KOR";
    func_02064328(path, "/script/%s/select/%s.bmg", lang, p->name);
    func_020ab83c(&p->unk_08, path, p, &p->unk_64);
}
