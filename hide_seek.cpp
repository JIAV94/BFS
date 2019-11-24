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

void fill_map(){
  char aux;
  for(int i=0; i<rows; i++){
    for(int j=0; j<columns; j++){
      if(i==search.first && j==search.second)
        map[i][j] = 'S';
      else if(i==hide.first && j==hide.second)
        map[i][j] = 'H';
      else {
        aux = map_elements[rand() % 10];
        map[i][j] = aux;
      }
      cout << map[i][j] << " ";
    }
    cout << "\n";
  }
}

void adjacentNodes(int row, int column){ //rows, columns, direction_x, direction_y, visited
  pair<int, int> next;
  for(int i=0; i<4; i++){
    next.first = row + direction[i].first;
    next.second = column + direction[i].second;
    if(next.first < 0 || next.second < 0)
      continue;
    if(next.first >= rows || next.second >= columns)
      continue;
    if(visited[next.first][next.second]==1)
      continue;
    if(map[next.first][next.second] == '#')
      continue;
    q.push(make_pair(next.first, next.second));
    visited[next.first][next.second] = 1;
    previous[next.first][next.second] = make_pair(row, column);
  }
}

int find_path (){ //q_x, q_y, start_x, start_y, map, solved
  int row, column;
  q.push(make_pair(search.first, search.second));
  visited[search.first][search.second] = 1;
  while (q.size() > 0){
    row = q.front().first;
    column = q.front().second;
    q.pop();
    if (map[row][column] == 'H'){
      solved = true;
      break;
    }
    adjacentNodes(row, column);
  }
  if(solved)
    return solved;
  return false;
}

void mark_path (){
  char aux;
  pair<int, int> i;
  map_res = map;
  while(!path.empty()){
    i = path.top();
    path.pop();
    map_res[i.first][i.second] = '|';
  }
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
      // We use the path stack to invert the order
      path.push(hide);
    }
    // Draw the path in the matrix and print it
    mark_path();
  }
  else
    cout << "There is no solution";
}
