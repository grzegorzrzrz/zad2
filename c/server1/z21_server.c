#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char **argv)
{
  char bufor[6400];
  int port;
  if (argc < 2)
  {
    port = 8000;
    printf("Brak podanego portu\nProgram będzie korzystał z portu 8000\n");
  }

  else
  {
    port = (int)strtol(argv[1], NULL, 0);
    printf("Korzystamy z portu %d\n", port);
  }

  struct sockaddr_in adres_serwera = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = htonl(INADDR_ANY),
      .sin_port = htons(port)};

  struct sockaddr_in adres_klienta;

  socklen_t dlugosc_adresu_klienta = sizeof(adres_klienta);

  int gniazdko = socket(AF_INET, SOCK_STREAM, 0);

  if (gniazdko < 0)
  {
    perror("Błąd przy tworzeniu gniazdka");
    return 1;
  }

  if (bind(gniazdko, (const struct sockaddr *)&adres_serwera, sizeof(adres_serwera)) != 0)
  {
    perror("Błąd przy wiązaniu gniazdka");
    return 1;
  }

  if (listen(gniazdko, 3) != 0)
  {
    perror("Błąd przy nasłuchiwaniu");
    return 1;
  }

  printf("Uruchomiono prawidłowo\n");
  while (1)
  {
    int polaczenie = accept(gniazdko, (struct sockaddr *)&adres_klienta, &dlugosc_adresu_klienta);

    if (polaczenie < 0)
    {
      perror("Błąd w zaakceptowaniu połączenia");
      return 1;
    }
    else
    {
      pid_t pid = fork();
      if (pid < 0)
      {
        perror("Fork failed");
        return 1;
      }
      else if (pid == 0)
      {
        while (1)
        {
          int wiadomosc_otrzymana = (int)recv(polaczenie, bufor, 64, 0);

          if (wiadomosc_otrzymana < 0)
          {
            perror("Błąd w czasie odbierania danych\n");
          }

          if (wiadomosc_otrzymana > 0)
          {
            printf("Otrzymano %d bajtów danych z %s:\n%.*s\n\n", wiadomosc_otrzymana, inet_ntoa(adres_klienta.sin_addr), wiadomosc_otrzymana, bufor);
          }
          else
          {
            break;
          }
        }
        close(polaczenie);
      }
      else
      {
        close(polaczenie);
        wait(NULL);
      }
    }
  }
  return 0;
}