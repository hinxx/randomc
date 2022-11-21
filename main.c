#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct map {
    int count;
    int *ids;
    char **names;
};

struct map2 {
    int id;
    char *name;
};

struct driver {
    int cid;
    int fid;
    struct list_head list;
};

struct list_head drivers;
struct map cids;
struct map fids;

char *cid_name(const int cid) {
    for (int i = 0; i < cids.count; i++) {
        if (cids.ids[i] == cid) {
            return cids.names[i];
        }
    }
    return NULL;
}

char *fid_name(const int fid) {
    for (int i = 0; i < fids.count; i++) {
        if (fids.ids[i] == fid) {
            return fids.names[i];
        }
    }
    return NULL;
}

#define ARRAY_SIZE(ar)  (sizeof(ar) / sizeof(ar[0]))

struct map2 cids2[] = {
    {11, "oneone"},
    {22, "twotwo"},
    {33, "threethree"}
};
int cids2size = ARRAY_SIZE(cids2);

struct map2 fids2[] = {
    {1, "one"},
    {2, "two"},
    {3, "three"}
};
int fids2size = ARRAY_SIZE(fids2);

char *cid_name2(const int cid) {
    for (int i = 0; i < cids2size; i++) {
        if (cids2[i].id == cid) {
            return cids2[i].name;
        }
    }
    return NULL;
}

char *fid_name2(const int fid) {
    for (int i = 0; i < fids2size; i++) {
        if (fids2[i].id == fid) {
            return fids2[i].name;
        }
    }
    return NULL;
}


void (*f)(const int a, const int b);

void show(const int cid, const int fid) {
    printf("show: cid %d %s, fid %d %s\n", cid, cid_name(cid), fid, fid_name(fid));
}

void show2(const int cid, const int fid) {
    printf("show2: cid %d %s, fid %d %s\n", cid, cid_name2(cid), fid, fid_name2(fid));
}

void list_drivers1(void(*fn)(const int, const int)) {
    struct driver *drv;
    list_for_each_entry(drv, &drivers, list) {
        fn(drv->cid, drv->fid);
    }
}

int main() {

    static int cidids[] = {11, 22, 33, 44, 55};
    static char *cidnames[] = {"oneone", "twotwo", "threethree", "fourfour", "fivefive"};
    // struct map cids = {
    //     .count = 5,
    //     .ids = cidids,
    //     .names = cidnames
    // };
    cids.count = 5;
    cids.ids = cidids;
    cids.names = cidnames;

    for (int i = 0; i < cids.count; i++)
    {
        printf("CID %d = %s\n", cids.ids[i], cids.names[i]);
    }

    static int fidids[] = {1, 2, 3, 4, 5};
    static char *fidnames[] = {"one", "two", "three", "four", "five"};
    // struct map fids = {
    //     .count = 5,
    //     .ids = fidids,
    //     .names = fidnames
    // };
    fids.count = 5;
    fids.ids = fidids;
    fids.names = fidnames;
    for (int i = 0; i < fids.count; i++)
    {
        printf("FID %d = %s\n", fids.ids[i], fids.names[i]);
    }

    INIT_LIST_HEAD(&drivers);

    struct driver *drv;
    drv = calloc(1, sizeof(struct driver));
    drv->cid = 11;
    drv->fid = 1;
    INIT_LIST_HEAD(&drv->list);
    list_add_tail(&drv->list, &drivers);
    drv = calloc(1, sizeof(struct driver));
    drv->cid = 22;
    drv->fid = 2;
    INIT_LIST_HEAD(&drv->list);
    list_add_tail(&drv->list, &drivers);
    drv = calloc(1, sizeof(struct driver));
    drv->cid = 33;
    drv->fid = 3;
    INIT_LIST_HEAD(&drv->list);
    list_add_tail(&drv->list, &drivers);

    // list_for_each_entry(drv, &drivers, list) {
    //     printf("loop: cid %d, fid %d\n", drv->cid, drv->fid);
    // }

    list_prepare_entry(drv, &drivers, list);
    // printf(".. cid %d, fid %d\n", drv->cid, drv->fid);
    list_for_each_entry_continue(drv, &drivers, list) {
        printf("cont: cid %d, fid %d\n", drv->cid, drv->fid);
    }

    list_drivers1(show);

    list_drivers1(show2);

    return 0;
}

