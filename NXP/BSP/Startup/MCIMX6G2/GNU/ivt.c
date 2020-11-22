
#define NULL 0

struct data {
    void *start;
    unsigned int length;
    unsigned int plugin;
};

struct ivt {
    unsigned int header;
    void *entry;
    unsigned int reserved1i;
    void *dcd;
    struct data *data;
    void *self;
    void *csf;
    unsigned int reserved2;
};

extern void *_start;
extern void *_prog_size;

struct data data __attribute__ ((section (".ivt"))) = {
    &_start,
    (unsigned int)&_prog_size,
    0
};

struct ivt ivt __attribute__ ((section (".ivt_entry"))) = {
    0x402000d1,
    &_start,
    0,
    NULL,
    &data,
    &ivt,
    NULL,
    0,
};
