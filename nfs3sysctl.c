/*
 * linux/fs/nfs/sysctl.c
 *
 * Sysctl interface to NFS parameters
 */
#include <linux/types.h>
#include <linux/linkage.h>
#include <linux/ctype.h>
#include <linux/fs.h>
#include <linux/sysctl.h>
#include <linux/module.h>
#include <linux/nfs_fs.h>

extern int nfsd_zql_control;

static struct ctl_table_header *nfsd3_callback_sysctl_table;

static struct ctl_table nfsd3_cb_sysctls[] = {
	{
		.procname	= "nfsd_zql_control",
		.data		= &nfsd_zql_control,
		.maxlen		= sizeof(nfsd_zql_control),
		.mode		= 0644,
		.proc_handler	= proc_dointvec,
	},
	{ }
};

static struct ctl_table nfsd3_cb_sysctl_dir[] = {
	{
		.procname = "nfs",
		.mode = 0555,
		.child = nfsd3_cb_sysctls,
	},
	{ }
};

static struct ctl_table nfsd3_cb_sysctl_root[] = {
	{
		.procname = "fs",
		.mode = 0555,
		.child = nfsd3_cb_sysctl_dir,
	},
	{ }
};

int nfsd3_register_sysctl(void)
{
	nfsd3_callback_sysctl_table = register_sysctl_table(nfsd3_cb_sysctl_root);
	if (nfsd3_callback_sysctl_table == NULL)
		return -ENOMEM;
	return 0;
}

void nfsd3_unregister_sysctl(void)
{
	unregister_sysctl_table(nfsd3_callback_sysctl_table);
	nfsd3_callback_sysctl_table = NULL;
}
