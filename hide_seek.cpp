#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<stack>
#include<utility>
#include<vector>

using namespace std;

// Global variables
int rows = 10, columns=10;
pair<int, int> search, hide;
vector< vector<int> > visited(rows, vector<int>(columns, 0));
vector< vector<char> >map(rows, vector<char>(columns, '0')), map_res(rows, vector<char>(columns, '0'));
vector<vector<pair<int, int>>> previous(rows, vector<pair<int, int>>(columns, make_pair(-1,-1)));
vector<pair<int, int>> direction = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
stack<pair<int, int>> path;
vector<char>  map_elements{'_','_','_','_','_','_','_','#','#','#'};
queue<pair<int, int>> q;
bool solved = false;

// Generate a random map
void fill_map(){
  char aux;
  for(int i=0; i<rows; i++){
    for(int j=0; j<columns; j++){
      // Look if i and j are at the position of the start or goal points
      if(i==search.first && j==search.second)
        map[i][j] = 'S';
      else if(i==hide.first && j==hide.second)
        map[i][j] = 'H';
      // else choose a random char between '_' and '#'
      else {
        aux = map_elements[rand() % 10];
        map[i][j] = aux;
      }
      cout << map[i][j] << " ";
    }
    cout << "\n";
  }
}

void adjacentNodes(int row, int column){
  pair<int, int> next;
  // Verify if the adjacent nodes are valid
  for(int i=0; i<4; i++){
    next.first = row + direction[i].first;
    next.second = column + direction[i].second;
    // See if the adjecent positions are out of bounds
    if(next.first < 0 || next.second < 0)
      continue;
    // See if the adjecent positions are out of bounds
    if(next.first >= rows || next.second >= columns)
      continue;
    // Make sure that the node hasn'n been visited
    if(visited[next.first][next.second]==1)
      continue;
    // Make sure that the adjacent node is not a block
    if(map[next.first][next.second] == '#')
      continue;
    // Push the node to the q
    q.push(make_pair(next.first, next.second));
    // Set the new node's position as visited
    visited[next.first][next.second] = 1;
    // Write its previous node
    previous[next.first][next.second] = make_pair(row, column);
  }
}

int find_path (){
  int row, column;
  // push the start position to the queue
  q.push(make_pair(search.first, search.second));
  visited[search.first][search.second] = 1;
  while (q.size() > 0){
    // Get the row and column of the first element of the que and pop it so you don't go over it again
    row = q.front().first;
    column = q.front().second;
    q.pop();
    // Verify if the element of the queue was at the same position of the goal
    // If it is then stop searching and return true.
    if (map[row][column] == 'H'){
      solved = true;
      break;
    }
    // Look for the adjacent nodes and push them into the queue
    adjacentNodes(row, column);
  }
  // If there is a solution return true
  if(solved)
    return solved;
  return false;
}

void mark_path (){
  char aux;
  pair<int, int> i;
  // Copy the original map so you do not modify it and compare at the end
  map_res = map;
  while(!path.empty()){
    // get the top element of the stack and store it in a temporary variable
    i = path.top();
    // remove the top element from the stack
    path.pop();
    // modify the copy of the map so the path can be shown with a diferent character
    map_res[i.first][i.second] = '|';
  }
  // print both maps at the same time
  for(int i=0; i<rows; i++){
    for(int j=0; j<columns; j++){
      cout << map[i][j] << " ";
    }
    cout << "\t";
    for(int j=0; j<columns; j++){
      cout << map_res[i][j] << " ";
    }
    cout << "\n";
  }
}

int main() {
  srand(time(0));
  // Randomly get the starting points of the 2 players
  search = make_pair(rand() % 10, rand() % 10);
  hide = make_pair(rand() % 10, rand() % 10);

  // Generate the playground
  fill_map();
  cout << "\n";
  // Look if there is a solution with the function find_path
  if(find_path()){
    pair<int, int> j = {-1,-1};
    // We have to backtrack from the hidding player to build the path
    for(hide; hide!=j; hide=previous[hide.first][hide.second]){
      // We use the path stack to reverse the order
      path.push(hide);
    }
    // Draw the path in the matrix and print it
    mark_path();
  }
  else
    cout << "There is no solution";
}
