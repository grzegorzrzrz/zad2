#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  char bufor[100];
  int gniazdo, port, adres;
  char *IPbuffer;
  struct sockaddr_in serwer;
  struct sockaddr_in name;
  struct hostent *hp, *gethostbyname();

  if (argc < 2)
  {
    printf("Brak podanego portu lub DNS\nProgram zostanie zakonczony\n");
    return 1;
  }

  else
  {
    hp = gethostbyname(argv[1]);
    port = (int)strtol(argv[2], NULL, 0);

    IPbuffer = inet_ntoa(*((struct in_addr*) hp->h_addr_list[0]));

    printf("Program będzie korzystał z portu %d i DNS %s\n", port, IPbuffer);
  }

  struct sockaddr_in adres_klienta = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = htonl(INADDR_ANY),
      .sin_port = htons(0)};

  struct sockaddr_in adres_serwera = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = inet_addr(IPbuffer),
      .sin_port = htons(port)};

  int gniazdko = socket(AF_INET, SOCK_STREAM, 0);

  if (gniazdko < 0)
  {
    perror("Błąd przy tworzeniu gniazdka");
    return 1;
  }

  if (bind(gniazdko, (const struct sockaddr *)&adres_klienta, sizeof(adres_klienta)) < 0)
  {
    perror("Błąd przy wiązaniu gniazdka");
    return 1;
  }

  if (connect(gniazdko, (struct sockaddr *)&adres_serwera, sizeof(adres_serwera)) < 0 )
  {
    perror("Błąd przy łączeniu z serwerem");
    return 1;
  }


  int ile_pakietow = 5;
  for (int pakiet = 1; pakiet < ile_pakietow + 1; pakiet++)
  {
    if (pakiet <= ile_pakietow)
    {
      sprintf(bufor, "Przesyłam %d/%d pakiet", pakiet, ile_pakietow);
    }

    else
    {
      sprintf(bufor, "Koniec");
    }

    int wyslana_wiadomosc = (int)send(gniazdko, bufor, sizeof(bufor), 0);

    if (wyslana_wiadomosc < 0)
    {
      perror("Błąd w wysyłaniu danych");
      return 1;
    }

    printf("Wysłano %d bajtów do serwera\n", wyslana_wiadomosc);
    sleep(1);
  }

  return 0;
}
