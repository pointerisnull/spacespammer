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
    lots[i].spaceCount = rand() % 50 + 1;//255;
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

  int YCPlotcount = 1;
  state.lotCount = YCPlotcount;
  Lot *YCPlots = malloc(sizeof(Lot)*state.lotCount);
  init(YCPlots, 6);

  for(int i = 0; i < state.lotCount; i++) {
    makeInitPacket("init.JSON", 0, YCPlots[i]);
    sendPacket("init.JSON", "/api/new/lot", 0);
    sendPacket("init.JSON", "/api/update/lot", 0);
  } 

  int airportlotcount = 2;
  state.lotCount = airportlotcount;
  Lot *airport = malloc(sizeof(Lot)*state.lotCount);
  init(airport, 500);
  for(int i = 0; i < state.lotCount; i++) {
    makeInitPacket("init.JSON", 1, airport[i]);
    sendPacket("init.JSON", "/api/new/lot", 1);
    sendPacket("init.JSON", "/api/update/lot", 0);
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


  int threecarcount = 3;
  state.lotCount = threecarcount;
  Lot *threecar = malloc(sizeof(Lot)*state.lotCount);
  init(threecar, 40);
  for(int i = 0; i < state.lotCount; i++) {
    makeInitPacket("init.JSON", 4, threecar[i]);
    sendPacket("init.JSON", "/api/new/lot", 4);
    sendPacket("init.JSON", "/api/update/lot", 4);
  } 

  long long lastTime = time(NULL);
  long long thisTime;
  while(state.RUNNING) {
  thisTime = time(NULL);
  if(thisTime - lastTime > 5) {
    //printf("test\n", 0); 
    int l = rand()%YCPlotcount;
    int s = rand()%YCPlots[l].spaceCount;
    makeUpdatePacket("update.JSON", 0, 1, l, s, YCPlots[l].space[s].popularity, YCPlots[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 0);
    l = rand()%YCPlotcount;
    s = rand()%YCPlots[l].spaceCount;
    makeUpdatePacket("update.JSON", 0, 0, l, s, YCPlots[l].space[s].popularity, YCPlots[l].space[s].timeTaken);
    sendPacket("update.JSON" ,"/api/update/space", 0);

    l = rand()%airportlotcount;
    s = rand()%airport[l].spaceCount;
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
