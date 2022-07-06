#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>

#include "eie_device/eie_device.h"

int main(int argc, char **argv) {

    int ret = 0;

    char json[] = "{config:config}";

    thing * device;

    device = create_device(json);
    printf("ID: %d\n", device->thing_id);

    return ret;
}
