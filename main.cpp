#include <iostream>
#include <cstring>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

/*
Lina Goto
2/22/24
sort and print numbers from input and file by use of heap
*/


static int childleft (int i) { return 2 * i + 1; }
static int childright(int i) { return 2 * i + 2; }
static int parent    (int i) { return (i - 1) / 2; }
static int depth     (int i) { int count = 0; i --; while (i > 0) { count ++; i = parent(i); }; return count; }
static int width     (int i) { return (1 << i); }

void print(int count, int *array){
  int d, w, i, z, chl, chr;

  //go through the depth
  for (d = 0; d < depth(count) + 1; d ++) {
    //find out the spaces needed for each row
    int gap = (width(depth(count) - d) - 1) * 4;
    //put half of the gap for the first
    for (z = 0; z < gap / 2; z ++)  { cout << " "; };
    //put numbers of width
    for (w = 0; w < width(d); w ++) {
      //tracking number of printout
      i = width(d) - 1 + w;
      if (i < count) {
	cout << setw(4) << array[i];
	//put spaces
	if (w < width(d) - 1) {
	  for (z = 0; z < gap; z ++) { cout << " "; }
	}
      }
    }
    //return
    cout << endl;
  }
  //return
  cout << endl;
}

void order(int count, int *array){
  //p is parent
  int p;

  // decrement by 1 to point out the last
  count --;

  //nothing if count is too small
  if (count < 1) return;

  //switch out the numbers if parent is smaller
  while (count > 0) {
    p = parent(count);
    if (array[count] > array[p]){
      int save = array[count];
      array[count] = array[p];
      array [p] = save;
    }
    //set count to the parent count
    count = p;
  }
}

void reorder(int number, int *array){
  int count = 0;

  //while it does not reach the end
  while(count < number){
    //find the left and right child
    int lchild = childleft (count);
    int rchild = childright(count);
    //if both child exists
    if (lchild < number && rchild < number) {
    //if child left is bigger than right and the parent
      if (array[lchild] >= array[rchild] && array[lchild] > array[count]) {
	int save = array[count];
	array[count] = array[lchild];
	array[lchild] = save;
	count = lchild;
      } else 
	//if child right is bigger than left and the parent
	if (array[lchild] <= array[rchild] && array[rchild] > array[count]) {
	  int save = array[count];
	  array[count] = array[rchild];
	  array[rchild] = save;
	  count = rchild;
	}
      //break if there is nothing
	else break;

    } else
      //if one child exist and if it is bigger than the parent
      if (lchild < number && rchild >= number && array[lchild] > array[count]){
	int save = array[count];
	array[count] = array[lchild];
	array[lchild] = save;
	count = lchild;
      }
    //break if ther is nothing
      else break;
  }
}

int main(void){
  //set 100 values and track heap number
  int heap[100];
  int track = 0;

  //input or by file
  char input [10];
  cout << "input or file?: " << endl;
  cin.get (input, 10);
  cin.get(); 
  
  //number entered by input
  if (input[0] == 'i' || input[0] == 'I'){
    int num;
    //how many entries are going to be made
    cout << "Total number of entries? " << endl;
    cin >> track;
    cin.get();

    //get each entry
    for (num = 0; num < track; num ++) {
      int newnum;
      cout << "number for " << num << "?" << endl;
      cin >> newnum;
      cin.get();

      heap[num] = newnum;
      
      //order heap
      order(num + 1, heap);
    }

  } else{
      string myText;
      
      //Read from the text file
      ifstream MyReadFile("random_number.txt");
      
      //read the file and send it to viod file
      getline (MyReadFile, myText);
      stringstream MyStreamText(myText);

      //get each number and order it
      while(getline(MyStreamText, myText, ' ')) {

	heap[track] = atoi(myText.c_str());
	track ++;
	
	//order heap
	order(track, heap);
      }
      
      // Close the file
      MyReadFile.close();
  }
  
  //print out
  print(track, heap);

  //print out all the numbers from big to small
  while(track > 0){
    cout << heap[0] << endl;
    heap[0] = heap[track-1];
    track--;
    //reorder to find the next largest one
    reorder(track, heap);

  }


  
  return 0;
}
