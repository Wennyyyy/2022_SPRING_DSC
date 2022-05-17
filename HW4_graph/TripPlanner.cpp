// ===================================================================
// Copyright © 2022 Wynne Lin
//
// All rights reserved.
// This program is free to use, but the ban on selling behavior.
// Modify the program must keep all the original text description,
// and can only comment out the original code (not allowed to delete).
// ===================================================================
// Language: C++
// -------------------------------------------------------------------
// Descript:
//     <DSC HW4 GRAPH> TripPlanner
// ===================================================================
#include <float.h>
#include <limits.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// -----------------------------------------------
// Variable and Function Declare
// -----------------------------------------------
class Tourism {
   public:
    string Name;
    int Index;
    int PS;
    bool State;
};

class Graph_SP {
#ifdef _WYNNE_DEBUG_
   public:
#else   // _WYNNE_DEBUG_
   private:
#endif  // _WYNNE_DEBUG_
    class time_chart_type {
       public:
        int pre_position = -1;
        int optimal_time = INT_MAX;
        int total_PS = 0;
        int second_index = 0;
    };

    class flow_chart_type {
       public:
        int pre_position = -1;
        double optimal_flow = DBL_MAX;
        int total_PS = 0;
        int second_index = 0;
    };
    int N;
    Tourism *tourism;
    int **time;
    double **flow;

    // <previous position, optimal time>
    time_chart_type **optimal_time_chart;

    // <previous position, optimal flow>
    flow_chart_type **optimal_flow_chart;

    int start_pos;

    void build_optimal_time_chart();
    void build_optimal_flow_chart();

   public:
    Graph_SP(int N, Tourism *tourism, int **time, double **flow);
    ~Graph_SP();
    bool set_origin(string place_name);
    bool mark_state(string place_name, bool status);
    stack<string> limited_path_time(string place_name, int limit);
    stack<string> limited_path_flow(string place_name, int limit);
    stack<string> optimal_path_time(string place_name);
    stack<string> optimal_path_flow(string place_name);
    void update_chart();
};

vector<string> divide_str(string s);
// ===============================================
// Main
// ===============================================
int main(int argc, char **argv) {
    int N;
    Tourism *tourism;
    int **time;
    double **flow;
    int start_pos;
    string line, place_name, status;
    vector<string> command;
    Graph_SP *graph_SP;

    cin >> N;

    // Initial
    tourism = new Tourism[N];
    time = new int *[N];
    flow = new double *[N];
    for (int i = 0; i < N; ++i) {
        time[i] = new int[N];
        flow[i] = new double[N];
    }

    // tourism
    for (int i = 0; i < N; i++) {
        cin >> tourism[i].Index >> tourism[i].Name >> tourism[i].PS;
        tourism[i].State = 1;
    }

    // time
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> time[i][j];
        }
    }

    // flow
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double x;
            cin >> x;
            flow[i][j] = log(x);
        }
    }

    // graph_SP
    graph_SP = new Graph_SP(N, tourism, time, flow);
#ifdef _WYNNE_DEBUG_
    cout << "graph_SP -> tourism" << endl;
    for (int i = 0; i < N; ++i) {
        cout << setw(4) << i << "|";
        cout << "("
             << setw(2) << graph_SP->tourism[i].Index << ","
             << setw(5) << graph_SP->tourism[i].Name << ","
             << setw(2) << graph_SP->tourism[i].PS << ","
             << setw(2) << graph_SP->tourism[i].State << ""
             << ")|";
        cout << endl;
    }

    cout << "graph_SP -> flow" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(8) << setprecision(4) << flow[i][j] << "|";
        }
        cout << endl;
    }
#endif  // _WYNNE_DEBUG_
    while (true) {
        char enter;
        enter = cin.get();

        if (enter == '\n') {
            break;
        }
    }
    getline(cin, line);
    command = divide_str(line);
#ifdef _WYNNE_DEBUG_
    cout << "Command: ";
    for (int i = 0; i < command.size(); i++) {
        cout << command[i] << "|";
    }
    cout << endl;
