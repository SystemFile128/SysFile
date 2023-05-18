#include <bits/stdc++.h>
#define CH1_TS 5
#define CH2_TS 5
#define CH3_TS 2

using namespace std;

struct state
{
    char IC[4], R[4], IR[4], error[100];
    bool T;
    int SI, TI, PI;
};
int Global_Timer = 0;
int IOI = 1;
class PCB
{

public:
    int Job_id;
    int TTL, TTC, LLC, TLL, Ptr;
    int datacount, program_count;
    vector<int> CodePtr, DataPtr, OutputPtr;
    state curr_state;
    char flag;
    PCB()
    {
    }
    PCB(string card)
    {
        cout << "in PCB\n"
             << card << "\n";
        Job_id = atoi(card.substr(4, 4).c_str());
        TTL = atoi(card.substr(8, 4).c_str());
        TLL = atoi(card.substr(12, 4).c_str());
        TTC = 0;
        LLC = 0;
        datacount = 0;
        program_count = 0;
        // TLL = 0;
        CodePtr.clear();
        DataPtr.clear();
        cout << "-------------------------------------------\n";
        cout << "                    PCB\n";
        // cout << "\n-----------------------------------------" << endl;
        // cout << "\n_______________" << endl;
        cout << "\t---------------------\n";
        cout << "\t| job_id\t|  " << Job_id << "\t|" << endl;
        cout << "\t---------------------\n";
        cout << "\t| llc\t\t|  " << LLC << "\t|" << endl;
        cout << "\t---------------------\n";
        cout << "\t| ttc\t\t|  " << TTC << "\t|" << endl;
        cout << "\t---------------------\n";
        cout << "\t| ttl\t\t|  " << TTL << "\t|" << endl;
        cout << "\t---------------------\n";
        cout << "\t| tll\t\t|  " << TLL << "\t|" << endl;
        cout << "\t---------------------\n";
        cout << "\t| Data_count\t|  " << datacount << "\t|" << endl;
        cout << "\t---------------------\n";
        cout << "\t| Program_count\t|  " << program_count << "\t|" << endl;
        cout << "\t---------------------\n";
        cout << "-------------------------------------------\n";
    }
};

PCB temp, *ptr;
class SuperVisiorMem
{

public:
    queue<int> EmptyBuffers;
    queue<int> InputFullBuffers;
    queue<int> OutputFullBuffers;
    char buffer[10][40];

    SuperVisiorMem()
    {
        buffer[0][0] = 0;
        for (int i = 0; i < 10; i++)
            EmptyBuffers.push(i);
    }

    int allotEmptyBuffer()
    {
        int t;
        if (!EmptyBuffers.empty())
        {
            t = EmptyBuffers.front();
            EmptyBuffers.pop();
            return t;
        }
        else
            return -1;
    }

    void addInputBuffer(int buff_no)
    {
        InputFullBuffers.push(buff_no);
    }

    void addOutputBuffer(int buff_no)
    {
        OutputFullBuffers.push(buff_no);
    }
    void addEmptyBuffer(int buff_no)
    {
        EmptyBuffers.push(buff_no);
    }

    int returnIFB()
    {
        if (!InputFullBuffers.empty())
        {
            int t;
            t = InputFullBuffers.front();
            InputFullBuffers.pop();
            return t;
        }
        return -1;
    }
};

class DrumMem
{

public:
    char drum[1000][41];
    queue<int> EmptyTracks;
    DrumMem()
    {
        drum[0][0] = 0;
        for (int i = 0; i < 100; i++)
            EmptyTracks.push(i);
    }

    int allocateTrack()
    {
        int t;
        t = EmptyTracks.front();
        EmptyTracks.pop();
        return t;
    }

    void FreeTrack(int tno)
    {
        EmptyTracks.push(tno);
    }
};

struct CPU
{
    char IR[4];
    char R[4];
    bool T;
    int SI, PI, TI;
    char IC[2];
    char Mem[300][4];
    SuperVisiorMem sm;
    DrumMem dm;
    char error[100];
    ifstream inputCard;
    deque<PCB *> loadQ, readyQ, IOQ, terminateQ;
    vector<int> v;
    string TASK;
} c;

int no_of_pages = 0;

void clearbuffer(char buffer[][40], int n);

void loadInMain(PCB *pcb)
{
    cout << "\n---------------------------------\n";
    cout << "------------Load in Main----------\n";
    no_of_pages = 0;
    int n;
    bool code;
    char temp[40], ch;
    int b = 0;
    int k = -1, i = 0, j, currP = 0, x = 0, l, uptr, m, currentPage;
    bool new_block = true, flag = false;
    cout << "Creating a new Block" << endl;
    pcb->Ptr = -1;
    code = !pcb->CodePtr.empty();
    while (!pcb->CodePtr.empty())
    {
        cout << "while (!pcb->CodePtr.empty())" << endl;
        for (int q = 0; q < 40; ++q)
            temp[q] = '\0';

        if (!pcb->CodePtr.empty())
        {
            cout << "CodePtr is not empty" << endl;
            cout << "Adding process to drum" << endl;
            strcpy(temp, c.dm.drum[pcb->CodePtr[0]]);
            pcb->CodePtr.erase(pcb->CodePtr.begin());
        }

        if (pcb->Ptr == -1)
        {
            cout << "If memory no allocated" << endl;
            cout << "Allocating memory" << endl;
            pcb->Ptr = rand() % 30;
            if (pcb->Ptr == -1)
            {
                exit(0);
            }
            uptr = pcb->Ptr * 10;
            for (int n = 0; n < 10; n++)
                for (int o = 0; o < 4; o++)
                    c.Mem[uptr + n][o] = '#';
        }
        b = -1;
        k = -1;
        i = 0;
        while (b != 40)
        {

            b++;
            ch = temp[b];

            if (isprint(ch))
            {
                if (i % 4 == 0)
                {
                    k++;
                    if (k % 10 == 0)
                        flag = true;
                }
                if (flag)
                {
                    flag = false;
                    k = 0;
                    while (1)
                    {
                        currentPage = rand() % 30;
                        for (j = 0; j < c.v.size(); j++)
                        {
                            if (c.v[j] == currentPage)
                                break;
                        }
                        if (j >= c.v.size())
                            break;
                    }
                    no_of_pages++;
                    c.v.push_back(currentPage);
                }

                c.Mem[pcb->Ptr * 10 + no_of_pages - 1][0] = '0' + currentPage / 10;
                c.Mem[pcb->Ptr * 10 + no_of_pages - 1][1] = '0' + currentPage % 10;

                c.Mem[currentPage * 10 + k][i % 4] = ch;
                i++;
            }
            else
                break;
        }
    }
    cout << "\n---------------------------------\n";
}
