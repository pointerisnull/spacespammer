#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "data.h"
#include "net.h"

State state;

void init(Lot *lots, int spaceCount) {
  state.RUNNING = 1;
  for(int i = 0; i < state.lotCount; i++) {
    lots[i].spaceCount = spaceCount;
    lots[i].id = i;
    strncpy(lots[i].name, "default", 8);
    lots[i].space = malloc(sizeof(Space)*lots[i].spaceCount);
    for(int j = 0; j < lots[i].spaceCount; j++) {
      lots[i].space[j].id = j;
      lots[i].space[j].isOccupied = rand() %2;
      lots[i].space[j].timeTaken = 0;
      lots[i].space[j].popularity = 0;
    }
  }
}

int main(int argc, char *argv[]) {

  int airportlotcount = 2;
  state.lotCount = airportlotcount;
  Lot *airport = malloc(sizeof(Lot)*state.lotCount);
  init(airport, 500);
  for(int i = 0; i < state.lotCount; i++) {
    makeInitPacket("init.JSON", 1, airport[i]);
    sendPacket("init.JSON", "/api/new/lot", 1);
    sendPacket("init.JSON", "/api/update/lot", 1);
  } 

  int wallmartcount = 3;
  state.lotCount = wallmartcount;
  Lot *wallmart = malloc(sizeof(Lot)*state.lotCount);
  init(wallmart, 40);
  for(int i = 0; i < state.lotCount; i++) {
    makeInitPacket("init.JSON", 2, wallmart[i]);
    sendPacket("init.JSON", "/api/new/lot", 2);
    sendPacket("init.JSON", "/api/update/lot", 2);
  } 

  int citycount = 100;
  state.lotCount = citycount;
  Lot *city = malloc(sizeof(Lot)*state.lotCount);
  init(city, 6);
  for(int i = 0; i < state.lotCount; i++) {
    makeInitPacket("init.JSON", 3, city[i]);
    sendPacket("init.JSON", "/api/new/lot", 3);
    sendPacket("init.JSON", "/api/update/lot", 3);
  } 

  long long lastTime = time(NULL);
  long long thisTime;
  while(state.RUNNING) {
  thisTime = time(NULL);
  if(thisTime - lastTime > 3) {
    //printf("test\n", 0); 
    int l = rand()%airportlotcount;
    int s = rand()%airport[l].spaceCount;
    makeUpdatePacket("update.JSON", 1, 1, l, s, airport[l].space[s].popularity, airport[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 1);
    l = rand()%airportlotcount;
    s = rand()%airport[l].spaceCount;
    makeUpdatePacket("update.JSON", 1, 0, l, s, airport[l].space[s].popularity, airport[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 1);

    l = rand()%wallmartcount;
    s = rand()%wallmart[l].spaceCount;
    makeUpdatePacket("update.JSON", 2, 1, l, s, wallmart[l].space[s].popularity, wallmart[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 2);
    l = rand()%wallmartcount;
    s = rand()%wallmart[l].spaceCount;
    makeUpdatePacket("update.JSON", 2, 0, l, s, wallmart[l].space[s].popularity, wallmart[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 2);

    l = rand()%citycount;
    s = rand()%city[l].spaceCount;
    makeUpdatePacket("update.JSON", 3, 1, l, s, city[l].space[s].popularity, city[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 3);
    l = rand()%citycount;
    s = rand()%city[l].spaceCount;
    makeUpdatePacket("update.JSON", 3, 0, l, s, city[l].space[s].popularity, city[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 3);

    lastTime = thisTime;
    }
  }
  return 0;
}