#endif  // _WYNNE_DEBUG_
    while (command[0] != "END_OF_INSTRUCTION") {
        if (command[0] == "SET_ORIGIN") {
            place_name = command[1];
            if (graph_SP->set_origin(place_name)) {
                cout << place_name << " is the new origin" << endl;
            } else {
                cout << "Fail to reset the origin" << endl;
            }
        } else if (command[0] == "MARK_STATE") {
            bool is_modified = false;

            status = command[1];
            if (status == "CLOSE") {
                for (int i = 2; i < command.size(); ++i) {
                    place_name = command[i];
                    if (!graph_SP->mark_state(place_name, false)) {
                        cout << "Fail to close " << place_name << endl;
                    } else {
                        is_modified = true;
                    }
                }
            } else {
                for (int i = 2; i < command.size(); ++i) {
                    place_name = command[i];
                    if (!graph_SP->mark_state(place_name, true)) {
                        cout << "Fail to open " << place_name << endl;
                    } else {
                        is_modified = true;
                    }
                }
            }
            if (is_modified) {
                graph_SP->update_chart();
            }
        } else if (command[0] == "OPTIMAL_PATH") {
            stack<string> optimal_path;
            if (command[2] == "TIME") {
                optimal_path = graph_SP->optimal_path_time(command[1]);
                if (!optimal_path.empty()) {
                    string first = optimal_path.top();
                    int len = first.length();
                    optimal_path.pop();
                    while (!optimal_path.empty()) {
                        string next = optimal_path.top();
                        // equal (A -> A)
                        if (!first.compare(next)) {
                            cout << "No such optimal path to " << command[1];
                            break;
                        } else {
                            if (len) {
                                cout << "Optimal TIME : " << first;
                                len = 0;
                            }
                            cout << " -> " << next;
                            optimal_path.pop();
                        }
                    }
                    cout << endl;
                } else {
                    cout << "No such optimal path to " << command[1] << endl;
                }

            } else {
                optimal_path = graph_SP->optimal_path_flow(command[1]);
                if (!optimal_path.empty()) {
                    cout << "Optimal FLOW : ";
                    cout << optimal_path.top();
                    optimal_path.pop();
                    while (!optimal_path.empty()) {
                        cout << " -> " << optimal_path.top();
                        optimal_path.pop();
                    }
                    cout << endl;
                } else {
                    cout << "No such optimal path to " << command[1] << endl;
                }
            }
        } else if (command[0] == "LIMITED_PATH") {
            stack<string> optimal_path;
            if (command[2] == "TIME") {
                optimal_path = graph_SP->limited_path_time(command[1], stoi(command[3]));
                if (!optimal_path.empty()) {
                    cout << "Limited TIME : ";
                    cout << optimal_path.top();
                    optimal_path.pop();
                    while (!optimal_path.empty()) {
                        cout << " -> " << optimal_path.top();
                        optimal_path.pop();
                    }
                    cout << endl;
                } else {
                    cout << "No such optimal path to " << command[1] << endl;
                }

            } else {
                optimal_path = graph_SP->limited_path_flow(command[1], stoi(command[3]));
                // string first = optimal_path.top();
                // int len = first.length();
                // optimal_path.pop();
                if (!optimal_path.empty()) {
                    cout << "Limited FLOW : ";
                    // if( len ){
                    //     cout << first;
                    //     len = 0;
                    // }else{
                    cout << optimal_path.top();
                    // }
                    optimal_path.pop();
                    while (!optimal_path.empty()) {
                        cout << " -> " << optimal_path.top();
                        optimal_path.pop();
                    }
                    cout << endl;
                } else {
                    cout << "No such optimal path to " << command[1] << endl;
                }
            }
        }

#ifdef _WYNNE_DEBUG_
        cout << "INT_MAX:" << INT_MAX << endl;
        cout << "graph_SP -> optimal_time" << endl;
        cout << "(pre_position, optimal_time, total_PS, second_index)" << endl;
        cout << "    |";
        for (int i = 0; i < N; ++i) {
            cout << setw(16) << i << "|";
        }
        cout << endl;
        for (int i = 0; i < (17 * (N) + 5); ++i) {
            cout << "-";
        }
        cout << endl;
        for (int i = 1; i < N; ++i) {
            cout << setw(4) << i << "|";
            for (int j = 0; j < N; ++j) {
                cout << "("
                     << setw(2) << graph_SP->optimal_time_chart[i][j].pre_position << ","
                     << setw(5) << graph_SP->optimal_time_chart[i][j].optimal_time << ","
                     << setw(2) << graph_SP->optimal_time_chart[i][j].total_PS << ","
                     << setw(2) << graph_SP->optimal_time_chart[i][j].second_index
                     << ")|";
            }
            cout << endl;
        }

        cout << "DBL_MAX:" << DBL_MAX << endl;
        cout << "graph_SP -> optimal_flow_chart" << endl;
        cout << "(pre_position, optimal_flow, total_PS, second_index)" << endl;
        cout << "    |";
        for (int i = 0; i < N; ++i) {
            cout << setw(20) << i << "|";
        }
        cout << endl;
        for (int i = 0; i < (21 * (N) + 5); ++i) {
            cout << "-";
        }
        cout << endl;
        for (int i = 1; i < N; ++i) {
            cout << setw(4) << i << "|";
            for (int j = 0; j < N; ++j) {
                cout << "("
                     << setw(2) << graph_SP->optimal_flow_chart[i][j].pre_position << ","
                     << setw(9) << setprecision(2) << graph_SP->optimal_flow_chart[i][j].optimal_flow << ","
                     << setw(2) << graph_SP->optimal_flow_chart[i][j].total_PS << ","
                     << setw(2) << graph_SP->optimal_flow_chart[i][j].second_index
                     << ")|";
            }
            cout << endl;
        }
#endif  // _WYNNE_DEBUG_
        getline(cin, line);
        command = divide_str(line);
#ifdef _WYNNE_DEBUG_
        cout << "Command: ";
        for (int i = 0; i < command.size(); i++) {
            cout << command[i] << "|";
        }
        cout << endl;
#endif  // _WYNNE_DEBUG_
    }

    cout << "Stop receiving instructions" << endl;
    return 0;
}

