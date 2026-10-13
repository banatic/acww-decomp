/* func_020b312c @ 0x020b312c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" unsigned char data_021f4bd0[];

// An item id; the empty destructor keeps the eight bytes the ROM reserves for it.
class ItemId {
  public:
    ItemId(unsigned int v) : id(v) {}
    ~ItemId() {}
    unsigned int id;
};

extern "C" int func_020b312c(unsigned int x)
{
    ItemId item(x);
    int index;
    if (item.id < 0x5000 || item.id > 0x5021) {
        goto fail;
    }
    if (item.id >= 0x5000 && item.id <= 0x5021) {
        index = item.id & 0xfff;
    } else {
        index = -1;
    }
    if ((unsigned int) index >= 0x22) {
        goto fail;
    }
    return data_021f4bd0[index];
fail:
    return 0;
}
