/* link_scene_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a6eb0 @ 0x020a6eb0, 0x10 bytes, Thumb
 * func_020a6ea0 @ 0x020a6ea0, 0x10 bytes, Thumb
 * func_020a6e8c @ 0x020a6e8c, 0x14 bytes, Thumb
 * func_020a6e7c @ 0x020a6e7c, 0x10 bytes, Thumb
 * func_020a6e6c @ 0x020a6e6c, 0x10 bytes, Thumb
 */

extern void func_020a6688(void *dst, const void *src);
extern unsigned char data_021f4320[];
extern int func_020a6684(void *);
extern void func_020a635c(void *dst, const void *src, unsigned int size);
extern void func_020a6288(void *dst, const void *src);
extern void func_020a6248(void *param1, void *param2);

void func_020a6eb0(void *arg0)
{
    func_020a6688((void *) data_021f4320, arg0);
}

int func_020a6ea0(void)
{
    return func_020a6684(((char *) data_021f4320));
}

void func_020a6e8c(unsigned char *param0, unsigned char *param1)
{
    unsigned char *dst;
    unsigned char *src;

    dst = param0;
    src = param1;
    func_020a635c(data_021f4320, dst, (unsigned int) src);
}

void func_020a6e7c(void *arg0)
{
    func_020a6288((void *) data_021f4320, arg0);
}

void func_020a6e6c(void *param)
{
    func_020a6248((void *) data_021f4320, param);
}
