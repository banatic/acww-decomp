/* func_ov106_0229d414 @ 0x0229d414, 0x40 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f43ec;
extern void func_ov002_0220b830(void *arg1, void *arg2, int arg3);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_02207e9c(void *arg1, int arg2, int arg3);

void func_ov106_0229d414(void *obj, char c)
{
    char local;
    local = data_021f43ec;
    local = c;
    func_ov002_0220b830((char *) obj + 0x26f8, &local, 1);
    func_ov002_02208098((void *) (obj), 0x1a);
    func_ov002_02207e9c(obj, 0, 0);
}
