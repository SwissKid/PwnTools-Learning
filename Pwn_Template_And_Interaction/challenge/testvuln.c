#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 128

void give_shell(){
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
    system("/bin/sh -i");
}

void vuln(){
  char buf[BUFSIZE];
  puts("Give me some text:");
  fflush(stdout);
  gets(buf);
  puts(buf);
  fflush(stdout);
}

int main(int argc, char **argv){
  // Set the gid to the effective gid
  // this prevents /bin/sh from dropping the privileges
  gid_t gid = getegid();
  setresgid(gid, gid, gid);

  vuln();
  return 0;
}
