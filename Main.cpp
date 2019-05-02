#include <iostream>
#include "Graph.h"
using namespace std;
/*
Ralph Mehitang
Professor Anderson
Cosc-320
Lab11
*/
int menu(Graph<int>& g)
{
    int input = 0;
while(input!=7){
  /* code */
    cout << "Menu:" << endl;
    cout << "1. Add Node" << endl;
    cout << "2. Add Edge" << endl;
    cout << "3. Depth First Search" << endl;
    cout << "4. Topological Sort" << endl;
    cout << "5. Connected Components" << endl;
    cout << "6. Print" <<endl;
    cout << "7. Quit" << endl;
    cout << "Please input the option you would like: ";
    cin >> input;
    cout << "---------------------------------------" << endl;

        switch(input)
        {
            case 1:
            {
                cout<< "what int would you like to add?";
        int add = 0;
        cin >> add;
        g.addVertex(add);
                break;
            }
            case 2:
            {
                int v = 0, u = 0;
        cout << "Vertex 1: ";
        cin >> v;
        cout << "Vertex 2: ";
        cin >> u;

        g.addEdge(v, u);
        break;
            }

      case 3:
      {
        cout << "What vertex would you like to start at? ";
        int start = 0;
        cin >> start;
        g.Dfs(start);
                break;
      }
      case 4:
      {
        vector<int> x = g.topoSort();
        cout << endl;
        for(int a : x)
          cout << a << " ";
        cout << endl;
        break;
      }
      case 5:
      {
        vector<vector<int>> x = g.connectedComps();
        cout << endl;
        for(vector<int> a : x)
        {
          for(int b : a)
          {	cout << b; }
          cout << endl;
        }
        break;
      }
      case 6:
        {

                g.print();
                break;
            }
      case 7:
      {

                exit(-1);
                break;
            }
        }
      }
}


int main()
{
    Graph<int> g = Graph<int>(true);
    menu(g);
    return 0;
}
