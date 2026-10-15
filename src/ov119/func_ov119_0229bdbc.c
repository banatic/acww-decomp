/* func_ov119_0229bdbc @ 0x0229bdbc, 0x34 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov119_0229b828(void *);
extern int func_ov002_02208e28(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov119_0229bdbc(void *arg0)
{
    if (func_ov002_02208e28((char *) arg0 + 0xdc)) {
        if (func_0206fe54()) {
            func_ov119_0229b828(arg0);
            func_ov002_02208098(arg0, 6);
        } else {
            func_ov002_02208098(arg0, 1);
        }
    }
}