// ===============================================
// Function Implement
// ===============================================
// -----------------------------------------------
// divide str
// -----------------------------------------------
// Description:
//     Divide string by space
// -----------------------------------------------
vector<string> divide_str(string s) {
    stringstream ss(s);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    return vstrings;
}

// -----------------------------------------------
// Graph_SP Constructor
// -----------------------------------------------
// Description:
//     Initial data
// -----------------------------------------------
Graph_SP::Graph_SP(int N, Tourism *tourism, int **time, double **flow)
    : N(N), tourism(tourism), time(time), flow(flow), start_pos(-1) {
    this->optimal_time_chart = new time_chart_type *[N + 1];
    this->optimal_flow_chart = new flow_chart_type *[N + 1];

    for (int i = 0; i <= N; ++i) {
        this->optimal_time_chart[i] = new time_chart_type[N];
        this->optimal_flow_chart[i] = new flow_chart_type[N];
    }
}

// -----------------------------------------------
// Graph_SP Destructor
// -----------------------------------------------
// Description:
//     delete data
// -----------------------------------------------
Graph_SP::~Graph_SP() {
    delete this->tourism;
    for (int i = 0; i < N; ++i) {
        delete this->time[i];
        delete this->flow[i];
        delete this->optimal_flow_chart[i];
        delete this->optimal_time_chart[i];
    }
    delete this->time;
    delete this->flow;
    delete this->optimal_flow_chart;
    delete this->optimal_time_chart;
}

// -----------------------------------------------
// Graph_SP::set_origin
// -----------------------------------------------
// Description:
//     Set origin space
// -----------------------------------------------
bool Graph_SP::set_origin(string place_name) {
    for (int i = 0; i < this->N; i++) {
        if (place_name == tourism[i].Name && tourism[i].State == 1) {
            if (this->start_pos != i) {
                this->start_pos = i;

                // Update Chart
                update_chart();
            }
            return true;
        }
    }
    return false;
}

