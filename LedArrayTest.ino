#include "Arduino_LED_Matrix.h"
#include <vector>
using namespace std;

ArduinoLEDMatrix matrix;


vector<vector<byte>> all_frames;
int step = 0;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  
  Serial.println("Started.");

  vector<vector<byte>> empty_frame = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  vector<vector<byte>> buffer_frame = {
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0}  
  };

  vector<vector<byte>> h_frame = {
    { 0, 0, 0 },
    { 1, 0, 1 },
    { 1, 0, 1 },
    { 1, 1, 1 },
    { 1, 0, 1 },
    { 1, 0, 1 },
    { 0, 0, 0 },
    { 0, 0, 0 } 
  };

  vector<vector<byte>> i_frame = {
    { 0, 0, 0 },
    { 1, 1, 1 },
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 1, 1, 1 },
    { 0, 0, 0 },
    { 0, 0, 0 } 
  };

  vector<vector<byte>> heart_frame = {
    { 0, 1, 1, 0, 0, 0, 1, 1, 0},
    { 1, 0, 0, 1, 0, 1, 0, 0, 1},
    { 1, 0, 0, 0, 1, 0, 0, 0, 1},
    { 1, 0, 0, 0, 0, 0, 0, 0, 1},
    { 0, 1, 0, 0, 0, 0, 0, 1, 0},
    { 0, 0, 1, 0, 0, 0, 1, 0, 0},
    { 0, 0, 0, 1, 0, 1, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 0, 0, 0}
  };

  vector<vector<byte>> happy_frame = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };


  vector<vector<vector<byte>>> frame_sequence = {
    happy_frame,
    empty_frame,
    heart_frame,
    buffer_frame,
    h_frame,
    buffer_frame,
    i_frame,
    buffer_frame,
    heart_frame,
    empty_frame,
    happy_frame
  };

  all_frames = frame_sequence[0];

  for (int i = 1; i < frame_sequence.size(); i++) {
    vector<vector<byte>> tempVec;
    tempVec.resize(all_frames.size());
    for (int j = 0; j < all_frames.size(); j++) {
      tempVec[j].reserve(all_frames[j].size() + frame_sequence[i][j].size());
      tempVec[j].insert(tempVec[j].end(), all_frames[j].begin(), all_frames[j].end());
      tempVec[j].insert(tempVec[j].end(), frame_sequence[i][j].begin(), frame_sequence[i][j].end());
    }
    all_frames = tempVec;
  }
}

void loop(){
  updateFrame();
  step++;
  delay(100);
}

void printVec(vector<vector<byte>> vec) {
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      Serial.print(vec[i][j]);
    }
    Serial.print("\n");
  }
}

void updateFrame() {
  if (step + 12 > all_frames[0].size()) {
    for (int i = 0; i < 3; i++) {
      flashHappy();
    }
    step = 0;
  }

  byte frame[8][12] = {{0}};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = all_frames[i][j+step];
    }
  }
  matrix.renderBitmap(frame, 8, 12);
}

void flashHappy() {

  vector<vector<byte>> empty_frame = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  vector<vector<byte>> happy_frame = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  byte frame[8][12] = {{0}};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = empty_frame[i][j];
    }
  }
  matrix.renderBitmap(frame, 8, 12);
  delay(250);
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = happy_frame[i][j];
    }
  }
  matrix.renderBitmap(frame, 8, 12);
  delay(250);
}

