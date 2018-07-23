#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netpoll.h>
#include <linux/inet.h>

static struct netpoll* np = NULL;
static struct netpoll  nps;

void np_init(void)
{
    nps.name = '\x00';
    strlcpy(nps.dev_name, "eth0", IFNAMSIZ);
    nps.local_ip.ip         = htonl((unsigned long)0x0A000005);
    nps.local_ip.in.s_addr  = htonl((unsigned long)0x0A000005);
    nps.remote_ip.ip        = htonl((unsigned long)0x0A00000A);
    nps.remote_ip.in.s_addr = htonl((unsigned long)0x0A00000A);
    nps.local_port          = 42420;
    nps.remote_port         = 123;
    nps.ipv6                = 0;
    memset(nps.remote_mac, 0xff, ETH_ALEN);
    netpoll_setup(&nps);
    np = &nps;
}

void send_udp(const char *buf)
{
    int len;

    len = strlen(buf);
    netpoll_send_udp(np, buf, len);
}

int init_module(void)
{
    np_init();
    send_udp("AHOY");
    return 0;
}

void cleanup_module(void)
{
    printk("Cya\n");
}
