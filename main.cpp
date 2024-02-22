#include <iostream>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <fstream>

using namespace std;

static int childleft (int i) { return 2 * i + 1; }
static int childright(int i) { return 2 * i + 2; }
static int parent    (int i) { return (i - 1) / 2; }
static int depth     (int i) { int count = 0; i --; while (i > 0) { count ++; i = parent(i); }; return count; }
static int width     (int i) { return (1 << i); }

void print(int count, int *array){
  int d, w, i, z, chl, chr;
  
  for (d = 0; d < depth(count) + 1; d ++) {
    int gap = (width(depth(count) - d) - 1) * 4;
    for (z = 0; z < gap / 2; z ++) printf(" ");
    for (w = 0; w < width(d); w ++) {
      i = width(d) - 1 + w;
      if (i < count) {
	printf("%4d", array[i]);
	if (w < width(d) - 1) {
	  for (z = 0; z < gap; z ++) printf(" ");
	}
      }
    }
      printf("\n");
  }
  printf("\n");
}

void order(int count, int *array){
  //p is parent
  int p = parent(count);
  
  while (array[count] > array[p]){
    int save = array[count];
    array[count] = array[p];
    array [p] = save;

    count = p;
    p = parent(count);
  }
}

void file (const char *text, int *array, int number){
  char taken [10];
  int takennum  = 0;
  int arraycount = 0;

  for (int i=0; i<number; i++){
    if (text[i] != ' '){
      taken[takennum] = text[i];
      takennum++;
    }
    if (text[i] == ' '){
      int value = atoi(taken);
      array[arraycount] = value;
      arraycount ++;
      taken[0] = '\0';
      value = 0;
    }
  }
  
  
}

int main(void){

  int heap[100];
  int track =0;
  bool play = true;
  do{
    //input or by file
    char input [10];
    cout << "input or file?: " << endl;
    cin.get (input, 10);
    cin.get(); 
    
    
    //number entered by input
    if (input[0] == 'i' || input[0] == 'I'){
      if (track < 100){
	cout << "enter a number:" << endl;
	int num;
	cin >> num;
	cin.get();
	heap[track] = num;
	track ++;
	//order heap
	order(track, heap);
	print(track, heap);
      }
      else{
	cout << "there are already 100 inputs" << endl;
      }
    }
    
    else{
      string myText;
      
      //Read from the text file
      ifstream MyReadFile("random number.txt");
      
      //read the file and send it to viod file
      getline (MyReadFile, myText);
      file (myText.c_str(), heap, myText.length());
      
      // Close the file
      MyReadFile.close();

      print(track, heap);
      }

    /*  
    for (track = 0; track < 10; track ++) {
      heap[track] = rand() % 20;
      print (track, heap);
      printf("  x x x x\n");
      order(track, heap);
      print (track, heap);
      printf(" --------\n");
      }
    */
  }while(play == true);
}