// -----------------------------------------------
// Graph_SP::build_optimal_time_chart
// -----------------------------------------------
// Description:
//     Use Bellman–Ford algorithm to build optimal
// time chart
// -----------------------------------------------
void Graph_SP::build_optimal_time_chart() {
    for (int i = 0; i < this->N; ++i) {
        if (tourism[i].State) {
            if (i == start_pos) {
                this->optimal_time_chart[1][i].total_PS = this->tourism[this->start_pos].PS;
            } else {
                this->optimal_time_chart[1][i].total_PS = this->tourism[this->start_pos].PS + this->tourism[i].PS;
            }
            this->optimal_time_chart[1][i].pre_position = this->start_pos;
            this->optimal_time_chart[1][i].optimal_time = this->time[this->start_pos][i];
            this->optimal_time_chart[1][i].second_index = i;
        } else {
            this->optimal_time_chart[1][i].pre_position = -1;
            this->optimal_time_chart[1][i].optimal_time = 0;
            this->optimal_time_chart[1][i].total_PS = 0;
            this->optimal_time_chart[1][i].second_index = i;
        }
    }
    for (int i = 2; i <= this->N; ++i) {
        for (int j = 0; j < this->N; ++j) {
            if (tourism[j].State) {
                this->optimal_time_chart[i][j].pre_position = this->optimal_time_chart[i - 1][j].pre_position;
                this->optimal_time_chart[i][j].optimal_time = this->optimal_time_chart[i - 1][j].optimal_time;
                this->optimal_time_chart[i][j].total_PS = this->optimal_time_chart[i - 1][j].total_PS;
                this->optimal_time_chart[i][j].second_index = this->optimal_time_chart[i - 1][j].second_index;

                if (j != start_pos) {
                    for (int k = 0; k < this->N; ++k) {
                        if (k != j && this->tourism[k].State) {
                            int new_time = this->optimal_time_chart[i - 1][k].optimal_time + this->time[k][j];
                            int new_PS = this->optimal_time_chart[i - 1][k].total_PS + this->tourism[j].PS;

                            if (new_time < this->optimal_time_chart[i][j].optimal_time) {
                                this->optimal_time_chart[i][j].pre_position = k;
                                this->optimal_time_chart[i][j].optimal_time = new_time;
                            } else if (new_time == this->optimal_time_chart[i][j].optimal_time) {
                                if (new_PS > this->optimal_time_chart[i][j].total_PS) {
                                    this->optimal_time_chart[i][j].pre_position = k;
                                    this->optimal_time_chart[i][j].total_PS = new_PS;
                                } else if ((new_PS == this->optimal_time_chart[i][j].total_PS) && (this->optimal_time_chart[i - 1][k].second_index < this->optimal_time_chart[i][j].second_index)) {
                                    this->optimal_time_chart[i][j].pre_position = k;
                                    this->optimal_time_chart[i][j].second_index = this->optimal_time_chart[i - 1][k].second_index;
                                }
                            }
                        }
                    }
                }
            } else {
                optimal_time_chart[i][j].pre_position = -1;
                optimal_time_chart[i][j].optimal_time = 0;
                optimal_time_chart[i][j].total_PS = 0;
                optimal_time_chart[i][j].second_index = j;
            }
        }
    }
}

// -----------------------------------------------
// Graph_SP::build_optimal_flow_chart
// -----------------------------------------------
// Description:
//     Use Bellman–Ford algorithm to build optimal
// flow chart
// -----------------------------------------------
void Graph_SP::build_optimal_flow_chart() {
    for (int i = 0; i < this->N; ++i) {
        if (tourism[i].State) {
            if (i == start_pos) {
                this->optimal_flow_chart[1][i].total_PS = this->tourism[this->start_pos].PS;
            } else {
                this->optimal_flow_chart[1][i].total_PS = this->tourism[this->start_pos].PS + this->tourism[i].PS;
            }
            this->optimal_flow_chart[1][i].pre_position = this->start_pos;
            this->optimal_flow_chart[1][i].optimal_flow = this->flow[this->start_pos][i];
            this->optimal_flow_chart[1][i].second_index = i;
        } else {
            this->optimal_flow_chart[1][i].pre_position = -1;
            this->optimal_flow_chart[1][i].optimal_flow = 0;
            this->optimal_flow_chart[1][i].total_PS = 0;
            this->optimal_flow_chart[1][i].second_index = i;
        }
    }
    for (int i = 2; i <= this->N; ++i) {
        for (int j = 0; j < this->N; ++j) {
            if (tourism[j].State) {
                this->optimal_flow_chart[i][j].pre_position = this->optimal_flow_chart[i - 1][j].pre_position;
                this->optimal_flow_chart[i][j].optimal_flow = this->optimal_flow_chart[i - 1][j].optimal_flow;
                this->optimal_flow_chart[i][j].total_PS = this->optimal_flow_chart[i - 1][j].total_PS;
                this->optimal_flow_chart[i][j].second_index = this->optimal_flow_chart[i - 1][j].second_index;

                if (j != start_pos) {
                    for (int k = 0; k < this->N; ++k) {
                        if (k != j && this->tourism[k].State) {
                            double new_flow = this->optimal_flow_chart[i - 1][k].optimal_flow + this->flow[k][j];
                            int new_PS = this->optimal_flow_chart[i - 1][k].total_PS + this->tourism[j].PS;

                            if (new_flow > this->optimal_flow_chart[i][j].optimal_flow) {
                                this->optimal_flow_chart[i][j].pre_position = k;
                                this->optimal_flow_chart[i][j].optimal_flow = new_flow;
                            } else if (new_flow == this->optimal_flow_chart[i][j].optimal_flow) {
                                if (new_PS > this->optimal_flow_chart[i][j].total_PS) {
                                    this->optimal_flow_chart[i][j].pre_position = k;
                                    this->optimal_flow_chart[i][j].total_PS = new_PS;
                                } else if ((new_PS == this->optimal_flow_chart[i][j].total_PS) && (this->optimal_flow_chart[i - 1][k].second_index < this->optimal_flow_chart[i][j].second_index)) {
                                    this->optimal_flow_chart[i][j].pre_position = k;
                                    this->optimal_flow_chart[i][j].second_index = this->optimal_flow_chart[i - 1][k].second_index;
                                }
                            }
                        }
                    }
                }
            } else {
                optimal_flow_chart[i][j].pre_position = -1;
                optimal_flow_chart[i][j].optimal_flow = 0;
                optimal_flow_chart[i][j].total_PS = 0;
                optimal_flow_chart[i][j].second_index = j;
            }
        }
    }
}

