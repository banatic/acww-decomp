/* func_020ae67c @ 0x020ae67c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[4];
    signed char unk_04;
} UnkStruct_020ae67c;

extern int func_020ae470(UnkStruct_020ae67c *);
extern int func_020644cc(int);
extern int func_020ae458(UnkStruct_020ae67c *, unsigned int);
extern void func_020ae440(UnkStruct_020ae67c *, unsigned int);
extern void func_0208722c(void *);
extern void func_020ae03c(void *);
extern void func_020ae564(UnkStruct_020ae67c *);
extern void func_0209f100(void *, int);
extern int data_021f3aec, data_021f3b30, data_021dc7a8;

int func_020ae67c(UnkStruct_020ae67c *obj)
{
    int k, cnt, n;
    unsigned int i;

    if (obj->unk_04 == -1) {
        n = func_020ae470(obj);
        if (n != 0) {
            k = func_020644cc(n);
            cnt = 0;
            for (i = 0; i < 0x20; i++) {
                if (func_020ae458(obj, i) == 0) {
                    if (k == cnt) {
                        obj->unk_04 = i;
                        func_020ae440(obj, i);
                        func_0208722c(&data_021f3aec);
                        func_020ae03c(&data_021f3b30);
                        func_020ae564(obj);
                        func_0209f100(&data_021dc7a8, 8);
                        return 1;
                    }
                    cnt++;
                }
            }
        }
        return 0;
    }
    return 1;
}
