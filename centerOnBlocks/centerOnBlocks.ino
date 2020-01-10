
#include <Pixy2.h>

// This is the main Pixy object 
Pixy2 pixy;

//Globale Variablen
int nrBl = 0;   //anzahl erkannte Blöcke

void setup() {
  
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  pixy.init();
  
}

void loop() {

  float rSchub = 0;
  float lSchub = 0;
    

  if (countBlocks()){

  float xPos = 0;

  if (countBlocks() > 1){
    xPos = pixy.ccc.blocks[closestBlock()].m_x;
    }
    else{
      xPos = pixy.ccc.blocks[0].m_x;
      }

//158 ist die Mittelposition, da die Auflösung bei 316 ist
  if (xPos < 158){
    // Rechts mehr Schub
    rSchub = -0.6329 * xPos + 100;
    }
    else{
      //Links mehr Schub
      lSchub = 0.6329 * xPos - 100;
      }
  }
  
  Serial.print("Anzahl erkannte Blocks: ");
  Serial.println(countBlocks());
  //Serial.println(closestBlock());
  Serial.print("Links ");
  Serial.print(lSchub);
  Serial.println("% mehr Schub");
  Serial.print("Rechts ");
  Serial.print(rSchub);
  Serial.println("% mehr Schub");
  delay(400);

}

int countBlocks(){
  
    // grab blocks!
    pixy.ccc.getBlocks();
  
    return (pixy.ccc.numBlocks);
      
  }

int closestBlock(){
  
    // grab blocks!
    pixy.ccc.getBlocks();

    int number = countBlocks();
    int closest = 0;
    int maxWidth = 0; 

    for (int i = 1; i > number; i++){
      if (maxWidth < pixy.ccc.blocks[i].m_width){
        maxWidth = pixy.ccc.blocks[i].m_width;
        }
        else{
          closest = i;
          }
      
      }
  return closest;
  }