// -----------------------------------------------
// Graph_SP::mark_state
// -----------------------------------------------
// Description:
//     Mark place state
// -----------------------------------------------
bool Graph_SP::mark_state(string place_name, bool status) {
    for (int i = 0; i < this->N; i++) {
        if (place_name == this->tourism[i].Name) {
            if (i == this->start_pos) {
                return true;
            } else if (this->tourism[i].State != status) {
                this->tourism[i].State = status;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

// -----------------------------------------------
// Graph_SP::update_chart
// -----------------------------------------------
// Description:
//     Update Chart.
// -----------------------------------------------
void Graph_SP::update_chart() {
    // build optimal_time_chart
#ifdef _WYNNE_DEBUG_
    cout << "Start build optimal time chart." << endl;
    cout << "Start position is " << this->start_pos << endl;
#endif  // _WYNNE_DEBUG_
    build_optimal_time_chart();

    // build optimal_flow_chart
    build_optimal_flow_chart();
}

// -----------------------------------------------
// Graph_SP::optimal_path
// -----------------------------------------------
// Description:
//     Return optimal path
// -----------------------------------------------
stack<string> Graph_SP::optimal_path_time(string place_name) {
    stack<string> final_path;
    for (int i = 0; i < this->N; i++) {
        // find the destination and check if it is open.
        if (place_name == tourism[i].Name && tourism[i].State == 1) {
            int pos = i;
            int times = N;
            while (times > 1) {
                if (optimal_time_chart[times][pos].pre_position == optimal_time_chart[times - 1][pos].pre_position) {
                    times--;
                } else {
                    break;
                }
            }
            while (times > 0) {
                final_path.push(tourism[pos].Name);
                pos = optimal_time_chart[times][pos].pre_position;
                times--;
            }
            final_path.push(tourism[start_pos].Name);
            return final_path;
        }
    }
    return final_path;
}

stack<string> Graph_SP::optimal_path_flow(string place_name) {
    stack<string> final_path;
    for (int i = 0; i < this->N; i++) {
        if (place_name == tourism[i].Name && tourism[i].State == 1) {
            int pos = i;
            int times = N;
            while (times > 1) {
                if (optimal_flow_chart[times][pos].pre_position == optimal_flow_chart[times - 1][pos].pre_position) {
                    times--;
                } else {
                    break;
                }
            }

            while (times > 0) {
                final_path.push(tourism[pos].Name);
                pos = optimal_flow_chart[times][pos].pre_position;
                times--;
            }
            final_path.push(tourism[start_pos].Name);
            return final_path;
        }
    }
    return final_path;
}

// -----------------------------------------------
// Graph_SP::limited_path
// -----------------------------------------------
// Description:
//     Return limited path
// -----------------------------------------------
stack<string> Graph_SP::limited_path_time(string place_name, int limit) {
    stack<string> final_path;
    for (int i = 0; i < this->N; i++) {
        if (place_name == tourism[i].Name && tourism[i].State == 1) {
            int pos = i;
            int times = limit - 1;
            while (times > 1) {
                if (optimal_time_chart[times][pos].pre_position == optimal_time_chart[times - 1][pos].pre_position) {
                    times--;
                } else {
                    break;
                }
            }
            while (times > 0) {
                final_path.push(tourism[pos].Name);
                pos = optimal_time_chart[times][pos].pre_position;
                times--;
            }
            final_path.push(tourism[start_pos].Name);
            return final_path;
        }
    }
    return final_path;
}
stack<string> Graph_SP::limited_path_flow(string place_name, int limit) {
    stack<string> final_path;
    for (int i = 0; i < this->N; i++) {
        if (place_name == tourism[i].Name && tourism[i].State == 1) {
            int pos = i;
            int times = limit - 1;
            while (times > 1) {
                if (optimal_flow_chart[times][pos].pre_position == optimal_flow_chart[times - 1][pos].pre_position) {
                    times--;
                } else {
                    break;
                }
            }

            while (times > 0) {
                final_path.push(tourism[pos].Name);
                pos = optimal_flow_chart[times][pos].pre_position;
                times--;
            }
            final_path.push(tourism[start_pos].Name);
            return final_path;
        }
    }
    return final_path;
}