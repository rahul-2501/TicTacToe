#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define EMPTY_SPACE '_'
#define AI 'X'
#define PLAYER 'O'
#define WIN 1000
#define DRAW 0
#define LOSS -1000
#define START_DEPTH 0

vector<vector<pair<int,int> > > state;

vector<pair<int,int> > getlegal_positions(char board[3][3])
{
vector<pair<int,int> > legal_moves;
for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
    {
        if(board[i][j]!=AI && board[i][j]!=PLAYER)
        {
            legal_moves.push_back(make_pair(i,j));
        }
    }
}

return legal_moves;
}



void print_game_state(int state)
{
    if(WIN == state)
    {
        cout<<"WIN"<<endl;
    }
    if(LOSS == state)
    {
        cout<<"LOSS"<<endl;
    }
    if(DRAW == state)
    {
        cout<<"DRAW"<<endl;
    }
}


bool board_full(char board[3][3])
{

vector <pair<int,int> > legal_moves=getlegal_positions(board);

if(legal_moves.size()==0)
{
    return true;
}
else
{
    return false;
}

}
char get_opponent_marker(char marker)
{
    if(marker==AI)
    {
        return PLAYER;
    }
    else
    {
        return AI;
    }
    
}
vector<pair<int,int> > get_occupied_positions(char board[3][3],char marker)
{
    vector<pair<int,int> > occupied_positions;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==marker)
            {
                occupied_positions.push_back(make_pair(i,j));
            }
        }
    }

    return occupied_positions;

}

bool is_occupied(char board[3][3],pair<int,int> pos)
{
     vector<pair<int,int> > legal_moves=getlegal_positions(board);

     for(int i=0;i<legal_moves.size();i++)
     {
         if(pos.first==legal_moves[i].first && pos.second==legal_moves[i].second)
         {
             return false;
         }
     }

     return true;
}

bool game_is_won(vector<pair<int,int> > positions_occupied)
{
    bool game_won;

    for(int i=0;i<state.size();i++)
    {
        game_won=true;

        vector<pair<int,int> > current_state=state[i];
        int cnt=0;
        for(int j=0;j<current_state.size();j++)
        {
               if( !(find(begin(positions_occupied),end(positions_occupied),current_state[j])!=end(positions_occupied)))
               {
                   game_won=false;
                   break;
               }
        }
        if(game_won)
    {
        break;
    }

    }

    return game_won;

    
}
int game_state(char board[3][3],char marker)
{
    char opponent_marker=get_opponent_marker(marker);

    vector<pair<int,int> > positions_occupied = get_occupied_positions(board,marker);

    bool is_won= game_is_won(positions_occupied);

    if(is_won)
    {
        return WIN;
    }

    positions_occupied=get_occupied_positions(board,opponent_marker);

    bool is_lost=game_is_won(positions_occupied);

    if(is_lost)
    {
        return LOSS;
    }

    bool is_full=board_full(board);

    if(is_full)
    {
        return DRAW;
    }

    return DRAW;


}


bool game_over(char board[3][3])
{
    if(board_full(board))
    {
        return true;
    }

    if(DRAW!=game_state(board,AI))
    {
       return true;
    }
    return false;


}

void printboard(char board[3][3])
{
    cout<<board[0][0]<<"   "<<board[0][1]<<"   "<<board[0][2]<<"\n";
    cout<<board[1][0]<<"   "<<board[1][1]<<"   "<<board[1][2]<<"\n";
    cout<<board[2][0]<<"   "<<board[2][1]<<"   "<<board[2][2]<<"\n";
    cout<<"\n";

}

