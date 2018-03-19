#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RXBYTES "/sys/class/net/wlan0/statistics/rx_bytes"
#define TXBYTES "/sys/class/net/wlan0/statistics/tx_bytes"
#define RATE (100 * 1024)
#define BRIGHTNESS "/sys/class/leds/chip:white:status/brightness"

static void build_daemon (void)
{
  int i;
  pid_t pid;

  if ((i = open("/dev/null", O_RDONLY)) != 0) {
    dup2(i, 0);
    close(i);
  }
  if ((i = open("/dev/null", O_WRONLY)) != 1) {
    dup2(i, 1);
    close(i);
  }
  if ((i = open("/dev/null", O_WRONLY)) != 2) {
    dup2(i, 2);
    close(i);
  }

  setsid();

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  } else if (pid) {
    exit(0);
  }
}


static unsigned long long refresh (void)
{
  char buf[32];
  int pntr;
  unsigned long long ret;

  pntr = open(RXBYTES, O_RDONLY);

  if (pntr < 0) {
    perror("open");
    return -1;
  }

  read(pntr, buf, 32);
  ret = atoll(buf);

  close(pntr);

  pntr = open(TXBYTES, O_RDONLY);

  if (pntr < 0) {
    perror("open");
    return -1;
  }

  read(pntr, buf, 32);
  ret += atoll(buf);

  close(pntr);

  return ret;
}

static int ledpntr;

int main (int argc, char ** argv)
{
  unsigned long long cur;
  unsigned long long prev;

  ledpntr = open(BRIGHTNESS, O_WRONLY);
  if (ledpntr < 0) {
    perror("open");
    exit(-1);
  }

  build_daemon();

  prev = 0;

  for (;;) {
    cur = refresh();

    if ((cur / RATE) != (prev / RATE)) {
      write(ledpntr, "0", 1);

      usleep(100 * 1000);

      write(ledpntr, "1", 1);
    }

    prev = cur;

    usleep(100 * 1000);
  }

  close(ledpntr);
}
