/* func_ov106_0229d978 @ 0x0229d978, 0x84 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220b7b8(char *);
extern int func_ov002_02207f3c(char *, int);
extern int func_ov002_02207f60(char *);
extern void func_ov002_0220a690(char *);
extern void func_ov002_02207eb4(char *, int, int);
extern int func_ov002_0220ab84(char *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void *func_ov002_0220ad0c(char *);
extern void func_ov002_02208090(char *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);

void func_ov106_0229d978(char *obj)
{
    int v = func_ov002_0220b7b8(obj + 0x26f8) & func_ov002_02207f3c(obj, -1);
    *(int *) (obj + 0xa0) = func_ov002_02207f60(obj);
    if (v) {
        func_ov002_0220a690(obj + 0x3fb4);
        if (*(unsigned char *) (obj + 0xbe) == 0) {
            func_ov002_02207eb4(obj, 0, 0);
            func_ov002_0220ab84(obj + 0x3fb4, 0x88);
            func_ov002_02208098((void *) (obj), 0x21);
        } else {
            func_ov002_0220ad0c(obj + 0x3fb4);
            func_ov002_02208090(obj, 4);
            func_ov002_022080a0((void *) (obj), 1);
        }
    }
}
