/*
 * namedev.h
 *
 * Userspace devfs
 *
 * Copyright (C) 2003 Greg Kroah-Hartman <greg@kroah.com>
 *
 *	This program is free software; you can redistribute it and/or modify it
 *	under the terms of the GNU General Public License as published by the
 *	Free Software Foundation version 2 of the License.
 * 
 *	This program is distributed in the hope that it will be useful, but
 *	WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *	General Public License for more details.
 * 
 *	You should have received a copy of the GNU General Public License along
 *	with this program; if not, write to the Free Software Foundation, Inc.,
 *	675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef NAMEDEV_H
#define NAMEDEV_H

#include "udev.h"
#include "list.h"

struct sysfs_class_device;


enum config_type {
	KERNEL_NAME	= 0,	/* must be 0 to let memset() default to this value */
	LABEL		= 1,
	NUMBER		= 2,
	TOPOLOGY	= 3,
	REPLACE		= 4,
	CALLOUT		= 5,
	IGNORE		= 6,
};

#define BUS_SIZE	30
#define FILE_SIZE	50
#define VALUE_SIZE	100
#define ID_SIZE		50
#define PLACE_SIZE	50
#define PROGRAM_SIZE	100

#define TYPE_LABEL	"LABEL"
#define TYPE_NUMBER	"NUMBER"
#define TYPE_TOPOLOGY	"TOPOLOGY"
#define TYPE_REPLACE	"REPLACE"
#define TYPE_CALLOUT	"CALLOUT"
#define TYPE_IGNORE	"IGNORE"

#define FIELD_BUS	"BUS"
#define FIELD_ID	"ID"
#define FIELD_SYSFS	"SYSFS_"
#define FIELD_PLACE	"PLACE"
#define FIELD_PROGRAM	"PROGRAM"
#define FIELD_KERNEL	"KERNEL"
#define FIELD_NAME	"NAME"
#define FIELD_SYMLINK	"SYMLINK"

#define CALLOUT_MAXARG	8
#define MAX_SYSFS_PAIRS	5

struct sysfs_pair {
	char file[FILE_SIZE];
	char value[VALUE_SIZE];
};

struct config_device {
	struct list_head node;

	enum config_type type;
	char bus[BUS_SIZE];
	char id[ID_SIZE];
	char place[PLACE_SIZE];
	char kernel_name[NAME_SIZE];
	char exec_program[PROGRAM_SIZE];
	char name[NAME_SIZE];
	char symlink[NAME_SIZE];
	struct sysfs_pair sysfs_pair[MAX_SYSFS_PAIRS];
};

struct perm_device {
	struct list_head node;

	char name[NAME_SIZE];
	char owner[OWNER_SIZE];
	char group[GROUP_SIZE];
	mode_t mode;
};

extern struct list_head config_device_list;
extern struct list_head perm_device_list;

extern int namedev_init(void);
extern int namedev_name_device(struct sysfs_class_device *class_dev, struct udevice *dev);
extern int namedev_init_permissions(void);
extern int namedev_init_rules(void);

extern int add_perm_dev(struct perm_device *new_dev);
extern void dump_config_dev(struct config_device *dev);
extern void dump_config_dev_list(void);
extern void dump_perm_dev(struct perm_device *dev);
extern void dump_perm_dev_list(void);

extern int get_pair(char **orig_string, char **left, char **right);

#endif