pair< int,pair<int,int> > minimax_optimization(char board[3][3],char marker,int depth,int alpha,int beta)
{

    pair<int,int> bestmove=make_pair(-1,-1);

    int bestscore=(marker==AI)?LOSS:WIN;

    if(board_full(board) || DRAW!= game_state(board,AI))
    {
        bestscore=game_state(board,AI);
        return make_pair(bestscore,bestmove);

    }

    vector<pair<int,int> > legal_moves=getlegal_positions(board);

    for(int i=0;i<legal_moves.size();i++)
    {
        pair<int,int> curr_move=legal_moves[i];

        board[curr_move.first][curr_move.second]=marker;


        if(marker==AI)
        {
            int score=minimax_optimization(board,PLAYER,depth+1,alpha,beta).first;

            if(bestscore < score)
            {
                bestscore=score-depth*10;

                bestmove=curr_move;


                alpha=max(alpha,bestscore);
                board[curr_move.first][curr_move.second]=EMPTY_SPACE;
                if(beta<=alpha)
                {
                    break;
                }
            }
        }

        else
        {
            int score=minimax_optimization(board,AI,depth+1,alpha,beta).first;
            if(bestscore>score)
            {
                bestscore=score+depth*10;
                bestmove=curr_move;


                beta=min(beta,bestscore);
                board[curr_move.first][curr_move.second]=EMPTY_SPACE;
                if(beta<=alpha)
                {
                    break;
                }
            }

        }

        board[curr_move.first][curr_move.second]=EMPTY_SPACE;
 
    }

    return make_pair(bestscore,bestmove);

}

int main()
{
    char board[3][3]={ {'_','_','_'},{'_','_','_'},{'_','_','_'} };
    
    vector <pair<int,int> > v1;

    v1.push_back(make_pair(0,0));
    v1.push_back(make_pair(0,1));
    v1.push_back(make_pair(0,2));
    
    vector<pair<int,int> > v2;
    v2.push_back(make_pair(1,0));
    v2.push_back(make_pair(1,1));
    v2.push_back(make_pair(1,2));

    vector<pair<int,int> > v3;
    v3.push_back(make_pair(2,0));
    v3.push_back(make_pair(2,1));
    v3.push_back(make_pair(2,2));

    vector<pair<int,int> > h1;
    h1.push_back(make_pair(0,0));
    h1.push_back(make_pair(1,0));
    h1.push_back(make_pair(2,0));

    vector<pair<int,int> > h2;
    h2.push_back(make_pair(0,1));
    h2.push_back(make_pair(1,1));
    h2.push_back(make_pair(2,1));

    vector<pair<int,int> > h3;
    h3.push_back(make_pair(0,2));
    h3.push_back(make_pair(1,2));
    h3.push_back(make_pair(2,2));

    vector<pair<int,int> > d1;
    d1.push_back(make_pair(0,0));
    d1.push_back(make_pair(1,1));
    d1.push_back(make_pair(2,2));

    vector<pair<int,int> > d2;
    d2.push_back(make_pair(2,0));
    d2.push_back(make_pair(1,1));
    d2.push_back(make_pair(0,2));


    state.push_back(v1);
    state.push_back(v2);
    state.push_back(v3);
    state.push_back(h1);
    state.push_back(h2);
    state.push_back(h3);
    state.push_back(d1);
    state.push_back(d2);
    cout<<"##########################  TIC TAC TOE ###############################"<<"\n";
    cout<<"PLAYER = O  AI = X"<<endl;
    printboard(board);

 while(!game_over(board))
 {
         int row,col;
         cout<<"row play : ";
         cin>>row;
         cout<<"col play : ";
         cin>>col;
         cout<<endl<<endl;

        if(is_occupied(board,make_pair(row,col)))
        {
            cout<<"the position ("<<row<<","<<col<<"is occupied.try another one...";
            continue;
        }
        else
        {
            board[row][col]=PLAYER;
        }

        pair<int,pair<int,int> > ai =minimax_optimization(board,AI,START_DEPTH,LOSS,WIN);

        board[ai.second.first][ai.second.second]=AI;

        printboard(board);
        
 }

cout<<"#################### GAME OVER ###########################";
cout<<"\n";
int player_state=game_state(board,PLAYER);
cout<<" PLAYER "; 
print_game_state(player_state);

return 0;

}