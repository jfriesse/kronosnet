/*
 * Copyright (C) 2020 Red Hat, Inc.  All rights reserved.
 *
 * Authors: Fabio M. Di Nitto <fabbione@kronosnet.org>
 *
 * This software licensed under GPL-2.0+
 */

#include "config.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libknet.h"

#include "internals.h"
#include "test-common.h"

static int private_data;

static void onwire_ver_notify(void *priv_data,
			      uint8_t onwire_min_ver,
			      uint8_t onwire_max_ver,
			      uint8_t onwire_ver)
{
	return;
}

static void test(void)
{
	knet_handle_t knet_h;
	int logfds[2];

	printf("Test knet_handle_enable_onwire_ver_notify incorrect knet_h\n");

	if ((!knet_handle_enable_onwire_ver_notify(NULL, NULL, onwire_ver_notify)) || (errno != EINVAL)) {
		printf("knet_handle_enable_onwire_ver_notify accepted invalid knet_h or returned incorrect error: %s\n", strerror(errno));
		exit(FAIL);
	}

	setup_logpipes(logfds);

	knet_h = knet_handle_start(logfds, KNET_LOG_DEBUG);

	printf("Test knet_handle_enable_onwire_ver_notify with no private_data\n");

	if (knet_handle_enable_onwire_ver_notify(knet_h, NULL, onwire_ver_notify) < 0) {
		printf("knet_handle_enable_onwire_ver_notify failed: %s\n", strerror(errno));
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);
	}

	if (knet_h->onwire_ver_notify_fn_private_data != NULL) {
		printf("knet_handle_enable_onwire_ver_notify failed to unset private_data");
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);

	}

	flush_logs(logfds[0], stdout);

	printf("Test knet_handle_enable_onwire_ver_notify with private_data\n");

	if (knet_handle_enable_onwire_ver_notify(knet_h, &private_data, NULL) < 0) {
		printf("knet_handle_enable_onwire_ver_notify failed: %s\n", strerror(errno));
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);
	}

	if (knet_h->onwire_ver_notify_fn_private_data != &private_data) {
		printf("knet_handle_enable_onwire_ver_notify failed to set private_data");
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);

	}

	flush_logs(logfds[0], stdout);

	printf("Test knet_handle_enable_onwire_ver_notify with no onwire_ver_notify fn\n");

	if (knet_handle_enable_onwire_ver_notify(knet_h, NULL, NULL) < 0) {
		printf("knet_handle_enable_onwire_ver_notify failed: %s\n", strerror(errno));
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);
	}

	if (knet_h->onwire_ver_notify_fn != NULL) {
		printf("knet_handle_enable_onwire_ver_notify failed to unset onwire_ver_notify fn");
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);

	}

	flush_logs(logfds[0], stdout);

	printf("Test knet_handle_enable_onwire_ver_notify with onwire_ver_notify fn\n");

	if (knet_handle_enable_onwire_ver_notify(knet_h, NULL, onwire_ver_notify) < 0) {
		printf("knet_handle_enable_onwire_ver_notify failed: %s\n", strerror(errno));
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);
	}

	if (knet_h->onwire_ver_notify_fn != &onwire_ver_notify) {
		printf("knet_handle_enable_onwire_ver_notify failed to set onwire_ver_notify fn");
		knet_handle_free(knet_h);
		flush_logs(logfds[0], stdout);
		close_logpipes(logfds);
		exit(FAIL);

	}

	flush_logs(logfds[0], stdout);

	knet_handle_free(knet_h);
	flush_logs(logfds[0], stdout);
	close_logpipes(logfds);
}

int main(int argc, char *argv[])
{
	test();

	return PASS;
}
